/*
//  main.c
//  pure_adj_list_dijkstra
//
//  Created by Valerio Freschi on 12/03/2018.
//  Copyright © 2018 Valerio Freschi. All rights reserved.
/*/
/*
 *
 *  Dijkstra algorithm
 *  The graph is represented as an adjacency list
 *  and the priority queue is an array
 *  (VF, May 2018)
 **
 ** added parser from file (VF, April 2020)
 */


#include <stdlib.h>
#include <stdio.h>

#define MAX 100
#define INFINITO -1

/*
 *  data structures declarations
 */
typedef enum {bianco, grigio, nero} colore_t;


typedef struct vertice_grafo
{
    int                  valore;
    struct vertice_grafo *vertice_succ_p;
    struct arco_grafo    *lista_archi_p;
    double               distanza_min;
    struct vertice_grafo *padre_p;
} vertice_grafo_t;


typedef struct arco_grafo
{
    double               peso;               /* presente in caso di grafo pesato */
    struct vertice_grafo *vertice_adiac_p;
    struct arco_grafo    *arco_succ_p;
} arco_grafo_t;


/*
 * function declarations
 */
vertice_grafo_t *acquisisci_grafo(int *n, FILE *fp);
vertice_grafo_t *cerca_in_lista(vertice_grafo_t *testa_p, int valore);
vertice_grafo_t *estrai_min(vertice_grafo_t *PQ[], int n_el_in_pq);
void inizializza(vertice_grafo_t *grafo_p, vertice_grafo_t *sorgente_p);


/* * main function */

int main(int argc, char **argv) {
    int  n, sorgente, i, n_el_in_pq;
    vertice_grafo_t *grafo_p, *vertice_p, *sorgente_p;
    arco_grafo_t *arco_p;
    vertice_grafo_t *PQ[MAX]; /*coda con priorità implementata (simulata) tramite array*/
    FILE *INFILE;
    //char *fname;
    
    /*if(argc < 2) {
        printf("USO: dijkstra_graph_from_file <file> \n");
        exit(1);
    }*/
    //fname = argv[1];
    if (!(INFILE = fopen("graph.txt","r"))) {
        printf("ERROR: errore apertura file %s\n", "graph.txt");
        exit(-1);
    }
    printf("Lettura input file %s caricamento dati...\n", "graph.txt");
    grafo_p = acquisisci_grafo(&n,INFILE);
    /* stampa liste primaria e secondaria */
    for (vertice_p = grafo_p;(vertice_p!=NULL);vertice_p = vertice_p->vertice_succ_p){
        printf("Lista di adiacenza del vertice %d:\n",vertice_p->valore);
        for (arco_p = vertice_p->lista_archi_p; (arco_p!= NULL); arco_p = arco_p->arco_succ_p)
            printf("%d , peso = %f\n",arco_p->vertice_adiac_p->valore, arco_p->peso);
        printf("\n");
    }
    
    printf("Vertice sorgente: ");
    scanf("%d", &sorgente);
    for (vertice_p = grafo_p; vertice_p != NULL; vertice_p = vertice_p->vertice_succ_p) {
        if (vertice_p->valore == sorgente)
            sorgente_p = vertice_p;
    }
    
    n_el_in_pq = n;
    i = 0;
    printf("Numero vertici = %d\n",n_el_in_pq);
    printf("Inizializza\n");
    inizializza(grafo_p,sorgente_p);
    for (vertice_p=grafo_p; (vertice_p!=NULL); vertice_p=vertice_p->vertice_succ_p){
        PQ[i] =  vertice_p;
        i++;
    }
    printf("...calcola percorsi brevi...\n");
    while (n_el_in_pq > 0) {
        vertice_p = estrai_min(PQ,n_el_in_pq);
        printf("Estratto vertice %d con dmin = %f\n",vertice_p->valore,vertice_p->distanza_min);
        /*scansione della lista secondaria per esplorare l'insieme di adiacenza del vertice appena estratto dalla coda e rilassamento degli archi */
        for (arco_p = vertice_p->lista_archi_p; (arco_p!=NULL); arco_p = arco_p->arco_succ_p) {
            if (arco_p->vertice_adiac_p->distanza_min== INFINITO || arco_p->vertice_adiac_p->distanza_min > vertice_p->distanza_min + arco_p->peso){
                arco_p->vertice_adiac_p->padre_p = vertice_p;
                arco_p->vertice_adiac_p->distanza_min = vertice_p->distanza_min + arco_p->peso;
            }
        }
        n_el_in_pq--;
    }
    /* stampa albero percorsi piu' brevi*/
    printf("\n Albero dei percorsi più brevi:\n");
    for (vertice_p = grafo_p; vertice_p!=NULL; vertice_p = vertice_p->vertice_succ_p){
        printf("vertice %d: \n",vertice_p->valore);
        if (vertice_p->padre_p!=NULL){
            printf("padre =  %d, ",vertice_p->padre_p->valore);
            printf("distanza =  %f\n",vertice_p->distanza_min);
        }
    }
    return(0);
}



