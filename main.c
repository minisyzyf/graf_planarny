#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f-r.h"
#include "tutte.h"
#include "io.h"
#include "graf.h"

int main(int argc, char* argv[]) {

    // Sprawdzenie minimalnej liczby argumentów: prog, -i, plik1, -o, plik2
    if (argc < 5) {
        fprintf(stderr, "Uzycie: -i <plik_grafu> -o <plik_wyjsciowy> [-a algorytm] [-f format_pliku_wyjsciowego]\n");
        return 1;
    }

    char *in = NULL;
    char *out = NULL;
    int algorytm = 0; // 0 = F-R, 1 = Tutte
    int format = 0; // 0 = txt, 1 = bin

    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            in = argv[++i];
        }
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            out = argv[++i];
        }
        else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
            i++;
            if (strcmp(argv[i], "tutte") == 0) {
                algorytm = 1;
            } else {
                algorytm = 0; // domyślnie F-R
            }
        }
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            i++;
            if (strcmp(argv[i], "bin") == 0) {
                format = 1;
            } else {
                format = 0; // domyślnie txt
            }
        }
    }

 // Zabezpieczenie, gdyby ktos nie podal flag -i oraz -o
    if (in == NULL || out == NULL) {
        fprintf(stderr, "Blad: Nie podano pliku wejsciowego lub wyjsciowego.\n");
        return 1;
    }

    // ==========================================
    // --- SPRAWDZARKA (TEST WCZYTYWANIA) ---
    // ==========================================
    printf("Probujemy wczytac graf z pliku: %s\n", in);
    Graf *g = wczytaj_graf(in);

    if (g == NULL) {
        fprintf(stderr, "Nie udalo sie wczytac grafu. Koncze dzialanie.\n");
        return 2;
    }

    printf("\n--- WCZYTANO POMYSLNIE! ---\n");
    printf("Liczba wierzcholkow (V): %d\n", g->V);
    printf("Liczba krawedzi (E): %d\n\n", g->E);

    printf("--- LISTA WIERZCHOLKOW ---\n");
    for (int j = 0; j < g->V; j++) {
        printf("Indeks tablicy [%d] | ID z pliku: %d | Stopien: %d | Wspolrzedne: (%.1f, %.1f)\n",
               j, g->wierzcholki[j].id, g->wierzcholki[j].degree,
               g->wierzcholki[j].x, g->wierzcholki[j].y);
    }

    printf("\n--- LISTA KRAWEDZI ---\n");
    for (int j = 0; j < g->E; j++) {
        printf("Krawedz '%s' | Waga: %.1f | Laczy ID: %d z ID: %d\n",
               g->krawedzie[j].nazwa,
               g->krawedzie[j].waga,
               g->krawedzie[j].p->id,
               g->krawedzie[j].k->id);
    }
    printf("---------------------------\n\n");

    // Sprzatamy pamiec po tescie, zeby wyciekow nie bylo
    free(g->wierzcholki);
    free(g->krawedzie);
    free(g);

    return 0;
}