#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "auxiliar_c.h"

/*
void print_patient(Patient p) {
    printf("Patient ID: %d\n", p.id);
    printf("Bases A: %d\n", p.A);
    printf("Bases C: %d\n", p.C);
    printf("Bases U: %d\n", p.U);
    printf("Bases G: %d\n", p.G);
}*/

int converter_with_forks(char* caminho, int n_bases, int n_patients, int num_processes){
    if (num_processes <= 0 || num_processes > n_patients) {
        printf("Invalid number of processes. Must be between 1 and number of patients.\n");
        return 1;
    }
    
    char buf[n_bases+1];

    int fd = open(caminho, O_RDONLY);
    if (fd == -1) {
        perror("Erro ao abrir o ficheiro.");
        return 1;
    }

    int patients_per_process = n_patients / num_processes;
    int remaining_patients = n_patients % num_processes;

    for (int i = 0; i < num_processes; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Erro ao criar processo.");
            close(fd);
            return 1;
        } else if (pid == 0) { // processo filho
            int start_patient = i * patients_per_process;
            int end_patient = start_patient + patients_per_process;

            // distribui os restantes pacientes pelo último processo filho
            if (i == num_processes - 1) {
                end_patient += remaining_patients;
            }

            for (int num = start_patient; num < end_patient; num++) {
                ssize_t res = read(fd, buf, n_bases+1);
                
                if (res == 0) {
                    printf("Fim do arquivo atingido antes de processar todos os pacientes.\n");
                    break;
                } else if (res < 0) {
                    perror("Erro ao ler o arquivo");
                    close(fd);
                    exit(1);
                }

                char* sequence = dnatomrna(buf, n_bases);
                //printf("Paciente %d: Bytes lidos: %zd\n", num + 1, res);

                /*
                // se quisermos criar um ficheiro que contém a sequência traduzida sem ser em binário (mas aumentava o tempo de execução)
                char filename[50];
                sprintf(filename, "paciente_mRNA_%d.txt", num + 1);
                int fd_p = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd_p == -1) {
                    perror("Erro ao abrir o arquivo do paciente");
                    free(sequence);
                    close(fd);
                    exit(1);
                }
                
                write(fd_p, sequence, n_bases);
                
                close(fd_p);
                */

                char filename2[50];
                sprintf(filename2, "%d", num + 1);
                int fd_s = open(filename2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd_s == -1) {
                    perror("Erro ao abrir o arquivo do paciente");
                    free(sequence);
                    close(fd);
                    exit(1);
                }

                Patient p = contador_bases(sequence, n_bases, num + 1);
                write(fd_s, &p, sizeof(Patient));
                close(fd_s);

                /*
                 ler a struct do ficheiro binário   
                Patient p2;
                fd_s = open(filename2, O_RDONLY);
                if (fd_s == -1) {
                    perror("Erro ao abrir o arquivo do paciente");
                    free(sequence);
                    close(fd);
                    exit(1);
                }

                read(fd_s, &p2, sizeof(Patient));
                close(fd_s);
                */
                //print_patient(p2);
                free(sequence);
            }

            close(fd);
            exit(0); 
        }
    }

    // processo pai espera por todos os processo filhos
    while (wait(NULL) > 0);

    close(fd);
    
    return 0;
}
