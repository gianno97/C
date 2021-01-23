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

int main(int argc, char **argv)
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

    sent_p = NULL;

    srand(time(NULL)); /* inizializza il generatore */

    printf("Gli elementi dell'albero sono:\n");

    for(i = 0; i < num_elem_albero; i++)
    {
        x = 1 + rand() % 40; /*genera un numero casuale tra 1 e 40*/
        inserisci_in_albero_bin_ric_rn(sent_p, x);
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

    return 0;
}
