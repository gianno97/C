#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <float.h>
#include <time.h>

typedef struct elem_albero_bin
{
    int chiave;
    char codice_cpu[7];
} elem_albero_bin_t;

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

int inserisci_in_albero_bin_ric(nodo_albero_bin_t **radice_p, int chiave, int tempo, char codice_cpu[7], double potenza, double temperatura, double processi, double memoria);
//int inserisci_in_albero_bin_ric(nodo_albero_bin_t **radice_p, int chiave);
void cerca_in_albero_bin_ric(nodo_albero_bin_t *radice_p, int chiave);
void visita_albero_bin_ant(nodo_albero_bin_t *nodo_p, char codice_ricerca[7]);

int main(int argc, char **argv)
{
    FILE *cpuPtr;
    
    int x = 0;
    //int inserito;
    //int confronto;
    int tempo;
    char codice_cpu[7];
    double potenza;
    double temperatura;
    double processi;
    double memoria;
    char codice_ricerca[7];
    nodo_albero_bin_t *radice = NULL;
    
    if((cpuPtr = fopen("file_CPU.txt", "r")) == NULL)
    {
        puts("Il file non può essere aperto");
    }
    else
    {
        srand(time(NULL));
        
        //printf("%-10s%-13s%-15s%-15s%-15s%-15s\n", "Tempo", "CPU", "Potenza", "Temperatura", "Processi", "Memoria");
        //fscanf(cpuPtr, "%d%s%lf%lf%lf%lf", &tempo, codice_cpu, &potenza, &temperatura, &processi, &memoria);
        //x = 1 + rand() % 40;
        //inserisci_in_albero_bin_ric(&radice, x, tempo, codice_cpu, potenza, temperatura, processi, memoria);
        //printf("%d\n", inserito);
        //fscanf(cpuPtr, "%d%s%lf%lf%lf%lf", &(radice->tempo), (radice->codice_cpu), &(radice->potenza), &(radice->temperatura), &(radice->processi), &(radice->memoria));
        
        while(!feof(cpuPtr))
        {
            //printf("%-10d%-13s%-15.2f%-15.2f%-15.2f%-15.2f\n", radice->tempo, radice->codice_cpu, radice->potenza, radice->temperatura, radice->processi, radice->memoria);
            //tempo = 0;
            //codice_cpu = {0};
            //potenza = 0;
            //temperatura = 0;
            //processi = 0;
            //memoria = 0;
            fscanf(cpuPtr, "%d%s%lf%lf%lf%lf", &tempo, codice_cpu, &potenza, &temperatura, &processi, &memoria);
            if(feof(cpuPtr))
                printf("Inserimento completato\n");
            else
            {
                x += 1;
                inserisci_in_albero_bin_ric(&radice, x, tempo, codice_cpu, potenza, temperatura, processi, memoria);
            }
            /*if(inserito != 1)
            {
                while(inserito != 1)
                {
                    x = 1 + rand() % 40;
                    inserito = inserisci_in_albero_bin_ric(&radice, x, tempo, codice_cpu, potenza, temperatura, processi, memoria);
                }
            }*/
            //printf("%d\n", inserito);
            //printf("%-10d%-13s%-15.2f%-15.2f%-15.2f%-15.2f\n", radice->tempo, radice->nome_cpu->codice_cpu, radice->potenza, radice->temperatura, radice->processi, radice->memoria);
            //fscanf(cpuPtr, "%d%s%lf%lf%lf%lf", &tempo, codice_cpu, &potenza, &temperatura, &processi, &memoria);
        }
        fclose(cpuPtr);
    }
    
    //printf("Digitare il codice della CPU:\n");
    //scanf("%s", codice_ricerca);
    //printf("%s", codice_cpu);
    visita_albero_bin_ant(radice, codice_ricerca);
    
    return 0;
}

int inserisci_in_albero_bin_ric(nodo_albero_bin_t **radice_p, int chiave, int tempo, char codice_cpu[7], double potenza, double temperatura, double processi, double memoria)
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
        //nuovo_p->nome_cpu = (elem_albero_bin_t *)malloc(sizeof(elem_albero_bin_t));
        //nuovo_p->nome_cpu->chiave = chiave;
        nuovo_p->chiave = chiave;
        nuovo_p->tempo = tempo;
        strcpy(nuovo_p->codice_cpu, codice_cpu);
        nuovo_p->potenza = potenza;
        nuovo_p->temperatura = temperatura;
        nuovo_p->processi = processi;
        nuovo_p->memoria = memoria;
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

void cerca_in_albero_bin_ric(nodo_albero_bin_t *radice_p, int chiave)
{
    nodo_albero_bin_t *nodo_p;
    
    for (nodo_p = radice_p;
         ((nodo_p != NULL) && (nodo_p->chiave != chiave));
         nodo_p = (chiave < nodo_p->chiave)?
                    nodo_p->sx_p:
                    nodo_p->dx_p);
}

void visita_albero_bin_ant(nodo_albero_bin_t *nodo_p, char codice_ricerca[7])
{
    //int confronto;
    
    /*if(nodo_p != NULL)
    {
        confronto = strcmp(nodo_p->codice_cpu, codice_ricerca);
        if(confronto == confronto)
        {
            printf("%-10d%-13s%-15.2f%-15.2f%-15.2f%-15.2f\n", nodo_p->tempo, nodo_p->codice_cpu, nodo_p->potenza, nodo_p->temperatura, nodo_p->processi, nodo_p->memoria);
        }
        visita_albero_bin_ant(nodo_p->sx_p, codice_ricerca);
        visita_albero_bin_ant(nodo_p->dx_p, codice_ricerca);
    }*/
    if(nodo_p != NULL)
    {
        //printf("%-10d%-13s%-15.2f%-15.2f%-15.2f%-15.2f\n", nodo_p->tempo, nodo_p->codice_cpu, nodo_p->potenza, nodo_p->temperatura, nodo_p->processi, nodo_p->memoria);
        visita_albero_bin_ant(nodo_p->sx_p, codice_ricerca);
        //printf("%-10d%-13s%-15.2f%-15.2f%-15.2f%-15.2f\n", nodo_p->tempo, nodo_p->codice_cpu, nodo_p->potenza, nodo_p->temperatura, nodo_p->processi, nodo_p->memoria);
        visita_albero_bin_ant(nodo_p->dx_p, codice_ricerca);
        printf("%-10d%-13s%-15.2f%-15.2f%-15.2f%-15.2f\n", nodo_p->tempo, nodo_p->codice_cpu, nodo_p->potenza, nodo_p->temperatura, nodo_p->processi, nodo_p->memoria);
    }
}
