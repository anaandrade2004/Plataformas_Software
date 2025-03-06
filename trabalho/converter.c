#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#include "converter_no_forks.h"
#include "converter_with_forks.h"
#include "converter_wf_fifo.h"

int main(int argc, char* argv[]) {
    if (argc == 6) {
        char* caminho = argv[1];
        int n_bases = atoi(argv[2]);
        int n_patients = atoi(argv[3]);
        int num_processes = atoi(argv[4]);
        char* flag_atv = argv[5];
        if (strcmp(flag_atv, "yes") == 0) {
            converter_with_forks_fifo(caminho, n_bases, n_patients, num_processes);
        } else if (strcmp(flag_atv, "no") == 0) {
            converter_with_forks(caminho, n_bases, n_patients, num_processes);
        }

    } else if (argc == 4) {
        char* caminho = argv[1];
        int n_bases = atoi(argv[2]);
        int n_patients = atoi(argv[3]);

        converter_no_forks(caminho, n_bases, n_patients); 
    } else {
        printf("Erro na inserção de parâmetros!\n");
        printf("Insira os seguintes parâmetros se quiser executar o programa em paralelo com fifo (<flag_atv> -> yes) ou sem fifo (<flag_atv> -> no): ./converter <genomic_file> <size_of_sequence> <number_patients> <num_processes> <flag_atv>\n");
        printf("Insira os seguintes parâmetros se quiser executar o programa sequencialmente: ./converter <genomic_file> <size_of_sequence> <number_patients>\n");
    }
    return 0;
}
