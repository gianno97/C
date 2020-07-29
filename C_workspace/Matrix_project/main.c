#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int ordine_uno, ordine_due, determinante;
    int contatore = 0;
    
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
        for(int i = 0; i < ordine_uno; i++)
        {
            for(int j = 0; j < ordine_uno; j++)
            {
                if(matrice_uno[i][j] == 0)
                {
                    contatore++;
                } 
            }
            if(contatore == ordine_uno)
            {
                determinante = 0;
                break;
            }
            else if(contatore == (ordine_uno - 1))
            {
                for(int a = j; a < ordine_uno; a++)
                {
                    if(matrice_uno[i][a] != 0)
                    {
                        matrice_uno[i][a] * 
                    }
                }
                break;
            }
        }
        
        if(contatore == ordine_uno || contatore == (ordine_uno - 1))
        {
            
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
    
    /*Seconda matrice quadrata*/
    printf("Digita l'ordine della seconda matrice quadrata: ");
    scanf("%d", &ordine_due);
    
    int matrice_due[ordine_due][ordine_due];
    
    for(int i = 0; i < ordine_due; i++)
    {
        for(int j = 0; j < ordine_due; j++)
        {
            matrice_due[i][j] = j * 2; 
        }
    }
    
    for(int i = 0; i < ordine_due; i++)
    {
        for(int j = 0; j < ordine_due; j++)
        {
            printf("%d ", matrice_due[i][j]);
        }
        printf("\n");
    }
}


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
