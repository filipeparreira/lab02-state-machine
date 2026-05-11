#include "MenuLCD.h"

const int MenuLCD::velocidadeScroll = 400;

MenuLCD::MenuLCD(LiquidCrystal *lcdRef, int *x, int *y)
{
  lcd = lcdRef;
  cursorX = x;
  cursorY = y;
  tempoAnteriorLCD = 0;
  indiceScroll = 0;
  ultimaVariavel = "";
}

void MenuLCD::atualizarHoraLCD(Relogio *r, int linha)
{
  if (r->getHoras() == 0 || r->segMudou())
  {
    lcd->setCursor(8, linha);
    if (r->getHoras() < 10)
    {
      lcd->print("0");
      lcd->setCursor(9, linha);
    }
    lcd->print(r->getHoras());
    lcd->setCursor(10, linha);
    lcd->print(":");
  }

  if (r->getMinutos() == 0 || r->minMudou())
  {
    lcd->setCursor(11, linha);
    if (r->getMinutos() < 10)
    {
      lcd->print("0");
      lcd->setCursor(12, linha);
    }
    lcd->print(r->getMinutos());
    lcd->setCursor(13, linha);
    lcd->print(":");
  }

  if (r->getSegundos() == 0 || r->horaMudou())
  {

    lcd->setCursor(14, linha);
    if (r->getSegundos() < 10)
    {
      lcd->print("0");
      lcd->setCursor(15, linha);
    }
    lcd->print(r->getSegundos());
  }

  lcd->setCursor(*cursorX, *cursorY);
}

void MenuLCD::exibirMenuScroll(String variavel, String menuSelecionado)
{
  int tamanhoTexto = variavel.length();

  // Se o usuário mudou de opção no joystick, reseta o letreiro para o início
  if (variavel != ultimaVariavel)
  {
    indiceScroll = 0;
    ultimaVariavel = variavel;
    lcd->clear(); // Limpa a tela uma vez para evitar lixo de memória
  }

  unsigned long tempoAtual = millis();

  // Atualiza a tela apenas no intervalo definido para não causar "flicker" (piscar)
  if (tempoAtual - tempoAnteriorLCD >= velocidadeScroll)
  {
    tempoAnteriorLCD = tempoAtual;

    // --- LINHA DE BAIXO (Menu Atual) ---
    lcd->setCursor(0, 1);
    int tamanhoMenu = menuSelecionado.length();
    String linhaBaixo = "";

    if (tamanhoMenu <= 16)
    {
      // Calcula os espaços para centralizar nos 16 blocos do LCD
      int espacosTotaisMenu = 16 - tamanhoMenu;
      int espacosEsqMenu = espacosTotaisMenu / 2;
      int espacosDirMenu = espacosTotaisMenu - espacosEsqMenu;

      // Monta a string com espaços na esquerda, o texto, e espaços na direita
      for (int i = 0; i < espacosEsqMenu; i++)
      {
        linhaBaixo += " ";
      }
      linhaBaixo += menuSelecionado;
      for (int i = 0; i < espacosDirMenu; i++)
      {
        linhaBaixo += " ";
      }
    }
    else
    {
      // Se, por acaso, o nome do menu for maior que 16, corta para não bugar a tela
      linhaBaixo = menuSelecionado.substring(0, 16);
    }

    lcd->print(linhaBaixo);
    // Preenche com espaços vazios para apagar caracteres antigos sem usar lcd.clear()
    while (linhaBaixo.length() < 16)
      linhaBaixo += " ";
    lcd->print(linhaBaixo);

    // --- LINHA DE CIMA (Variável com Scroll) ---
    lcd->setCursor(0, 0);
    lcd->print("<"); // Fixo na coluna 0

    if (tamanhoTexto <= 14)
    {
      // 1. Calcula quantos espaços em branco vão sobrar nos 14 espaços disponíveis
      int espacosTotais = 14 - tamanhoTexto;

      // 2. Divide os espaços (se for ímpar, a direita fica com 1 espaço a mais)
      int espacosEsquerda = espacosTotais / 2;
      int espacosDireita = espacosTotais - espacosEsquerda;

      // 3. Imprime o preenchimento da esquerda
      for (int i = 0; i < espacosEsquerda; i++)
      {
        lcd->print(" ");
      }

      // 4. Imprime o texto no meio
      lcd->print(variavel);

      // 5. Imprime o preenchimento da direita
      for (int i = 0; i < espacosDireita; i++)
      {
        lcd->print(" ");
      }
    }
    else
    {
      // Texto maior que 14, precisa rolar (scroll)
      String janela = "";

      // Adiciona 3 espaços virtuais no final do texto para dar um respiro
      // antes de recomeçar a mostrar o início da frase
      int tamanhoVirtual = tamanhoTexto + 3;

      // Monta a janela de 14 caracteres capturando partes da string
      for (int i = 0; i < 14; i++)
      {
        int posChar = (indiceScroll + i) % tamanhoVirtual;
        if (posChar < tamanhoTexto)
        {
          janela += variavel[posChar];
        }
        else
        {
          janela += " "; // Imprime os espaços de separação
        }
      }

      lcd->print(janela); // Imprime os 14 caracteres do meio

      // Avança o letreiro para a próxima execução
      indiceScroll++;
      if (indiceScroll >= tamanhoVirtual)
      {
        indiceScroll = 0;
      }
    }

    lcd->print(">"); // Fixo na coluna 15
  }
}
