/******************************************************/
/* Progetto sessione estiva 2016-17 *******************/
/* Studenti: Mancini Andrea Matricola: 276435 *********/
/*********** Perticaroli Luca matricola: 278970 *******/
/******************************************************/

/*****************************/
/* Inclusione delle librerie */
/*****************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/**************************************/
/* Definizioni di Costanti simboliche */
/**************************************/

#define INF 1000000


/*******************************/
/* Definizione nuove strutture */
/*******************************/

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

void skip_line(FILE *file_stazioni);
int acquisizione_grafo(vertice_grafo_t **grafo, int *num_archi_tot);
int inserisci_in_lista_primaria(vertice_grafo_t **grafo, char nome_stazione[], int id);
vertice_grafo_t* cerca_in_lista_primaria(vertice_grafo_t *testa, char *stazione);
int inserisci_in_lista_secondaria(vertice_grafo_t *vertice, vertice_grafo_t *adiacente, double distanza, double tempo);
void crea_array(vertice_grafo_t *grafo, vertice_grafo_t **vertici);
void setaccia_heap( vertice_grafo_t **vertici, int sx, int dx);
void crea_heap(vertice_grafo_t** vertici, int stazioni_tot);
void dijkstra_distanza(vertice_grafo_t *grafo, vertice_grafo_t *sorgente, int stazioni_tot);
void dijkstra_tempo(vertice_grafo_t *grafo, vertice_grafo_t *sorgente, int stazioni_tot);
void rilassa_tempo(arco_grafo_t *arco_p, vertice_grafo_t *vertice_p);
void rilassa_distanza(arco_grafo_t *arco_p, vertice_grafo_t *vertice_p);
void inizializza(vertice_grafo_t *grafo, vertice_grafo_t *sorgente);
void calcola_statistiche_ordine(vertice_grafo_t **vertici, int stazioni_tot);
void assegna_figli(vertice_grafo_t* partenza, vertice_grafo_t* arrivo);
void scambia(vertice_grafo_t **a, vertice_grafo_t **b);
void crea_array_pesi(vertice_grafo_t *grafo, arco_grafo_t **pesi);
void statistiche(vertice_grafo_t* grafo, int num_archi_tot, int scelta);
void insertsort(arco_grafo_t **pesi, int sx, int dx, int scelta);
int partiziona(arco_grafo_t **pesi, int sx, int dx, int valore_pivot, int scelta);
arco_grafo_t *selezione_det(arco_grafo_t **pesi,int sx, int dx, int k, int scelta);

/********************************/
/* Definizione delle funzioni ***/
/********************************/

