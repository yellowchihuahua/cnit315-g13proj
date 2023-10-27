#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include <curl/curl.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, char**userp){
    size_t totalSize = size*nmemb;
    size_t oldLength = strlen(*userp);
    char *temp = realloc(*userp, oldLength + totalSize + 1);
    if (temp == NULL) {
        fprintf(stderr, "realloc() failed\n");
        return 0;
    }
    *userp = temp;
    memcpy(*userp + oldLength, contents, totalSize);
    (*userp)[oldLength + totalSize] = '\0';
    return totalSize;
}


void PrintDeveloperCredits() {
  // Print the information
  printf("Credits:\n");
  printf("Developed Oct. 2023\n");
  printf("Joyanna Hammer, Ryan Cosillo, Hunter King, Chia-Hua Lin\n");
}

void DisplayMenu(){
    int cont = 1;
    char input[4];
    LinkedList* historyList = NULL;
    historyList = CreateList();

    CURL *curl;
    CURLcode result;
    char *data;
    char *shortenedUrl = malloc(1);
    if (shortenedUrl == NULL) {
        printf("DisplayMenu(); -- Memory allocation failed.\n");
        return;
    }
    *shortenedUrl = '\0';

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
               printf("Ender a URL to shorten: "); 

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
