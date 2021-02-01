/*******************************************/
/* Programma per l'ordinamento di un array */
/*******************************************/
	
/*****************************/
/* Inclusione delle librerie */
/*****************************/
		
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*******************************/
/* Definizione nuove strutture */
/*******************************/

typedef struct nodo_albero_bin
{
	int valore;
	struct nodo_albero_bin *sx_p, *dx_p;
} nodo_albero_bin_t;

/************************/
/* Definizione funzioni */
/************************/

int inserisci_in_albero_bin_ric(nodo_albero_bin_t **radice_p, int valore);
nodo_albero_bin_t *cerca_in_albero_bin_ric(nodo_albero_bin_t *radice_p, int valore);

/************************************/
/* Definizione della funzione Main **/
/************************************/

int main(void)

{
		
	/* dichiarazione delle variabili locali alla funzione */
	int	i,
		x,
		y,
		esito_lettura,
		num_elem_albero;
	char carattere_rimosso;
	nodo_albero_bin_t *radice,
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

	radice = NULL;

	srand(time(NULL)); /* inizializza il generatore */

	printf("Gli elementi dell'albero sono:\n");

	for(i = 0; i < 	num_elem_albero; i++)
	{
		x = 1 + rand() % 40; /*genera un numero casuale tra 1 e 40*/
		inserisci_in_albero_bin_ric(&radice, x);
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
	

	esito = cerca_in_albero_bin_ric(radice, y);

	if(esito != NULL)
		printf("Elemento presente nell'albero!\n");
	else
		printf("Elemento non presente nell'albero!\n");
	 
	
	return(0);
}

int inserisci_in_albero_bin_ric(nodo_albero_bin_t **radice_p, int valore)
{
	int inserito;
	nodo_albero_bin_t *nodo_p,
					  *padre_p,
					  *nuovo_p;

	for (nodo_p = padre_p = *radice_p;
		((nodo_p != NULL) && (nodo_p->valore != valore));
		 padre_p = nodo_p, nodo_p = (valore < nodo_p->valore)?
									 nodo_p->sx_p:
								 	 nodo_p->dx_p);
	if (nodo_p != NULL)
		inserito = 0;
	
	else
	{
		inserito = 1;
		nuovo_p = (nodo_albero_bin_t *)malloc(sizeof(nodo_albero_bin_t));
		nuovo_p->valore = valore;
		nuovo_p->sx_p = nuovo_p->dx_p = NULL;
		if (nodo_p == *radice_p)
			*radice_p = nuovo_p;
		else
			if (valore < padre_p->valore)
				padre_p->sx_p = nuovo_p;
			else
				padre_p->dx_p = nuovo_p;
	}
	return(inserito);
}

nodo_albero_bin_t *cerca_in_albero_bin_ric(nodo_albero_bin_t *radice_p, int valore)
{
	nodo_albero_bin_t *nodo_p;

	for (nodo_p = radice_p;
		 ((nodo_p != NULL) && (nodo_p->valore != valore));
         nodo_p = (valore < nodo_p->valore)?
				  nodo_p->sx_p:
				  nodo_p->dx_p);
	return(nodo_p);
}
