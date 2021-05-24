#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

typedef struct elem_lista
{
    int valore_uno;
    int valore_due;
    struct elem_lista *succ_p;
} elem_lista_t;

void visita_lista(elem_lista_t *testa_p);
int ricerca_lineare_array(int a[],
                          int n,
                          int valore);
int inserisci_in_lista_ordinata(elem_lista_t **testa_p,
                                int valore_uno,
                                int valore_due);
void composizione(elem_lista_t *testa_p,
                  elem_lista_t *testa_p_due,
                  elem_lista_t **testa_p_comp);
void differenza_simmetrica(elem_lista_t *testa_p,
                           elem_lista_t *testa_p_due,
                           elem_lista_t **testa_p_diff);
void acquisizione_coppia(int *insieme_finito_num_naturali,
                         int grandezza_insieme,
                         int coppia_rel_bin[]);
void composizione_ricorsiva(elem_lista_t **testa_p,
                            elem_lista_t **testa_p_due);
int conta_elem_lista(elem_lista_t *testa_p);

int main(int argc, char **argv)
{
    int *insieme_finito_num_naturali;
    int grandezza_insieme;
    int i;
    int j;
    int contatore_numeri_insieme = 0;
    int esito_lettura;
    //int trovato = -1;
    int coppia_prima_rel_bin[2] = {-1, -1};
    int coppia_sec_rel_bin[2] = {-1, -1};
    elem_lista_t *testa_p = NULL;
    elem_lista_t *testa_p_due = NULL;
    //elem_lista_t *testa_p_comp = NULL;
    elem_lista_t *testa_p_diff = NULL;
    int inserito;
    int fine_inser_prima_rel_bin = 1;
    int fine_inser_sec_rel_bin = 1;
    int valore_inserito = -1;
    int numero_presente;
    int numero_naturale;
    //int numero_coppia;
    
    do
    {
        printf("Digita la grandezza dell'insieme(1 <= grandezza <= 20):\n");
        esito_lettura = scanf("%d", &grandezza_insieme);
        if(esito_lettura != 1 || grandezza_insieme < 1 || grandezza_insieme > 20)
            printf("Inserimento non valido\n");
        else
            insieme_finito_num_naturali = (int*) malloc(grandezza_insieme * sizeof(int));
        while (getchar() != '\n');
    }
    while(esito_lettura != 1 || grandezza_insieme < 1 || grandezza_insieme > 20);
    
    for(j = 0; j < grandezza_insieme; j++)
        insieme_finito_num_naturali[j] = -1;
    
    printf("Digita uno alla volta i numeri di un insieme finito di numeri naturali{0, 1, 2, 3, 4...}:\n");
    do
    {
        esito_lettura = scanf("%d", &numero_naturale);
        if(esito_lettura != 1 || numero_naturale < 0)
            printf("Inserimento non valido\n");
        else
        {
            numero_presente = ricerca_lineare_array(insieme_finito_num_naturali, grandezza_insieme, numero_naturale);
            if(numero_presente == -1)
            {
                insieme_finito_num_naturali[contatore_numeri_insieme] = numero_naturale;
                contatore_numeri_insieme++;
            }
            else
                printf("Il numero inserito e' gia' presente all'interno dell'insieme\n");
        }
        while (getchar() != '\n');
    }
    while(esito_lettura != 1 || numero_naturale < 0 || (contatore_numeri_insieme < grandezza_insieme));
    
    printf("Insieme acquisito da tastiera:\n");
    for(i = 0; i < grandezza_insieme; i++)
        printf("%d ", insieme_finito_num_naturali[i]);
    printf("\n");
    
    printf("Digita due relazioni binarie sull'insieme acquisito da tastiera.\n");
    printf("Digita la prima relazione binaria.\n");
    while(fine_inser_prima_rel_bin == 1)
    {
        printf("Digita il primo numero della coppia:\n");
        acquisizione_coppia(insieme_finito_num_naturali, grandezza_insieme, coppia_prima_rel_bin);
        printf("Digita il secondo numero della coppia:\n");
        acquisizione_coppia(insieme_finito_num_naturali, grandezza_insieme, coppia_prima_rel_bin);
        inserito = inserisci_in_lista_ordinata(&testa_p, coppia_prima_rel_bin[0], coppia_prima_rel_bin[1]);
        coppia_prima_rel_bin[0] = -1;
        coppia_prima_rel_bin[1] = -1;
        if(inserito == 1)
            printf("Coppia inserita\n");
        else
            printf("Coppia gia' presente all'interno della relazione binaria\n");
        
        visita_lista(testa_p);
        printf("\n");
        
        do
        {
            printf("Digita 0 per terminare l'inserimento delle coppie per la prima relazione binaria.\n");
            printf("Digita 1 per continuare l'inserimento.\n");
            esito_lettura = scanf("%d", &valore_inserito);
            
            if(esito_lettura != 1)
                printf("Input non valido!\n");
            else
            {
                if(valore_inserito == 0)
                {
                    printf("Inserimento terminato\n");
                    fine_inser_prima_rel_bin = 0;
                }
                else if(valore_inserito == 1)
                {
                    printf("Proseguimento dell'inserimento\n"); 
                }
                else
                    printf("Input non valido!\n");
            }
            while (getchar() != '\n');
        }
        while(valore_inserito != 0 && valore_inserito != 1);
        valore_inserito = -1;
    }
    
    printf("Digita la seconda relazione binaria.\n");
    while(fine_inser_sec_rel_bin == 1)
    {
        printf("Digita il primo numero della coppia:\n");
        acquisizione_coppia(insieme_finito_num_naturali, grandezza_insieme, coppia_sec_rel_bin);
        printf("Digita il secondo numero della coppia:\n");
        acquisizione_coppia(insieme_finito_num_naturali, grandezza_insieme, coppia_sec_rel_bin);
        inserito = inserisci_in_lista_ordinata(&testa_p_due, coppia_sec_rel_bin[0], coppia_sec_rel_bin[1]);
        coppia_sec_rel_bin[0] = -1;
        coppia_sec_rel_bin[1] = -1;
        if(inserito == 1)
            printf("Coppia inserita\n");
        else
            printf("Coppia gia' presente all'interno della relazione binaria\n");
        
        visita_lista(testa_p_due);
        printf("\n");
        
        do
        {
            printf("Digita 0 per terminare l'inserimento delle coppie per la seconda relazione binaria.\n");
            printf("Digita 1 per continuare l'inserimento.\n");
            esito_lettura = scanf("%d", &valore_inserito);
            
            if(esito_lettura != 1)
                printf("Input non valido!\n");
            else
            {
                if(valore_inserito == 0)
                {
                    printf("Inserimento terminato\n");
                    fine_inser_sec_rel_bin = 0;
                }
                else if(valore_inserito == 1)
                {
                    printf("Proseguimento dell'inserimento\n"); 
                }
                else
                    printf("Input non valido!\n");
            }
            while (getchar() != '\n');
        }
        while(valore_inserito != 0 && valore_inserito != 1);
        valore_inserito = -1;
    }
    
    /*Composizione*/
    printf("Composizione:\n");
    //composizione(testa_p, testa_p_due, &testa_p_comp);
    composizione_ricorsiva(&testa_p, &testa_p_due);
    //visita_lista(testa_p_comp);
    printf("\n");
    
    /*Differenza simmetrica*/
    printf("Differenza simmetrica:\n");
    differenza_simmetrica(testa_p, testa_p_due, &testa_p_diff);
    visita_lista(testa_p_diff);
    printf("\n");
    
    return 0;
}

