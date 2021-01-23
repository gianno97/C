#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/********************************/
/*definizione di nuove strutture*/
/********************************/

typedef struct nodo_albero_bin{
    int valore;
    struct nodo_albero_bin *sx_p, *dx_p;
}nodo_albero_bin_t;

/****************************/
/*definizione delle funzioni*/
/****************************/

int inserisci_in_albero_bin_ric(nodo_albero_bin_t **radice_p,
                                int valore);
int genera_num_cas(int numeri_casuali[],
                   int dim);
nodo_albero_bin_t *cerca_in_albero_bin_ric(nodo_albero_bin_t *radice_p,
                                            int valore);
int rimuovi_da_albero_bin_ric(nodo_albero_bin_t **radice_p,
                              int valore);
void visita_albero_bin_ant(nodo_albero_bin_t *nodo_p);

/*********************************/
/*definizione della funzione main*/
/*********************************/

int main (void)
{
    int *numeri_casuali,
        i,
        x,
        dim,
        valore,
        inserito,
        rimosso,
        esito_lettura;
    nodo_albero_bin_t *valore_ricercato;
    char c,
         v,
         carattere_rimosso;
    do
	{
		printf("digita il numero di elementi che si vogliono inserire nell'albero (>0):\n");
        esito_lettura = scanf("%d",
                              &dim);
		if(esito_lettura != 1 || dim <= 0)
		{
			printf("\ninput non accettabile!\n\n");
			do
				carattere_rimosso = getchar();
			while(carattere_rimosso != '\n');
		}
	}
	while(esito_lettura != 1 || dim <= 0);

    while(getchar()!='\n');

    numeri_casuali=(int *)malloc(dim*sizeof(int));

    nodo_albero_bin_t *radice_p;

    radice_p = NULL;

    genera_num_cas(numeri_casuali, dim);

    printf("\nGli elementi dell'albero sono:\n");
    for(i=0; i<dim; i++)
    {
        inserito=inserisci_in_albero_bin_ric(&radice_p,
                                             numeri_casuali[i]);
        printf("\n%d",
               numeri_casuali[i]);
    }

    printf("\n\npremi R(r) per ricercare un nodo:");
    printf("\npremi I(i) per inserire un nodo:");
    printf("\npremi D(d) per rimuovere un nodo:\n");



    do
    {
    c = getchar();
    switch(c)
    {
        case 'R':
        case 'r':

        printf("\n\ninserisci valore che vuoi ricercare:\n");
        scanf("%d",
              &valore);

        valore_ricercato = cerca_in_albero_bin_ric(radice_p,
                                                   valore);
        if(valore_ricercato!=NULL)
        printf("il valore ricercato e' presente!\n", valore_ricercato->valore);
        else
            printf("\nil valore non e' presente!\n");

        break;

        case 'I':
        case 'i':

        do {
                do
                {
                    printf("\ndigita il valore da inserire:\n");
                    esito_lettura = scanf("%d",
                                          &valore);
                    if(esito_lettura != 1 || valore < 0)
                    {
                        printf("\ninput non accettabile!\n");
                        do
                            carattere_rimosso = getchar();
                        while(carattere_rimosso != '\n');
                    }
                }
                while(esito_lettura != 1 || valore < 0);


        while(getchar()!='\n');

        inserito = inserisci_in_albero_bin_ric(&radice_p,
                                    valore);
        if(inserito==1)
            printf("\nelemento inserito\n");
        else
            printf("\nnessun inserimento, elemento gia' presente!\n");

        }while(inserito!=1);

        printf("\npremi V(v) se vuoi visitare il l'albero(con visita anticipata), altro per uscire:");
        v=getchar();
        if(v == 'V'||v == 'v'){
            visita_albero_bin_ant(radice_p);
        break;
        }
        else
            break;

        case 'D':
        case 'd':

            do {

                    do
                    {
                        printf("\ndigita il valore da rimuovere:\n");
                        esito_lettura = scanf("%d",
                                              &valore);
                    if(esito_lettura != 1 || valore < 0)
                    {
                        printf("\ninput non accettabile!\n");
                        do
                            carattere_rimosso = getchar();
                        while(carattere_rimosso != '\n');
                    }
                }
                while(esito_lettura != 1 || valore < 0);

        while(getchar()!='\n');

        rimosso = rimuovi_da_albero_bin_ric(&radice_p,
                                             valore);
        if(rimosso==1)
            printf("\nrimosso\n");
        else
            printf("\nnessuna rimozione, l'elemento non e' presente!\n");

        }while(rimosso!=1);

        printf("\npremi V(v) se vuoi visitare il l'albero(con visita anticipata), altro per uscire:");
        v=getchar();
        if(v == 'V'||v == 'v'){
            visita_albero_bin_ant(radice_p);
        break;
        }
        else
            break;

        default:
            printf("\nerrore!, digitare una delle tre lettere!:\n");
            while(getchar()!='\n');
            c = 0;
    }
    }while(c==0);

    return(0);
}

