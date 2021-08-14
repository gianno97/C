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
    char                  str_ins[4];
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

vertice_grafo_t *acquisisci_grafo(FILE *);
vertice_grafo_t *cerca_in_lista(vertice_grafo_t *,
                                char str_ins[]);
vertice_grafo_t *avvia_ord_top_grafo(vertice_grafo_t *);
void ordina_top_grafo(vertice_grafo_t *,
                      vertice_grafo_t **);
int controlla_lista(vertice_grafo_t *,
                    char str_ins[]);
void stampa_ord_top(vertice_grafo_t *grafo_p);

/******************************/
/* definizione delle funzioni */
/******************************/

/* definizione della funzione main */
int main(void)
{
    /* dichiarazione delle variabili locali alla funzione */
    vertice_grafo_t *grafo_p; /* testa della lista primaria del grafo */
    FILE            *fiPtr;   /* variabile puntatore a file */
    
    /* controllare se il file può essere aperto in lettura */
    if (!(fiPtr = fopen("grafo.txt", "r")))
        printf("ERRORE: errore nell'apertura del file di input %s\n",
               "grafo.txt");
    else
    {
        /* acquisire il grafo */
        grafo_p = acquisisci_grafo(fiPtr);
        /* avviare l'ordinamento topologico sul grafo */
        grafo_p = avvia_ord_top_grafo(grafo_p);
        /* stampare il grafo */
        stampa_ord_top(grafo_p);
    }
    return (0);
}

/* definizione della funzione per acquisire il grafo */
vertice_grafo_t *acquisisci_grafo(FILE *fiPtr)
{
    int              num_vert_grafo,  /* variabile utilizzata per acquisire il numero di vertici del grafo */
                     num_archi_usc,   /* variabile utilizzata per acquisire il numero di archi uscenti da un 
                                         certo vertice durante la creazione della lista di adiacenza */
                     i,               /* variabile utilizzata all'interno del ciclo for*/
                     val_rit,         /* variabile utilizzata per non lasciare scoperto il valore di ritorno delle fscanf */
                     inserito;        /* variabile utilizzata per comprendere se un vertice è già presente o no
                                         all'interno della lista primaria */
    vertice_grafo_t *vertice_p;       /* variabile utilizzata per muoversi all'interno della lista primaria */
                                      /* durante la creazione della lista di adiacenza */
    vertice_grafo_t *nuovov_p,        /* variabile utilizzata per la creazione di un nuovo vertice */
                    *grafo_p;         /* variabile utilizzata per identificare la testa della lista primaria di vertici */
    arco_grafo_t    *arco_p,          /* variabile utilizzata per la creazione della lista di adiacenza */
                    *nuovoa_p;        /* variabile utilizzata per allocare il nuovo arco */
    char             str_ins[4];      /* stringa utilizzata per memorizzare la stringa dell'insegnamento */
    char             origine[4];      /* stringa utilizzata per cercare il vertice di partenza */
    char             destinazione[4]; /* stringa utilizzata per cercare il vertice di destinazione */ 
    
    printf("Acquisizione del file di testo %s contenente le indicazioni delle propedeuticita'.\n",
           "grafo.txt");
    printf("Inserimento dei dati all'interno di una struttura dati di tipo grafo...\n");
    grafo_p = NULL;
    arco_p = NULL;
    
    /* creazione della lista primaria dei vertici */
    while(!feof(fiPtr))
    {
        val_rit = fscanf(fiPtr,
                         "%s\n",
                         str_ins);
        /* controllare che ciò che è stato acquisito dal file non sia un numero */
        if(!isdigit(str_ins[0]) && val_rit == 1)
        {
            /* controllare che la stringa identificativa dell'insegnamento non sia */
            /* già presente all'interno della lista primaria dei vertici */
            inserito = controlla_lista(grafo_p,
                                       str_ins);
            /* inserire il nuovo insegnamento all'interno della lista primaria */
            if(inserito == 1)
            {
                nuovov_p = (vertice_grafo_t *)malloc(sizeof(vertice_grafo_t));
                strcpy(nuovov_p->str_ins,
                       str_ins);
                nuovov_p->lista_archi_p = NULL;
                nuovov_p->vertice_succ_p = grafo_p;
                grafo_p = nuovov_p;
            }
        }
    }
    /* riportare il puntatore del file all'inizio del file */
    rewind(fiPtr);
    val_rit = fscanf(fiPtr,
                      "%d\n",
                      &num_vert_grafo);
    
    vertice_p = grafo_p;
    /* creazione della lista di adiacenza del grafo */
    while (fscanf(fiPtr, "%s%d", str_ins, &num_archi_usc) != EOF) {
        arco_p = NULL;
        for (i = 0;
             i < num_archi_usc;
             i++)
        {
            val_rit = fscanf(fiPtr,
                             "%s%s",
                             origine,
                             destinazione);
            vertice_p = cerca_in_lista(grafo_p,
                                       origine);
            nuovoa_p = malloc(sizeof(arco_grafo_t));
            nuovoa_p->vertice_adiac_p = cerca_in_lista(grafo_p,
                                                       destinazione);
            nuovoa_p->arco_succ_p = arco_p;
            arco_p = nuovoa_p;
            vertice_p->lista_archi_p = arco_p;
        }
        vertice_p = vertice_p->vertice_succ_p;
    }
    fclose(fiPtr);
    
    printf("Dati inseriti.\n");
    printf("Grafo con %d vertici.\n",
           num_vert_grafo);
    return(grafo_p);
}