void acquisizione_coppia(int *insieme_finito_num_naturali, int grandezza_insieme, int coppia_rel_bin[])
{
    int esito_lettura,
        numero_coppia;
    int trovato = -1;
        
    do
    {
        esito_lettura = scanf("%d", &numero_coppia);
        if (esito_lettura != 1)
        {
            printf("Inserimento non valido\n");
        }
        else 
        {
            trovato = ricerca_lineare_array(insieme_finito_num_naturali, grandezza_insieme, numero_coppia);
            if(trovato == -1)
            {
                printf ("Il numero inserito non e' presente all'interno dell'insieme\n");
            }
            else
            {
                if(coppia_rel_bin[0] == -1)
                {
                    printf("Primo numero acquisito\n");
                    coppia_rel_bin[0] = numero_coppia;
                    trovato = 0;
                }
                else
                {
                    printf("Secondo numero acquisito\n");
                    coppia_rel_bin[1] = numero_coppia;
                    trovato = 0;
                }
            }
        }
        while (getchar() != '\n');
    }
    while(trovato == -1);
}

void differenza_simmetrica(elem_lista_t *testa_p, elem_lista_t *testa_p_due, elem_lista_t **testa_p_diff)
{
    elem_lista_t *elem_p_diff,
                 *elem_p_diff_due;
    int sentinella = 1;
    
    for(elem_p_diff = testa_p; (elem_p_diff != NULL); elem_p_diff = elem_p_diff->succ_p)
    {
        for(elem_p_diff_due = testa_p_due; (elem_p_diff_due != NULL) && (sentinella != 0); elem_p_diff_due = elem_p_diff_due->succ_p)
        {
            if(elem_p_diff->valore_uno == elem_p_diff_due->valore_uno && elem_p_diff->valore_due == elem_p_diff_due->valore_due)
                sentinella = 0;
            else
                if(elem_p_diff_due->succ_p == NULL)
                    inserisci_in_lista_ordinata(testa_p_diff, elem_p_diff->valore_uno, elem_p_diff->valore_due);
        }
        sentinella = 1;
    }
    
    for(elem_p_diff_due = testa_p_due; (elem_p_diff_due != NULL); elem_p_diff_due = elem_p_diff_due->succ_p)
    {
        for(elem_p_diff = testa_p; (elem_p_diff != NULL) && (sentinella != 0); elem_p_diff = elem_p_diff->succ_p)
        {
            if(elem_p_diff->valore_uno == elem_p_diff_due->valore_uno && elem_p_diff->valore_due == elem_p_diff_due->valore_due)
                sentinella = 0;
            else
                if(elem_p_diff->succ_p == NULL)
                    inserisci_in_lista_ordinata(testa_p_diff, elem_p_diff_due->valore_uno, elem_p_diff_due->valore_due);
        }
        sentinella = 1;
    }
}

