#ifndef TUTTE_H
#define TUTTE_H

#include "graf.h"

// Funkcja wyszukująca zewnętrzny cykl
void wyznacz_zewnetrzny_cykl(Graf *g);

// Funkcja główna algorytmu Tutte'a
void oblicz_tutte(Graf *g, int it);

// Funkcja pomocnicza do rozmieszczenia wierzchołków na okręgu
void ustaw_zewnetrzne_na_kole(Graf *g, double promien);

#endif //TUTTE_H
