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

#define INFINITO 9999

/*data structures declarations*/

typedef enum {bianco, grigio, nero} colore_t;


typedef struct vertice_grafo
{
    int valore;
    struct vertice_grafo *vertice_succ_p;
    struct arco_grafo *lista_archi_p;
    colore_t colore;
    double distanza_min;
    int distanza, inizio, fine;
    struct vertice_grafo *padre_p;
} vertice_grafo_t;

typedef struct arco_grafo
{
    double               peso;               /* presente in caso di grafo pesato */
    struct vertice_grafo *vertice_adiac_p;
    struct arco_grafo    *arco_succ_p;
} arco_grafo_t;

typedef struct elem_lista {
    vertice_grafo_t *valore;
    struct elem_lista *succ_p;
} elem_lista_vertici_t;


/*
* function declarations
*/

arco_grafo_t *acquisisci_lista(vertice_grafo_t *grafo_p);
vertice_grafo_t *acquisisci_grafo(int *n, FILE *fp);
vertice_grafo_t *cerca_in_lista(vertice_grafo_t *testa_p, int valore);
void avvia_visita_grafo_amp(vertice_grafo_t *grafo_p);
void visita_grafo_amp(vertice_grafo_t *vertice_partenza_p);
void avvia_visita_grafo_prof(vertice_grafo_t *grafo_p);
void visita_grafo_prof(vertice_grafo_t *vertice_p, int *tempo);
void metti_in_coda(elem_lista_vertici_t **uscita_p, elem_lista_vertici_t **ingresso_p, vertice_grafo_t *valore);
elem_lista_vertici_t *togli_da_coda(elem_lista_vertici_t **uscita_p, elem_lista_vertici_t **ingresso_p);
void inizializza(vertice_grafo_t *grafo_p, vertice_grafo_t *sorgente_p);
void riduci(arco_grafo_t *arco_p, vertice_grafo_t *vertice_p);
void dijkstra(vertice_grafo_t *grafo_p, vertice_grafo_t *sorgente_p, int n);
void crea_array(vertice_grafo_t *grafo, vertice_grafo_t **vertici);
void setaccia_heap(vertice_grafo_t **a, int sx, int dx);
void crea_heap(vertice_grafo_t **a, int n);
void scambia(vertice_grafo_t **a, vertice_grafo_t **b);
void crea_array_pesi(vertice_grafo_t *grafo, arco_grafo_t **pesi);



/*
 *  Main function
 */

int main(int argc, char **argv){
    int n;
    vertice_grafo_t *grafo_p, *vertice_p, *sorgente_p;
    arco_grafo_t *arco_p;
    FILE *INFILE;
    //char *fname;
    
/*    if(argc < 2) {
        printf("USAGE: parse_graph_from_file <file> \n");
        exit(-1);
    }*/
    
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
    /*for (vertice_p = grafo_p;(vertice_p!=NULL);vertice_p = vertice_p->vertice_succ_p){
        //printf("Adjacency list of vertex %d:\n",vertice_p->valore);
        for (arco_p = vertice_p->lista_archi_p; (arco_p!= NULL); arco_p = arco_p->arco_succ_p)
            //printf("%d ",arco_p->vertice_adiac_p->valore);
        printf("\n");
    }*/
    
    printf("Visita in ampiezza: ");
    avvia_visita_grafo_amp(grafo_p);
    
    printf("\n");
    printf("Visita in profondita': ");
    avvia_visita_grafo_prof(grafo_p);
    printf("\n");
    
    
    dijkstra(grafo_p, sorgente_p, n);
    //printf("Traversal of the graph...\n");
    //printf(".. and print tree of traversal\n");
    return(0);
}


