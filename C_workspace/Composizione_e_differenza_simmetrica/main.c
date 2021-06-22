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
    int              cardinalita_insieme;           /* input: cardinalità insieme */
    elem_lista_t    *testa_p = NULL;                /* input/output: prima relazione binaria */
    elem_lista_t    *testa_p_due = NULL;            /* input/output: seconda relazione binaria */
    elem_lista_t    *testa_p_comp = NULL;           /* output: composizione delle due relazioni binarie */
    /* input: messaggio da stampare durante l'acquisizione della prima relazione binaria */
    char             stringa_prima_relazione_binaria[] = {"Digita due relazioni binarie sull'insieme acquisito da tastiera.\n"
                                                          "Digita la prima relazione binaria.\n"};
    /* input: messaggio da stampare durante l'acquisizione della seconda relazione binaria */
    char             stringa_seconda_relazione_binaria[] = {"Digita la seconda relazione binaria.\n"};
    
    /* acquisire l'insieme finito di numeri naturali */
    cardinalita_insieme = acquisizione_insieme(&insieme_num_naturali);
    /* controllare se l'insieme è uguale a 0 */
    if(cardinalita_insieme == 0)
        /* stampare messaggio a schermo */
        printf("Insieme vuoto: {}\n");
    else
    {
        /* acquisire la prima relazione binaria */
        acquisizione_relazione_binaria(&insieme_num_naturali,
                                       cardinalita_insieme,
                                       &testa_p,
                                       stringa_prima_relazione_binaria);
        /* acquisire la seconda relazione binaria */
        acquisizione_relazione_binaria(&insieme_num_naturali,
                                       cardinalita_insieme,
                                       &testa_p_due,
                                       stringa_seconda_relazione_binaria);
        /* calcolare la composizione delle due relazioni binarie */
        composizione_ricorsiva(testa_p,
                               testa_p_due,
                               testa_p_due,
                               &testa_p_comp);
        /* calcolare la differenza simmetrica delle due relazioni binarie */
        differenza_simmetrica(testa_p,
                              testa_p_due);
    }
    return (0);
}

