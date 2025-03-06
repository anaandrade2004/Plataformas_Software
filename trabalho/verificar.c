#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>



typedef struct patient{
    int id; //identificador do utente 
    int A; //soma de todos as bases A
    int C; //soma de todos as bases C
    int U; //soma de todos as bases G
    int G; //soma de todos as bases T
}Patient;

void print_patient(Patient p) {
    printf("Patient ID: %d\n", p.id);
    printf("Bases A: %d\n", p.A);
    printf("Bases C: %d\n", p.C);
    printf("Bases U: %d\n", p.U);
    printf("Bases G: %d\n", p.G);
}

// quando retornar p devolve 
Patient contador_bases(char* caminho, int n_bases, int id){

    //abrir o arquivo para ler outra vez ia dar ao inicio do ficheiro
   /* // Abrindo o arquivo para leitura
    int fd = open(caminho, O_RDONLY);
    printf("caminho a seguir: %s", caminho);
    if (fd == -1) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    // Ler os dados do arquivo
    char* dna = (char*)malloc(n_bases * sizeof(char));
    ssize_t res = read(fd, dna, n_bases);

    if (res == -1) {
        perror("Erro ao ler o arquivo");
        free(dna);
        close(fd);
        return -1;
    }*/

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

    printf("Resultado para o paciente:\n");
    printf("Bases A: %d\n", p.A);
    printf("Bases C: %d\n", p.C);
    printf("Bases U: %d\n", p.U);
    printf("Bases G: %d\n", p.G);
    printf("\n");


    return p;
}

int main(int argc, char* argv[]){

    if (argc != 2){
        printf("Erro na inserção dos parâmetros. Insira os seguintes parâmetros: ./verificar <num_pacientes_a_verificar>");
    }

    int num_pacientes = atoi(argv[1]);

    for (int i=1; i<=num_pacientes; i++) {

        char filename2[50];
        sprintf(filename2, "%d", i);
        int fd_s = open(filename2, O_RDONLY, 0644);
        if (fd_s == -1) {
            perror("Erro ao abrir o arquivo do paciente");
            exit(1);
        }


        Patient p2;

        read(fd_s, &p2, sizeof(Patient));
        close(fd_s);

        print_patient(p2);

    }
    return 0;
}