
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "auxiliar_g.h"
#include "auxiliar_g_fifo.h"


int main(int argc, char *argv[]) {
    int num_patients = atoi(argv[1]);
    char* flag_atv = argv[2];

    if (argc != 3) {
        printf("Erros no parâmetros inseridos. Insira os seguintes parâmetros: ./aggregator <n_patients_a_ler> <flag_atv>\n");
        printf("Insira o valor de <flag_atv> igual a 0 se desejar fazer fifo e caso não queira o uso de fifo insira 1. \n");
        return -1;
    }
    if (strcmp(flag_atv, "yes") == 0) {
        aggregate_patients_fifo(num_patients);
    } else if (strcmp(flag_atv, "no") == 0) {
        aggregate_patients(num_patients);
    }


    if (num_patients <= 0) {
        perror("Número de pacientes inválido!\n");
        return -1;
    }


    return 0;
}
