#include <stdio.h>
#include <stdlib.h>

int determinant(int **matrice_uno, int ordine_uno);

int main(void)
{
    int d, i, j;
    //int k;
    //int a[10][10];
    int **matrice_uno;
    int ordine_uno;
    
    /*Prima matrice quadrata*/
    /*Prendiamo la grandezza della matrice da tastiera*/
    printf("Digita l'ordine della prima matrice quadrata: ");
    scanf("%d", &ordine_uno);
    
    /*Allochiamo la matrice*/
    matrice_uno = malloc(sizeof(int*) * ordine_uno);
    
    for(int q = 0; q < ordine_uno; q++)
    {
        matrice_uno[q] = malloc(sizeof(int*) * ordine_uno);
    }
    
/*    printf("Enter order of matrix: ");
    scanf("%d", &k);
    
    if(k > 10)
        exit(0);*/
    
    printf("Enter the value for a matrix of order %d\n", ordine_uno);
    
    for(i = 0; i < ordine_uno; i++)
        for(j = 0; j < ordine_uno; j++)
            scanf("%d", &matrice_uno[i][j]);
    
    d = determinant(matrice_uno, ordine_uno);
    printf("Determinant is %d\n", d);
    /*getch();*/
    
    return 0;
}

int determinant(int **matrice_uno, int ordine_uno)
{
    int det, c, i, j, m, n;
    //int b[10][10];
    int **b;
    int s = 1;
    
    /*Allochiamo la matrice b*/
    b = malloc(sizeof(int*) * ordine_uno);
    
    for(int f = 0; f < ordine_uno; f++)
    {
        b[f] = malloc(sizeof(int*) * ordine_uno);
    }
    
    if(ordine_uno == 1)
        det = matrice_uno[0][0];
    else
    {
        det = 0;
        for(c = 0; c < ordine_uno; c++)
        {
            m = 0;
            n = 0;
            for(i = 0; i < ordine_uno; i++)
            {
                for(j = 0; j < ordine_uno; j++)
                {
                    b[i][j] = 0;
                    if(i != 0 && j != c)
                    {
                        b[m][n] = matrice_uno[i][j];
                        if(n < (ordine_uno - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            det = det + s * (matrice_uno[0][c] * determinant(b, ordine_uno - 1));
            s = -1 * s;
        }
    }
    return det;
}
