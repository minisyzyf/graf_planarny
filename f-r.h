#ifndef F_R_H
#define F_R_H

#include "io.h"
#include "graf.h"

#define EPS 0.01 // zakładamy, że minimalne przesunięcie do 2 liczb po przecinku

// funkcja rozrzucająca wierzchołki losowo, aby nadać im pewne współrzędne
void losuj_wspolrzedne(Graf *g);

// funkcja wyznaczająca iteracyjnie współrzędne wierzchołków opierając się na algorytmie
// Fruchtermana-Reingolda
void oblicz_f_r(Graf *g, int it);

#endif //F_R_H