/* funzione che scorre la lista primaria e salva i vertici in un array */
void crea_array(vertice_grafo_t *grafo, vertice_grafo_t **vertici)
{
	vertice_grafo_t *corr_p;
	int indice;
	/* il primo elemento nn lo considero poichè lo heap di seguito nell'algoritmo
	   di Dijkstra nn lo considera */
	vertici[0] = NULL;
	for(indice = 1, corr_p = grafo; (corr_p != NULL); corr_p = corr_p -> stazione_succ_p)
	{
		vertici[indice] = corr_p;
		indice++;
	}
}
/* Funzione che permettere di saltare una riga di File di testo */
void skip_line(FILE *file_stazioni)
{
	/* usando il char come intero si ha la possibilita' di sapere
	   quando il file termina */
	int tmp_char;
	while((tmp_char = getc(file_stazioni)) != '\n' && tmp_char != EOF );
}
/* funzione per acquisire il grafo da file */
int acquisizione_grafo(vertice_grafo_t **grafo, int *num_archi_tot)
{

	vertice_grafo_t *attuale,
					*adiacente;
	FILE *file_stazioni;			/* variabile puntatore a FILE per acquisizione dei dati da file */
	int i,							/* variabile contatore per lo scorrimento del numero delle stazioni */
		j,							/* variabile contatore per lo scorrimento del numero di stazioni adiacenti */
		stazioni_tot,				/* variabile numero stazioni totali */
		num_archi,					/* variabile per numero di archi che partono da ogni vertice */
		esito_lettura,				/* variabile per controllo valore di ritorno della fscanf */
        inserito;					/* variabile per controllo inserimento in lista */

	double 	distanza,				/* variabile per la distanza presente */ 
			tempo_percorrenza;


	char nome_stazione[15];			/* variabile di appoggio per il nome della stazione */
	char temp[15];					/* variabile dove inserire temporaneamente la prima stringa che non utilizzerò
									   perchè già inserita in lista primaria */

	/* inizializzazione grafo */
	(*grafo) = NULL;

	/* apro file di testo */
	file_stazioni = fopen("file_stazioni.txt", "r");
	if (file_stazioni == NULL)
		printf("ERRORE! FILE NON TROVATO\n");
	else
	{
		/* acquisizione numero totale di stazioni*/
		esito_lettura = fscanf(file_stazioni, "%d", &stazioni_tot);
		if(esito_lettura != 1 || stazioni_tot < 0)
			printf("Eerrore numero stazioni non valido");

		/* acquisizione del numero di archi, del nome delle stazioni da inserire in lista primaria */
		for(i = 0; i < stazioni_tot; i++)
		{
			/* acquisizione numero archi */
			esito_lettura = fscanf(file_stazioni, "%d", &num_archi);
			(*num_archi_tot) += num_archi;

			if(esito_lettura != 1 || num_archi < 0)
				printf("Errore! lettura del valore dal file non valida!\n");
			else
			{
				esito_lettura = fscanf(file_stazioni, "%s", temp);
				/* inserimento del nome della stazione in lista primaria */
				inserito = inserisci_in_lista_primaria(grafo, temp, i);
				if(inserito == 0 || esito_lettura != 1)
					printf("Errore in inserimento in lista primaria!\n");
				if(!feof(file_stazioni))
					/* ciclo for per saltare l'acquisizione dei dati che non interessano per la lista primaria */
					for(j = 0; j < num_archi; j++)
						skip_line(file_stazioni);
			}
		}
		/* torno all'inizio del file */
		rewind(file_stazioni);
		/* salto la prima rig del file */
		skip_line(file_stazioni);
		for(i = 0; i < stazioni_tot; i++)
		{
			/* acquisizione numero archi che partono da ogni vertice */
			esito_lettura = fscanf(file_stazioni, "%d", &num_archi);

			/* controllo se ci sono archi */
			if(num_archi >= 1)
			{
				/* acquisisco i dati riga per riga inserendo la prima stinga in una  variabile stringa temporanea
				visto che nn ho necessità di dargli un nome significativo perchè l'ho gia inserita in lista primaria */
				esito_lettura = fscanf(file_stazioni, "%s %s %lf %lf", temp, nome_stazione, &distanza, &tempo_percorrenza);
				if(esito_lettura != 4 || distanza <= 0 || tempo_percorrenza <= 0)
					printf("Valori acquisiti non validi Errore!!");
				/* cerco il vertice dove inserire gli archi */
				attuale = cerca_in_lista_primaria((*grafo), temp);
				adiacente = cerca_in_lista_primaria((*grafo), nome_stazione);

				/* inserisco in lista secondaria i vertici adiacenti la distanza e il tempo di percorrenza */
				inserito = inserisci_in_lista_secondaria(attuale, adiacente, distanza, tempo_percorrenza);
				if (inserito == 0)
					printf("Errore inserimento in lista secondaria!\n");
				/* scorro le righe in base al num di archi - 1 perchè la prima riga è già acquisita */
				for(j = 0; j < num_archi - 1; j++)
				{
					esito_lettura = fscanf(file_stazioni, "%s %s %lf %lf", temp, nome_stazione, &distanza, &tempo_percorrenza);
					if(esito_lettura != 4 || distanza <= 0 || tempo_percorrenza <= 0)
						printf("Valori acquisiti non validi Errore!!");
					/* cerco il vertice in lista a cui collegare l'arco */
					adiacente = cerca_in_lista_primaria((*grafo), nome_stazione);
					/* inserisco l'arco in lista secondaria nel vertice cercato */
					inserito = inserisci_in_lista_secondaria(attuale, adiacente, distanza, tempo_percorrenza);
					if (inserito == 0)
						printf("Errore inserimento in lista secondaria!\n");
				}
			}
		}
	}

	fclose(file_stazioni);
	return(stazioni_tot);
}

