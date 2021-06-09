/*********************************************************/
/* programma per il calcolo della composizione e
   della differenza simmetrica tra due relazioni binarie */
/*********************************************************/

/*****************************/
/* inclusione delle librerie */
/*****************************/

#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/* definizione della variabile di tipo struttura */
/*************************************************/

typedef struct elem_lista
{
    int                valore_uno;
    int                valore_due;
    struct elem_lista *succ_p;
} elem_lista_t;

/********************************/
/* dichiarazione delle funzioni */
/********************************/

void acquisizione_relazione_binaria(int **,
                                    int,
                                    elem_lista_t **,
                                    char stringa_relazione_binaria[]);
void stampa_lista(elem_lista_t *);
int acquisizione_insieme(int **);
int ricerca_lineare_array(int a[],
                          int,
                          int);
int inserisci_in_lista_ordinata(elem_lista_t **,
                                int,
                                int);
void differenza_simmetrica(elem_lista_t *,
                           elem_lista_t *);
void acquisizione_coppia(int **,
                         int,
                         int coppia_rel_bin[]);
void composizione_ricorsiva(elem_lista_t *,
                            elem_lista_t *,
                            elem_lista_t *,
                            elem_lista_t **);

/******************************/
/* definizione delle funzioni */
/******************************/

/* definizione della funzione main */
int main(void)
{
    /* dichiarazione delle variabili locali alla funzione */
    int             *insieme_num_naturali = NULL;   /* input/output: insieme finito numeri naturali */
    int              grandezza_insieme;             /* input: cardinalità insieme */
    elem_lista_t    *testa_p = NULL;                /* input/output: prima relazione binaria */
    elem_lista_t    *testa_p_due = NULL;            /* input/output: seconda relazione binaria */
    elem_lista_t    *testa_p_comp = NULL;           /* output: composizione delle due relazioni binarie */
    /* input: messaggio da stampare durante l'acquisizione della prima relazione binaria */
    char             stringa_prima_relazione_binaria[] = {"Digita due relazioni binarie sull'insieme acquisito da tastiera.\n"
                                                          "Digita la prima relazione binaria.\n"};
    /* input: messaggio da stampare durante l'acquisizione della seconda relazione binaria */
    char             stringa_seconda_relazione_binaria[] = {"Digita la seconda relazione binaria.\n"};
    
    /* acquisire l'insieme finito di numeri naturali */
    grandezza_insieme = acquisizione_insieme(&insieme_num_naturali);
    /* controllare se l'insieme è uguale a 0 */
    if(grandezza_insieme == 0)
        /* stampare messaggio a schermo */
        printf("Insieme vuoto: {}\n");
    else
    {
        /* acquisire prima relazione binaria */
        acquisizione_relazione_binaria(&insieme_num_naturali,
                                       grandezza_insieme,
                                       &testa_p,
                                       stringa_prima_relazione_binaria);
        /* acquisire seconda relazione binaria */
        acquisizione_relazione_binaria(&insieme_num_naturali,
                                       grandezza_insieme,
                                       &testa_p_due,
                                       stringa_seconda_relazione_binaria);
        /* calcolare composizione delle due relazioni binarie */
        composizione_ricorsiva(testa_p,
                               testa_p_due,
                               testa_p_due,
                               &testa_p_comp);
        /* calcolare differenza simmetrica delle due relazioni binarie */
        differenza_simmetrica(testa_p,
                              testa_p_due);
    }
    return (0);
}

