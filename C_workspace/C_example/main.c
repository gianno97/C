#include <stdio.h>
#include <stdlib.h>

/***************LIBERARE LA MEMORIA DEI PUNTATORI***************************/
/*1. Formattazione output*/
/*1. Long double*/
/*1. Controlli stretti sui valori in input*/
/*1. Controlli sui valori massimi e minimi inseribili in riferimento al long double*/

double calcola_determinante(double **matrice_uno, int ordine_uno);
void matrice_inversa(double determinante, double **matrice_uno, int ordine_uno);
void calcola_matrice_trasposta(double **matrice_due, int ordine_due);

int main(void)
{
    double determinante;
    double **matrice_uno, **matrice_due;
    int ordine_uno, ordine_due;
    
    /*Prima matrice quadrata*/
    /*Prendiamo la grandezza della matrice da tastiera*/
    printf("Digita l'ordine della prima matrice quadrata: ");
    scanf("%d", &ordine_uno);
    
    /*Allochiamo la matrice*/
    matrice_uno = malloc(sizeof(double*) * ordine_uno);
    
    for(int q = 0; q < ordine_uno; q++)
    {
        matrice_uno[q] = malloc(sizeof(double*) * ordine_uno);
    }
    
    printf("Inserisci i valori per una matrice quadrata di ordine %d\n", ordine_uno);
    
    for(int i = 0; i < ordine_uno; i++)
        for(int j = 0; j < ordine_uno; j++)
            scanf("%lf", &matrice_uno[i][j]);
    
    /*Seconda matrice quadrata*/
    /*Prendiamo la grandezza della matrice da tastiera*/
    printf("Digita l'ordine della seconda matrice quadrata: ");
    scanf("%d", &ordine_due);
    
    /*Allochiamo la matrice*/
    matrice_due = malloc(sizeof(double*) * ordine_due);
    
    for(int t = 0; t < ordine_due; t++)
    {
        matrice_due[t] = malloc(sizeof(double*) * ordine_due);
    }
    
    printf("Inserisci i valori per una matrice quadrata di ordine %d\n", ordine_due);
    
    for(int k = 0; k < ordine_due; k++)
        for(int l = 0; l < ordine_due; l++)
            scanf("%lf", &matrice_due[k][l]);
    
    determinante = calcola_determinante(matrice_uno, ordine_uno);
    printf("Il determinante della prima matrice quadrata e' %.3f\n", determinante);
    
    if(determinante != 0)
        if(ordine_uno == 1)
            printf("La matrice inversa della prima matrice quadrata e': %.3f\n", matrice_uno[0][0]);
        else
            matrice_inversa(determinante, matrice_uno, ordine_uno);
    else
        printf("Il determinante della prima matrice quadrata e' nullo, quindi non esiste la matrice inversa\n");
    
    calcola_matrice_trasposta(matrice_due, ordine_due);
    
    return 0;
}

double calcola_determinante(double **matrice_uno, int ordine_uno)
{
    int m, n;
    double determinante;
    double **b;
    int s = 1;
    
    /*Allochiamo la matrice b*/
    b = malloc(sizeof(double*) * ordine_uno - 1);
    
    for(int f = 0; f < ordine_uno - 1; f++)
    {
        b[f] = malloc(sizeof(double*) * ordine_uno - 1);
    }
    
    if(ordine_uno == 1)
        determinante = matrice_uno[0][0];
    else
    {
        determinante = 0;
        for(int c = 0; c < ordine_uno; c++)
        {
            m = 0;
            n = 0;
            for(int i = 0; i < ordine_uno; i++)
            {
                for(int j = 0; j < ordine_uno; j++)
                {
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
            determinante = determinante + s * (matrice_uno[0][c] * calcola_determinante(b, ordine_uno - 1));
            s = -1 * s;
        }
    }
    return determinante;
}

void matrice_inversa(double determinante, double **matrice_uno, int ordine_uno)
{
    int s = 1;
    int m = 0;
    int n = 0;
    int y = 0;
    int u = 0;
    double **matrice_ridotta;
    double **matrice_trasposta;
    double cofattore;
    double reciproco_determinante = 1 / determinante;
    
    /*Allochiamo la matrice_ridotta e la matrice trasposta*/
    matrice_ridotta = malloc(sizeof(double*) * (ordine_uno - 1));
    for(int f = 0; f < (ordine_uno - 1); f++)
    {
        matrice_ridotta[f] = malloc(sizeof(double*) * (ordine_uno - 1));
    }
    
    matrice_trasposta = malloc(sizeof(double*) * ordine_uno);
    for(int p = 0; p < ordine_uno; p++)
    {
        matrice_trasposta[p] = malloc(sizeof(double*) * ordine_uno);
    }
    
    for(int g = 0; g < ordine_uno; g++)
    {
        for(int h = 0; h < ordine_uno; h++)
        {
            for(int a = 0; a < ordine_uno; a++)
            {
                for(int b = 0; b < ordine_uno; b++)
                {
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
            cofattore = s * calcola_determinante(matrice_ridotta, ordine_uno - 1);
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
    
    printf("La matrice inversa della prima matrice quadrata e':\n");
    for(int z = 0; z < ordine_uno; z++)
    {
        for(int x = 0; x < ordine_uno; x++)
        {
            printf("  %.3f  ", reciproco_determinante * matrice_trasposta[z][x]);
        }
        printf("\n");
    }
}

void calcola_matrice_trasposta(double **matrice_due, int ordine_due)
{
    printf("La matrice trasposta della seconda matrice quadrata e':\n");
    
    for(int i = 0; i < ordine_due; i++)
    {
        for(int j = 0; j < ordine_due; j++)
        {
            printf("  %.3f  ", matrice_due[j][i]);
        }
        printf("\n");
    }
}