/* Funzione di inserimento in lista non ordinata */
int inserisci_in_lista_primaria(vertice_grafo_t **grafo, char *nome_stazione, int id)
{
	int inserito,					/* variabile per controllo inserimento in lista */
		esito_lettura;				/* variabile per l'esito del controllo tra i nomi delle stazioni */

	vertice_grafo_t *staz_corr,		/* variabile puntatore a stazione corrente */
					*staz_prec,		/* variabile puntatore a stazione precedente */
					*nuova_staz;	/* variabile puntatore a nuova stazione */

	for (staz_corr = staz_prec = *grafo; ((staz_corr != NULL)); staz_prec = staz_corr, staz_corr = staz_corr -> stazione_succ_p);

	if(staz_corr != NULL)
	{
		/* controllo se una stazione è gia presente in lista */
		esito_lettura = strcmp(staz_corr -> nome_stazione, nome_stazione);
	}
		/* se già presente non la inserisco */
	if ((staz_corr != NULL) && (esito_lettura == 1))
		inserito = 0;
	else
	{
		/* allocazione in memoria di un vertice del grafo */
		inserito = 1;
		nuova_staz = (vertice_grafo_t *)malloc(sizeof(vertice_grafo_t));
        nuova_staz -> lista_stazioni_adiacenti_p = NULL;
		nuova_staz -> min = 0;
		nuova_staz -> id = id;
		strcpy(nuova_staz -> nome_stazione, nome_stazione);
		nuova_staz -> stazione_succ_p = staz_corr;
		if (staz_corr == *grafo)
			*grafo = nuova_staz;
		else
			staz_prec -> stazione_succ_p = nuova_staz;
	}

	return(inserito);
}

/* ricerca in lista primaria dato il nome della stazione */
vertice_grafo_t* cerca_in_lista_primaria(vertice_grafo_t *testa, char *stazione)
{
    vertice_grafo_t *corr;
	
	/* scorro la lista primaria */
    for(corr = testa; (corr != NULL) && (( strcmp(stazione, corr -> nome_stazione) != 0)); corr = corr -> stazione_succ_p);

    return corr;
}

/* funzione di inserimento in lista non ordinata */
int inserisci_in_lista_secondaria(vertice_grafo_t *vertice, vertice_grafo_t *adiacente, double distanza, double tempo)
{
	int inserito;
	arco_grafo_t    *corr_p,	/* variabile puntatore a arco corrente */
					*prec_p,	/* variabile puntatore a arco precedente */
					*nuovo_p;	/* variabile puntatore a nuovo arco */


	/* scorro la lista secondaria */
	for (corr_p = prec_p = vertice -> lista_stazioni_adiacenti_p; ((corr_p != NULL)); prec_p = corr_p, corr_p = corr_p -> arco_succ_p);

    if ((corr_p != NULL))
		inserito = 0;
	else
	{
		inserito = 1;
		/* allocazione in memoria di un arco */
		nuovo_p = (arco_grafo_t*)malloc(sizeof(arco_grafo_t));
		nuovo_p -> stazione_adiac_p = adiacente;
        nuovo_p -> distanza = distanza;
        nuovo_p -> tempo_percorrenza = tempo;
		nuovo_p -> arco_succ_p = NULL;
		if (corr_p == vertice->lista_stazioni_adiacenti_p)
			vertice->lista_stazioni_adiacenti_p = nuovo_p;
		else
			prec_p -> arco_succ_p = nuovo_p;
    }

	return(inserito);
}

