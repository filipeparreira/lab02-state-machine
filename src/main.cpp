/*
- Utilizar o máximo de máquinas de estados possível
OBJETIVOS PRINCIPAIS:
- Permitir ajustes de horário atual
- Permitir ajustes de horário do alarme (minutos e segundos)
- Apresentar no display o horário atual e o horário do alarme
- Acionar o buzzer quando o horário do alarme chegar
*/

// CONFIGURAÇÕES
#define INTERVALO_CLK 1000
#define BUTTON 2 // Deve ser um pino com interrupção externa
// Arduino MEGA 2560 - 2, 3, 18, 19, 20, 21

// -- Definindo os timers
#define USE_TIMER_1 true
#if (defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__) ||                   \
defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_MINI) || defined(ARDUINO_AVR_ETHERNET) ||                        \
defined(ARDUINO_AVR_FIO) || defined(ARDUINO_AVR_BT) || defined(ARDUINO_AVR_LILYPAD) || defined(ARDUINO_AVR_PRO) ||                            \
defined(ARDUINO_AVR_NG) || defined(ARDUINO_AVR_UNO_WIFI_DEV_ED) || defined(ARDUINO_AVR_DUEMILANOVE) || defined(ARDUINO_AVR_FEATHER328P) ||    \
defined(ARDUINO_AVR_METRO) || defined(ARDUINO_AVR_PROTRINKET5) || defined(ARDUINO_AVR_PROTRINKET3) || defined(ARDUINO_AVR_PROTRINKET5FTDI) || \
defined(ARDUINO_AVR_PROTRINKET3FTDI))
#define USE_TIMER_2 true
#warning Using Timer1, Timer2
#else
#define USE_TIMER_3 true
#warning Using Timer1, Timer3
#endif

// Bibliotecas
#include "TimerInterrupt.h"
#include "Arduino.h"
#include "LiquidCrystal.h"
#include "Relogio.h"
#include "MenuLCD.h"
#include "Musicas.h"

// Intervalos para os timers (tempo)
#define TIMER_TX_INTERVALO_MS INTERVALO_CLK
#define TIMER_TX_FREQUENCIA (float)(1000.0f / TIMER_TX_INTERVALO_MS)

#define TIMER_RX_INTERVALO_MS 100
#define TIMER_RX_FREQUENCIA (float)(1000.0f / TIMER_RX_INTERVALO_MS)

const unsigned long tempoDebounce = 250;
int posX, posY;
int cursorX;
int cursorY;
volatile bool botaoApertado;
volatile bool joystick, joystickEsqDir = false, joystickUpDown = false;
volatile bool estadoInicio;
volatile unsigned long ultimoTempoBotao;
volatile bool atualizandoHora = false;
volatile bool estadoAlarme = false;
unsigned long indiceEsqDir = 2400000L; // Variável de controle das opções
bool moveu = false;

// FLAGS SEGURAS PARA AS INTERRUPÇÕES
volatile bool flagAtualizarDisplay = false; 
volatile bool flagBotao = false; 

// Conteúdos das opções
String opcoesMenu[] = {"ATUALIZAR HORARIO", "ATUALIZAR ALARME", "SELECIONAR MUSICA", "VOLTAR"};
String opcoesMusica[] = {"Super Mario Bros", "Mii Channel", "Pacman", "Nokia Tune", "Tetris", "VOLTAR"};

// Variáveis de controle
int tamVetor = sizeof(opcoesMenu) / sizeof(opcoesMenu[0]);
int tamVetorMusicas = sizeof(opcoesMusica) / sizeof(opcoesMusica[0]);
int opcaoSelecionada = (indiceEsqDir % tamVetor);
int musicaSelecionada = 1;

// Caractere especial criado para ícone de menu
byte sliders[8] = { B00000, B10111, B00000, B10111, B00000, B10111, B00000, B00000 };

// Variável global 
Relogio *rel;

