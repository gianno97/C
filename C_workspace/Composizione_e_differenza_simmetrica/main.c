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
    int array_composizione[100] = {0};
    int contatore_esterno = 0;
    int contatore_interno = 0;
    int contatore_prima_rel_bin = 1;
    int contatore_seconda_rel_bin = 0;
    int contatore_elem_coppia_comp = 0;
    int a;
    
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
        contatore_prima_rel_bin += 2;
    }
    
    printf("Composizione:\n");
    for(a = 0; a < 100; a += 2)
        printf("%d,%d ", array_composizione[a], array_composizione[a+1]);
    printf("\n");
    
    
    return 0;
}
