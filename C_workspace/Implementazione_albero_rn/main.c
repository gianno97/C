#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <float.h>
#include <time.h>

typedef enum {rosso, nero} colore_t;

typedef struct nodo_albero_bin_rn
{
    int valore;
    colore_t colore;
    struct nodo_albero_bin_rn *sx_p, *dx_p, *padre_p;
} nodo_albero_bin_rn_t;

int inserisci_in_albero_bin_ric_rn(nodo_albero_bin_rn_t *sent_p, int valore);
nodo_albero_bin_rn_t *cerca_in_albero_bin_ric_rn(nodo_albero_bin_rn_t *sent_p, int valore);
void ripristina_ins_albero_bin_ric_rn(nodo_albero_bin_rn_t *sent_p, nodo_albero_bin_rn_t *nodo_p);
void ruota_sx(nodo_albero_bin_rn_t *sent_p, nodo_albero_bin_rn_t *x_p);
void ruota_dx(nodo_albero_bin_rn_t *sent_p, nodo_albero_bin_rn_t *y_p);

int main(void)
{
    /* dichiarazione delle variabili locali alla funzione */
    int i,
        x,
        y,
        esito_lettura,
        num_elem_albero;
    char carattere_rimosso;
    nodo_albero_bin_rn_t *sent_p,
                         *esito;
    int inserito;

    do
    {
        printf("Digita il numero di elementi da inserire nell'albero:" );
        esito_lettura = scanf("%d",
                              &num_elem_albero);
        if(esito_lettura != 1 || num_elem_albero < 0)
        {
            printf("input non accettabile!");
            do
                carattere_rimosso = getchar();
            while(carattere_rimosso != '\n');
        }
    }
    while(esito_lettura != 1 || num_elem_albero < 0);

    sent_p = (nodo_albero_bin_rn_t *)malloc(sizeof(nodo_albero_bin_rn_t));
    //sent_p = NULL;
    //padre_p = NULL;
    sent_p->padre_p = NULL;
    sent_p->sx_p = NULL;
    sent_p->dx_p = NULL;
    sent_p->colore = nero;
    //sent_p->valore = 0;
    
    srand(time(NULL)); /* inizializza il generatore */

    printf("Gli elementi dell'albero sono:\n");

    for(i = 0; i < num_elem_albero; i++)
    {
        x = 1 + rand() % 40; /*genera un numero casuale tra 1 e 40*/
        inserito = inserisci_in_albero_bin_ric_rn(sent_p, x);
        printf("%d,", x); 
    }
    printf("\n");

    do
    {
        printf("Digita l'elemento da cercare nell'albero: ");
        esito_lettura = scanf("%d",
                              &y);
        if(esito_lettura != 1 || y < 0)
        {
            printf("input non accettabile!");
            do
                carattere_rimosso = getchar();
            while(carattere_rimosso != '\n');
        }
    }
    while(esito_lettura != 1 || y < 0);

    esito = cerca_in_albero_bin_ric_rn(sent_p, y);
    
    if(esito != NULL)
        printf("Elemento presente nell'albero!\n");
    else
        printf("Elemento non presente nell'albero!\n");

    return (0);
}

void ruota_sx(nodo_albero_bin_rn_t *sent_p, nodo_albero_bin_rn_t *x_p)
{
    nodo_albero_bin_rn_t *y_p;
    
    y_p = x_p->dx_p;
    x_p->dx_p = y_p->sx_p;
    y_p->sx_p->padre_p = x_p;
    y_p->padre_p = x_p->padre_p;
    
    if(x_p == sent_p->sx_p)
        sent_p->sx_p = sent_p->dx_p = y_p;
    else
        if(x_p == x_p->padre_p->sx_p)
            x_p->padre_p->sx_p = y_p;
        else
            x_p->padre_p->dx_p = y_p;

    y_p->sx_p = x_p;
    x_p->padre_p = y_p;
}

void ruota_dx(nodo_albero_bin_rn_t *sent_p, nodo_albero_bin_rn_t *y_p)
{
    nodo_albero_bin_rn_t *x_p;
    
    x_p = y_p->sx_p;
    y_p->sx_p = x_p->dx_p;
    x_p->dx_p->padre_p = y_p;
    x_p->padre_p = y_p->padre_p;
    
    if(y_p == sent_p->dx_p)
        sent_p->dx_p = sent_p->sx_p = x_p;
    else
        if(y_p == y_p->padre_p->dx_p)
            y_p->padre_p->dx_p = x_p;
        else
            y_p->padre_p->sx_p = x_p;
            
    x_p->dx_p = y_p;
    y_p->padre_p = x_p;
}

