#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct 	nodo_albero_bin 
{
	int 	valore;
	struct 	nodo_albero_bin *sx_p, *dx_p;
} nodo_albero_bin_t;

int inserisci_in_albero_binario_ric (nodo_albero_bin_t **radice_p, int value);

int main (void) {

	int 	value,
		i,
		inserito,
		elemento;
    int valore;

printf	("Digitare quanti valori sono presenti nell'albero binario: \n");
scanf	("%d",
		&value);
for	(i=0; (i<value); i++) {
	elemento = rand() % 100 + 1;
	printf	("%d ",elemento);}

//srand (time(NULL));
//value = rand() % 100 + 1;

	nodo_albero_bin_t	*radice_p;
    radice_p->valore = 100;
    valore = 20;
    
    inserito = inserisci_in_albero_binario_ric(&radice_p, valore);
}

int inserisci_in_albero_binario_ric (nodo_albero_bin_t **radice_p, int value) {

	int	inserito;

	nodo_albero_bin_t	*nodo_p,
      				*padre_p,
      				*nuovo_p;

	for	(nodo_p = padre_p = *radice_p;
		((nodo_p != NULL) && (nodo_p->valore != value));
		padre_p = nodo_p, nodo_p = (value < nodo_p->valore)? nodo_p->sx_p : nodo_p->dx_p);

	if	(nodo_p != NULL)

		inserito = 0;

	else {
		inserito = 1;
		nuovo_p = (nodo_albero_bin_t *) malloc (sizeof (nodo_albero_bin_t));
		nuovo_p->valore = value;
		nuovo_p->sx_p = nuovo_p->dx_p = NULL;
		if	(nodo_p == *radice_p)
			*radice_p = nuovo_p;
		else
			if	(value < padre_p->valore)
				padre_p->sx_p = nuovo_p;
			else
				padre_p->dx_p = nuovo_p;}

printf	("Albero generato con successo! \n");

return (inserito);
}


