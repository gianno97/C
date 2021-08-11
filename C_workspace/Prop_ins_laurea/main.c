/*********************************************************/
/* programma per la gestione delle propedeuticità degli **/ 
/* insegnamenti di un corso di laurea ********************/
/*********************************************************/

/*****************************/
/* inclusione delle librerie */
/*****************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*************************************************/
/* definizione della variabile enumerativa *******/
/*************************************************/

typedef enum {bianco, grigio, nero} colore_t;

/*************************************************/
/* definizione delle variabili di tipo struttura */
/*************************************************/

typedef struct vertice_grafo
{
    char                  nome[10];
    struct vertice_grafo *vertice_succ_p;
    struct arco_grafo    *lista_archi_p;
    colore_t              colore;
} vertice_grafo_t;

typedef struct arco_grafo
{
    struct vertice_grafo *vertice_adiac_p;
    struct arco_grafo    *arco_succ_p;
} arco_grafo_t;

/********************************/
/* dichiarazione delle funzioni */
/********************************/

vertice_grafo_t *acquisisci_grafo(int *,
                                  FILE *);
vertice_grafo_t *cerca_in_lista(vertice_grafo_t *,
                                char nome[]);
vertice_grafo_t *avvia_ord_top_grafo(vertice_grafo_t *);
void ordina_top_grafo(vertice_grafo_t *,
                      vertice_grafo_t **);
int controlla_lista(vertice_grafo_t *,
                    char nome[]);

/******************************/
/* definizione delle funzioni */
/******************************/

/* definizione della funzione main */
int main(int argc, char **argv)
{
    int              n;
    vertice_grafo_t *grafo_p,
                    *vertice_p_ord_top;
    FILE            *INFILE;
    
    if (!(INFILE = fopen("ciao.txt", "r")))
        printf("ERROR: error opening input file %s\n",
               "ciao.txt");
    else
    {
        printf("Reading input file %s and loading data...\n", "prova.txt");
        grafo_p = acquisisci_grafo(&n,INFILE);
        printf("... done.\n******************\n");
        printf("Graph with %d vertices\n",n);
    
        printf("Ordinamento topologico:\n");
        grafo_p = avvia_ord_top_grafo(grafo_p);
        for (vertice_p_ord_top = grafo_p; (vertice_p_ord_top != NULL); vertice_p_ord_top = vertice_p_ord_top->vertice_succ_p)
            printf("%s\n", vertice_p_ord_top->nome);
    }
    return(0);
}

vertice_grafo_t *acquisisci_grafo(int *nvg, FILE *fin){
    FILE            *fin_2;
    int              n,
                     nV,
                     i,
                     inserito;
    vertice_grafo_t *vertice_p;
    vertice_grafo_t *nuovov_p,
                    *grafo_p;
    arco_grafo_t    *arco_p,
                    *nuovoa_p;
    char             nom[10];
    char             nome[10];
    char             source[10];
    char             destination[10];
    
    grafo_p = NULL;
    arco_p = NULL;
    
    while(!feof(fin))
    {
        fscanf(fin, "%s\n", nom);
        if(!isdigit(nom[0]))
        {
            inserito = controlla_lista(grafo_p, nom);
            if(inserito == 1)
            {
                nuovov_p = (vertice_grafo_t *)malloc(sizeof(vertice_grafo_t));
                strcpy(nuovov_p->nome, nom);
                nuovov_p->lista_archi_p = NULL;
                nuovov_p->vertice_succ_p = grafo_p;
                grafo_p = nuovov_p;
            }
        }
    }
    fclose(fin);
    
    fin_2 = fopen("prova.txt","r");
    fscanf(fin_2,"%d\n",&n);
    *nvg = n;
    
    vertice_p = grafo_p;
    while (fscanf(fin_2, "%s%d", nome, &nV) != EOF) {
        arco_p = NULL;
        for (i=0; i<nV; i++) {
            fscanf(fin_2, "%s%s", source, destination);
            vertice_p = cerca_in_lista(grafo_p, source);
            nuovoa_p = malloc(sizeof(arco_grafo_t));
            nuovoa_p->vertice_adiac_p = cerca_in_lista(grafo_p, destination);
            nuovoa_p->arco_succ_p = arco_p;
            arco_p = nuovoa_p;
            vertice_p->lista_archi_p = arco_p;
        }
        vertice_p = vertice_p->vertice_succ_p;
    }
    fclose(fin_2);
    
    return(grafo_p);
}

int controlla_lista(vertice_grafo_t *testa_p,
                    char             nome[10])
{
    vertice_grafo_t *elem_p;
    int              inserito;
    
    for (elem_p = testa_p;
         ((elem_p != NULL) && (strcmp(elem_p->nome, nome) != 0));
         elem_p = elem_p->vertice_succ_p);
    if ((elem_p != NULL) && (strcmp(elem_p->nome, nome) == 0))
        inserito = 0;
    else
        inserito = 1;
    
    return(inserito);
}

vertice_grafo_t *cerca_in_lista(vertice_grafo_t *testa_p,
                                char nome[10])
{
    vertice_grafo_t *elem_p;
    for (elem_p = testa_p;
         ((elem_p != NULL) && (strcmp(elem_p->nome, nome) != 0));
         elem_p = elem_p->vertice_succ_p);
    return(elem_p);
}

vertice_grafo_t *avvia_ord_top_grafo(vertice_grafo_t *grafo_p)
{
    vertice_grafo_t *testa_p,
                    *vertice_p;

    for (vertice_p = grafo_p;
         (vertice_p != NULL);
         vertice_p = vertice_p->vertice_succ_p)
        vertice_p->colore = bianco;
    for (vertice_p = grafo_p, testa_p = NULL;
         (vertice_p != NULL);
         vertice_p = vertice_p->vertice_succ_p)
        if (vertice_p->colore == bianco)
            ordina_top_grafo(vertice_p,
                             &testa_p);
    return(testa_p);
}

void ordina_top_grafo(vertice_grafo_t *vertice_p,
                      vertice_grafo_t **testa_p)
{
    arco_grafo_t    *arco_p;
    vertice_grafo_t *nuovo_elem_p;

    vertice_p->colore = grigio;
    for (arco_p = vertice_p->lista_archi_p;
         (arco_p != NULL);
         arco_p = arco_p->arco_succ_p)
        if (arco_p->vertice_adiac_p->colore == bianco)
            ordina_top_grafo(arco_p->vertice_adiac_p,
                             testa_p);
    vertice_p->colore = nero;
    nuovo_elem_p = (vertice_grafo_t *)malloc(sizeof(vertice_grafo_t));
    strcpy(nuovo_elem_p->nome, vertice_p->nome);
    nuovo_elem_p->lista_archi_p = vertice_p->lista_archi_p;
    nuovo_elem_p->vertice_succ_p = *testa_p;
    *testa_p = nuovo_elem_p;
}