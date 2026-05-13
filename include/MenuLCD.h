#ifndef MENULCD_H
#define MENULCD_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "Relogio.h"

class MenuLCD
{
private:
    LiquidCrystal* lcd;
    int* cursorX;
    int* cursorY;
    static const int velocidadeScroll;
    unsigned long tempoAnteriorLCD;
    int indiceScroll;
    String ultimaVariavel;
public:
    MenuLCD(LiquidCrystal* lcdRef, int* x, int* y);

    /**
        @brief Utualiza as horas, minutos e segundos com base no objeto chamado,
        a linha também deve ser passada para que seja possível imprimir corretamente.
        Idealmente é impresso somente o atributo que mudou, buscando uma maior agilidade
        na impressão.

        @param r Objeto do tipo Relogio que será utilizado para verificar os atributos 
        de hora, minutos e segundos. 

        @param linha A linha do display LCD em que será impresso os dados de horário.
    */
    void atualizarHoraLCD(Relogio* r, int linha);

    /**
        @brief Imprime na linha superior e na linha inferior em formato de menu.
        Caso o número de carateres seja maior do que a quantidade de células no 
        display, é realizado um scroll na String para que seja possível visualizar
        toda ela.

        @param variavel Conteudo referente a opção a ser selecionada, será impresso 
        na primeira linha do display LCD.

        @param menuSelecionado Conteudo referente ao menu que esta atualmente, será
        impresso na segunda linha do display LCD.
    */
    void exibirMenuScroll(String variavel, String menuSelecionado);
    /**
        @brief Imprime o tempo atual somente uma vez.
        
        @param r Objeto do tipo Relogio passado para verificar os valores de tempo.
        
        @param linha Inteiro 0 ou 1 referente a linha a ser escrito os valores de 
        tempo no display. 0 é para o tempo do relógio e 1 é para o tempo do alarme.
    */
    void escreverTempo(Relogio* r, int linha);
};

#endif