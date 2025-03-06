#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "auxiliar_c.h"


char* dnatomrna(char* dna, int n_caracteres){
    char* rna = (char*)malloc(n_caracteres * sizeof(char));
    for (int i = 0; i < n_caracteres; i++) {
        if (dna[i] == 'A') {
            rna[i] = 'U';
        } else if (dna[i] == 'T') {
            rna[i] = 'A';
        } else if (dna[i] == 'G') {
            rna[i] = 'C';
        } else if (dna[i] == 'C') {
            rna[i] = 'G';
        }
    }
    return rna;

}


Patient contador_bases(char* caminho, int n_bases, int id){

    Patient p;
    p.id=id;
    p.A = 0;
    p.C = 0;
    p.U = 0;
    p.G = 0;

    for (int i = 0; i < n_bases; i++) {
        if (caminho[i] == 'A') {
            p.A++;
        } else if (caminho[i] == 'U') {
            p.U++;
        } else if (caminho[i] == 'C') {
            p.C++;
        } else if (caminho[i] == 'G') {
            p.G++;
        }
    }

    // para ver as estatísticas individuais de cada paciente
    /*
    printf("Resultado para o paciente:\n");
    printf("Bases A: %d\n", p.A);
    printf("Bases C: %d\n", p.C);
    printf("Bases U: %d\n", p.U);
    printf("Bases G: %d\n", p.G);
    printf("\n");*/


    return p;
}




