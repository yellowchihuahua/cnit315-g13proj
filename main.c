#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"


void PrintDeveloperCredits() {
  // Print the information
  printf("Credits:\n");
  printf("Developed Oct. 2023\n");
  printf("Joyanna Hammer, Ryan Cosillo, Hunter King, Chia-Hua Lin\n");
}

void DisplayMenu(){
    int cont = 1;
    char input[4];

    do {
        char functionNumber = 0; //ref https://www.programiz.com/c-programming/examples/calculator-switch-case
        printf("\n===============================================================================\n");
        printf("Here are your options: \n");
        printf("(1) Enter a URL to shorten\n");
        printf("(2) Show history of URLs you have shortened while using this program\n");
        printf("(3) Credits\n");
        printf("(4) Exit the program\n");
        printf("\nEnter the number of the function you would like to use (1-4): ");
        scanf("%s", input); //receiving as string then converting to int validates value
		functionNumber = atoi(input);

        switch(functionNumber) {
            case 1:
                //shorten URL (Maybe allow them to create custom URL not just a random shortened one)
                break;
                
            case 2:
                //show history
                break;

            case 3:
                //credits
                PrintDeveloperCredits();
                break;

            case 4:
                //exit program
                cont = 0;
                break;

            default:
                printf("\nSorry, that is an invalid input.\n");
        }

    } while (cont == 1);
}

int main()
{
	DisplayMenu();
	return 0;
}