/* definizione della funzione per acquisire le due relazioni binarie */
void acquisizione_relazione_binaria(int          **insieme_num_naturali,
                                    int            grandezza_insieme,
                                    elem_lista_t **testa_p,
                                    char           stringa_relazione_binaria[])
{
    elem_lista_t *elem_p = NULL;
    int           fine_inser_rel_bin = 1;
    int           coppia_rel_bin[2] = {-1, -1};
    int           inserito,
                  esito_lettura;
    int           valore_inserito = -1;
    int          *insieme_finito_num_naturali;
    
    insieme_finito_num_naturali = *insieme_num_naturali;
    
    printf("%s",
           stringa_relazione_binaria);
    while(fine_inser_rel_bin == 1)
    {
        printf("Digita il primo numero della coppia:\n");
        acquisizione_coppia(&insieme_finito_num_naturali,
                            grandezza_insieme,
                            coppia_rel_bin);
        printf("Digita il secondo numero della coppia:\n");
        acquisizione_coppia(&insieme_finito_num_naturali,
                            grandezza_insieme,
                            coppia_rel_bin);
        inserito = inserisci_in_lista_ordinata(&elem_p,
                                               coppia_rel_bin[0],
                                               coppia_rel_bin[1]);
        coppia_rel_bin[0] = -1;
        coppia_rel_bin[1] = -1;
        if(inserito == 1)
            printf("Coppia inserita\n");
        else
            printf("Coppia gia' presente all'interno della relazione binaria\n");
        stampa_lista(elem_p);
        printf("\n");
        do
        {
            printf("Digita 0 per terminare l'inserimento delle coppie per la relazione binaria.\n");
            printf("Digita 1 per continuare l'inserimento.\n");
            esito_lettura = scanf("%d",
                                  &valore_inserito);
            
            if(esito_lettura != 1)
                printf("Input non valido!\n");
            else
            {
                if(valore_inserito == 0)
                {
                    printf("Inserimento terminato\n");
                    fine_inser_rel_bin = 0;
                }
                else if(valore_inserito == 1)
                    printf("Proseguimento dell'inserimento\n"); 
                else
                    printf("Input non valido!\n");
            }
            while (getchar() != '\n');
        }
        while(valore_inserito != 0 && valore_inserito != 1);
        valore_inserito = -1;
    }
    *testa_p = elem_p;
}