/* definizione della funzione per acquisire le due relazioni binarie */
void acquisizione_relazione_binaria(int          **insieme_num_naturali,        /* input: insieme finito numeri naturali */
                                    int            cardinalita_insieme,         /* input: cardinalità insieme */
                                    elem_lista_t **testa_p,                     /* output: relazione binaria */
                                    char           stringa_relazione_binaria[]) /* input: stringa da stampare */
{
    /* dichiarazione delle variabili locali alla funzione */
    elem_lista_t *elem_p = NULL;                                        /* output: relazione binaria */
    int           fine_inser_rel_bin = 1;                               /* input: operazione scelta dall'utente */
    int           coppia_rel_bin[2] = {-1, -1};                         /* input: coppia relazione binaria */
    int           inserito,                                             /* lavoro: esito inserimento coppia */
                  esito_lettura;                                        /* lavoro: esito della scanf */
    int           valore_inserito = -1;                                 /* input: valore inserito dall'utente */
    int          *insieme_finito_num_naturali = *insieme_num_naturali;  /* input: insieme finito numeri naturali */
    
    /* stampare la stringa */
    printf("%s",
           stringa_relazione_binaria);
    /* acquisire la relazione binaria */
    while(fine_inser_rel_bin == 1)
    {
        printf("Digita il primo numero della coppia:\n");
        /* acquisire il primo numero della coppia */
        acquisizione_coppia(&insieme_finito_num_naturali,
                            cardinalita_insieme,
                            coppia_rel_bin);
        printf("Digita il secondo numero della coppia:\n");
        /* acquisire il secondo numero della coppia */
        acquisizione_coppia(&insieme_finito_num_naturali,
                            cardinalita_insieme,
                            coppia_rel_bin);
        /* inserire la coppia all'interno della relazione binaria */
        inserito = inserisci_in_lista_ordinata(&elem_p,
                                               coppia_rel_bin[0],
                                               coppia_rel_bin[1]);
        coppia_rel_bin[0] = -1;
        coppia_rel_bin[1] = -1;
        /* controllare che la coppia non sia già presente all'interno della relazione binaria */
        if(inserito == 1)
            printf("Coppia inserita\n");
        else
            printf("Coppia gia' presente all'interno della relazione binaria\n");
        /* stampare la relazione binaria */
        stampa_lista(elem_p);
        printf("\n");
        /* proseguire o terminare l'inserimento delle coppie per la relazione binaria */
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
    /* assegnare l'indirizzo della lista contenente la relazione binaria alla variabile presente nella funzione main */
    *testa_p = elem_p;
}

/* definizione della funzione per acquisire l'insieme finito di numeri naturali */
int acquisizione_insieme(int **insieme_num_naturali) /* output: insieme finito numeri naturali*/
{
    /* dichiarazione delle variabili locali alla funzione */
    int  numero_naturale,                       /* input: numero inserito dall'utente */
         numero_presente,                       /* lavoro: esito ricerca nell'insieme */
         i,                                     /* lavoro: indice per stampare l'insieme */
         j;                                     /* lavoro: indice per inizializzare l'insieme */
    int  esito_lettura = 0;                     /* lavoro: esito della scanf */
    int  cardinalita_insieme = -1;              /* input: cardinalità dell'insieme */
    int  contatore_numeri_insieme = 0;          /* input: contatore cardinalità dell'insieme */
    int *insieme_finito_num_naturali = NULL;    /* output: insieme finito numeri naturali*/
    
    /* acquisire la grandezza dell'insieme e allocare dinamicamente l'insieme */
    do
    {
        printf("Digita la cardinalita' dell'insieme(>= 0):\n");
        esito_lettura = scanf("%d",
                              &cardinalita_insieme);
        if(esito_lettura != 1 || cardinalita_insieme < 0)
            printf("Inserimento non valido\n");
        else
            insieme_finito_num_naturali = (int*) malloc(cardinalita_insieme * sizeof(int));
        while (getchar() != '\n');
    }
    while(esito_lettura != 1 || cardinalita_insieme < 0);
    
    /* controllare che la grandezza dell'insieme sia diversa da 0 */
    if(cardinalita_insieme != 0)
    {
        /* inizializzare i numeri dell'insieme a -1 */
        for(j = 0;
            (j < cardinalita_insieme);
            j++)
            insieme_finito_num_naturali[j] = -1;

        /* acquisire i numeri dell'insieme */
        printf("Digita uno alla volta i numeri di un insieme finito di numeri naturali:\n");
        do
        {
            esito_lettura = scanf("%d",
                                  &numero_naturale);
            if(esito_lettura != 1 || numero_naturale < 0)
                printf("Inserimento non valido\n");
            else
            {
                /* controllare che il numero non sia già presente all'interno dell'insieme */
                numero_presente = ricerca_lineare_array(insieme_finito_num_naturali,
                                                        cardinalita_insieme,
                                                        numero_naturale);
                if(numero_presente == -1)
                {
                    /* inserire all'interno dell'insieme il numero acquisito */
                    insieme_finito_num_naturali[contatore_numeri_insieme] = numero_naturale;
                    contatore_numeri_insieme++;
                }
                else
                    printf("Il numero inserito e' gia' presente all'interno dell'insieme\n");
            }
            while (getchar() != '\n');
        }
        while(esito_lettura != 1 || numero_naturale < 0 || (contatore_numeri_insieme < cardinalita_insieme));
    
        /* stampare l'insieme */
        printf("Insieme acquisito da tastiera:\n");
        printf("{");
        for(i = 0;
            (i < cardinalita_insieme);
            i++)
        {
            if(i != (cardinalita_insieme - 1))
                printf("%d,",
                       insieme_finito_num_naturali[i]);
            else
                printf("%d}",
                       insieme_finito_num_naturali[i]);
        }
        printf("\n");
    /* assegnare l'indirizzo del puntatore contenente l'insieme alla variabile presente nella funzione main */
    *insieme_num_naturali = insieme_finito_num_naturali;
    }
    return(cardinalita_insieme);
}

/* definizione della funzione per acquisire le coppie delle due relazioni binarie */
void acquisizione_coppia(int **insieme_num_naturali,    /* input: insieme finito numeri naturali */
                         int   cardinalita_insieme,     /* input: cardinalità dell'insieme */
                         int   coppia_rel_bin[])        /* output: coppia relazione binaria */
{
    /* dichiarazione delle variabili locali alla funzione */
    int  esito_lettura,                                         /* lavoro: esito della scanf */
         numero_coppia;                                         /* input: numero inserito dall'utente */
    int  trovato = -1;                                          /* lavoro: esito ricerca nell'insieme */
    int *insieme_finito_num_naturali = *insieme_num_naturali;   /* input: insieme finito numeri naturali */
    
    /* acquisire le coppie della relazione binaria */
    do
    {
        esito_lettura = scanf("%d",
                              &numero_coppia);
        if (esito_lettura != 1)
            printf("Inserimento non valido\n");
        else 
        {
            /* controllare che sia stato inserito da tastiera un numero che è presente */
            /* all'interno dell'insieme precedentemente acquisito */
            trovato = ricerca_lineare_array(insieme_finito_num_naturali,
                                            cardinalita_insieme,
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
void differenza_simmetrica(elem_lista_t *testa_p,       /* input: prima relazione binaria */
                           elem_lista_t *testa_p_due)   /* input: seconda relazione binaria */
{
    /* dichiarazione delle variabili locali alla funzione */
    elem_lista_t *elem_p_diff,          /* input: prima relazione binaria */
                 *elem_p_diff_due;      /* input: seconda relazione binaria */
    int           sentinella = 1;       /* input: variabile per l'uscita dal ciclo for */
    elem_lista_t *testa_p_diff = NULL;  /* output: differenza simmetrica */
    
    /* calcolare la differenza simmetrica tra le due relazioni binarie */
    printf("Differenza simmetrica:\n");
    /* controllare tutti gli elementi della prima relazione binaria rispetto alla seconda*/
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
    
    /* controllare tutti gli elementi della seconda relazione binaria rispetto alla prima */
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
    /* stampare la differenza simmetrica */
    stampa_lista(testa_p_diff);
    printf("\n");
}

/* definizione della funzione per calcolare la composizione tra le due relazioni binarie */
void composizione_ricorsiva(elem_lista_t  *elem_p,          /* input: prima relazione binaria */
                            elem_lista_t  *elem_p_due,      /* input: seconda relazione binaria */
                            elem_lista_t  *testa_p_due,     /* input: seconda relazione binaria */
                            elem_lista_t **testa_p_comp)    /* output: composizione */
{
    /* calcolare la composizione tra le due relazioni binarie */
    if(elem_p == NULL)
    {
        /* stampare la composizione */
        printf("Composizione:\n");
        stampa_lista(*testa_p_comp);
        printf("\n");
    }
    else
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
}

/* definizione della funzione per la ricerca di un valore all'interno dell'insieme finito di numeri naturali */
int ricerca_lineare_array(int a[],      /* input: insieme finito numeri naturali */
                          int n,        /* input: cardinalità insieme */
                          int valore)   /* input: numero da cercare */
{
    /* dichiarazione delle variabili locali alla funzione */
    int i;  /* output: indice per la ricerca nell'insieme */
    
    /* ricercare il valore all'interno dell'insieme */
    for(i = 0;
        ((i < n) && (a[i] != valore));
        i++);
    return((i < n)?
             i:
             -1);
}

/* definizione della funzione per l'inserimento dei valori all'interno della lista */
int inserisci_in_lista_ordinata(elem_lista_t **testa_p,     /* output: lista di coppie di valori */
                                int            valore_uno,  /* input: primo valore della coppia */
                                int            valore_due)  /* input: secondo valore della coppia*/
{
    /* dichiarazione delle variabili locali alla funzione */
    int           inserito = 1; /* output: esito dell'inserimento nella lista */
    elem_lista_t *corr_p,       /* input: variabile per scorrere la lista */
                 *prec_p,       /* input: variabile per scorrere la lista */
                 *nuovo_p;      /* input: variabile per la creazione di un nuovo elemento della lista */
    
    /* controllare che la coppia di valori non sia già presente nella lista */
    for(corr_p = prec_p = *testa_p;
        (corr_p != NULL);
        prec_p = corr_p, corr_p = corr_p->succ_p)
        {
            if((corr_p->valore_uno == valore_uno) && (corr_p->valore_due == valore_due))
                inserito = 0;
        }
    if(inserito == 1)
    {
        /* inserire la nuova coppia all'interno della lista */
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
void stampa_lista(elem_lista_t *testa_p)    /* input: lista da stampare */
{
    /* dichiarazione delle variabili locali alla funzione */
    elem_lista_t *elem_p;   /* input: lista da stampare */
    
    /* stampare la lista */
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
    else
        printf("{}");
}
