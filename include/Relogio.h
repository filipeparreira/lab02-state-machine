#ifndef RELOGIO_H
#define RELOGIO_H

#include <Arduino.h>

struct Tempo {
  int horas;
  int minutos;
  int segundos;
};

class Relogio {
private:
Tempo tempo;

public:
bool mudouSeg;
bool mudouMin;
bool mudouHora;
  Relogio(int h = 0, int m = 0, int s = 0);

  /**
    @brief Incrementa em 1 os segundos ligado ao atributo do objeto,
    manipulando indiretamente os minutos e horas.
  */
  void tick();

  /**
    @brief Getter - Retorna os segundos.
    
    @return Segundos no formato inteiro.
  */
  int getSegundos();
  
  /**
    @brief Getter - Retorna os minutos.
    
    @return Minutos no formato inteiro.
  */
  int getMinutos();
  
  /**
    @brief Getter - Retorna as horas.
    
    @return Horas no formato inteiro.
  */
  int getHoras();

  /**
    @brief Setter - Ajusta os segundos. 
    
    @param segundos Segundos a serem ajustados.
  */
  void setSegundos(int segundos);
  
  /**
    @brief Setter - Ajusta os minutos.
    
    @param minutos Minutos a serem ajustados.
  */
  void setMinutos(int minutos);
  
  /**
    @brief Setter - Ajusta as horas.  
    
    @param horas Horas a serem ajustados.
  */
  void setHoras(int horas);

  /**
    @brief Verifica se o segundo mudou. 
    
    @return Booleano indicando a mudança do segundo.   
  */
  bool segMudou();
  
  /**
    @brief Verifica se o minuto mudou. 
    
    @return Booleano indicando a mudança do minuto.   
  */
  bool minMudou();

  /**
    @brief Verifica se a hora mudou.
    
    @return Booleano indicando a mudança da hora.
  */
  bool horaMudou();

  /**
    @brief Variação do Getter - Retorna os segundos já formatados
    e no formato de String.

    @return String formatada dos segundos 
  */
  String getSegundosString();
  
  /**
    @brief Variação do Getter - Retorna os minutos já formatados
    e no formato de String.

    @return String formatada dos minutos 
  */
  String getMinutosString();

  /**
    @brief Variação do Getter - Retorna as horas já formatadas
    e no formato de String.

    @return String formatada das horas 
  */
  String getHorasString();
};

#endif