#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "auxiliar_c.h"
#include "converter_wf_fifo.h"

int converter_with_forks_fifo(char* caminho, int n_bases, int n_patients, int num_processes) {
    if (num_processes <= 0 || num_processes > n_patients) {
        printf("Invalid number of processes. Must be between 1 and number of patients.\n");
        return 1;
    }

    // +1 por causa do enter
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

            // caso o resto da divisão inteira não dê zero, distribui os restantes pacientes para o último processo
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
                Patient p = contador_bases(sequence, n_bases, num + 1);

                char fifo_name[50];
                sprintf(fifo_name, "patient_fifo_%d", num + 1);

                // Create FIFO for the patient
                if (mkfifo(fifo_name, 0666) == -1) {
                    perror("Erro ao criar FIFO");
                    free(sequence);
                    close(fd);
                    exit(1);
                }

                // abre o fifo e escreve os dados dos pacientes
                int fifo_fd = open(fifo_name, O_WRONLY);
                if (fifo_fd == -1) {
                    perror("Erro ao abrir FIFO para escrita");
                    free(sequence);
                    close(fd);
                    exit(1);
                }

                write(fifo_fd, &p, sizeof(Patient));
                close(fifo_fd);
                free(sequence);
            }

            close(fd);
            exit(0);
        }
    }

    // processo pai espera pro todos os processos filhos
    while (wait(NULL) > 0);

    close(fd);
    return 0;
}
