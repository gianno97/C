#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

#define MAXINPUT 100

typedef struct elem_lista
{
    unsigned int valore_uno;
    unsigned int valore_due;
    struct elem_lista *succ_p;
} elem_lista_t;

int ricerca_lineare_array(unsigned int a[], int n, unsigned int valore);
int inserisci_in_lista_ordinata(elem_lista_t **testa_p,
                                unsigned int valore_uno,
                                unsigned int valore_due);
void visita_lista(elem_lista_t *testa_p);

int main(int argc, char **argv)
{
    //int insieme_finito_num_naturali[10] = {0};
    unsigned int *insieme_finito_num_naturali;
    int grandezza_insieme;
    int prima_relazione_binaria[10] = {0};
    int seconda_relazione_binaria[10] = {0};
    unsigned int numero_acquisito = -1;
    unsigned int numero_acquisito_due = -1;
    int i;
    int contatore_numeri_insieme = 0;
    //int contatore_coppie_relazioni_binarie = 0;
    //int j, k;
    int array_composizione[100] = {0};
    int array_diff_simm[100] = {0};
    int contatore_esterno = 0;
    int contatore_interno = 0;
    int contatore_prima_rel_bin = 1;
    int contatore_seconda_rel_bin = 0;
    int contatore_elem_coppia_comp = 0;
    int a, b;
    int contatore_esterno_diff = 0;
    int contatore_interno_diff = 0;
    int contatore_prima_rel_bin_diff_simm = 0;
    int contatore_seconda_rel_bin_diff_simm = 0;
    int contatore_array_diff_simm = 0;
    int esito_lettura;
    int trovato = -1;
    unsigned int coppia_prima_rel_bin[2] = {-1, -1};
    unsigned int coppia_sec_rel_bin[2] = {-1, -1};
    
    /*Dichiarazione variabili per la validazione dell'input*/
    char input[MAXINPUT] = "";
    int contatore_str_input = 0;
    //unsigned long number = -1;

    char input_prima_rel_bin[MAXINPUT] = "";
    int contatore_str_prima_rel_bin = 0;
    char input_seconda_rel_bin[MAXINPUT] = "";
    int contatore_str_seconda_rel_bin = 0;
    char input_sec_rel_bin[MAXINPUT] = "";
    int contatore_str_sec_rel_bin = 0;
    
    elem_lista_t *testa_p = NULL;
    elem_lista_t *testa_p_due = NULL;
    int inserito;
    int fine_inser_prima_rel_bin = 1;
    int fine_inser_sec_rel_bin = 1;
    int valore_inserito = -1;
    //int valore_inserito_due = -1;
    
    
    do
    {
        printf("Digita la grandezza dell'insieme(<= 20):\n");
        esito_lettura = scanf("%d", &grandezza_insieme);
        if(esito_lettura != 1 || grandezza_insieme < 1 || grandezza_insieme > 20)
            printf("Inserimento non valido\n");
        else
            insieme_finito_num_naturali = (unsigned int*) malloc(grandezza_insieme * sizeof(unsigned int));
        while (getchar() != '\n');
    }
    while(esito_lettura != 1 || grandezza_insieme < 1 || grandezza_insieme > 20);
    
    printf("Digita uno alla volta i numeri di un insieme finito di numeri naturali{0, 1, 2, 3, 4...}:\n");
    do
    {
        scanf ("%s", input);
        if (!isdigit(input[contatore_str_input]))
        {
            printf("Inserimento non valido\n");
        }
        else 
        {
            numero_acquisito = strtoul(input, NULL, 0);
            if(numero_acquisito < 0 || numero_acquisito >= ULONG_MAX)
            {
                printf ("L'input inserito è un numero ma non è valido\n");
            }
            else
            {
                insieme_finito_num_naturali[contatore_numeri_insieme] = numero_acquisito;
                contatore_numeri_insieme++;
            }
        }
    }
    while(numero_acquisito < 0 || numero_acquisito >= ULONG_MAX || numero_acquisito == -1 || (contatore_numeri_insieme < grandezza_insieme));
    //numero_acquisito = 0;
    
    printf("Insieme acquisito da tastiera:\n");
    for(i = 0; i < grandezza_insieme; i++)
        printf("%u ", insieme_finito_num_naturali[i]);
    printf("\n");
    
    printf("Digita due relazioni binarie sull'insieme acquisito da tastiera.\n");
    printf("Digita la prima relazione binaria.\n");
    printf("Digita i due numeri della coppia:\n");
    
    while(fine_inser_prima_rel_bin == 1)
    {
        do
        {
            printf("Digita il primo numero della coppia:\n");
            scanf ("%s", input_prima_rel_bin);
            if (!isdigit(input_prima_rel_bin[contatore_str_prima_rel_bin]))
            {
                printf("Inserimento non valido\n");
            }
            else 
            {
                numero_acquisito = strtoul(input_prima_rel_bin, NULL, 0);
                trovato = ricerca_lineare_array(insieme_finito_num_naturali, grandezza_insieme, numero_acquisito);
                if(trovato == -1)
                {
                    printf ("Il numero inserito non è presente all'interno dell'insieme\n");
                }
                else
                {
                    coppia_prima_rel_bin[0] = numero_acquisito;
                    trovato = 0;
                }
            }
        }
        while(trovato == -1);
    
        trovato = -1;
        do
        {
            printf("Digita il secondo numero della coppia:\n");
            scanf ("%s", input_seconda_rel_bin);
            if (!isdigit(input_seconda_rel_bin[contatore_str_seconda_rel_bin]))
            {
                printf("Inserimento non valido\n");
            }
            else 
            {
                numero_acquisito_due = strtoul(input_seconda_rel_bin, NULL, 0);
                trovato = ricerca_lineare_array(insieme_finito_num_naturali, grandezza_insieme, numero_acquisito_due);
                if(trovato == -1)
                {
                    printf ("Il numero inserito non è presente all'interno dell'insieme\n");
                }
                else
                {
                    coppia_prima_rel_bin[1] = numero_acquisito_due;
                    trovato = 0;
                }
            }
        }
        while(trovato == -1);
    
        //printf("%u %u\n", testa_p->valore_uno, testa_p->valore_due);
        inserito = inserisci_in_lista_ordinata(&testa_p, coppia_prima_rel_bin[0], coppia_prima_rel_bin[1]);
        //printf("%u %u\n", testa_p->valore_uno, testa_p->valore_due);
    
        if(inserito == 1)
            printf("Coppia inserita\n");
        else
            printf("Coppia già presente all'interno della relazione binaria\n");
        
        visita_lista(testa_p);
        printf("\n");
        
        do
        {
            printf("Digita 0 per terminare l'inserimento delle coppie per la prima relazione binaria.\n");
            printf("Digita 1 per continuare l'inserimento.\n");
            esito_lettura = scanf("%d", &valore_inserito);
            
            if(esito_lettura != 1 || valore_inserito != 0 || valore_inserito != 1)
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
            }
            while (getchar() != '\n');
        }
        while(esito_lettura != 1 || valore_inserito != 0 || valore_inserito != 1);
    }
    
    printf("Digita la seconda relazione binaria.\n");
    printf("Digita i due numeri della coppia:\n");
    
    while(fine_inser_sec_rel_bin == 1)
    {
        do
        {
            printf("Digita il primo numero della coppia:\n");
            scanf ("%s", input_sec_rel_bin);
            if (!isdigit(input_sec_rel_bin[contatore_str_sec_rel_bin]))
            {
                printf("Inserimento non valido\n");
            }
            else 
            {
                numero_acquisito = strtoul(input_sec_rel_bin, NULL, 0);
                trovato = ricerca_lineare_array(insieme_finito_num_naturali, grandezza_insieme, numero_acquisito);
                if(trovato == -1)
                {
                    printf ("Il numero inserito non è presente all'interno dell'insieme\n");
                }
                else
                {
                    coppia_sec_rel_bin[0] = numero_acquisito;
                    trovato = 0;
                }
            }
        }
        while(trovato == -1);
    
        trovato = -1;
        do
        {
            printf("Digita il secondo numero della coppia:\n");
            scanf ("%s", input_sec_rel_bin);
            if (!isdigit(input_sec_rel_bin[contatore_str_sec_rel_bin]))
            {
                printf("Inserimento non valido\n");
            }
            else 
            {
                numero_acquisito = strtoul(input_sec_rel_bin, NULL, 0);
                trovato = ricerca_lineare_array(insieme_finito_num_naturali, grandezza_insieme, numero_acquisito);
                if(trovato == -1)
                {
                    printf ("Il numero inserito non è presente all'interno dell'insieme\n");
                }
                else
                {
                    coppia_sec_rel_bin[1] = numero_acquisito;
                    trovato = 0;
                }
            }
        }
        while(trovato == -1);
    
        //printf("%u %u\n", testa_p->valore_uno, testa_p->valore_due);
        inserito = inserisci_in_lista_ordinata(&testa_p_due, coppia_sec_rel_bin[0], coppia_sec_rel_bin[1]);
        //printf("%u %u\n", testa_p->valore_uno, testa_p->valore_due);
    
        if(inserito == 1)
            printf("Coppia inserita\n");
        else
            printf("Coppia già presente all'interno della relazione binaria\n");
        
        visita_lista(testa_p_due);
        printf("\n");
        
        do
        {
            printf("Digita 0 per terminare l'inserimento delle coppie per la seconda relazione binaria.\n");
            printf("Digita 1 per continuare l'inserimento.\n");
            esito_lettura = scanf("%d", &valore_inserito);
            
            if(esito_lettura != 1 || valore_inserito != 0 || valore_inserito != 1)
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
            }
            while (getchar() != '\n');
        }
        while(esito_lettura != 1 || valore_inserito != 0 || valore_inserito != 1);
    }
    
    /*Composizione*/
    while(contatore_esterno < 5){
        while(contatore_interno < 5){
            if(prima_relazione_binaria[contatore_prima_rel_bin] == seconda_relazione_binaria[contatore_seconda_rel_bin]){
                array_composizione[contatore_elem_coppia_comp] = prima_relazione_binaria[contatore_prima_rel_bin-1];
                contatore_elem_coppia_comp++;
                array_composizione[contatore_elem_coppia_comp] = seconda_relazione_binaria[contatore_seconda_rel_bin+1];
                contatore_elem_coppia_comp++;
            }
            contatore_seconda_rel_bin += 2;
            contatore_interno++;
        }
        contatore_esterno++;
        contatore_interno = 0;
        contatore_seconda_rel_bin = 0;
        contatore_prima_rel_bin += 2;
    }
    
    printf("Composizione:\n");
    for(a = 0; a < 50; a += 2)
        printf("%d,%d ", array_composizione[a], array_composizione[a+1]);
    printf("\n");
    
    /*Differenza simmetrica*/
    while(contatore_esterno_diff < 10){
        if(contatore_esterno_diff < 5){
            while(contatore_interno_diff < 5){
                if((prima_relazione_binaria[contatore_prima_rel_bin_diff_simm] == seconda_relazione_binaria[contatore_seconda_rel_bin_diff_simm]) && 
                   (prima_relazione_binaria[contatore_prima_rel_bin_diff_simm+1] == seconda_relazione_binaria[contatore_seconda_rel_bin_diff_simm+1])){
                    contatore_interno_diff = 5;
                }
                else{
                    contatore_interno_diff++;
                    contatore_seconda_rel_bin_diff_simm += 2;
                    if(contatore_interno_diff == 5){
                        array_diff_simm[contatore_array_diff_simm] = prima_relazione_binaria[contatore_prima_rel_bin_diff_simm];
                        contatore_array_diff_simm++;
                        array_diff_simm[contatore_array_diff_simm] = prima_relazione_binaria[contatore_prima_rel_bin_diff_simm+1];
                        contatore_array_diff_simm++;
                    }
                }
            }
            contatore_prima_rel_bin_diff_simm += 2;
            contatore_seconda_rel_bin_diff_simm = 0;
            contatore_interno_diff = 0;
            contatore_esterno_diff++;
        }
        else{
            contatore_prima_rel_bin_diff_simm = 0;
            while(contatore_interno_diff < 5){
                if((seconda_relazione_binaria[contatore_seconda_rel_bin_diff_simm] == prima_relazione_binaria[contatore_prima_rel_bin_diff_simm]) && 
                   (seconda_relazione_binaria[contatore_seconda_rel_bin_diff_simm+1] == prima_relazione_binaria[contatore_prima_rel_bin_diff_simm+1])){
                    contatore_interno_diff = 5;
                }
                else{
                    contatore_interno_diff++;
                    contatore_prima_rel_bin_diff_simm += 2;
                    if(contatore_interno_diff == 5){
                        array_diff_simm[contatore_array_diff_simm] = seconda_relazione_binaria[contatore_seconda_rel_bin_diff_simm];
                        contatore_array_diff_simm++;
                        array_diff_simm[contatore_array_diff_simm] = seconda_relazione_binaria[contatore_seconda_rel_bin_diff_simm+1];
                        contatore_array_diff_simm++;
                    }
                }
            }
            contatore_prima_rel_bin_diff_simm = 0;
            contatore_seconda_rel_bin_diff_simm += 2;
            contatore_interno_diff = 0;
            contatore_esterno_diff++;
        }
    }
    
    printf("Differenza simmetrica:\n");
    for(b = 0; b < 50; b += 2)
        printf("%d,%d ", array_diff_simm[b], array_diff_simm[b+1]);
    printf("\n");
    
    return 0;
}

int ricerca_lineare_array(unsigned int a[], int n, unsigned int valore)
{
    int i;
    
    for(i = 0; ((i < n) && (a[i] != valore)); i++);
    
    return ((i < n)?i:-1);
}

int inserisci_in_lista_ordinata(elem_lista_t **testa_p,
                                unsigned int valore_uno,
                                unsigned int valore_due)
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

void visita_lista(elem_lista_t *testa_p)
{
    elem_lista_t *elem_p;
    
    for(elem_p = testa_p;
        (elem_p != NULL);
        elem_p = elem_p->succ_p)
        printf("%u,%u ", elem_p->valore_uno, elem_p->valore_due);
}