/* definizione della funzione per acquisire l'insieme finito di numeri naturali */
int acquisizione_insieme(int **insieme_num_naturali)
{
    int  numero_naturale,
         numero_presente,
         i,
         j;
    int  esito_lettura = 0;
    int  grandezza_insieme = -1;
    int  contatore_numeri_insieme = 0;
    int *insieme_finito_num_naturali = NULL;
    
    do
    {
        printf("Digita la grandezza dell'insieme(>= 0):\n");
        esito_lettura = scanf("%d",
                              &grandezza_insieme);
        if(esito_lettura != 1 || grandezza_insieme < 0)
            printf("Inserimento non valido\n");
        else
            insieme_finito_num_naturali = (int*) malloc(grandezza_insieme * sizeof(int));
        while (getchar() != '\n');
    }
    while(esito_lettura != 1 || grandezza_insieme < 0);
    
    if(grandezza_insieme != 0)
    {
        for(j = 0;
            (j < grandezza_insieme);
            j++)
            insieme_finito_num_naturali[j] = -1;

        printf("Digita uno alla volta i numeri di un insieme finito di numeri naturali{0, 1, 2, 3, 4...}:\n");
        do
        {
            esito_lettura = scanf("%d",
                                  &numero_naturale);
            if(esito_lettura != 1 || numero_naturale < 0)
                printf("Inserimento non valido\n");
            else
            {
                numero_presente = ricerca_lineare_array(insieme_finito_num_naturali,
                                                        grandezza_insieme,
                                                        numero_naturale);
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
        printf("{");
        for(i = 0;
            (i < grandezza_insieme);
            i++)
        {
            if(i != (grandezza_insieme - 1))
                printf("%d,",
                       insieme_finito_num_naturali[i]);
            else
                printf("%d}",
                       insieme_finito_num_naturali[i]);
        }
        printf("\n");
    *insieme_num_naturali = insieme_finito_num_naturali;
    }
    return(grandezza_insieme);
}

/* definizione della funzione per acquisire le coppie delle due relazioni binarie */
void acquisizione_coppia(int **insieme_num_naturali,
                         int   grandezza_insieme,
                         int   coppia_rel_bin[])
{
    int  esito_lettura,
         numero_coppia;
    int  trovato = -1;
    int *insieme_finito_num_naturali;
    
    insieme_finito_num_naturali = *insieme_num_naturali;
    
    do
    {
        esito_lettura = scanf("%d",
                              &numero_coppia);
        if (esito_lettura != 1)
            printf("Inserimento non valido\n");
        else 
        {
            trovato = ricerca_lineare_array(insieme_finito_num_naturali,
                                            grandezza_insieme,
                                            numero_coppia);
            if(trovato == -1)
                printf ("Il numero inserito non e' presente all'interno dell'insieme\n");
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

/* definizione della funzione per calcolare la differenza simmetrica tra le due relazioni binarie */
void differenza_simmetrica(elem_lista_t *testa_p,
                           elem_lista_t *testa_p_due)
{
    elem_lista_t *elem_p_diff,
                 *elem_p_diff_due;
    int           sentinella = 1;
    elem_lista_t *testa_p_diff = NULL;
    
    printf("Differenza simmetrica:\n");
    for(elem_p_diff = testa_p;
        (elem_p_diff != NULL);
        elem_p_diff = elem_p_diff->succ_p)
    {
        for(elem_p_diff_due = testa_p_due;
            (elem_p_diff_due != NULL) && (sentinella != 0);
            elem_p_diff_due = elem_p_diff_due->succ_p)
        {
            if(elem_p_diff->valore_uno == elem_p_diff_due->valore_uno && elem_p_diff->valore_due == elem_p_diff_due->valore_due)
                sentinella = 0;
            else
                if(elem_p_diff_due->succ_p == NULL)
                    inserisci_in_lista_ordinata(&testa_p_diff,
                                                elem_p_diff->valore_uno,
                                                elem_p_diff->valore_due);
        }
        sentinella = 1;
    }
    
    for(elem_p_diff_due = testa_p_due;
        (elem_p_diff_due != NULL);
        elem_p_diff_due = elem_p_diff_due->succ_p)
    {
        for(elem_p_diff = testa_p;
            (elem_p_diff != NULL) && (sentinella != 0);
            elem_p_diff = elem_p_diff->succ_p)
        {
            if(elem_p_diff->valore_uno == elem_p_diff_due->valore_uno && elem_p_diff->valore_due == elem_p_diff_due->valore_due)
                sentinella = 0;
            else
                if(elem_p_diff->succ_p == NULL)
                    inserisci_in_lista_ordinata(&testa_p_diff,
                                                elem_p_diff_due->valore_uno,
                                                elem_p_diff_due->valore_due);
        }
        sentinella = 1;
    }
    stampa_lista(testa_p_diff);
    printf("\n");
}

/* definizione della funzione per calcolare la composizione tra le due relazioni binarie */
void composizione_ricorsiva(elem_lista_t  *elem_p,
                            elem_lista_t  *elem_p_due,
                            elem_lista_t  *testa_p_due,
                            elem_lista_t **testa_p_comp)
{
    if(elem_p != NULL)
    {
        if(elem_p->valore_due == elem_p_due->valore_uno)
        {
            inserisci_in_lista_ordinata(testa_p_comp,
                                        elem_p->valore_uno,
                                        elem_p_due->valore_due);
            if(elem_p_due->succ_p != NULL)
                composizione_ricorsiva(elem_p,
                                       elem_p_due->succ_p,
                                       testa_p_due,
                                       testa_p_comp);
            else
            {
                elem_p_due = testa_p_due;
                composizione_ricorsiva(elem_p->succ_p,
                                       elem_p_due,
                                       testa_p_due,
                                       testa_p_comp);
            }
        }
        else
        {
            if(elem_p_due->succ_p != NULL)
                composizione_ricorsiva(elem_p,
                                       elem_p_due->succ_p,
                                       testa_p_due,
                                       testa_p_comp);
            else
            {
                elem_p_due = testa_p_due;
                composizione_ricorsiva(elem_p->succ_p,
                                       elem_p_due,
                                       testa_p_due,
                                       testa_p_comp);
            }
        }
    }
    else
    {
        printf("Composizione:\n");
        stampa_lista(*testa_p_comp);
        printf("\n");
    }
}

/* definizione della funzione per la ricerca di un valore all'interno dell'insieme finito di numeri naturali */
int ricerca_lineare_array(int a[],
                          int n,
                          int valore)
{
    int i;
    
    for(i = 0;
        ((i < n) && (a[i] != valore));
        i++);
    return((i < n)?
             i:
             -1);
}

/* definizione della funzione per l'inserimento dei valori all'interno della lista */
int inserisci_in_lista_ordinata(elem_lista_t **testa_p,
                                int            valore_uno,
                                int            valore_due)
{
    int           inserito = 1;
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

/* definizione della funzione per stampare la lista */
void stampa_lista(elem_lista_t *testa_p)
{
    elem_lista_t *elem_p;
    
    if(testa_p != NULL)
    {
        printf("{");
        for(elem_p = testa_p;
            (elem_p != NULL);
            elem_p = elem_p->succ_p)
            {
                if(elem_p->succ_p != NULL)
                    printf("(%d,%d),",
                           elem_p->valore_uno,
                           elem_p->valore_due);
                else
                    printf("(%d,%d)}",
                           elem_p->valore_uno,
                           elem_p->valore_due);
            }
    }
}