// Estados da Máquinas de Estados
enum Movimento {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

enum Estados {
  MOSTRAR_HORARIO,
  VISUALIZAR_MENU,
  ATUALIZAR_HORARIO,
  ATUALIZAR_ALARME,
  MODIFICAR_SEGUNDOS,
  MODIFICAR_MINUTOS,
  MODIFICAR_HORAS,
  SELECIONAR_MUSICA,
  DISPARAR_ALARME,
  LIGAR_ALARME
};

Musicas reprodutor(A2);
Relogio alarme;
Relogio horario;
LiquidCrystal lcd(23, 22, 24, 25, 26, 27);
MenuLCD menu(&lcd, &cursorX, &cursorY);

// Função de ínicio do relógio
void inicio() {
  lcd.clear();
  lcd.home();
  lcd.setCursor(0, 0);
  lcd.write("Relogio|");
  menu.atualizarHoraLCD(&horario, 0);
  lcd.setCursor(0, 1);
  lcd.write(byte(1));
  lcd.setCursor(1, 1);
  lcd.write("Alarme|");
  menu.atualizarHoraLCD(&alarme, 1);
}

// Classe responsável por guardar e manipular os estados do objeto principal (despertador)
class MaquinaDeEstados {
private:
  Estados estadoAtual;
  Estados estadoAnterior;

  LiquidCrystal *lcd;
  MenuLCD *menu;
  Relogio *relogio;

