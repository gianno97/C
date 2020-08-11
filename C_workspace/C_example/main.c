#include <stdio.h>
#include <stdlib.h>

int determinant(int **matrice_uno, int ordine_uno);
void matrice_inversa(int determinante, int **matrice_uno, int ordine_uno);

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
    
    if(d != 0)
        if(ordine_uno == 1)
            printf("La matrice inversa della prima matrice quadrata e': %d\n", matrice_uno[0][0]);
        else
            matrice_inversa(d, matrice_uno, ordine_uno);
    else
        printf("Il determinante della prima matrice quadrata e' nullo, quindi non esiste la matrice inversa\n");
        
    return 0;
}

int determinant(int **matrice_uno, int ordine_uno)
{
    int det, c, i, j, m, n;
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

void matrice_inversa(int determinante, int **matrice_uno, int ordine_uno)
{
    int s = 1;
    int m = 0;
    int n = 0;
    int y = 0;
    int u = 0;
    int **matrice_ridotta;
    int **matrice_trasposta;
    int cofattore;
    
    /*Allochiamo la matrice_ridotta e la matrice trasposta*/
    matrice_ridotta = malloc(sizeof(int*) * (ordine_uno - 1));
    for(int f = 0; f < (ordine_uno - 1); f++)
    {
        matrice_ridotta[f] = malloc(sizeof(int*) * (ordine_uno - 1));
    }
    
    matrice_trasposta = malloc(sizeof(int*) * ordine_uno);
    for(int p = 0; p < ordine_uno; p++)
    {
        matrice_trasposta[p] = malloc(sizeof(int*) * ordine_uno);
    }
    
    for(int g = 0; g < ordine_uno; g++)
    {
        for(int h = 0; h < ordine_uno; h++)
        {
            for(int a = 0; a < ordine_uno; a++)
            {
                for(int b = 0; b < ordine_uno; b++)
                {
                    //if((matrice_uno[a][b] != matrice_uno[g][b]) || (matrice_uno[a][b] != matrice_uno[a][h]))
                    if(a != g && b != h)
                    {
                        matrice_ridotta[m][n] = matrice_uno[a][b];
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
            m = 0;
            n = 0;
            cofattore = s * determinant(matrice_ridotta, ordine_uno - 1);
            //cofattore = -1 * determinant(matrice_ridotta, ordine_uno - 1);
            s = -1 * s;
            
            if(ordine_uno % 2 == 0)
            {
                if(u % 2 == 1)
                {
                    cofattore = -1 * cofattore;
                }
            }
        
            matrice_trasposta[y][u] = cofattore;
            if(y < ordine_uno - 1)
                y++;
            else
            {
                y = 0;
                u++;
            }
        }
    }
    
    for(int z = 0; z < ordine_uno; z++)
    {
        for(int x = 0; x < ordine_uno; x++)
        {
            printf("%d\t", matrice_trasposta[z][x]);
        }
        printf("\n");
    }
}
