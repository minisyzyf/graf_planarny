#include "tutte.h"
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

void ustaw_zewnetrzne_na_kole(Graf *g, double promien) {
    int licznik_zew = 0;
    // Liczymy ile wierzchołków ma być na zewnątrz
    for (int i = 0; i < g->V; i++) {
        if (g->wierzcholki[i].is_fixed) licznik_zew++;
    }

    if (licznik_zew == 0) return;

    int j = 0;
    for (int i = 0; i < g->V; i++) {
        if (g->wierzcholki[i].is_fixed) {
            // Rozmieszczamy je równomiernie co kąt (2*PI / liczba_wierzchołków)
            double kat = 2.0 * M_PI * j / licznik_zew;
            g->wierzcholki[i].x = promien + promien * cos(kat);
            g->wierzcholki[i].y = promien + promien * sin(kat);
            j++;
        }
    }
}

void oblicz_tutte(Graf *g, int it) {
    if (g->V < 3) return;

    // KROK 1: Sprawdzenie czy są wierzchołki stałe (is_fixed)
    int fixed_exists = 0;
    for(int i=0; i < g->V; i++) {
        if(g->wierzcholki[i].is_fixed) fixed_exists = 1;
    }

    // Jeśli nie oznaczono żadnych, przyjmujemy domyślnie pierwsze 3 jako otoczkę
    if (!fixed_exists) {
        for(int i=0; i < (g->V > 3 ? 3 : g->V); i++) {
            g->wierzcholki[i].is_fixed = 1;
        }
    }

    // KROK 2: Ustawienie wierzchołków stałych na okręgu
    ustaw_zewnetrzne_na_kole(g, 400.0);

    // KROK 3: Iteracyjne wyliczanie pozycji wierzchołków wewnętrznych
    for (int iter = 0; iter < it; iter++) {
        for (int i = 0; i < g->V; i++) {
            // Nie ruszamy wierzchołków stałych
            if (g->wierzcholki[i].is_fixed) continue;

            double suma_x = 0;
            double suma_y = 0;
            int liczba_sasiadow = 0;

            // Przeszukujemy krawędzie, aby znaleźć sąsiadów wierzchołka 'i'
            for (int e = 0; e < g->E; e++) {
                if (g->krawedzie[e].p->id == g->wierzcholki[i].id) {
                    suma_x += g->krawedzie[e].k->x;
                    suma_y += g->krawedzie[e].k->y;
                    liczba_sasiadow++;
                } else if (g->krawedzie[e].k->id == g->wierzcholki[i].id) {
                    suma_x += g->krawedzie[e].p->x;
                    suma_y += g->krawedzie[e].p->y;
                    liczba_sasiadow++;
                }
            }

            // Ustawiamy wierzchołek w środku ciężkości sąsiadów
            if (liczba_sasiadow > 0) {
                g->wierzcholki[i].x = suma_x / liczba_sasiadow;
                g->wierzcholki[i].y = suma_y / liczba_sasiadow;
            }
        }
    }
}