  int *cursorX;
  int *cursorY;

public:
  MaquinaDeEstados(LiquidCrystal *lcdRef, int *x, int *y, MenuLCD *menuLCD);
  Estados getEstadoAtual();
  void proxEstado(bool botaoApertado, int opcaoSelecionada);
  void setEstadoAtual(Estados estado);
  void executar();
};

MaquinaDeEstados::MaquinaDeEstados(LiquidCrystal *lcdRef, int *x, int *y, MenuLCD *menuLCD) {
  lcd = lcdRef;
  cursorX = x;
  cursorY = y;
  menu = menuLCD;
  estadoAtual = MOSTRAR_HORARIO;
  estadoAnterior = MOSTRAR_HORARIO;
}

Estados MaquinaDeEstados::getEstadoAtual() {
  return estadoAtual;
}

void MaquinaDeEstados::setEstadoAtual(Estados novoEstado) {
  estadoAnterior = estadoAtual;
  estadoAtual = novoEstado;
}

void MaquinaDeEstados::executar() {
  switch (estadoAtual) {
    case MOSTRAR_HORARIO:
      joystick = false;
      if (estadoInicio) {
        lcd->clear();
        lcd->blink();
        lcd->home();
        
        lcd->setCursor(0, 0);
        lcd->write("Relogio|");
        menu->atualizarHoraLCD(&horario, 0);
        
        lcd->setCursor(0, 1);
        lcd->write(byte(1));
        lcd->setCursor(1, 1);
        lcd->write("Alarme|");
        menu->atualizarHoraLCD(&alarme, 1);
        
        estadoInicio = false;
      } else if (flagAtualizarDisplay) { 
        menu->atualizarHoraLCD(&horario, 0);
        if(estadoAlarme){
        menu->atualizarHoraLCD(&alarme, 1);
      } else{
        lcd->setCursor(8, 1);
        lcd->print("--:--:--");
      }
        flagAtualizarDisplay = false;
      } else {
        if (horario.getHoras() == alarme.getHoras() &&
            horario.getMinutos() == alarme.getMinutos() &&
            horario.getSegundos() == alarme.getSegundos()) {
          Serial.print("Musica selecionada:");
          Serial.println(musicaSelecionada);
          reprodutor.iniciarMusica(musicaSelecionada);
          setEstadoAtual(DISPARAR_ALARME);
        }
      }

      break;
      
    case VISUALIZAR_MENU:
      opcaoSelecionada = indiceEsqDir % tamVetor;
      joystick = true;
      lcd->noBlink();
      menu->exibirMenuScroll(opcoesMenu[opcaoSelecionada], "MENU");
      flagAtualizarDisplay = false; 
      break;
      
    case SELECIONAR_MUSICA:
      opcaoSelecionada = indiceEsqDir % tamVetorMusicas;
      reprodutor.atualizar();
      joystick = true;
      lcd->noBlink();
      menu->exibirMenuScroll(opcoesMusica[opcaoSelecionada], "MUSICA");
      flagAtualizarDisplay = false;
      break;

    case ATUALIZAR_HORARIO:
      rel = &horario;
      joystick = true;
      lcd->clear();
      lcd->setCursor(0, 1);
      lcd->print("ATUALIZ. HORARIO");
      lcd->setCursor(4, 0);
      lcd->print(horario.getHorasString());
      lcd->setCursor(6, 0);
      lcd->print(":");
      lcd->print(horario.getMinutosString());
      lcd->setCursor(9, 0);
      lcd->print(":");
      lcd->print(horario.getSegundosString());
      lcd->blink();
      lcd->setCursor(11, 0);
      setEstadoAtual(MODIFICAR_SEGUNDOS);
      flagAtualizarDisplay = false;
      break;
    
    case ATUALIZAR_ALARME:
      rel = &alarme;
      joystick = true;
      lcd->clear();
      lcd->setCursor(0, 1);
      if(estadoAlarme){
        lcd->print("  [X]ON [ ]OFF");
      } else{
        lcd->print("  [ ]ON [X]OFF");
      }
      // 
      lcd->setCursor(4, 0);
      lcd->print(alarme.getHorasString());
      lcd->setCursor(6, 0);
      lcd->print(":");
      lcd->print(alarme.getMinutosString());
      lcd->setCursor(9, 0);
      lcd->print(":");
      lcd->print(alarme.getSegundosString());
      lcd->blink();
      lcd->setCursor(11, 0);
      setEstadoAtual(MODIFICAR_SEGUNDOS);
      flagAtualizarDisplay = false;
      break;
    
    case MODIFICAR_SEGUNDOS:
    case MODIFICAR_MINUTOS:
    case MODIFICAR_HORAS:
      // Removemos o "if(moveu)" daqui. A lógica foi integralmente transferida para a função moverCursor(), evitando bugs e repetições rápidas de tela.
      flagAtualizarDisplay = false;
      break;
    
    case DISPARAR_ALARME:
      reprodutor.atualizar();
      if (flagAtualizarDisplay) { 
        menu->atualizarHoraLCD(&horario, 0);
        menu->atualizarHoraLCD(&alarme, 1);
        flagAtualizarDisplay = false;
      }
      break;
    case LIGAR_ALARME:
    break;
    default:
      break;
  }
} 

void MaquinaDeEstados::proxEstado(bool botaoApertado, int opcaoSelecionada) {
  opcaoSelecionada = abs(opcaoSelecionada);
  switch (estadoAtual) {
    case MOSTRAR_HORARIO:
      if (botaoApertado) {
        joystickEsqDir = true;
        joystickUpDown = false;
        setEstadoAtual(VISUALIZAR_MENU);
      }
      break;

    case VISUALIZAR_MENU:
      lcd->noBlink();
      if (opcaoSelecionada == 0) {
        joystickEsqDir = false;
        joystickUpDown = true;
        setEstadoAtual(ATUALIZAR_HORARIO);
        atualizandoHora = true;
      }
      else if (opcaoSelecionada == 1) {
        joystickEsqDir = false;
        joystickUpDown = true;
        lcd->clear();
        lcd->setCursor(0, 1);
        if(estadoAlarme){
          lcd->print("  [X]ON [ ]OFF");
        } else{
          lcd->print("  [ ]ON [X]OFF");
        }
        lcd->setCursor(4, 0);
        lcd->print(alarme.getHorasString());
        lcd->setCursor(6, 0);
        lcd->print(":");
        lcd->print(alarme.getMinutosString());
        lcd->setCursor(9, 0);
        lcd->print(":");
        lcd->print(alarme.getSegundosString());
        lcd->blink();
        if(estadoAlarme){
          lcd->setCursor(3,1);
        }else{
          lcd->setCursor(9,1);
        }
        
        setEstadoAtual(LIGAR_ALARME);
      }
      else if (opcaoSelecionada == 2 && botaoApertado) {
        reprodutor.iniciarMusica(1);
        setEstadoAtual(SELECIONAR_MUSICA);
      }
      else if (opcaoSelecionada == 3) {
        setEstadoAtual(MOSTRAR_HORARIO);
      }
      break;
      
    case MODIFICAR_SEGUNDOS:
    case MODIFICAR_MINUTOS:
    case MODIFICAR_HORAS:
      atualizandoHora = false;
      setEstadoAtual(MOSTRAR_HORARIO);
      break;

    case SELECIONAR_MUSICA:
      if (opcaoSelecionada == 5) {
        setEstadoAtual(estadoAnterior);
      } else {
        reprodutor.pararBuzzer();
        musicaSelecionada = opcaoSelecionada+1;
        Serial.print("Musica selecionada (SELECIONAR MUSICA):");
        Serial.println(musicaSelecionada);
        setEstadoAtual(MOSTRAR_HORARIO);
      }
      break;
    
    case DISPARAR_ALARME:
      reprodutor.pararBuzzer();
      setEstadoAtual(MOSTRAR_HORARIO);
      break;
    case LIGAR_ALARME:
      if(estadoAlarme){
        setEstadoAtual(ATUALIZAR_ALARME);
      }else{
        setEstadoAtual(VISUALIZAR_MENU);
      }
    break;
    default:
      break;
  }
}

// Objetos utilizados
MaquinaDeEstados despertador(&lcd, &cursorX, &cursorY, &menu);

// ---------------- MÉTODOS DE INTERRUPÇÕES ----------------
void atualizarDisplay() {
  return;
}

void botao() {
  unsigned long tempoAtual = millis();
  if ((tempoAtual - ultimoTempoBotao) > tempoDebounce) {
    flagBotao = true;
    ultimoTempoBotao = tempoAtual;
  }
}

void timerHandler() {
  if (!atualizandoHora) {
    horario.tick(); 
    flagAtualizarDisplay = true;
  }
}
// ----------------------------------------------------

void tocarMusica() {
  if (despertador.getEstadoAtual() == SELECIONAR_MUSICA) {
    int opcaoAtual = indiceEsqDir % tamVetorMusicas;
    if (opcaoAtual == 5) { 
      reprodutor.pararBuzzer();
    } else {
      reprodutor.iniciarMusica(opcaoAtual + 1);
    }
  }
}

void setup() {
  cursorX = 0;
  cursorY = 1;
  botaoApertado = false;
  joystick = false;
  estadoInicio = true;
  ultimoTempoBotao = 0;

  Serial.begin(9600);

  lcd.begin(16, 2); 
  lcd.createChar(1, sliders);
  despertador.setEstadoAtual(MOSTRAR_HORARIO);
  horario.setHoras(12);
  horario.setMinutos(12);
  horario.setSegundos(12);
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON), botao, RISING);
  lcd.setCursor(cursorX, cursorY);

