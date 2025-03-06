#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "auxiliar_g.h"


int aggregate_patients(int num_patients) {
    int total_A = 0;
    int total_C = 0;
    int total_G = 0;
    int total_U = 0;

    
    // Ler ficheiros binários dos utentes e enviar pelo FIFO
    for (int i = 1; i <= num_patients; i++) {
        char filename[256];
        sprintf(filename, "%d", i); // Nome do ficheiro do utente e armazena no buffer

        int fd = open(filename, O_RDONLY);
        if (fd == -1) {
            perror("Erro ao abrir ficheiro binário");
            break; 
        }

        
        Patient patient;
        ssize_t bytes_read = read(fd, &patient, sizeof(Patient));// lê os dados e armazena

        if (bytes_read != sizeof(Patient)){
            perror("Erro na leitura no aggreagte_patients");
        }
        close(fd);
    
        total_A += patient.A;
        total_C += patient.C;
        total_G += patient.G;
        total_U += patient.U;
    }

    // Imprimir estatísticas globais no terminal
    printf("Aggregator: Estatísticas Globais\n");
    printf("Total Utentes: %d\n", num_patients);
    printf("Total de tipos de base A: %d\n", total_A);
    printf("Total de tipos de base C: %d\n", total_C);
    printf("Total de tipos de base G: %d\n", total_G);
    printf("Total de tipos de base U: %d\n", total_U);

    return 0;
}