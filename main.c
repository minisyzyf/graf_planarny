#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f-r.h"
#include "tutte.h"
#include "io.h"
#include "graf.h"
#include "logger.h"

int main(int argc, char* argv[]) {

    // Sprawdzenie minimalnej liczby argumentów: prog, -i, plik1, -o, plik2
    if (argc < 5) {
      	fprintf(stderr, "Blad: Brak wymaganych argumentow.\n");
        fprintf(stderr, "Uzycie: -i <plik_grafu> -o <plik_wyjsciowy> [-a algorytm] [-f format_pliku_wyjsciowego] [-n liczba iteracji] [-d]\n");
        return 1;
    }

    char *in = NULL;
    char *out = NULL;
    int algorytm = 0; // 0 = F-R, 1 = Tutte
    int format = 0; // 0 = txt, 1 = bin
    int debug = 0; // flaga debugowania; 0 = wyłączona, 1 = włączona
    int iteracje_uzytkownika = 0; // jeśli zostanie 0 - program sam dobiera ilość iteracji

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
            }
            else if (strcmp(argv[i], "fr") == 0) {
              	algorytm = 0;
            }
            else {
                fprintf(stderr, "Blad: Nierozpoznany algorytm.\n");
                return 5;
            }
        }
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            i++;
            if (strcmp(argv[i], "bin") == 0) {
                format = 1;
            }
            else if (strcmp(argv[i], "txt") == 0) {
              	format = 0;
            }
            else {
                fprintf(stderr, "Blad: Nierozpoznany format.\n");
                return 6;
            }
        }
        else if (strcmp(argv[i], "-d") == 0 && i + 1 < argc) {
          	debug = 1;
        }
        else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            iteracje_uzytkownika = atoi(argv[++i]);
        }
    }

	// Zabezpieczenie, gdyby ktos nie podal nazw plików
    if (in == NULL || out == NULL) {
        fprintf(stderr, "Blad: Nie podano pliku wejsciowego lub wyjsciowego.\n");
        fprintf(stderr, "Uzycie: -i <plik_grafu> -o <plik_wyjsciowy> [-a algorytm] [-f format_pliku_wyjsciowego] [-d]\n");
        return 7;
    }

    int kod_bledu = 0;
    Graf *g = wczytaj_graf(in, &kod_bledu);
    if (g == NULL) {
     	if (kod_bledu == 2) fprintf(stderr, "Blad: Nie mozna otworzyc pliku wejsciowego.\n");
        if (kod_bledu == 3) fprintf(stderr, "Blad: Nieprawidlowy format danych w pliku.\n");
        if (kod_bledu == 8) fprintf(stderr, "Blad: Nieudana alokacja pamieci.\n");
        return kod_bledu;
    }

    // Jeśli włączono flagę -d
    if (debug) wypisz_debug(g);

    // Sprawdzanie spójności
    int spojnosc = sprawdz_spojnosc(g);
    if (spojnosc == -1) {
        fprintf(stderr, "Blad: Nieudana alokacja pamieci.\n");
        zwolnij_graf(g);
        return 8;
    } else if (spojnosc == 0) {
        fprintf(stderr, "Blad: Graf wejsciowy jest niespojny.\n");
        zwolnij_graf(g);
        return 9;
    }

    // Ustawienie ilości iteracji (zależnie od użytkownika lub uruchamianego algorytmu)
    int iteracje = 0;
    if (iteracje_uzytkownika > 0) { // nawet jeśli użytkownik poda ujemną liczbę, nie ma szans na błąd
      	iteracje = iteracje_uzytkownika;
    }
    else {
      	if (algorytm == 0) {
          	iteracje = 100 + (5 * g->V);
    	} else {
      		iteracje = 100 + (10 * g->V);
    	}
    }
    printf("Liczba iteracji do symulacji: %d\n", iteracje);

    // Odpalenie algorytmu
    int kod_algorytmu = (algorytm == 0) ? oblicz_f_r(g, iteracje) : oblicz_tutte(g, iteracje);
    if (kod_algorytmu != 0) {
        if (kod_algorytmu == 10) fprintf(stderr, "Blad: Dzielenie przez zero w symulacji.\n");
        if (kod_algorytmu == 8) fprintf(stderr, "Blad: Nieudana alokacja pamieci.\n");
        zwolnij_graf(g);
        return kod_algorytmu;
    }

    // Zapis wynikow
    int kod_zapisu = 0;
    if (format == 0) {
        kod_zapisu = zapisz_graf_txt(g, out);
        printf("Zapisano wyniki do pliku tekstowego: %s\n", out);
    } else {
        kod_zapisu = zapisz_graf_bin(g, out);
        printf("Zapisano wyniki do pliku binarnego: %s\n", out);
    }

    if (kod_zapisu != 0) {
        fprintf(stderr, "Blad: Nie mozna utworzyc pliku wyjsciowego.\n");
        zwolnij_graf(g);
        return 4;
    }

    // Sprzątanie pamięci
    zwolnij_graf(g);

    return 0;
}