#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <float.h>

typedef enum {rosso, nero} colore_t;

typedef struct nodo_albero_bin_rn
{
    int valore;
    colore_t colore;
    struct nodo_albero_bin_rn *sx_p, *dx_p, *padre_p;
} nodo_albero_bin_rn_t;




int main(int argc, char **argv)
{
    FILE *cpuPtr;
    
    if((cpuPtr = fopen("file_CPU.txt", "r")) == NULL)
    {
        puts("File could not be opened");
    }
    else
    {
        int tempo;
        char cpu_code[7];
        double potenza;
        double temperature;
        double process;
        double memory;
        
        printf("%-10s%-13s%-15s%-15s%-15s%-15s\n", "Tempo", "CPU", "Potenza", "Temperatura", "Processi", "Memoria");
        fscanf(cpuPtr, "%d%s%lf%lf%lf%lf", &tempo, cpu_code, &potenza, &temperature, &process, &memory);
        
        while(!feof(cpuPtr))
        {
            printf("%-10d%-13s%-15f%-15f%-15f%-15f\n", tempo, cpu_code, potenza, temperature, process, memory);
            fscanf(cpuPtr, "%d%s%lf%lf%lf%lf", &tempo, cpu_code, &potenza, &temperature, &process, &memory);
        }
        fclose(cpuPtr);
    }
    
    return 0;
}
