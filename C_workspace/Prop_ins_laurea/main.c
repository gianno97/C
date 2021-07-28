#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*data structures declarations*/

typedef enum {bianco, grigio, nero} colore_t;

typedef struct vertice_grafo
{
    int valore;
    char nome[3];
    struct vertice_grafo *vertice_succ_p;
    struct arco_grafo *lista_archi_p;
    colore_t colore;
    int distanza, inizio, fine;
    struct vertice_grafo *padre_p;
} vertice_grafo_t;

typedef struct arco_grafo
{
    struct vertice_grafo *vertice_adiac_p;
    struct arco_grafo    *arco_succ_p;
} arco_grafo_t;

typedef struct elem_lista {
    vertice_grafo_t *valore;
    struct elem_lista *succ_p;
} elem_lista_t;

/*
* function declarations
*/

arco_grafo_t *acquisisci_lista(vertice_grafo_t *grafo_p);
vertice_grafo_t *acquisisci_grafo(int *n, FILE *fp);
vertice_grafo_t *cerca_in_lista(vertice_grafo_t *testa_p,
                                char nome[3]);
vertice_grafo_t *avvia_ord_top_grafo(vertice_grafo_t *grafo_p);
void ordina_top_grafo(vertice_grafo_t *vertice_p,
                      vertice_grafo_t **testa_p);

int main(int argc, char **argv)
{
    int n;
    vertice_grafo_t *grafo_p, *vertice_p;
    arco_grafo_t *arco_p;
    FILE *INFILE;
    
    if (!(INFILE = fopen("graph.txt","r"))) {
        printf("ERROR: error opening input file %s\n", "graph.txt");
        exit(-1);
    }
    printf("Reading input file %s and loading data...\n", "graph.txt");
    grafo_p = acquisisci_grafo(&n,INFILE);
    printf("... done.\n******************\n");
    printf("Graph with %d vertices\n",n);
    /* stampa liste primaria e secondaria */
    for (vertice_p = grafo_p;(vertice_p!=NULL);vertice_p = vertice_p->vertice_succ_p){
        printf("Adjacency list of vertex %s:\n",vertice_p->nome);
        for (arco_p = vertice_p->lista_archi_p; (arco_p!= NULL); arco_p = arco_p->arco_succ_p)
            printf("%s ,",arco_p->vertice_adiac_p->nome);
        printf("\n");
    }
    
    printf("Traversal of the graph...\n");
    printf(".. and print tree of traversal\n");
    return(0);
}

vertice_grafo_t *acquisisci_grafo(int *nvg, FILE *fin){
    int n, nV, i;
    //int src, dest;
    vertice_grafo_t *nuovov_p, *grafo_p, *vertice_p, *elem_p;
    arco_grafo_t *arco_p, *nuovoa_p;
    char nom[3];
    char nome[3];
    char source[3];
    char destination[3];

    grafo_p = NULL;
    arco_p = NULL;
    fscanf(fin,"%d\n",&n);
    *nvg = n;
    printf("Nr. of nodes = %d\n",*nvg);
    
    /* costruiamo prima la lista primaria, senza liste secondarie */
    fscanf(fin, "%s\n", nom);
    nuovov_p = (vertice_grafo_t *)malloc(sizeof(vertice_grafo_t));
    strcpy(nuovov_p->nome, nom);
    nuovov_p->lista_archi_p = NULL;
    nuovov_p->vertice_succ_p = grafo_p;
    grafo_p = nuovov_p;
    
    elem_p = grafo_p;
    while(!feof(fin)){
        fscanf(fin, "%s\n", nom);
        elem_p = cerca_in_lista(grafo_p, nom);
        printf("ECCOMI: %s  %s\n", nom, elem_p->nome);
        if(elem_p->nome != nom)
        {
            nuovov_p = (vertice_grafo_t *)malloc(sizeof(vertice_grafo_t));
            strcpy(nuovov_p->nome, nom);
            nuovov_p->lista_archi_p = NULL;
            nuovov_p->vertice_succ_p = grafo_p;
            grafo_p = nuovov_p;
        }
    }
    
    /*
    vertice_p = grafo_p;
    while (fscanf(fin, "%d", &nV) != EOF) {
        arco_p = NULL;
        for (i=0; i<nV; i++) {
            fscanf(fin, "%d %d\n", &src, &dest);
            printf("src = %d, dest = %d\n",src, dest);
            vertice_p = cerca_in_lista(grafo_p,src);
            if (vertice_p!=NULL)
                printf("found vertex %d\n",vertice_p->valore);
            nuovoa_p = malloc(sizeof(arco_grafo_t));
            nuovoa_p->vertice_adiac_p = cerca_in_lista(grafo_p,dest);
            if (nuovoa_p->vertice_adiac_p!=NULL)
                printf("found vertex %d\n",nuovoa_p->vertice_adiac_p->valore);
            nuovoa_p->arco_succ_p = arco_p;
            arco_p = nuovoa_p;
            vertice_p->lista_archi_p = arco_p;
        }
        vertice_p = vertice_p->vertice_succ_p;
    }
    fclose(fin);
    */
    
    vertice_p = grafo_p;
    while (fscanf(fin, "%s%d", nome, &nV) != EOF) {
        arco_p = NULL;
        for (i=0; i<nV; i++) {
            fscanf(fin, "%s %s\n", source, destination);
            printf("source = %s, destination = %s\n", source, destination);
            vertice_p = cerca_in_lista(grafo_p, source); /*cerca nella lista primaria il vertice con label src*/
            if (vertice_p!=NULL)
                printf("found vertex %s\n", vertice_p->nome);
            nuovoa_p = malloc(sizeof(arco_grafo_t));
            nuovoa_p->vertice_adiac_p = cerca_in_lista(grafo_p, destination); /*cerca nella lista primaria il vertice con label dest*/
            if (nuovoa_p->vertice_adiac_p!=NULL)
                printf("found vertex %s\n",nuovoa_p->vertice_adiac_p->nome);
            nuovoa_p->arco_succ_p = arco_p;
            arco_p = nuovoa_p;
            vertice_p->lista_archi_p = arco_p;
        }
        vertice_p = vertice_p->vertice_succ_p;
    }
    fclose(fin);

    return(grafo_p);
}

vertice_grafo_t *cerca_in_lista(vertice_grafo_t *testa_p,
                                char nome[3])
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
    nuovo_elem_p->valore = vertice_p->valore;
    nuovo_elem_p->lista_archi_p = vertice_p->lista_archi_p;
    nuovo_elem_p->vertice_succ_p = *testa_p;
    *testa_p = nuovo_elem_p;
}
