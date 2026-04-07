#include <stdio.h>
#include "logger.h"

void wypisz_debug(Graf *graf) {
    printf("\n=== TRYB DEBUG: STRUKTURA GRAFU ===\n");
    printf("Liczba wierzcholkow (V): %d\n", graf->V);
    printf("Liczba krawedzi (E): %d\n\n", graf->E);

    int ilosc = graf->V > 20 ? 20 : graf->V;

    printf("--- LISTA WIERZCHOLKOW ---\n");
    for (int j = 0; j < ilosc; j++) {
        printf("Indeks [%d] | ID: %d | Stopien: %d | is_fixed: %d | Wsp: (%.1f, %.1f)\n",
               j, graf->wierzcholki[j].id, graf->wierzcholki[j].degree,
               graf->wierzcholki[j].is_fixed, graf->wierzcholki[j].x, graf->wierzcholki[j].y);
    }

    printf("\n--- LISTA KRAWEDZI ---\n");
    for (int j = 0; j < ilosc; j++) {
        printf("Krawedz '%s' | Waga: %.1f | Laczy ID: %d z ID: %d\n",
               graf->krawedzie[j].nazwa,
               graf->krawedzie[j].waga,
               graf->krawedzie[j].p->id,
               graf->krawedzie[j].k->id);
    }
    printf("===================================\n\n");
}