int genera_num_cas(int numeri_casuali[],
                   int dim)
{
    int esito,
        i;

	srand(time (NULL));

	for (i=0; i<dim;i++)

	{
		numeri_casuali[i] = 1 + rand() % dim;
	}
}

int inserisci_in_albero_bin_ric(nodo_albero_bin_t **radice_p,
                                int valore)
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

nodo_albero_bin_t *cerca_in_albero_bin_ric(nodo_albero_bin_t *radice_p,
                                           int valore)
{
    nodo_albero_bin_t *nodo_p;

    for (nodo_p = radice_p;
        ((nodo_p != NULL) && (nodo_p->valore != valore));
        nodo_p = (valore < nodo_p->valore)?
        nodo_p->sx_p:
        nodo_p->dx_p);

    return(nodo_p);
}

int rimuovi_da_albero_bin_ric(nodo_albero_bin_t **radice_p,
                              int valore)
{
    int rimosso;
    nodo_albero_bin_t *nodo_p,
                      *padre_p,
                      *sost_p;
    for (nodo_p = padre_p = *radice_p;
        ((nodo_p != NULL) && (nodo_p->valore != valore));
        padre_p = nodo_p, nodo_p = (valore < nodo_p->valore)?
        nodo_p->sx_p:
        nodo_p->dx_p);
            if (nodo_p == NULL)
    rimosso = 0;
    else
    {
        rimosso = 1;
        if (nodo_p->sx_p == NULL)
        {
            if (nodo_p == *radice_p)
                *radice_p = nodo_p->dx_p;
            else
                if (valore < padre_p->valore)
                    padre_p->sx_p = nodo_p->dx_p;
                else
                    padre_p->dx_p = nodo_p->dx_p;
        }
        else
            if (nodo_p->dx_p == NULL)
        {
        if (nodo_p == *radice_p)
            *radice_p = nodo_p->sx_p;
        else
            if (valore < padre_p->valore)
                padre_p->sx_p = nodo_p->sx_p;
            else
                padre_p->dx_p = nodo_p->sx_p;
        }
        else
        {
            sost_p = nodo_p;
            for (padre_p = sost_p, nodo_p = sost_p->sx_p;
                (nodo_p->dx_p != NULL);
                padre_p = nodo_p, nodo_p = nodo_p->dx_p);
                sost_p->valore = nodo_p->valore;
            if (padre_p == sost_p)
                padre_p->sx_p = nodo_p->sx_p;
            else
                padre_p->dx_p = nodo_p->sx_p;
            }
            free(nodo_p);
        }
        return(rimosso);
}

void visita_albero_bin_ant(nodo_albero_bin_t *nodo_p)
{
	if (nodo_p != NULL)
	{
		printf("%d,", nodo_p->valore);
		visita_albero_bin_ant(nodo_p->sx_p);
		visita_albero_bin_ant(nodo_p->dx_p);
	}
}

