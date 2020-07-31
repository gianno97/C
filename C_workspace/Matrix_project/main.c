#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int ordine_uno, ordine_due;
    int contatore = 0;
    int determinante = 0;
    
    /*Prima matrice quadrata*/
    /*Prendiamo la grandezza della matrice da tastiera*/
    printf("Digita l'ordine della prima matrice quadrata: ");
    scanf("%d", &ordine_uno);
    
    /*Allochiamo la matrice*/
    int matrice_uno[ordine_uno][ordine_uno];
    
    /*Riempiamo la matrice con dei valori*/
    for(int i = 0; i < ordine_uno; i++)
    {
        for(int j = 0; j < ordine_uno; j++)
        {
            matrice_uno[i][j] = j * 3; 
        }
    }
    
    /*Calcoliamo il determinante della matrice*/
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
            determinante += matrice_uno[0][j] * power(-1, j) * riduzione_matrice(matrice_uno);
        }
    }
    
    /*Stampiamo la matrice*/
    for(int i = 0; i < ordine_uno; i++)
    {
        for(int j = 0; j < ordine_uno; j++)
        {
            printf("%d ", matrice_uno[i][j]);
        }
        printf("\n");
    }
}

int power(int base, unsigned int exp)
{
    int result = 1;
    for (int i = 0; i < exp; i++)
        result *= base;
    return result;
}

int calcolo_determinante(int ordine_uno, int matrice_uno, int matrice_ridotta)
{
    /*Calcoliamo il determinante della matrice*/
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
            determinante += matrice_uno[0][j] * power(-1, j) * calcolo_determinante(ordine_uno, matrice_uno, riduzione_matrice(matrice_uno));
        }
    }
    
    return determinante;
}

int **riduzione_matrice(int matrice_uno)
{
    /*Definizione di una matrice locale in cui copiare i valori della matrice principale*/
    int matrice_copia[ordine_uno][ordine_uno];
    int **matrice_ridotta;
    int ordine_ridotto = ordine_uno - 1;
    matrice_ridotta = malloc(sizeof(int*) * ordine_ridotto);
    
    for(int k = 0; k < ordine_ridotto; k++)
    {
        matrice_ridotta[k] = malloc(sizeof(int*) * ordine_ridotto);
    }
    
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
    for(int i = 1; i < ordine_ridotto; i++)
    {
        for(int j = 1; j < ordine_ridotto; j++)
        {
            matrice_ridotta[i - 1][j - 1] = matrice_uno[i][j];
        }
    }
    
    return matrice_ridotta;
}

/* NON È POSSIBILE FARE IL RETURN DI UN ARRAY IN C*/
/*
int riduzione_matrice(int matrice_uno)
{
    int matrice_ridotta[ordine_uno - 1][ordine_uno - 1];
    
    for(int i = 0; i < ordine_uno; i++)
    {
        for(int j = 0; j < ordine_uno; j++)
        {
            if(matrice_uno[i][j] == matrice_uno[0][j] || matrice_uno[i][j] == matrice_uno[i][0])
            {
                matrice_uno[i][j] = -1;
            }
        }
    }
    
    for(int i = 0; i < ordine_uno; i++)
    {
        for(int j = 0; j < ordine_uno; j++)
        {
            if(matrice_uno[i][j] == -1)
            {
                matrice_ridotta[i][j] = matrice_uno[i][j];
            }
        }
    }
    
    return matrice_ridotta;
}*/


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