nodo_albero_bin_rn_t *cerca_in_albero_bin_ric_rn(nodo_albero_bin_rn_t *sent_p, int valore)
{
    nodo_albero_bin_rn_t *nodo_p;
    
    for(nodo_p = sent_p->sx_p;
         ((nodo_p != sent_p) && (nodo_p->valore != valore));
         nodo_p = (valore < nodo_p->valore)?
                    nodo_p->sx_p:
                    nodo_p->dx_p);
    return(nodo_p);
}

int inserisci_in_albero_bin_ric_rn(nodo_albero_bin_rn_t *sent_p, int valore)
{
    int                  inserito;
    nodo_albero_bin_rn_t *nodo_p,
                         *padre_p,
                         *nuovo_p;
    
    nodo_p = (nodo_albero_bin_rn_t *)malloc(sizeof(nodo_albero_bin_rn_t));
    padre_p = (nodo_albero_bin_rn_t *)malloc(sizeof(nodo_albero_bin_rn_t));
    sent_p = (nodo_albero_bin_rn_t *)malloc(sizeof(nodo_albero_bin_rn_t));
    nodo_p->valore = valore;
    
    for(nodo_p = sent_p->sx_p, padre_p = sent_p;
        ((nodo_p != sent_p) && (nodo_p->valore != valore));
        padre_p = nodo_p, nodo_p = (valore < nodo_p->valore)?
                                     nodo_p->sx_p:
                                     nodo_p->dx_p);
    if(nodo_p != sent_p)
        inserito = 0;
    else
    {
        inserito = 1;
        nuovo_p = (nodo_albero_bin_rn_t *)malloc(sizeof(nodo_albero_bin_rn_t));
        nuovo_p->valore = valore;
        nuovo_p->colore = rosso;
        nuovo_p->sx_p = nuovo_p->dx_p = sent_p;
        nuovo_p->padre_p = padre_p;
        if(padre_p == sent_p)
            sent_p->sx_p = sent_p->dx_p = nuovo_p;
        else
            if(valore < padre_p->valore)
                padre_p->sx_p = nuovo_p;
            else
                padre_p->dx_p = nuovo_p;
        ripristina_ins_albero_bin_ric_rn(sent_p, nuovo_p);
    }
    return(inserito);
}

void ripristina_ins_albero_bin_ric_rn(nodo_albero_bin_rn_t *sent_p, nodo_albero_bin_rn_t *nodo_p)
{
    nodo_albero_bin_rn_t *zio_p;
    
    while(nodo_p->padre_p->colore == rosso)
        if(nodo_p->padre_p == nodo_p->padre_p->padre_p->sx_p)
        {
            zio_p = nodo_p->padre_p->padre_p->dx_p;
            if(zio_p->colore == rosso)
            {
                nodo_p->padre_p->colore = nero;
                zio_p->colore = nero;
                nodo_p->padre_p->padre_p->colore = rosso;
                nodo_p = nodo_p->padre_p->padre_p;
            }
            else
            {
                if(nodo_p == nodo_p->padre_p->dx_p)
                {
                    nodo_p = nodo_p->padre_p;
                    ruota_sx(sent_p, nodo_p);
                }
                nodo_p->padre_p->colore = nero;
                nodo_p->padre_p->padre_p->colore = rosso;
                ruota_dx(sent_p, nodo_p->padre_p->padre_p);
            }
        }
        else
        {
            zio_p = nodo_p->padre_p->padre_p->sx_p;
            if(zio_p->colore == rosso)
            {
                nodo_p->padre_p->colore = nero;
                zio_p->colore = nero;
                nodo_p->padre_p->padre_p->colore = rosso;
                nodo_p = nodo_p->padre_p->padre_p;
            }
            else
            {
                if(nodo_p == nodo_p->padre_p->sx_p)
                {
                    //nodo_p = nodo_p->padre_p;
                    nodo_p->padre_p->colore = nero;
                    nodo_p->padre_p->padre_p->colore = rosso;
                    ruota_dx(sent_p, nodo_p->padre_p->padre_p);
                    //ruota_sx(sent_p, nodo_p);
                }
                //nodo_p->padre_p->colore = nero;
                //nodo_p->padre_p->padre_p->colore = rosso;
                //ruota_dx(sent_p, nodo_p->padre_p->padre_p);
                nodo_p = nodo_p->padre_p;
                ruota_sx(sent_p, nodo_p);
            }
        }
    sent_p->sx_p->colore = nero;
}
