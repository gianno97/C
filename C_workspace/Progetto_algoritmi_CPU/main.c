#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <float.h>

typedef struct nodo_albero_bin
{
    int chiave;
    int tempo;
    char codice_cpu[7];
    double potenza;
    double temperatura;
    double processi;
    double memoria;
    struct nodo_albero_bin *sx_p, *dx_p;
} nodo_albero_bin_t;

int inserisci_in_albero_bin_ric(nodo_albero_bin_t **radice_p, int chiave);
nodo_albero_bin_t *cerca_in_albero_bin_ric(nodo_albero_bin_t *radice_p, int chiave);

int main(int argc, char **argv)
{
    FILE *cpuPtr;
    
    if((cpuPtr = fopen("file_CPU.txt", "r")) == NULL)
    {
        puts("Il file non può essere aperto");
    }
    else
    {
        nodo_albero_bin_t *radice = NULL;
        
        //printf("%-10s%-13s%-15s%-15s%-15s%-15s\n", "Tempo", "CPU", "Potenza", "Temperatura", "Processi", "Memoria");
        fscanf(cpuPtr, "%d%s%lf%lf%lf%lf", radice->tempo, radice->codice_cpu, radice->potenza, radice->temperatura, radice->processi, radice->memoria);
        
        while(!feof(cpuPtr))
        {
            //printf("%-10d%-13s%-15f%-15f%-15f%-15f\n", tempo, cpu_code, potenza, temperature, process, memory);
            fscanf(cpuPtr, "%d%s%lf%lf%lf%lf", radice->tempo, radice->codice_cpu, radice->potenza, radice->temperatura, radice->processi, radice->memoria);
        }
        fclose(cpuPtr);
    }
    
    return 0;
}

int inserisci_in_albero_bin_ric(nodo_albero_bin_t **radice_p, int chiave)
{
    int               inserito;
    nodo_albero_bin_t *nodo_p,
                      *padre_p,
                      *nuovo_p;

    for (nodo_p = padre_p = *radice_p;
         ((nodo_p != NULL) && (nodo_p->chiave != chiave));
         padre_p = nodo_p, nodo_p = (chiave < nodo_p->chiave)?
                                      nodo_p->sx_p:
                                      nodo_p->dx_p);
    if (nodo_p != NULL)
        inserito = 0;
    else
    {
        inserito = 1;
        nuovo_p = (nodo_albero_bin_t *)malloc(sizeof(nodo_albero_bin_t));
        nuovo_p->chiave = chiave;
        nuovo_p->sx_p = nuovo_p->dx_p = NULL;
        if (nodo_p == *radice_p)
            *radice_p = nuovo_p;
        else
            if (chiave < padre_p->chiave)
                padre_p->sx_p = nuovo_p;
            else
                padre_p->dx_p = nuovo_p;
    }
    return(inserito);
}

nodo_albero_bin_t *cerca_in_albero_bin_ric(nodo_albero_bin_t *radice_p, int chiave)
{
    nodo_albero_bin_t *nodo_p;

    for (nodo_p = radice_p;
         ((nodo_p != NULL) && (nodo_p->chiave != chiave));
         nodo_p = (chiave < nodo_p->chiave)?
                    nodo_p->sx_p:
                    nodo_p->dx_p);
    return(nodo_p);
}
