#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*data structures declarations*/

typedef enum {bianco, grigio, nero} colore_t;

typedef struct vertice_grafo
{
    int                   valore;
    char                  nome[3];
    struct vertice_grafo *vertice_succ_p;
    struct arco_grafo    *lista_archi_p;
    colore_t              colore;
    int                   distanza,
                          inizio,
                          fine;
    struct vertice_grafo *padre_p;
} vertice_grafo_t;

typedef struct arco_grafo
{
    struct vertice_grafo *vertice_adiac_p;
    struct arco_grafo    *arco_succ_p;
} arco_grafo_t;

typedef struct elem_lista
{
    char               nome[3];
    struct elem_lista *succ_p;
} elem_lista_t;

/*
* function declarations
*/

arco_grafo_t    *acquisisci_lista(vertice_grafo_t *grafo_p);
vertice_grafo_t *acquisisci_grafo(int *n, FILE *fp);
vertice_grafo_t *cerca_in_lista(vertice_grafo_t *testa_p,
                                char nome[3]);
vertice_grafo_t *avvia_ord_top_grafo(vertice_grafo_t *grafo_p);
void ordina_top_grafo(vertice_grafo_t *vertice_p,
                      vertice_grafo_t **testa_p);
int inserisci_in_lista_ordinata(elem_lista_t **testa_p,
                                char            nome[3]);
void stampa_lista(elem_lista_t *testa_p);
vertice_grafo_t *costruzione_lista_primaria_grafo(elem_lista_t *testa_p,
                                                  int           n);

int main(int argc, char **argv)
{
    int n;
    //vertice_grafo_t *grafo_p, *vertice_p;
    //arco_grafo_t *arco_p;
    FILE *INFILE;
    
    if (!(INFILE = fopen("graph.txt","r"))) {
        printf("ERROR: error opening input file %s\n", "graph.txt");
        exit(-1);
    }
    printf("Reading input file %s and loading data...\n", "graph.txt");
    acquisisci_grafo(&n,INFILE);
    /*
    printf("... done.\n******************\n");
    printf("Graph with %d vertices\n",n);
    */
    /* stampa liste primaria e secondaria */
    /*
    for (vertice_p = grafo_p;(vertice_p!=NULL);vertice_p = vertice_p->vertice_succ_p){
        printf("Adjacency list of vertex %s:\n",vertice_p->nome);
        for (arco_p = vertice_p->lista_archi_p; (arco_p!= NULL); arco_p = arco_p->arco_succ_p)
            printf("%s ,",arco_p->vertice_adiac_p->nome);
        printf("\n");
    }
    
    printf("Traversal of the graph...\n");
    printf(".. and print tree of traversal\n");
    */
    return(0);
}

vertice_grafo_t *acquisisci_grafo(int *nvg, FILE *fin){
    FILE            *fin_2;
    int              n,
                     nV,
                     i;
                     //inserito;
    //int src, dest;
    vertice_grafo_t *grafo_p_2,
                    *vertice_p;
                    //*elem_p;
    arco_grafo_t    *arco_p,
                    *nuovoa_p;
    elem_lista_t    *testa_p;
    char             nom[4];
    //int              number;
    char             nome[4];
    char             source[4];
    char             destination[4];
    
    /* costruiamo prima una lista con solo i vertici
       in modo da evitare eventuali ripetizioni o 
       la presenza di valori indesiderati */
    testa_p = NULL;
    grafo_p_2 = NULL;
    arco_p = NULL;
    
    while(!feof(fin))
    {
        fscanf(fin, "%s\n", nom);
        if(!isdigit(nom[0]))
        {
            inserisci_in_lista_ordinata(&testa_p, nom);
            /*
            if(inserito == 1)
                printf("Elemento inserito!\n");
            else
                printf("Elemento non inserito!\n");
            */
        }
    }
    fclose(fin);
    stampa_lista(testa_p);
    
    grafo_p_2 = costruzione_lista_primaria_grafo(testa_p, n);
    
    fin_2 = fopen("graph.txt","r");
    fscanf(fin_2,"%d\n",&n);
    *nvg = n;
    printf("Nr. of nodes = %d\n",*nvg);
    
    vertice_p = grafo_p_2;
    while (fscanf(fin_2, "%s %d\n", nome, &nV) != EOF) {
        printf("%s %d\n", nome, nV);
        arco_p = NULL;
        for (i=0; i<nV; i++) {
            fscanf(fin_2, "%s %s\n", source, destination);
            printf("src = %s, dest = %s\n", source, destination);
            vertice_p = cerca_in_lista(grafo_p_2, source);
            if (vertice_p!=NULL)
                printf("found vertex %s\n",vertice_p->nome);
            nuovoa_p = malloc(sizeof(arco_grafo_t));
            nuovoa_p->vertice_adiac_p = cerca_in_lista(grafo_p_2, destination);
            if (nuovoa_p->vertice_adiac_p != NULL)
                printf("found vertex %s\n", nuovoa_p->vertice_adiac_p->nome);
            nuovoa_p->arco_succ_p = arco_p;
            arco_p = nuovoa_p;
            vertice_p->lista_archi_p = arco_p;
        }
        vertice_p = vertice_p->vertice_succ_p;
    }
    fclose(fin_2);
    
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
    
    //return 0;
    return(grafo_p_2);
}

vertice_grafo_t *costruzione_lista_primaria_grafo(elem_lista_t *testa_p,
                                                  int           n)
{
    vertice_grafo_t *nuovov_p,
                    *grafo_p;
    int              i;
    int              counter = 0;
    
    for(i = 0; i < n; i++)
    {
        nuovov_p = (vertice_grafo_t *)malloc(sizeof(vertice_grafo_t));
        strcpy(nuovov_p->nome, testa_p->nome);
        nuovov_p->lista_archi_p = NULL;
        nuovov_p->vertice_succ_p = grafo_p;
        grafo_p = nuovov_p;
        counter++;
    }
    printf("ECCOMI: %d\n", counter);
    return (grafo_p);
}

vertice_grafo_t *cerca_in_lista(vertice_grafo_t *testa_p,
                                char nome[4])
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

int inserisci_in_lista_ordinata(elem_lista_t **testa_p,
                                char            nome[3])
{
    int           inserito;
    elem_lista_t *corr_p,
                 *prec_p,
                 *nuovo_p;

    for (corr_p = prec_p = *testa_p;
         ((corr_p != NULL) && (strcmp(corr_p->nome, nome) != 0));
         prec_p = corr_p, corr_p = corr_p->succ_p);
    if ((corr_p != NULL) && (strcmp(corr_p->nome, nome) == 0))
        inserito = 0;
    else
    {
        inserito = 1;
        nuovo_p = (elem_lista_t *)malloc(sizeof(elem_lista_t));
        strcpy(nuovo_p->nome, nome);
        nuovo_p->succ_p = corr_p;
        if (corr_p == *testa_p)
            *testa_p = nuovo_p;
        else
            prec_p->succ_p = nuovo_p;
    }
    return(inserito);
}

void stampa_lista(elem_lista_t *testa_p)
{
    elem_lista_t *elem_p;

    for (elem_p = testa_p;
         (elem_p != NULL);
         elem_p = elem_p->succ_p)
        printf("%s\n", elem_p->nome);
}
