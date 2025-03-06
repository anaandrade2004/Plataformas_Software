
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "auxiliar_g_fifo.h"

int aggregate_patients_fifo(int num_patients) {
    int total_A = 0;
    int total_C = 0;
    int total_G = 0;
    int total_U = 0;

    int pipes[num_patients][2]; // pipes para comunicação entre pai e filho

    for (int i = 0; i < num_patients; i++) {
        //cria um pipe para cada filho
        if (pipe(pipes[i]) == -1) {
            perror("Erro ao criar pipe");
            return 1;
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("Erro ao criar processo filho");
            return 1;
        } else if (pid == 0) { //processo filho
            close(pipes[i][0]); // fechar descritor de leitura

            char fifo_name[50];
            sprintf(fifo_name, "patient_fifo_%d", i + 1);

            //Abrir o fifo para ler
            int fifo_fd = open(fifo_name, O_RDONLY);
            if (fifo_fd == -1) {
                perror("Erro ao abrir FIFO para leitura");
                close(pipes[i][1]);
                exit(1);
            }

            Patient patient;
            ssize_t bytes_read = read(fifo_fd, &patient, sizeof(Patient));
            if (bytes_read != sizeof(Patient)) {
                perror("Erro na leitura dos dados do paciente");
                close(fifo_fd);
                close(pipes[i][1]);
                exit(1);
            }

            close(fifo_fd);

            //Envia os dados do paciente para o processo pai 
            if (write(pipes[i][1], &patient, sizeof(Patient)) == -1) {
                perror("Erro ao enviar dados para o processo pai");
                close(pipes[i][1]);
                exit(1);
            }

            close(pipes[i][1]);
            exit(0); 
        } else {
            close(pipes[i][1]);
        }
    }

    // Processo pai espera por todos os processo filho e agrega o os resultados 
    for (int i = 0; i < num_patients; i++) {
        Patient patient;

        // Read patient data from the pipe
        if (read(pipes[i][0], &patient, sizeof(Patient)) == -1) {
            perror("Erro ao ler dados do pipe");
            close(pipes[i][0]);
            continue;
        }

        close(pipes[i][0]); // Close read end after reading

        // Aggregate patient data
        total_A += patient.A;
        total_C += patient.C;
        total_G += patient.G;
        total_U += patient.U;
    }

    // Wait for all child processes to finish
    while (wait(NULL) > 0);

    // Print global statistics
    printf("Aggregator: Estatísticas Globais\n");
    printf("Total Utentes: %d\n", num_patients);
    printf("Total de tipos de base A: %d\n", total_A);
    printf("Total de tipos de base C: %d\n", total_C);
    printf("Total de tipos de base G: %d\n", total_G);
    printf("Total de tipos de base U: %d\n", total_U);

    return 0;
}