#include "Relogio.h"

Relogio::Relogio(int h, int m, int s)
{
  tempo = {h, m, s};
  mudouSeg = false;
  mudouMin = false;
  mudouHora = false;
}

void Relogio::tick()
{
  tempo.segundos++;
  mudouSeg = true;

  if (tempo.segundos >= 60)
  {
    tempo.segundos = 0;
    tempo.minutos++;
    mudouMin = true;

    if (tempo.minutos >= 60)
    {
      tempo.minutos = 0;
      tempo.horas++;
      mudouHora = true;

      if (tempo.horas >= 24)
      {
        tempo.horas = 0;
      }
    } else {
      mundouHora = false;
    }
  } else {
    mundouMin = false;
  }
}

int Relogio::getSegundos()
{
  //mudouSeg = false;
  return tempo.segundos;
}

int Relogio::getMinutos()
{
  //mudouMin = false;
  return tempo.minutos;
}

int Relogio::getHoras()
{
  //mudouHora = false;
  return tempo.horas;
}

void Relogio::setSegundos(int segundos){
  tempo.segundos = segundos;
}

void Relogio::setMinutos(int minutos){
  mudouMin = true;
  tempo.minutos = minutos;
}

void Relogio::setHoras(int horas){
  mudouHora = true;
  tempo.horas = horas;
}

// Flags de mudança
bool Relogio::segMudou()
{
  return mudouSeg;
}

bool Relogio::minMudou()
{
  return mudouMin;
}

bool Relogio::horaMudou()
{
  return mudouHora;
}

String Relogio::getSegundosString(){
  if (getSegundos() <= 9){
    return "0" + String(getSegundos());
  } else {
    return String(getSegundos());
  }
}

String Relogio::getMinutosString(){
  if (getMinutos() <= 9){
    return "0" + String(getMinutos());
  } else {
    return String(getMinutos());
  }
}

String Relogio::getHorasString(){
  if (getHoras() <= 9){
    return "0" + String(getHoras());
  } else {
    return String(getHoras());
  }
}