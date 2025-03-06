
#ifndef AUXILIAR_C_H
#define AUXILIAR_C_H

typedef struct patient{
    int id; //identificador do utente 
    int A; //soma de todos as bases A
    int C; //soma de todos as bases C
    int U; //soma de todos as bases G
    int G; //soma de todos as bases T
}Patient;

char* dnatomrna(char* dna, int n_caracteres);
Patient contador_bases(char* caminho, int n_bases, int id);


#endif