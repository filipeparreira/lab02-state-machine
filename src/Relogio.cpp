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
  tempo_anterior = {tempo.horas, tempo.minutos, tempo.segundos};
  
  tempo.segundos++;
  if (tempo.segundos >= 60){
    tempo.segundos = 0;
    tempo.minutos++;
    
    if (tempo.minutos >= 60){
      tempo.minutos = 0;
      tempo.horas++;

      if (tempo.horas >= 24){
        tempo.horas = 0;
      }
    }
  }
}

int Relogio::getSegundos()
{
  return tempo.segundos;
}

int Relogio::getMinutos()
{
  return tempo.minutos;
}

int Relogio::getHoras()
{
  return tempo.horas;
}

void Relogio::setSegundos(int segundos){
  tempo_anterior.segundos = segundos;
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

/*
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
}*/

bool Relogio::segMudou(){
  return tempo_anterior.segundos != tempo.segundos;
}

bool Relogio::minMudou(){
  return tempo_anterior.minutos != tempo.minutos;
}

bool Relogio::horaMudou(){
  return tempo_anterior.horas != tempo.horas;
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