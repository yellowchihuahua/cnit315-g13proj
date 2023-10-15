#include <stdio.h>
#include <stdlib.h>

void developerCredits() {
  // Print the information
  printf("Credits:\n");
  printf("Developed Oct. 2023\n");
  printf("Joyanna Hammer, Ryan Cosillo, Hunter King, Chia-Hua Lin\n");
}

int receiveIntInput(char *prompt, int minInclusive){
    int value = -1;
    do {
        char input[5];
        printf("%s", prompt);
        scanf("%s", &input);
        value = atoi(input);

        if (value < minInclusive) {
            printf("That is an invalid entry, please enter a valid integer over %i.\n", minInclusive);
            value = -1;
        }
    } while (value == -1);

    return value;
}

int main()
{
	int cont = 1;

    do {
        char functionNumber = 0; //ref https://www.programiz.com/c-programming/examples/calculator-switch-case
        printf("\n\n===============================================================================");
        printf("\nHere are your options: ");
        printf("\n(1) Enter a URL to shorten");
        printf("\n(2) Show history of URLs you have shortened using this program");
        printf("\n(3) Credits");
        printf("\n(4) Exit the program");
        functionNumber = receiveIntInput("\nEnter the number of the function you would like to use (1-4): ", 1);

        switch(functionNumber) {
            case 1:
                //shorten URL (Maybe allow them to create custom URL not just a random shortened one)
                break;
                
            case 2:
                //show history
                break;

            case 3:
                //credits
                developerCredits();
                break;

            case 4:
                //exit program
                cont = 0;
                break;

            default:
                printf("\nSorry, that is an invalid input.\n");
        }

    } while (cont == 1);

	return 0;
}