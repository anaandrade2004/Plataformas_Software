#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "auxiliar_c.h"


//print_patient(Patient p)-> para testar
/*
void print_patient(Patient p) {
    printf("Patient ID: %d\n", p.id);
    printf("Bases A: %d\n", p.A);
    printf("Bases C: %d\n", p.C);
    printf("Bases U: %d\n", p.U);
    printf("Bases G: %d\n", p.G);
}*/

int converter_no_forks(char* caminho, int n_bases, int n_patients){

    char buf[n_bases];
    char buf2[10];
    int fd = open(caminho, O_RDONLY);
    if (fd == -1) {
        perror("Erro ao abrir o ficheiro.");
        return 1;
    }

    ssize_t res = 0;
    int num = 0;

    
        
    for (int i = 0; i < n_patients; i++) {
        // Ler uma sequência de DNA para o paciente atual
        res = read(fd, buf, n_bases);
        // lê mais um byte por causa do enter para mudar de linha, podiamos apenas adicionar ao buf + 1  -> char buf[n_bases+1];
        read(fd,buf2,1);
        if (res == 0) {
            printf("Fim do arquivo atingido antes de processar todos os pacientes.\n");
            break;
        } else if (res < 0) {
            perror("Erro ao ler o arquivo \n");
            close(fd);
            return 1;
        }

        // Converter DNA para RNA
        char* sequence = dnatomrna(buf, n_bases);
        //printf("Paciente %d: Bytes lidos: %zd\n", num + 1, res);


        /*
        // se quisermos criar um ficheiro que contém a sequência traduzida sem ser em binário (mas aumentava o tempo de execução)
        char filename[50];
        sprintf(filename, "paciente_mRNA_%d.txt", num + 1);
        //printf("filename gerado: %s\n", filename);
        int fd_p = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_p == -1) {
            perror("Erro ao abrir o arquivo do paciente");
            free(sequence);
            close(fd);
            return 1;
        }
    
        write(fd_p, sequence, n_bases);
        
        close(fd_p);*/


        //criar ficheiro binário
        char filename2[50];
        sprintf(filename2, "%d", num + 1);
        //printf("filename gerado: %s\n", filename);
        int fd_s = open(filename2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_s == -1) {
            perror("Erro ao abrir o arquivo do paciente");
            free(sequence);
            close(fd);
            return 1;
        }

        Patient p = contador_bases(sequence, n_bases, num+1);

        // escrever a struct no ficheiro binário
        write(fd_s, &p, sizeof(Patient));
        close(fd_s);

        /* 
        // ler a struct do ficheiro binário         
        Patient p2;
        fd_s = open(filename2, O_RDONLY);
        if (fd_s == -1) {
            perror("Erro ao abrir o arquivo do paciente");
            free(sequence);
            close(fd);
            return 1;
        }

        read(fd_s, &p2, sizeof(Patient));
        close(fd_s);
        
        //Print dos dados do paciente
        //print_patient(p2);
        */
        
        free(sequence);
        num++;
    }

    close(fd);
    return 0;
}
