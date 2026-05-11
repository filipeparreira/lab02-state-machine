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

  void tick();

  int getSegundos();
  int getMinutos();
  int getHoras();

  void setSegundos(int segundos);
  void setMinutos(int minutos);
  void setHoras(int horas);

  bool segMudou();
  bool minMudou();
  bool horaMudou();

  String getSegundosString();
  String getMinutosString();
  String getHorasString();
};

#endif