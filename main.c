#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f-r.h"
#include "tutte.h"
#include "logger.h"

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

    return 0;
}
