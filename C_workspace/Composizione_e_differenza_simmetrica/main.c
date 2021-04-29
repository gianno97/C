#include <stdio.h>

int main(int argc, char **argv)
{
    int insieme_finito_num_naturali[10] = {0};
    int prima_relazione_binaria[10] = {0};
    int seconda_relazione_binaria[10] = {0};
    int numero_acquisito, i;
    int contatore_numeri_insieme = 0;
    int contatore_coppie_relazioni_binarie = 0;
    int j, k;
    
    printf("Digita uno alla volta i numeri di un insieme finito di numeri naturali{0, 1, 2, 3, 4...}:\n");
    while(contatore_numeri_insieme < 10){
        scanf("%d", &numero_acquisito);
        insieme_finito_num_naturali[contatore_numeri_insieme] = numero_acquisito;
        contatore_numeri_insieme++;
    }
    
    printf("Insieme acquisito da tastiera:\n");
    for(i = 0; i < 10; i++)
        printf("%d ", insieme_finito_num_naturali[i]);
        
    printf("\n");
    
    printf("Digita due relazioni binarie sull'insieme acquisito da tastiera.\n");
    printf("Digita la prima relazione binaria:\n");
    printf("Digita i due numeri della coppia:\n");
    
    while(contatore_coppie_relazioni_binarie < 10){
        scanf("%d %d", &prima_relazione_binaria[contatore_coppie_relazioni_binarie], &prima_relazione_binaria[contatore_coppie_relazioni_binarie+1]);
        contatore_coppie_relazioni_binarie += 2;
    }
    contatore_coppie_relazioni_binarie = 0;
    printf("Prima relazione binaria acquisita!\n");
    
    printf("Digita la seconda relazione binaria:\n");
    printf("Digita i due numeri della coppia:\n");
    while(contatore_coppie_relazioni_binarie < 10){
        scanf("%d %d", &seconda_relazione_binaria[contatore_coppie_relazioni_binarie], &seconda_relazione_binaria[contatore_coppie_relazioni_binarie+1]);
        contatore_coppie_relazioni_binarie += 2;
    }
    printf("Seconda relazione binaria acquisita!\n");
    
    printf("Prima relazione binaria:\n");
    for(j = 0; j < 10; j += 2)
        printf("%d,%d ", prima_relazione_binaria[j], prima_relazione_binaria[j+1]);
    printf("\n");
    
    printf("Seconda relazione binaria:\n");
    for(k = 0; k < 10; k += 2)
        printf("%d,%d ", seconda_relazione_binaria[k], seconda_relazione_binaria[k+1]);
        
    printf("\n");
    
    
    return 0;
}
