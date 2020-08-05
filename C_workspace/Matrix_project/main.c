#include <stdio.h>
#include <stdlib.h>

int controllo_zeri(int **matrice_uno, int *ordine_uno, char *riga_colonna);
int calcolo_determinante(int **matrice_uno, int *ordine_uno, int risultato, char riga_colonna);
int **riduzione_matrice(int **matrice_uno, int *ordine_uno, int riga, int colonna);

int main(void)
{
    int ordine_uno, risultato, determinante;
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
    
    if(ordine_uno == 1)
    {
        determinante = ordine_uno;
    }
    else if(ordine_uno == 2)
    {
        determinante = matrice_uno[0][0] * matrice_uno[1][1] - matrice_uno[0][1] * matrice_uno[1][0];
    }
    else
    {
        risultato = controllo_zeri(matrice_uno, &ordine_uno, &riga_colonna);
        determinante = calcolo_determinante(matrice_uno, &ordine_uno, risultato, riga_colonna);
    }
    
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


int power(int base, unsigned int exp)
{
    int result = 1;
    for (int i = 0; i < exp; i++)
        result *= base;
    return result;
}


int controllo_zeri(int **matrice_uno, int *ordine_uno, char *riga_colonna)
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


int calcolo_determinante(int **matrice_uno, int *ordine_uno, int risultato, char riga_colonna)
{
    int determinante = 0;
    
    if(riga_colonna == 'r')
    {
        
    }
    else
    {
        if(ordine_uno == 1)
        {
            determinante = ordine_uno;
        }
        else if(ordine_uno == 2)
        {
            determinante = matrice_uno[0][0] * matrice_uno[1][1] - matrice_uno[0][1] * matrice_uno[1][0];
        }
        else
        {
            for(int i = 0; i < ordine_uno; i++)
            {
                determinante += matrice_uno[i][risultato] * power(-1, i + risultato) * calcolo_determinante(riduzione_matrice(matrice_uno, ordine_uno, i, risultato),
                ordine_uno, risultato, riga_colonna);
            }
        }
    }
    return determinante;
}



int **riduzione_matrice(int **matrice_uno, int *ordine_uno, int riga, int colonna)
{
    int matrice_copia[ordine_uno][ordine_uno];
    int **matrice_ridotta;
    int ordine_ridotto = ordine_uno - 1;
    int riga_ridotta = 0;
    int colonna_ridotta = 0;
    matrice_ridotta = malloc(sizeof(int*) * ordine_ridotto);
    
    for(int k = 0; k < ordine_ridotto; k++)
    {
        matrice_ridotta[k] = malloc(sizeof(int*) * ordine_ridotto);
    }
    
    /*Copio i valori della matrice principale nella matrice copia*/
    for(int i = 0; i < ordine_uno; i++)
    {
        for(int j = 0; j < ordine_uno; j++)
        {
            matrice_copia[i][j] = matrice_uno[i][j];
        }
    }
    
    /*Inserisco nella matrice ridotta tutti gli elementi che non fanno parte della riga o della colonna dell'elemento selezionato*/
    for(int i = 0; i < ordine_uno; i++)
    {
        for(int j = 0; j < ordine_uno; j++)
        {
            if(matrice_copia[i][j] != matrice_copia[riga][j] || matrice_copia[i][j] != matrice_copia[i][colonna])
            {
                matrice_ridotta[riga_ridotta][colonna_ridotta] = matrice_copia[i][j];
                if(colonna_ridotta == (ordine_ridotto - 1))
                {
                    colonna_ridotta = 0;
                    riga_ridotta++;
                }
                else
                {
                    colonna_ridotta++;
                }
            }
        }
    }
    ordine_uno = ordine_uno - 1;
    return matrice_ridotta;
}