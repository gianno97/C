/************************/
/* Definizione dei tipi */
/************************/

typedef struct vertice_grafo
{
	int id;
	char nome_stazione[20];
	struct arco_grafo *lista_stazioni_adiacenti_p;
	struct vertice_grafo *stazione_succ_p;
	double min;
	struct vertice_grafo *padre_p,
						 *figlio_p;
} vertice_grafo_t;

typedef struct arco_grafo
{
	double tempo_percorrenza;
	double distanza;
	struct vertice_grafo *stazione_adiac_p;
	struct arco_grafo *arco_succ_p;
} arco_grafo_t;

/********************************/
/* Dichiarazione delle funzioni */
/********************************/

/* salta riga */
extern void skip_line(FILE *file_stazioni);

/* acquisizione lista primaria e secondaria da file di testo */
extern int acquisizione_grafo(vertice_grafo_t **grafo, 
					   		  int *num_archi_tot);

/* inserimento in lista non ordinata */
extern int inserisci_in_lista_primaria(vertice_grafo_t **grafo,
									   char nome_stazione[],
									   int id);
extern int inserisci_in_lista_secondaria(vertice_grafo_t *vertice,
								  		 vertice_grafo_t *adiacente,
								  		 double distanza,
								  		 double tempo);


/* Ricerca in lista */
extern vertice_grafo_t* cerca_in_lista_primaria(vertice_grafo_t *testa,
										 		char *stazione);


/* Crea array di vertici del grafo */
void crea_array(vertice_grafo_t *grafo,
				vertice_grafo_t **vertici);
				
/* Funzioni per creazione e setacciamento heap */				
void crea_heap(vertice_grafo_t** vertici,
			   int stazioni_tot);
 void setaccia_heap(vertice_grafo_t **vertici,
				    int sx, int dx);
				   
/* Funzioni relative all'algoritmo di Dijkstra e rilassamento archi per Tempo e Distanza */
extern void dijkstra_distanza(vertice_grafo_t *grafo,
					   		  vertice_grafo_t *sorgente, int stazioni_tot);
extern void dijkstra_tempo(vertice_grafo_t *grafo,
						   vertice_grafo_t *sorgente, int stazioni_tot);
void rilassa_tempo(arco_grafo_t *arco_p, 
				   vertice_grafo_t *vertice_p);
void rilassa_distanza(arco_grafo_t *arco_p,
					  vertice_grafo_t *vertice_p);
void inizializza(vertice_grafo_t *grafo,
				 vertice_grafo_t *sorgente);
void scambia(vertice_grafo_t **a, 
			 vertice_grafo_t **b);
				 
/* Funzioni relative al calcolo delle statistiche */
extern void statistiche(vertice_grafo_t* grafo,
				 		int num_archi_tot,
				 		int scelta);
void insertsort(arco_grafo_t **pesi,
				int sx, 
				int dx, 
				int scelta);
int partiziona(arco_grafo_t **pesi, 
				int sx,
				int dx, 
				int valore_pivot,
				int scelta);
arco_grafo_t *selezione_det(arco_grafo_t **pesi,
							int sx, 
							int dx,
							int k, 
							int scelta);

								
								
/* funzione per assegnare i figli per la stampa ordinata del percorso */								
void assegna_figli(vertice_grafo_t* partenza,
				   vertice_grafo_t* arrivo);


/* funzione per la creazione dell'array contenente gli archi */
void crea_array_pesi(vertice_grafo_t *grafo, 
					 arco_grafo_t **pesi);