/* function definitions */

vertice_grafo_t *acquisisci_grafo(int *nvg, FILE *fin){
    int n, nV, i, src, dest;
    double peso;
    vertice_grafo_t *nuovov_p, *grafo_p, *vertice_p;
    arco_grafo_t *arco_p, *nuovoa_p;
    
    grafo_p = NULL;
    arco_p = NULL;
    fscanf(fin,"%d\n",&n);
    *nvg = n;
    printf("Nr. of nodes = %d\n",*nvg);
    /* costruiamo prima la lista primaria, senza liste secondarie */
    for (i=n; i>0; i--) {
        nuovov_p = (vertice_grafo_t *)malloc(sizeof(vertice_grafo_t));
        nuovov_p->valore = i;
        nuovov_p->lista_archi_p = NULL;
        nuovov_p->vertice_succ_p = grafo_p;
        grafo_p = nuovov_p;
    }
    
    vertice_p = grafo_p;
    while (fscanf(fin, "%d", &nV) != EOF) {
        arco_p = NULL;
        for (i=0; i<nV; i++) {
            fscanf(fin, "%d %d %lf\n", &src, &dest, &peso);
            printf("src = %d, dest = %d\n",src, dest);
            vertice_p = cerca_in_lista(grafo_p,src); /*cerca nella lista primaria il vertice con label src*/
            if (vertice_p!=NULL)
                printf("trovato vertice %d\n",vertice_p->valore);
            nuovoa_p = malloc(sizeof(arco_grafo_t));
            nuovoa_p->vertice_adiac_p = cerca_in_lista(grafo_p,dest); /*cerca nella lista primaria il vertice con label dest*/
            if (nuovoa_p->vertice_adiac_p!=NULL)
                printf("trovato vertice %d\n",nuovoa_p->vertice_adiac_p->valore);
            nuovoa_p->arco_succ_p = arco_p;
            arco_p = nuovoa_p;
            arco_p->peso = peso;
            vertice_p->lista_archi_p = arco_p;
        }
        vertice_p = vertice_p->vertice_succ_p;
    }
    fclose(fin);
    
    return(grafo_p);
}



vertice_grafo_t *cerca_in_lista(vertice_grafo_t *testa_p,
                                int valore)
{
    vertice_grafo_t *elem_p;
    for (elem_p = testa_p;
         ((elem_p != NULL) && (elem_p->valore != valore));
         elem_p = elem_p->vertice_succ_p);
    return(elem_p);
}

void inizializza(vertice_grafo_t *grafo_p, vertice_grafo_t *sorgente_p) {
    vertice_grafo_t *vertice_p;
    
    for (vertice_p = grafo_p; (vertice_p != NULL); vertice_p = vertice_p->vertice_succ_p)
    {
        vertice_p->distanza_min = INFINITO;
        vertice_p->padre_p = NULL;
        printf("Vertice = %d\n",vertice_p->valore);
    }
    sorgente_p->distanza_min = 0.0;
    return;
}

vertice_grafo_t *estrai_min(vertice_grafo_t *PQ[], int n_el_in_pq) {
    int i, minpos;
    double min;
    vertice_grafo_t *tmp;
    
    min = PQ[0]->distanza_min;
    minpos = 0;
    for (i=0; i < n_el_in_pq; i++) {
        if ((PQ[i]->distanza_min>0 && PQ[i]->distanza_min<min)||(min == INFINITO)){
            min = PQ[i]->distanza_min;
            minpos = i;
        }
    }
    /* il nr di elementi nella coda PQ diminuisce di 1 ad ogni invocazione
     quindi viene spostato il minimo in fondo al vettore in posizione n_in_pq-1 */
    tmp = PQ[n_el_in_pq-1];
    PQ[n_el_in_pq-1] = PQ[minpos];
    PQ[minpos] = tmp;
  
    return(PQ[n_el_in_pq-1]);
}