vertice_grafo_t *acquisisci_grafo(int *nvg, FILE *fin){
    int n, nV, i, src, dest;
    double peso;
    vertice_grafo_t *nuovov_p, *grafo_p, *vertice_p;
    arco_grafo_t *arco_p, *nuovoa_p;

    grafo_p = NULL;
    arco_p = NULL;
    fscanf(fin,"%d\n",&n);
    *nvg = n;
    //printf("Nr. of nodes = %d\n",*nvg);
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
            //fscanf(fin, "%d %d %lf\n", &src, &dest, &peso);
            // printf
            //printf("src = %d, dest = %d\n",src, dest);
            vertice_p = cerca_in_lista(grafo_p,src); /*cerca nella lista primaria il vertice con label src*/
            // secondo printf
            if (vertice_p!=NULL)
                //printf("found vertex %d\n",vertice_p->valore);
            nuovoa_p = malloc(sizeof(arco_grafo_t));
            nuovoa_p->vertice_adiac_p = cerca_in_lista(grafo_p,dest); /*cerca nella lista primaria il vertice con label dest*/
            // terzo printf
            if (nuovoa_p->vertice_adiac_p!=NULL)
                //printf("found vertex %d\n",nuovoa_p->vertice_adiac_p->valore);
            nuovoa_p->arco_succ_p = arco_p;
            arco_p = nuovoa_p;
            arco_p->peso = 1;
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


//visita in ampiezza del grafo
void avvia_visita_grafo_amp(vertice_grafo_t *grafo_p)
{
    vertice_grafo_t *vertice_p;
    int valore_vertice = 5;
    //grafo_p->valore = valore;
    
    for(vertice_p = grafo_p; (vertice_p != NULL); vertice_p = vertice_p->vertice_succ_p)
    {
        //printf("VALORE: %d", vertice_p->valore);
        vertice_p->colore = bianco;
        vertice_p->distanza = -1;
        vertice_p->padre_p = NULL;
    }
    for(vertice_p = grafo_p; (vertice_p != NULL); vertice_p = vertice_p->vertice_succ_p)
    {
        //printf("%d ", vertice_p->valore);
        if(vertice_p->colore == bianco)
        {
            //printf("%d ", vertice_p->valore);
            //visita_grafo_amp(vertice_p);
            if(vertice_p->valore == valore_vertice)
            {
                //printf("%d ", vertice_p->valore);
                visita_grafo_amp(vertice_p);
            }
        }
    }
}

void visita_grafo_amp(vertice_grafo_t *vertice_partenza_p)
{
    vertice_grafo_t *vertice_p;
    arco_grafo_t *arco_p;
    elem_lista_vertici_t *uscita_p, *ingresso_p;
    
    vertice_partenza_p->colore = grigio;
    vertice_partenza_p->distanza = 0;
    uscita_p = ingresso_p = NULL;
    metti_in_coda(&uscita_p, &ingresso_p, vertice_partenza_p);
    
    while (uscita_p != NULL)
    {
        vertice_p = togli_da_coda(&uscita_p, &ingresso_p)->valore;
        //elabora(vertice_p->valore);
        printf("%d ", vertice_p->valore);
        
        for(arco_p = vertice_p->lista_archi_p; (arco_p != NULL); arco_p = arco_p->arco_succ_p)
            if(arco_p->vertice_adiac_p->colore == bianco)
            {
                arco_p->vertice_adiac_p->colore = grigio;
                arco_p->vertice_adiac_p->distanza = vertice_p->distanza + 1;
                arco_p->vertice_adiac_p->padre_p = vertice_p;
                metti_in_coda(&uscita_p, &ingresso_p, arco_p->vertice_adiac_p);
            }
        vertice_p->colore = nero;
    }
}

//algoritmi per la coda utilizzata nella visita in ampiezza
void metti_in_coda(elem_lista_vertici_t **uscita_p, elem_lista_vertici_t **ingresso_p, vertice_grafo_t *valore)
{
    elem_lista_vertici_t *nuovo_p;
    
    nuovo_p = (elem_lista_vertici_t *)malloc(sizeof(elem_lista_vertici_t));
    nuovo_p->valore = valore;
    //printf("%d ", nuovo_p->valore->valore);
    nuovo_p->succ_p = NULL;
    if(*ingresso_p != NULL)
        (*ingresso_p)->succ_p = nuovo_p;
    else
        *uscita_p = nuovo_p;
    *ingresso_p = nuovo_p;
}

elem_lista_vertici_t *togli_da_coda(elem_lista_vertici_t **uscita_p, elem_lista_vertici_t **ingresso_p)
{
    elem_lista_vertici_t *elem_p;
    
    elem_p = *uscita_p;
    if (*uscita_p != NULL)
    {
        *uscita_p = (*uscita_p)->succ_p;
        if (*uscita_p == NULL)
            *ingresso_p = NULL;
    }
    //printf("%d ", elem_p->valore->valore);
    return(elem_p);
}




// visita in profondità del grafo
void avvia_visita_grafo_prof(vertice_grafo_t *grafo_p)
{
    vertice_grafo_t *vertice_p;
    int tempo;
    int valore_vertice = 5;
    
    for(vertice_p = grafo_p; (vertice_p != NULL); vertice_p = vertice_p->vertice_succ_p)
    {
        vertice_p->colore = bianco;
        vertice_p->inizio = vertice_p->fine = -1;
        vertice_p->padre_p = NULL;
    }
    for(vertice_p = grafo_p, tempo = 0; (vertice_p != NULL); vertice_p = vertice_p->vertice_succ_p)
        if (vertice_p->colore == bianco)
            if(vertice_p->valore == valore_vertice)
                visita_grafo_prof(vertice_p, &tempo);
}


void visita_grafo_prof(vertice_grafo_t *vertice_p, int *tempo)
{
    arco_grafo_t *arco_p;
    
    vertice_p->colore = grigio;
    vertice_p->inizio = ++(*tempo);
    //elabora(vertice_p->valore);
    printf("%d ", vertice_p->valore);
    
    for(arco_p = vertice_p->lista_archi_p; (arco_p != NULL); arco_p = arco_p->arco_succ_p)
        if (arco_p->vertice_adiac_p->colore == bianco)
        {
            arco_p->vertice_adiac_p->padre_p = vertice_p;
            visita_grafo_prof(arco_p->vertice_adiac_p, tempo);
        }
    vertice_p->colore = nero;
    vertice_p->fine = ++(*tempo);
}






// implementazione algoritmo di dijkstra
void inizializza(vertice_grafo_t *grafo_p, vertice_grafo_t *sorgente_p)
{
    vertice_grafo_t *vertice_p;

    for (vertice_p = grafo_p; (vertice_p != NULL); vertice_p = vertice_p->vertice_succ_p)
    {
        vertice_p->distanza_min = INFINITO;
        vertice_p->padre_p = NULL;
    }
    sorgente_p->distanza_min = 0.0;
}

void riduci(arco_grafo_t *arco_p, vertice_grafo_t *vertice_p) /* vertice da cui l’arco esce */
{
    if (arco_p->vertice_adiac_p->distanza_min > vertice_p->distanza_min + arco_p->peso)
    {
        arco_p->vertice_adiac_p->distanza_min = vertice_p->distanza_min + arco_p->peso;
        arco_p->vertice_adiac_p->padre_p = vertice_p;
    }
}

void dijkstra(vertice_grafo_t *grafo_p, vertice_grafo_t *sorgente_p, int n)
{
    vertice_grafo_t *vertice_p;
    arco_grafo_t *arco_p;
    int k = 1;
    //int vertici_considerati = 1;
    vertice_grafo_t *non_considerati[n + 1];
    //"costruisci un insieme per i vertici gia’ considerati (inizialmente vuoto)";
    int considerati[n + 1];
    
    
    inizializza(grafo_p, sorgente_p);
    crea_array(grafo_p, non_considerati);
    crea_heap(non_considerati, n + 1);
    
    for(int i = 0; i < n + 1; i++)
        considerati[i] = -1;
    
    //"costruisci una struttura per i vertici da considerare (inizialmente tutti)";
    /*int non_considerati[n + 1];
    
    for(int j = 0; j < n + 1; j++)
        non_considerati[j] = j;*/
    
    while (k < n)
    {
/*        //"rimuovi dalla struttura il vertice vertice_p con distanza_min minima";
        non_considerati[vertici_considerati] = -1;
        //"inserisci vertice_p nell’insieme dei vertici gia’ considerati";
        considerati[vertici_considerati] = vertici_considerati;
        
        //"arco_p->vertice_adiac_p non e’ nell’insieme dei vertici gia’ considerati"
        for(arco_p = vertice_p->lista_archi_p; (arco_p != NULL); arco_p = arco_p->arco_succ_p)
        {
            if (considerati[arco_p->vertice_adiac_p->valore] == -1)
            {
                riduci(arco_p, vertice_p);
            }
        }
        k++;
        vertici_considerati++;*/
        
        
        vertice_p = non_considerati[1];
        considerati[vertice_p->valore] = 1;
        
        for(arco_p = vertice_p->lista_archi_p; (arco_p != NULL); arco_p = arco_p->arco_succ_p)
        {
            if (considerati[arco_p->vertice_adiac_p->valore] == -1)
            {
                riduci(arco_p, vertice_p);
            }
        }
        scambia(&non_considerati[1], &non_considerati[n - k]);
        crea_heap(non_considerati, (n - k));
        k++;
    }
}

/* funzione che scorre la lista primaria e salva i vertici in un array */
void crea_array(vertice_grafo_t *grafo, vertice_grafo_t **vertici)
{
	vertice_grafo_t *corr_p;
	int indice;
	/* il primo elemento nn lo considero poichè lo heap di seguito nell'algoritmo
	   di Dijkstra nn lo considera */
	vertici[0] = NULL;
	for(indice = 1, corr_p = grafo; (corr_p != NULL); corr_p = corr_p->vertice_succ_p)
	{
		vertici[indice] = corr_p;
		indice++;
	}
}

/* funzione di setacciamento per far risalire il minimo nella radice dello heap*/
void setaccia_heap(vertice_grafo_t **a, int sx, int dx) 
{
	vertice_grafo_t *vertice;
	int i,
		j;
		
	for(vertice = a[sx], i = sx, j = 2 * i; (j <= dx); ) 
	{
		if ((j < dx) && (a[j + 1]->distanza_min < a[j] -> distanza_min)) 
			j++;
		if (vertice -> distanza_min > a[j] -> distanza_min) 
		{
			a[i] = a[j];
			i = j;
			j = 2 * i; 
		}
		else 
			j = dx + 1; 
	}
	if (i != sx) 
		a[i] = vertice;
}

/* funzione per creare uno heap */
void crea_heap(vertice_grafo_t **a, int n) 
{
	int sx;
	
	for (sx = n / 2; (sx >= 1); sx--) 
		setaccia_heap(a, sx, n - 1);
}

/* funzione per scambiare due elementi dell'array di vertici */
void scambia(vertice_grafo_t **a, vertice_grafo_t **b)
{
	vertice_grafo_t *tmp;
	
	tmp = (*b);
	b = a;
	(*a) = tmp;
}

/* funzione per la creazione di un array che comprende tutti gli archi */
void crea_array_pesi(vertice_grafo_t *grafo, arco_grafo_t **pesi)
{
	vertice_grafo_t *corr_p;
	arco_grafo_t *arco;
	int indice = 0;
	
	for(corr_p = grafo; (corr_p != NULL); corr_p = corr_p->vertice_succ_p)
	{
		for(arco = corr_p ->lista_archi_p; arco != NULL; arco = arco -> arco_succ_p)
		{
			pesi[indice]->peso = 1;
			indice++;
			
		}
	}
}