void composizione_ricorsiva(elem_lista_t **testa_p, elem_lista_t **testa_p_due)
{
    elem_lista_t *elem_p,
                 *elem_p_due;
    elem_lista_t *testa_p_comp = NULL;
    
    elem_p = *testa_p;
    elem_p_due = *testa_p_due;
    
    if(elem_p_due->succ_p != NULL)
    {
        if(elem_p->valore_due == elem_p_due->valore_uno)
        {
            inserisci_in_lista_ordinata(&testa_p_comp, elem_p->valore_uno, elem_p_due->valore_due);
            //visita_lista(testa_p_comp);
        }
        else
            composizione_ricorsiva(&elem_p, &(elem_p_due->succ_p));
    }
    else
        composizione_ricorsiva(&(elem_p->succ_p), &elem_p_due);
    
    
    
    if((conta_elem_lista(testa_p) == 1) && (conta_elem_lista(testa_p_due) == 1))
    {
        if(elem_p->valore_due == elem_p_due->valore_uno)
            inserisci_in_lista_ordinata(&testa_p_comp, elem_p->valore_uno, elem_p_due->valore_due);
    }
    else
        
    
    visita_lista(testa_p_comp);
}

void composizione(elem_lista_t *testa_p, elem_lista_t *testa_p_due, elem_lista_t **testa_p_comp)
{
    elem_lista_t *elem_p,
                 *elem_p_due;
    
    for(elem_p = testa_p; (elem_p != NULL); elem_p = elem_p->succ_p)
        for(elem_p_due = testa_p_due; (elem_p_due != NULL); elem_p_due = elem_p_due->succ_p)
            if(elem_p->valore_due == elem_p_due->valore_uno)
                inserisci_in_lista_ordinata(testa_p_comp, elem_p->valore_uno, elem_p_due->valore_due);
}

int ricerca_lineare_array(int a[], int n, int valore)
{
    int i;
    
    for(i = 0; ((i < n) && (a[i] != valore)); i++);
    
    return ((i < n)?i:-1);
}

int inserisci_in_lista_ordinata(elem_lista_t **testa_p,
                                int valore_uno,
                                int valore_due)
{
    int          inserito = 1;
    elem_lista_t *corr_p,
                 *prec_p,
                 *nuovo_p;
    
    for(corr_p = prec_p = *testa_p;
        (corr_p != NULL);
        prec_p = corr_p, corr_p = corr_p->succ_p)
        {
            if((corr_p->valore_uno == valore_uno) && (corr_p->valore_due == valore_due))
                inserito = 0;
        }
    if(inserito == 1)
    {
        nuovo_p = (elem_lista_t *)malloc(sizeof(elem_lista_t));
        nuovo_p->valore_uno = valore_uno;
        nuovo_p->valore_due = valore_due;
        nuovo_p->succ_p = corr_p;
        if(corr_p == *testa_p)
            *testa_p = nuovo_p;
        else
            prec_p->succ_p = nuovo_p;
    }
    return(inserito);
}

int conta_elem_lista(elem_lista_t *testa_p)
{
    elem_lista_t *elem_p;
    int conta_elem_lista = 0;
    
    for(elem_p = testa_p;
        (elem_p != NULL);
        elem_p = elem_p->succ_p)
        conta_elem_lista++;
        
    return conta_elem_lista;
}

void visita_lista(elem_lista_t *testa_p)
{
    elem_lista_t *elem_p;
    
    for(elem_p = testa_p;
        (elem_p != NULL);
        elem_p = elem_p->succ_p)
        printf("%d,%d ", elem_p->valore_uno, elem_p->valore_due);
}
