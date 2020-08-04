#include <stdio.h>
#include <stdlib.h>

int controllo_zeri(int **matrice_uno, int ordine_uno, char *riga_colonna);

int main(void)
{
    int ordine_uno;
    char riga_colonna;
    int **matrice_uno;
    int num = 1;
    
    /*Prima matrice quadrata*/
    /*Prendiamo la grandezza della matrice da tastiera*/
    printf("Digita l'ordine della prima matrice quadrata: ");
    scanf("%d", &ordine_uno);
    
    /*Allochiamo la matrice*/
    matrice_uno = malloc(sizeof(int*) * ordine_uno);
    
    for(int k = 0; k < ordine_uno; k++)
    {
        matrice_uno[k] = malloc(sizeof(int*) * ordine_uno);
    }
    
    /*Riempiamo la matrice con dei valori*/
    for(int i = 0; i < ordine_uno; i++)
    {
        for(int j = 0; j < ordine_uno; j++)
        {
            matrice_uno[i][j] = ++num * 3;
            if(matrice_uno[i][j] == 57 || matrice_uno[i][j] == 72)
            {
                matrice_uno[i][j] = 0;
            }
        }
    }
    
    int risultato = controllo_zeri(matrice_uno, ordine_uno, &riga_colonna);
    
    /*Stampiamo la matrice*/
    for(int i = 0; i < ordine_uno; i++)
    {
        for(int j = 0; j < ordine_uno; j++)
        {
            printf("%d\t", matrice_uno[i][j]);
        }
        printf("\n");
    }
    
    printf("%c\n", riga_colonna);
    printf("%d\n", risultato);
    
}

/*
int power(int base, unsigned int exp)
{
    int result = 1;
    for (int i = 0; i < exp; i++)
        result *= base;
    return result;
}
*/


int controllo_zeri(int **matrice_uno, int ordine_uno, char *riga_colonna)
{
    
    int conta_zeri = 0;
    int max_zeri_riga = 0;
    int max_zeri_colonna = 0;
    int indice_riga = 0;
    int indice_colonna = 0;
    int indice_determinante;
    
 
    /*Controllo la matrice in cerca della riga con il numero di zeri maggiore*/
    for(int i = 0; i < ordine_uno; i++)
    {
        for(int j = 0; j < ordine_uno; j++)
        {
            if(matrice_uno[i][j] == 0)
                conta_zeri++;
        }
        if(conta_zeri > max_zeri_riga)
        {
            max_zeri_riga = conta_zeri;
            conta_zeri = 0;
            indice_riga = i;
        }
        else
            conta_zeri = 0;
    }
    conta_zeri = 0;
    
    
    /*Controllo la matrice in cerca della colonna con il numero di zeri maggiore*/
    for(int j = 0; j < ordine_uno; j++)
    {
        for(int i = 0; i < ordine_uno; i++)
        {
            if(matrice_uno[i][j] == 0)
                conta_zeri++;
        }
        if(conta_zeri > max_zeri_colonna)
        {
            max_zeri_colonna = conta_zeri;
            conta_zeri = 0;
            indice_colonna = j;
        }
        else
            conta_zeri = 0;
    }
    
    /*Confronto la riga con la colonna per conoscere quella con il numero di zeri maggiore*/
    if(max_zeri_riga >= max_zeri_colonna)
    {
        indice_determinante = indice_riga;
        *riga_colonna = 'r';
    }
    else
    {
        indice_determinante = indice_colonna;
        *riga_colonna = 'c';
    }
    
    return indice_determinante;
}

/*
int calcolo_determinante(int ordine_uno, int matrice_uno[][ordine_uno], int matrice_ridotta[][ordine_uno - 1])
{
    int determinante = 0;
    
    
    if(ordine_uno == 1)
        determinante = ordine_uno;
    else if(ordine_uno == 2)
    {
        determinante = matrice_uno[0][0] * matrice_uno[1][1] - matrice_uno[0][1] * matrice_uno[1][0];
    }
    else
    {        
        for(int j = 0; j < ordine_uno; j++)
        {
            determinante += matrice_uno[0][j] * power(-1, j) * calcolo_determinante(ordine_uno, matrice_uno[][ordine_uno], riduzione_matrice(matrice_uno[][ordine_uno]));
        }
    }
    
    return determinante;
}
*/
 
/* 
int **riduzione_matrice(int matrice_uno[][ordine_uno])
{
    
    int matrice_copia[ordine_uno][ordine_uno];
    int **matrice_ridotta;
    int ordine_ridotto = ordine_uno - 1;
    matrice_ridotta = malloc(sizeof(int*) * ordine_ridotto);
    
    for(int k = 0; k < ordine_ridotto; k++)
    {
        matrice_ridotta[k] = malloc(sizeof(int*) * ordine_ridotto);
    }
    */
    
    /*Copio i valori della matrice principale nella matrice copia escludendo tutti i valori*/
    /*che fanno parte della prima riga o della prima colonna*/
    /*
    for(int i = 0; i < ordine_uno; i++)
    {
        for(int j = 0; j < ordine_uno; j++)
        {
            if(matrice_uno[i][j] == matrice_uno[0][j] || matrice_uno[i][j] == matrice_uno[i][0])
                matrice_copia[i][j] = -1;
            else
                matrice_copia[i][j] = matrice_uno[i][j];
        }
    }*/
    
    /*Inserisco tutti i valori diversi da -1 in una matrice ridotta*/
    /*
    for(int i = 1; i < ordine_ridotto; i++)
    {
        for(int j = 1; j < ordine_ridotto; j++)
        {
            matrice_ridotta[i - 1][j - 1] = matrice_uno[i][j];
        }
    }
    
    return matrice_ridotta;
}
*/


/*#include <stdio.h> 
#include <stdlib.h> 

int main() 
{ 

	// This pointer will hold the 
	// base address of the block created 
	int* ptr; 
	int n, i; 

	// Get the number of elements for the array 
	n = 5; 
	printf("Enter number of elements: %d\n", n); 

	// Dynamically allocate memory using malloc() 
	ptr = (int*)malloc(n * sizeof(int)); 

	// Check if the memory has been successfully 
	// allocated by malloc or not 
	if (ptr == NULL) { 
		printf("Memory not allocated.\n"); 
		exit(0); 
	} 
	else { 

		// Memory has been successfully allocated 
		printf("Memory successfully allocated using malloc.\n"); 

		// Get the elements of the array 
		for (i = 0; i < n; ++i) { 
			ptr[i] = i + 1; 
		} 

		// Print the elements of the array 
		printf("The elements of the array are: "); 
		for (i = 0; i < n; ++i) { 
			printf("%d, ", ptr[i]); 
		} 
	} 

	return 0; 
}
 */