/* funzione di setacciamento per far risalire il minimo nella radice dello heap*/
void setaccia_heap(vertice_grafo_t **a, int sx, int dx) 
{
	vertice_grafo_t *vertice;
	int i,
		j;
		
	for(vertice = a[sx], i = sx, j = 2 * i; (j <= dx); ) 
	{
		if ((j < dx) && (a[j + 1] -> min < a[j] -> min)) 
			j++;
		if (vertice -> min > a[j] -> min) 
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

/* Algoritmo di Dijkstra per calcolo del percorso più breve in base alla Distanza */
void dijkstra_distanza(vertice_grafo_t *grafo, vertice_grafo_t *sorgente, int stazioni_tot)
{
	vertice_grafo_t *vertice_p;
	arco_grafo_t *arco_p;
	int i,
		j = 1,											/* Variabile per tenere il numero di vertici considerati */
		considerati[stazioni_tot + 1];						/* array per verificare se un vertice è stato considerato */	
	vertice_grafo_t *non_considerati[stazioni_tot + 1];		/* array di vertici non considerati */
	
	/* inizializzo Dikstra */
	inizializza(grafo, sorgente);
	/* creo array vertici */
	crea_array(grafo, non_considerati);
	/* creo lo heap */
	crea_heap(non_considerati, stazioni_tot + 1);
	

	/* inizializzo array a 0 come non considerati */
	for(i = 0; i < stazioni_tot + 1; i++) 
		considerati[i] = 0;
	
	/* finchè l'indice j < Stazioni_tot vuol dire che sono presenti dei vertici da considerare */
	while( j < stazioni_tot)
	{
		/* prendo il minimo che si trova in posizione 1 */
		vertice_p = non_considerati[1];
		
		/* assegno 1 in corrispondenza della posizione del vertice considerati */
		considerati[vertice_p -> id] = 1;		
		for(arco_p = vertice_p -> lista_stazioni_adiacenti_p; arco_p != NULL; arco_p = arco_p -> arco_succ_p)
		{
			/* se nn è stato considerato allora rilasso */
			if(considerati[arco_p -> stazione_adiac_p -> id] == 0)
			{
				rilassa_distanza(arco_p, vertice_p);				
			}		
				
		}
		/* scambio gli elementi portando quello con distanza min in fondo all'array */
		scambia(&non_considerati[1], &non_considerati[stazioni_tot - j]);
		/* ricreo lo heap per far si che il setacciamento funzioni */
		crea_heap(non_considerati, (stazioni_tot - j));
		j++;
	}
}

/* Algoritmo di Dijkstra per calcolo del percorso più breve in base al tempo di percorrenza*/
void dijkstra_tempo(vertice_grafo_t *grafo, vertice_grafo_t *sorgente, int stazioni_tot)
{
	vertice_grafo_t *vertice_p;
	arco_grafo_t *arco_p;
	int i,
		j = 1,												/* Variabile per tenere il numero di vertici considerati */
		considerati[stazioni_tot];							/* array per verificare se un vertice è stato considerato */	
	vertice_grafo_t *non_considerati[stazioni_tot + 1];		/* array di vertici non considerati */
	/* inizializzo Dikstra */
	inizializza(grafo, sorgente);
	/* creo array vertici */
	crea_array(grafo, non_considerati);
	/* creo lo heap */
	crea_heap(non_considerati, stazioni_tot + 1);
	/* inizializzo array a 0 come non considerati */
	for(i = 0; i < stazioni_tot; i++)
		considerati[i] = 0;
	
	/* finchè l'indice j < Stazioni_tot vuol dire che sono presenti dei vertici da considerare */
	while(j < stazioni_tot)
	{
		/* prendo il minimo che si trova in posizione 1 */
		vertice_p = non_considerati[1];
		/* assegno 1 in corriospondenza della posizione del vertice considerati */
		considerati[vertice_p -> id] = 1;		
		for(arco_p = vertice_p -> lista_stazioni_adiacenti_p; arco_p != NULL; arco_p = arco_p -> arco_succ_p)
		{
			/* se nn è stato considerato allora rilasso */
			if(considerati[arco_p -> stazione_adiac_p -> id] == 0)
				rilassa_tempo(arco_p, vertice_p);
		}
		/* scambio gli elementi portando quello con distanza min in fondo all'array */
		scambia(&non_considerati[1], &non_considerati[stazioni_tot - j]);
		/* ricreo lo heap per far si che il setacciamento funzioni */
		crea_heap(non_considerati, (stazioni_tot - j));
		j++;
	}
}
/* rilassamento della distanza */
void rilassa_distanza(arco_grafo_t *arco_p, vertice_grafo_t *vertice_p)
{
	if(arco_p -> stazione_adiac_p -> min > vertice_p -> min + arco_p -> distanza)
	{
		arco_p -> stazione_adiac_p -> min = vertice_p -> min + arco_p -> distanza;
		arco_p -> stazione_adiac_p -> padre_p = vertice_p;
	}
}

/* rilassamento del tempo di percorrenza */
void rilassa_tempo(arco_grafo_t *arco_p, vertice_grafo_t *vertice_p)
{
	if(arco_p -> stazione_adiac_p -> min  > vertice_p -> min + arco_p -> tempo_percorrenza)
	{
		arco_p -> stazione_adiac_p -> min = vertice_p -> min + arco_p -> tempo_percorrenza;	
		arco_p -> stazione_adiac_p -> padre_p = vertice_p;
	}
}

/* funzione che costruisce l'albero di percorrenza minima partendo dai padri del vertice di destinazione
   per poter avere un albero di percorrenza che va dalla partenza alla destinazione */
void assegna_figli(vertice_grafo_t* partenza, vertice_grafo_t* arrivo)
{
	vertice_grafo_t* corr_p;
	for(corr_p = arrivo; corr_p != NULL; corr_p = corr_p->padre_p)
		if(corr_p->padre_p != NULL)
			corr_p->padre_p->figlio_p = corr_p;
}

/* inizializza dijkstra */
void inizializza(vertice_grafo_t *grafo, vertice_grafo_t *sorgente)
{
	vertice_grafo_t *vertice_p;
	
	for(vertice_p = grafo; vertice_p != NULL; vertice_p = vertice_p -> stazione_succ_p)
	{
		vertice_p -> min = INF;
		vertice_p -> padre_p = NULL;
		vertice_p -> figlio_p = NULL;
	}
	sorgente -> min = 0.0;
}
/* funzione per la creazione di un array che comprende tutti gli archi */
void crea_array_pesi(vertice_grafo_t *grafo, arco_grafo_t **pesi)
{
	vertice_grafo_t *corr_p;
	arco_grafo_t *arco;
	int indice = 0;
	
	for(corr_p = grafo; (corr_p != NULL); corr_p = corr_p->stazione_succ_p)
	{
		for(arco = corr_p ->lista_stazioni_adiacenti_p; arco != NULL; arco = arco -> arco_succ_p)
		{
			pesi[indice] = arco;
			indice++;
			
		}
	}
}	

/* funzione per calcolo statistiche d'ordine */
void statistiche(vertice_grafo_t* grafo,
				int num_archi_tot, int scelta)
{
	arco_grafo_t **pesi,
				  *k_esimo;
	int i;			  
	double distanza_tot = 0.0,
		   tempo_tot = 0.0;
				
	/* creazione array */
	pesi = (arco_grafo_t **)malloc(sizeof(arco_grafo_t* ) * num_archi_tot);
	crea_array_pesi(grafo, pesi);

	if(scelta == 0)
	{
		/* Minimo */
		k_esimo = selezione_det(pesi, 
								0,
								num_archi_tot - 1,
								1,
								0);
	
		printf("Arco presente nel grafo con distanza minima: %f\n", k_esimo -> distanza);
		/* Mediana */	
		k_esimo = selezione_det(pesi, 
								0,
								num_archi_tot - 1,
								(num_archi_tot / 2),
								0);
	
		printf("L'arco mediano presente nel grafo ha distanza: %f\n", k_esimo -> distanza);
		/* Massimo */
		k_esimo = selezione_det(pesi, 
								0,
								num_archi_tot - 1,
								num_archi_tot,
								0);
	
		printf("Arco presente nel grafo con distanza massima: %f\n", k_esimo->distanza);
		
		for(i = 0; i < num_archi_tot; i++)
			distanza_tot += pesi[i] -> distanza;
		
		printf("la media delle distanze e': %f", distanza_tot/num_archi_tot);
	}
	else
	{
		/* Minimo */
		k_esimo = selezione_det(pesi, 
								0,
								num_archi_tot - 1,
								1,
								1);
	
		printf("Arco presente nel grafo con tempo percorrenza minima: %f\n", k_esimo->tempo_percorrenza);
		/* Mediana */	
		k_esimo = selezione_det(pesi, 
								0,
								num_archi_tot - 1,
								(num_archi_tot / 2),
								1);
	
		printf("Arco mediano presente nel grafo con tempo di percorrenza : %f\n", k_esimo->tempo_percorrenza);
		/* Massimo */
		k_esimo = selezione_det(pesi, 
								0,
								num_archi_tot - 1,
								num_archi_tot,
								1);
	
		printf("Arco presente nel grafo con tempo percorrenza massima: %f\n", k_esimo->tempo_percorrenza);
		
		for(i = 0; i < num_archi_tot; i++)
			tempo_tot += pesi[i] -> tempo_percorrenza;
		
		printf("la media dei tempi e': %f", tempo_tot/num_archi_tot);
	}	
	/* Libero memoria dell'array */
	free(pesi);
}


/* Funzione ricorsiva che ricerca il k-esimo arco minimo,
   sfruttando la selezione deterministica 
   Input: Array di archi; Limite sx e dx; Grado d'ordine */
arco_grafo_t *selezione_det(arco_grafo_t **pesi,
							int sx, 
							int dx,
							int k, 
							int scelta)
{
	int n,
	    i,    
	    n_gruppi,
	    pos_mediana;

	arco_grafo_t  *mediana_di_mediane,
				  **mediane;
	
	n = (dx - sx) + 1;
	n_gruppi = (n / 5);

	/* Se l'array ha dimensione minore o uguale a 5, lo ordino con insertsort
       e restituisco l'elemento di mezzo (mediana) */
	if(n <= 5)
	{
		insertsort(pesi,
				   sx,
				   dx,
				   (scelta == 0) ? 0 : 1);
        
        return pesi[(sx + k) - 1];
	}
	
	
	/* Alloco l'array di mediane di dimensione pari ai gruppi + 1 per il gruppo n mod 5 */	
	mediane = (arco_grafo_t **)malloc(sizeof(arco_grafo_t *) * (n_gruppi + 1));

	/* Ciclo da i al numero di gruppi da 5, calcolando per ognuno la mediana ricorsivamente,
	passando come ordine 	k, 3 che e' esattamente la mediana in gruppo di 5 elementi */
	for(i = 0; i < n_gruppi; i++)
		mediane[i] = selezione_det(pesi,
								   sx + (i * 5),
				                   sx + (i * 5) + 4,
								   3,
								   (scelta == 0) ? 0 : 1);

	/* Se rimane ancora un gruppo(minore di 5), calcolo anche di questo la mediana
		ricorsivamente, passando come oridne k, il resto di (n / 5) che sarebbe la dimensione
		del gruppo rimendente diviso 2, che e' esattamente la mediana */
	if((i * 5) < n)
	{
		mediane[i] = selezione_det(pesi,
								   sx + (i * 5),
								   sx + (i * 5) + (n % 5) - 1,
								   (n % 5) / 2,
								   (scelta == 0) ? 0 : 1);
		i++;
	}

	/* Calcolo la mediana delle mediane, invocando la funzione ricorsivamente sull'array
		delle mediane, che ha lunghezza i, passando come ordine k, (i / 2 + 1) */
	mediana_di_mediane = selezione_det(mediane, 
									   0,
									  (i - 1), 
									  (i / 2) + 1,
									  (scelta == 0) ? 0 : 1);

	/* Partiziono l'array usando come pivot la mediana delle mediane */
	pos_mediana = partiziona(pesi,
							 sx,
							 dx,
							 (scelta == 0) ? mediana_di_mediane -> distanza : mediana_di_mediane->tempo_percorrenza,
							 (scelta == 0) ? 0 : 1);

	if((pos_mediana - sx) + 1 == k)
	{
		free(mediane);
		return pesi[(sx + k) - 1];
	}	
	else if(k < (pos_mediana - sx) + 1)
    {
		return selezione_det(pesi,
							 sx,
							(pos_mediana - 1),
							 k,
							 (scelta == 0) ? 0 : 1);
	} else
    {
		return selezione_det(pesi,
							 (pos_mediana + 1),
							 dx,
							 k - ((pos_mediana - sx) + 1),
							 (scelta == 0) ? 0 : 1);
    }
}

/* Funzione di partizionamento dell'array in base al valore del pivot */
int partiziona(arco_grafo_t **pesi,
			   int sx,
			   int dx,
			   int valore_pivot, 
			   int scelta)
{
	int i, 
	    j;

	arco_grafo_t *tmp;

	for(i = sx, j = dx; (i < j);)
	{
		/* se scelta = 0 allora devo considerare il campo distanza */
		if(scelta == 0)
		{
			while(pesi[i] -> distanza < valore_pivot)
				i++;
			while(pesi[j] -> distanza > valore_pivot)
				j--;
		}
		/* altrimenti il campo tempo_percorrenza */
		else
		{
            while(pesi[i] -> tempo_percorrenza < valore_pivot)
				i++;
			while(pesi[j] -> tempo_percorrenza > valore_pivot)
				j--;
        }
		
		if( i <= j)
		{
			if(i < j)
			{
				tmp = pesi[i];
				pesi[i] = pesi[j];
				pesi[j] = tmp;
			}
			i++;
		}

	}

	return j;
}

/* Algoritmo di ordinamento array, insert sort */
void insertsort(arco_grafo_t **pesi,
			    int sx,
				int dx, 
				int scelta)
{
	int i,
	    j;

	arco_grafo_t *chiave;

    for(j = sx + 1; (j <= dx); j++)
	{
		if(scelta == 0)
		{
			for(chiave = pesi[j], i = j - 1;
				(i >= sx) && (pesi[i] -> distanza > chiave -> distanza);
				i--)  
			{
				pesi[i + 1] = pesi[i];
			}
			if((i + 1) != j)
				pesi[i + 1] = chiave;
		}
		else
		{
			for(chiave = pesi[j], i = j - 1;
				(i >= sx) && (pesi[i] -> tempo_percorrenza > chiave -> tempo_percorrenza);
				i--)  
			{
				pesi[i + 1] = pesi[i];
			}
			if((i + 1) != j)
				pesi[i + 1] = chiave;
			
		}
	}
}	
