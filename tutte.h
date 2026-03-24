#ifndef TUTTE_H
#define TUTTE_H

#include "graf.h"

// Funkcja główna algorytmu Tutte'a
// it - liczba iteracji do numerycznego wyznaczenia pozycji (metoda relaksacji)
void oblicz_tutte(Graf *g, int it);

// Funkcja pomocnicza do przypisania wierzchołkom zewnętrznym pozycji na okręgu
void ustaw_zewnetrzne_na_kole(Graf *g, double promien);

#endif //TUTTE_H
