
#ifndef AUXILIAR_G_H
#define AUXILIAR_G_H


typedef struct patient{
    int id; //identificador do utente 
    int A; //soma de todos as bases A
    int C; //soma de todos as bases C
    int G; //soma de todos as bases G
    int U; //soma de todos as bases T
}Patient;


int aggregate_patients(int n_patientes);


#endif