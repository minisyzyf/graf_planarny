#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"

#define BUFSIZE 128

Wierzcholek* pobierz_lub_dodaj(Graf* graf, int id) {
    int i;
    for (i = 0; i < graf->V; i++) {
		if(graf->wierzcholki[i].id == id) {
        	return &graf->wierzcholki[i];
        }
	}

    // gdy nie znaleziono indeksu, tworzony jest nowy
    int index = graf->V;
    graf->wierzcholki[index].id = id;
    graf->wierzcholki[index].x = 0;
    graf->wierzcholki[index].y = 0;
    graf->wierzcholki[index].dx = 0;
    graf->wierzcholki[index].dy = 0;
    graf->wierzcholki[index].degree = 0;
    graf->wierzcholki[index].is_fixed= 0;
    graf->V++;

   	return &graf->wierzcholki[index];
}

Graf* wczytaj_graf(const char* plik) {
	FILE* f = fopen(plik, "r");
    if (f == NULL) {
    	fprintf(stderr, "Nie mozna otworzyc pliku wejsciowego!!\n");
        exit(1);
    }

    int l_krawedzi = 0;
    char buf[BUFSIZE];
    while (fgets(buf, BUFSIZE, f)) {
    	l_krawedzi++;
    }

    Graf* graf = (Graf*)malloc(sizeof(Graf));
    graf->E = l_krawedzi;
    graf->V = 0;

    graf->krawedzie = (Krawedz*)malloc(graf->E * sizeof(Krawedz));
    graf->wierzcholki = (Wierzcholek*)malloc(2 * graf->E * sizeof(Wierzcholek));

    rewind(f);

    int i = 0;
    char nazwa_kr[MAX_ID_LEN];
    int id_p, id_k;
    double waga;

    while(fscanf(f, "%s %d %d %lf", nazwa_kr, &id_p, &id_k, &waga) != EOF) {
    	strcpy(graf->krawedzie[i].nazwa, nazwa_kr);
        graf->krawedzie[i].waga = waga;
        graf->krawedzie[i].p = pobierz_lub_dodaj(graf, id_p);
        graf->krawedzie[i].k = pobierz_lub_dodaj(graf, id_k);
        graf->krawedzie[i].p->degree++;
        graf->krawedzie[i].k->degree++;
        i++;
    }

    fclose(f);
    return graf;
}

int sprawdz_spojnosc(Graf *g) {
	if (g->V <= 1) return 1;

    int *odwiedzone = (int*)calloc(g->V, sizeof(int));
    odwiedzone[0] = 1;

    int dodany;
    do {
    	dodany = 0;
    	for (int i = 0; i < g->E; i++) {
			int p = g->krawedzie[i].p->id - 1;
            int k = g->krawedzie[i].k->id - 1;
        }
        if (odwiedzone[p] && !odwiedzone[k]) {
        	odwiedzone[k] = 1;
        	dodany = 1;
        }
        else if (!odwiedzone[p] && odwiedzone[k]) {
          	odwiedzone[p] = 1;
           	dodany = 1;
        }
	} while (dodany == 1);

    int spojny = 1;
    for (int i = 0; i < g->V; i++) {
      	if (!odwiedzone[i]) {
          	spojny = 0;
            break;
      	}
    }
    free(odwiedzone);
    return spojny;
}

