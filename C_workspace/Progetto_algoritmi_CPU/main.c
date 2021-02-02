#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <float.h>
#include <time.h>

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
void cerca_in_albero_bin_ric(nodo_albero_bin_t *radice_p, char codice_cpu[7]);
void visita_albero_bin_ant(nodo_albero_bin_t *nodo_p);

int main(int argc, char **argv)
{
    FILE *cpuPtr;
    
    int x, inserito;
    char codice_cpu[7];
    nodo_albero_bin_t *radice = NULL;
    
    if((cpuPtr = fopen("file_CPU.txt", "r")) == NULL)
    {
        puts("Il file non può essere aperto");
    }
    else
    {
        srand(time(NULL));
        
        printf("%-10s%-13s%-15s%-15s%-15s%-15s\n", "Tempo", "CPU", "Potenza", "Temperatura", "Processi", "Memoria");
        x = 1 + rand() % 40;
        inserisci_in_albero_bin_ric(&radice, x);
        fscanf(cpuPtr, "%d%s%lf%lf%lf%lf", &(radice->tempo), (radice->codice_cpu), &(radice->potenza), &(radice->temperatura), &(radice->processi), &(radice->memoria));
        
        while(!feof(cpuPtr))
        {
            x = 1 + rand() % 40;
            inserito = inserisci_in_albero_bin_ric(&radice, x);
            if(inserito == 1)
            {
                printf("%-10d%-13s%-15.2f%-15.2f%-15.2f%-15.2f\n", radice->tempo, radice->codice_cpu, radice->potenza, radice->temperatura, radice->processi, radice->memoria);
                fscanf(cpuPtr, "%d%s%lf%lf%lf%lf", &(radice->tempo), (radice->codice_cpu), &(radice->potenza), &(radice->temperatura), &(radice->processi), &(radice->memoria));
            }
        }
        fclose(cpuPtr);
    }
    
    printf("Digitare il codice della CPU:\n");
    scanf("%s", codice_cpu);
    cerca_in_albero_bin_ric(radice, codice_cpu);
    
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

void cerca_in_albero_bin_ric(nodo_albero_bin_t *radice_p, char codice_cpu[7])
{
    nodo_albero_bin_t *nodo_p;
    
    nodo_p = radice_p;
    
    while(nodo_p != NULL)
    {
        if(nodo_p->codice_cpu != codice_cpu)
        {
            if(nodo_p->sx_p != NULL)
            {
                nodo_p = nodo_p->sx_p;
            }
            else
            {
                nodo_p = nodo_p->dx_p;
            }
        }
        else
        {
            printf("%-10d%-13s%-15.2f%-15.2f%-15.2f%-15.2f\n", nodo_p->tempo, nodo_p->codice_cpu, nodo_p->potenza, nodo_p->temperatura, nodo_p->processi, nodo_p->memoria);
        }
    }

    /*for (nodo_p = radice_p;
         ((nodo_p != NULL) && (nodo_p->codice_cpu != codice_cpu));
         nodo_p = (chiave < nodo_p->chiave)?
                    nodo_p->sx_p:
                    nodo_p->dx_p);*/
}

void visita_albero_bin_ant(nodo_albero_bin_t *nodo_p)
{
    //printf("%-10s%-13s%-15s%-15s%-15s%-15s\n", "Tempo", "CPU", "Potenza", "Temperatura", "Processi", "Memoria");
    
    if(nodo_p != NULL)
    {
        printf("%-10d%-13s%-15f%-15f%-15f%-15f\n", (nodo_p->tempo), (nodo_p->codice_cpu), (nodo_p->potenza), (nodo_p->temperatura), (nodo_p->processi), (nodo_p->memoria));
        visita_albero_bin_ant(nodo_p->sx_p);
        visita_albero_bin_ant(nodo_p->dx_p);
    }
}