/* definizione della funzione per controllare se un vertice è già presente */ 
/* all'interno della lista primaria */
int controlla_lista(vertice_grafo_t *testa_p,
                    char             str_ins[4])
{
    vertice_grafo_t *elem_p;
    int              inserito;
    
    for (elem_p = testa_p;
         ((elem_p != NULL) && (strcmp(elem_p->str_ins, str_ins) != 0));
         elem_p = elem_p->vertice_succ_p);
    if ((elem_p != NULL) && (strcmp(elem_p->str_ins, str_ins) == 0))
        inserito = 0;
    else
        inserito = 1;
    
    return(inserito);
}

/* definizione della funzione per cercare un vertice all'interno della lista primaria */
vertice_grafo_t *cerca_in_lista(vertice_grafo_t *testa_p,
                                char             str_ins[4])
{
    vertice_grafo_t *elem_p;
    
    for (elem_p = testa_p;
         ((elem_p != NULL) && (strcmp(elem_p->str_ins, str_ins) != 0));
         elem_p = elem_p->vertice_succ_p);
         
    return(elem_p);
}

/* definizione della funzione per lanciare l'ordinamento topologico del grafo */
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

/* definizione della funzione per ordinare il grafo in ordine topologico */
void ordina_top_grafo(vertice_grafo_t  *vertice_p,
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
    strcpy(nuovo_elem_p->str_ins,
           vertice_p->str_ins);
    nuovo_elem_p->lista_archi_p = vertice_p->lista_archi_p;
    nuovo_elem_p->vertice_succ_p = *testa_p;
    *testa_p = nuovo_elem_p;
}

/* definizione della funzione per stampare a schermo la lista primaria dei vertici */ 
/* ordinati topologicamente */
void stampa_ord_top(vertice_grafo_t *grafo_p)
{
    vertice_grafo_t *vertice_p_ord_top;
    
    printf("Stampa dell'elenco degli insegnamenti ordinati topologicamente:\n");
    for (vertice_p_ord_top = grafo_p;
         (vertice_p_ord_top != NULL);
         vertice_p_ord_top = vertice_p_ord_top->vertice_succ_p)
        printf("%s\n",
               vertice_p_ord_top->str_ins);
}