#if USE_TIMER_1
  ITimer1.init();
  if (ITimer1.attachInterruptInterval(TIMER_TX_INTERVALO_MS, timerHandler)) {
    Serial.print(F("Timer1 inicializado corretamente.\n"));
  } else {
    Serial.println(F("Não foi possível inicializar o Timer1. Inicializar com outra frequência.\n"));
  }
#endif
#if USE_TIMER_2
  ITimer2.init();
  if (ITimer2.attachInterruptInterval(TIMER_RX_INTERVALO_MS, atualizarDisplay)) {
    Serial.print(F("Timer2 inicializado corretamente.\n"));
  } else {
    Serial.println(F("Não foi possível inicializar o Timer3. Inicializar com outra frequência.\n"));
  }
#elif USE_TIMER_3
  ITimer3.init();
  if (ITimer3.attachInterruptInterval(TIMER_RX_INTERVALO_MS, atualizarDisplay)) {
    Serial.print(F("Timer3 inicializado corretamente.\n"));
  } else {
    Serial.println(F("Não foi possível inicializar o Timer3. Inicializar com outra frequência.\n"));
  }
#endif
}

// ATUALIZADO: Toda a lógica de incremento de tempo e de pular as casas está devidamente isolada aqui
void moverCursor(Movimento movimento) {
  Estados estadoAtual = despertador.getEstadoAtual();
  
  switch (movimento) {
    case UP:
      if (joystickUpDown) {
        if (estadoAtual == MODIFICAR_SEGUNDOS) {
          rel->setSegundos(rel->getSegundos() < 59 ? rel->getSegundos() + 1 : 0);
          lcd.setCursor(10, 0); lcd.print(rel->getSegundosString()); lcd.setCursor(11, 0);
        } else if (estadoAtual == MODIFICAR_MINUTOS) {
          rel->setMinutos(rel->getMinutos() < 59 ? rel->getMinutos() + 1 : 0);
          lcd.setCursor(7, 0); lcd.print(rel->getMinutosString()); lcd.setCursor(8, 0);
        } else if (estadoAtual == MODIFICAR_HORAS) {
          rel->setHoras(rel->getHoras() < 23 ? rel->getHoras() + 1 : 0);
          lcd.setCursor(4, 0); lcd.print(rel->getHorasString()); lcd.setCursor(5, 0);
        }
      }
      break;

    case DOWN:
      if (joystickUpDown) {
        if (estadoAtual == MODIFICAR_SEGUNDOS) {
          rel->setSegundos(rel->getSegundos() > 0 ? rel->getSegundos() - 1 : 59);
          lcd.setCursor(10, 0); lcd.print(rel->getSegundosString()); lcd.setCursor(11, 0);
        } else if (estadoAtual == MODIFICAR_MINUTOS) {
          rel->setMinutos(rel->getMinutos() > 0 ? rel->getMinutos() - 1 : 59);
          lcd.setCursor(7, 0); lcd.print(rel->getMinutosString()); lcd.setCursor(8, 0);
        } else if (estadoAtual == MODIFICAR_HORAS) {
          rel->setHoras(rel->getHoras() > 0 ? rel->getHoras() - 1 : 23);
          lcd.setCursor(4, 0); lcd.print(rel->getHorasString()); lcd.setCursor(5, 0);
        }
      }
      break;

    case LEFT:
      if (joystickEsqDir) {
        indiceEsqDir--;
        tocarMusica();
      } else if (estadoAtual == MODIFICAR_SEGUNDOS) {
        despertador.setEstadoAtual(MODIFICAR_MINUTOS);
        lcd.setCursor(8, 0);
      } else if (estadoAtual == MODIFICAR_MINUTOS) {
        despertador.setEstadoAtual(MODIFICAR_HORAS);
        lcd.setCursor(5, 0);
      } else if (estadoAtual == MODIFICAR_HORAS) {
        despertador.setEstadoAtual(MODIFICAR_SEGUNDOS);
        lcd.setCursor(11, 0);
      } else if (estadoAtual == LIGAR_ALARME) {
        estadoAlarme = !estadoAlarme;
        if(estadoAlarme){
          lcd.setCursor(3 ,1);
        } else {
          lcd.setCursor(9, 1);
        }
      }
      break;
      
    case RIGHT:
      if (joystickEsqDir) {
        indiceEsqDir++;
        tocarMusica();
      } else if (estadoAtual == MODIFICAR_SEGUNDOS) {
        despertador.setEstadoAtual(MODIFICAR_HORAS);
        lcd.setCursor(5, 0);
      } else if (estadoAtual == MODIFICAR_MINUTOS) {
        despertador.setEstadoAtual(MODIFICAR_SEGUNDOS);
        lcd.setCursor(11, 0);
      } else if (estadoAtual == MODIFICAR_HORAS) {
        despertador.setEstadoAtual(MODIFICAR_MINUTOS);
        lcd.setCursor(8, 0);
      } else if (estadoAtual == LIGAR_ALARME) {
        estadoAlarme = !estadoAlarme;
        if(estadoAlarme){
          lcd.setCursor(3 ,1);
        } else {
          lcd.setCursor(9, 1);
        }
      }
      break;
  }
}

void loop() {
  if (flagBotao) {
    botaoApertado = true;
    indiceEsqDir = 2400000;
    despertador.proxEstado(botaoApertado, opcaoSelecionada);
    Serial.println(opcaoSelecionada);

    if (despertador.getEstadoAtual() == MOSTRAR_HORARIO)
      estadoInicio = true;
      
    flagBotao = false; 
  }

  posX = analogRead(A0);
  posY = analogRead(A1);

  bool noCentro = (posX >= 400 && posX <= 620 && posY >= 400 && posY <= 620);

  if (!noCentro && !moveu && joystick) {
    moveu = true;
    if (posX < 400) moverCursor(UP);
    else if (posX > 620) moverCursor(DOWN);
    else if (posY < 400) moverCursor(RIGHT);
    else if (posY > 620) moverCursor(LEFT);
  }
  else if (noCentro) {
    moveu = false;
  }
  
  despertador.executar();
  botaoApertado = false;
}