/******************************************************/
/* Progetto sessione estiva 2016-17 *******************/
/* Studenti: Mancini Andrea Matricola: 276435 *********/
/*********** Perticaroli Luca matricola: 278970 *******/
/******************************************************/

#define INF 1000000

/*****************************/
/* Inclusione delle librerie */
/*****************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "libreria.h"

/************************************/
/* Definizione della funzione Main **/
/************************************/

int main(void)
{
	vertice_grafo_t *vertice_p,
					*grafo,				/* Testa della lista primaria */
					*partenza, 			/* Vertice di partenza per il calcolo del percorso più breve */
					*destinazione;		/* Vertice di arrivo per il calcolo del percorso più breve */
	char 	nome_stazione[15],			/* Variabile per nome della stazione */
			carattere_rimosso;			/* Variabile per pulizia buffer */
	int n,
		scelta,							/* Variabile per la scelta di azioni dell'utente */
		esito_lettura,					/* variabile per valore di ritorno della scanf */
		num_archi_tot;					/* variabile per numero archi totali */							
	
	
	grafo = NULL;
	partenza = NULL;
	num_archi_tot = 0;
	
	/* acquisisco il grafo */
	n = acquisizione_grafo(&grafo, &num_archi_tot);
	
	
	printf("**************************************************************************\n");
	printf("** Benvenuto nel programma per il calcolo del percorso piu' breve tra  ***\n");
	printf("** due stazioni ferroviarie e statistiche d'ordine sui pesi degli archi **\n");
	printf("**************************************************************************\n");
	
	printf("\n*********************************************");
	printf("\n*** Autori: Mancini Andrea, Perticaroli Luca*");
	printf("\n*** Docente: Ing. Valerio Freschi************");
	printf("\n*** Corso: Algoritmi e strutture dati********");
	printf("\n*** Sessione estiva 2016/2017****************");
	printf("\n*********************************************");

		
	do 
	{	
		/* Validazione stretta degli input nel menu */
		do
		{
			printf("\n\n\n-------------------------MENU'-------------------------");
			printf("\nDigitare 1) per il calcolo della distanza piu' breve tra due stazioni.");
			printf("\nDigitare 2) per il calcolo del minor tempo di percorrenza tra due stazioni.");
			printf("\nDigitare 3) per il calcolo delle statistiche sui pesi degli archi in base alla distanza.");
			printf("\nDigitare 4) per il calcolo delle statistiche degli archi in base al tempo di percorrenza.");
			printf("\nDigitare 0) per terminare il programma.\n");
		
			esito_lettura = scanf("%d", &scelta);
			if(esito_lettura != 1 || scelta > 4)
			{
				printf("Input non accettabile!\n\n");
				do
					carattere_rimosso = getchar();
				while(carattere_rimosso != '\n');
			}
		}
		while(esito_lettura != 1 || scelta > 4);

		switch(scelta)
		{
			/* scelta 1 calcolo della distanza più breve in base alla distanza */
			case 1:
				/* richiesta Input con validazione stretta */
				do
				{
					printf("Seleziona tra le seguenti la stazione di partenza:\n");
					for(vertice_p = grafo; vertice_p != NULL; vertice_p = vertice_p -> stazione_succ_p)
					printf("\nstazione di:	%s", vertice_p -> nome_stazione);
					printf("\n\n");
					esito_lettura = scanf("%s", nome_stazione);
					partenza = cerca_in_lista_primaria(grafo, nome_stazione);
					if(partenza == NULL)
					{
						printf("Errore input non accettabile!\n");
						do
							carattere_rimosso = getchar();
						while(carattere_rimosso != '\n');
					}
				}
				while(partenza == NULL || esito_lettura != 1);
				/* richiesta Input con validazione stretta */
				do
				{
					printf("\nSeleziona stazione di arrivo:\n");
					esito_lettura = scanf("%s",nome_stazione);
					destinazione = cerca_in_lista_primaria(grafo, nome_stazione);
					if(destinazione == NULL || esito_lettura != 1)
					{
						printf("Errore input non accettabile!\n");
						do
							carattere_rimosso = getchar();
						while(carattere_rimosso != '\n');
					}
				}
				while(destinazione == NULL || esito_lettura != 1);
				/* richiamo la funzione per calcolo del percorso piu' breve in base alla distanza */
				dijkstra_distanza(grafo, partenza, n);
				
				if(destinazione -> min == INF)
					printf("Percorso non presente!");
				else
				{	
					printf("La distanza minima da %s a %s e' di %.2f Kilometri",
							partenza -> nome_stazione,
							destinazione -> nome_stazione,
							destinazione -> min);
					/* richiamo la funzione assegna figli in modo da poter stampare in ordire il percorso */
					assegna_figli(partenza, destinazione);
					printf("\nseguendo il seguente percorso:\n");
					/* faccio una visita della lista partendo dal vertice di partenza scorrendo i figli */
					for(vertice_p = partenza; vertice_p != NULL; vertice_p = vertice_p -> figlio_p)
						printf("%s\n", vertice_p -> nome_stazione);
			
				}
				break;
			/* scelta 2 calcolo della distanza più breve in base al tempo */
			case 2:
				do
				{
					/* Inserimento di input sempre con validazione stretta */
					printf("Seleziona la stazione da cui partire tra le seguenti:\n");
					for(vertice_p = grafo; vertice_p != NULL; vertice_p = vertice_p -> stazione_succ_p)
					printf("\nStazione di:	%s", vertice_p -> nome_stazione);
					printf("\n\n");
					esito_lettura = scanf("\n%s", nome_stazione);
					partenza = cerca_in_lista_primaria(grafo, nome_stazione);
					if(partenza == NULL || esito_lettura != 1)
					{
						printf("Errore input non accettabile!\n");
						do
							carattere_rimosso = getchar();
						while(carattere_rimosso != '\n');
					}
				}
				while(partenza == NULL || esito_lettura != 1);
				
				do
				{
					printf("Seleziona stazione di arrivo:\n");
					esito_lettura = scanf("\n%s",nome_stazione);
					destinazione = cerca_in_lista_primaria(grafo, nome_stazione);
					if(destinazione == NULL || esito_lettura != 1)
					{
						printf("Errore input non accettabile!\n");
						do
							carattere_rimosso = getchar();
						while(carattere_rimosso != '\n');
					}
				}
				while(destinazione == NULL || esito_lettura != 1);
				dijkstra_tempo(grafo, partenza, n);
				if(destinazione -> min == INF)
					printf("Percorso non presente!");
				else
				{
					printf("Tempo di percorrenza minimo da %s a %s e' di %.2f Minuti",
						   partenza -> nome_stazione,
						   destinazione -> nome_stazione,
						   destinazione -> min);
					assegna_figli(partenza, destinazione);
					printf("\nseguendo il seguente percorso:\n");
					for(vertice_p = partenza; vertice_p != NULL; vertice_p = vertice_p -> figlio_p)
						printf("%s\n", vertice_p -> nome_stazione);
				}
				break;
			/* scelta 3 calcolo delle statistiche in base alle distanze */	
			case 3:
				printf("Le statistiche d'ordine sulle distanze del grafo sono:\n");
				/* richiamo la funzione per le statistiche sulle distanze */
				statistiche(grafo, num_archi_tot,0);
				break;
			/* scelta 4 calcolo delle statistiche in base ai tempi */	
			case 4:
				printf("statistiche d'ordine sui tempi di percorrenza del grafo sono:\n");
				/* richiamo la funzione per le statistiche sui tempi  */
				statistiche(grafo, num_archi_tot, 1);
				break;
			
				
		}
	}
	while(scelta != 0);
	if(scelta == 0)
		printf("------------------PROGRAMMA TERMINATO ARRIVEDERCI------------------\n\n\n");
	
	return(0);
}
