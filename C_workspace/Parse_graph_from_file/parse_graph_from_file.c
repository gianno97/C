/*
 *  Parser of graph from file to be used by
 *  BF and DF graph traversal algorithms
 *  The graph is represented as an adjacency list
**  
**
**  VF (2018, March)
**  Revision: April 2020 for UniUrb Blended learning platform
*/

#include <stdlib.h>
#include <stdio.h>

/*data structures declarations*/

typedef enum {bianco, grigio, nero} colore_t;


typedef struct vertice_grafo
{
    int valore;
    struct vertice_grafo *vertice_succ_p;
    struct arco_grafo *lista_archi_p;
    colore_t colore;
    int distanza, inizio, fine;
    struct vertice_grafo *padre_p;
} vertice_grafo_t;

typedef struct arco_grafo
{
    double               peso;               /* presente in caso di grafo pesato */
    struct vertice_grafo *vertice_adiac_p;
    struct arco_grafo    *arco_succ_p;
} arco_grafo_t;

/*
typedef struct elem_lista {
    vertice_grafo_t *valore;
    struct elem_lista *succ_p;
} elem_lista_t;
*/


/*
* function declarations
*/

//arco_grafo_t *acquisisci_lista(vertice_grafo_t *grafo_p);
vertice_grafo_t *acquisisci_grafo(int *n, FILE *fp);
vertice_grafo_t *cerca_in_lista(vertice_grafo_t *testa_p, int valore);



/*
 *  Main function
 */

int main(int argc, char **argv){
    int n;
    vertice_grafo_t *grafo_p, *vertice_p;
    arco_grafo_t *arco_p;
    FILE *INFILE;
    //char *fname;
    
    /*
    if(argc < 2) {
        printf("USAGE: parse_graph_from_file <file> \n");
        exit(-1);
    }
    */
    
    //fname = argv[1];
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
        printf("Adjacency list of vertex %d:\n",vertice_p->valore);
        for (arco_p = vertice_p->lista_archi_p; (arco_p!= NULL); arco_p = arco_p->arco_succ_p)
            printf("%d ,",arco_p->vertice_adiac_p->valore);
        printf("\n");
    }
    
    
    printf("Traversal of the graph...\n");
    printf(".. and print tree of traversal\n");
    return(0);
}


vertice_grafo_t *acquisisci_grafo(int *nvg, FILE *fin){
    int n, nV, i, src, dest;
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
            fscanf(fin, "%d %d\n", &src, &dest);
            printf("src = %d, dest = %d\n",src, dest);
            vertice_p = cerca_in_lista(grafo_p,src); /*cerca nella lista primaria il vertice con label src*/
            if (vertice_p!=NULL)
                printf("found vertex %d\n",vertice_p->valore);
            nuovoa_p = malloc(sizeof(arco_grafo_t));
            nuovoa_p->vertice_adiac_p = cerca_in_lista(grafo_p,dest); /*cerca nella lista primaria il vertice con label dest*/
            if (nuovoa_p->vertice_adiac_p!=NULL)
                printf("found vertex %d\n",nuovoa_p->vertice_adiac_p->valore);
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
                             int valore)
{
    vertice_grafo_t *elem_p;
    for (elem_p = testa_p;
         ((elem_p != NULL) && (elem_p->valore != valore));
         elem_p = elem_p->vertice_succ_p);
    return(elem_p);
}
