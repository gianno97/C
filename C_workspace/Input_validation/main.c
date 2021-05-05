#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#define MAXINPUT 100

int main()
{
    char input[MAXINPUT] = "";
    int i = 0;
    int number = 0;
    
    while(number < 1 || number > 10)
    {
        printf("%u\n", UINT_MAX);
        printf("%lu\n", ULONG_MAX);
        scanf ("%s", input);
        if (!isdigit(input[i]))
        {
            printf ("Entered input is not valid\n");
        }
        else 
        {
            number = atoi(input);
            if(number < 1 || number > 10)
            {
                printf ("Entered input is a number but is not valid\n");
            }
            else
            {
                printf ("Given input is valid\n");
                printf("Number is: %d\n", number);
            }
        }
    }
}

        /*if (!isdigit(input[i]))
        {
            
            printf ("Entered input is not a number\n");
            //exit(1);
        }
        else
        {
            printf ("Given input is a number\n");
            number = atoi(input);
            printf("Number is: %d\n", number);
        }*/
    


        
        
        
        
        /*scanf ("%s", input);
        length = strlen (input);
        do
        {
            if (!isdigit(input[i]))
            {
                printf ("Entered input is not a number\n");
                //exit(1);
            }
            else
            {
                printf ("Given input is a number\n");
                sentinella = 0;
            }
        }while(sentinella == -1);*/




    //scanf ("%s", input);
    //length = strlen (input);
    /*for(i = 0; i < 1; i++)
    {
        if (!isdigit(input[i]))
        {
            
            printf ("Entered input is not a number\n");
            //exit(1);
        }
        else
        {
            printf ("Given input is a number\n");
            number = atoi(input);
            printf("Number is: %d\n", number);
        }
    }*/