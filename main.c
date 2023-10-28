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
    int nodeKey = 1;

    CURL *curl;
    CURLcode result;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl == NULL) {
        fprintf(stderr, "Curl initialization failed.\n");
        return;
    }

    char *shortenedUrl = malloc(1);
    if (shortenedUrl == NULL) {
        fprintf(stderr, "Curl initialization failed.\n");
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

                char urlToShorten[1024];
                scanf("%s", urlToShorten);

                urlToShorten[strcspn(urlToShorten, "\n")] = 0; //removes newline

                if (curl) {
                    char *encodedUrl = curl_easy_escape(curl, urlToShorten, 0);
                    if (encodedUrl == NULL) {
                        fprintf(stderr, "URL encoding failed\n");
                        curl_global_cleanup();
                        continue;
                    }
                    char apiUrl[1024];
                    snprintf(apiUrl, sizeof(apiUrl), "http://tinyurl.com/api-create.php?url=%s", encodedUrl); //copy url to apiurl

                    curl_easy_setopt(curl, CURLOPT_URL, apiUrl);
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &shortenedUrl);
                    
                    result = curl_easy_perform(curl);
                    if (result != CURLE_OK){
                        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
                        break;
                    }

                    printf("Shortened URL: %s\n", shortenedUrl);
                    //creates node and adds to linked list
                    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
                    newNode = CreateNode(nodeKey, urlToShorten, shortenedUrl);
                    InsertFront(historyList, newNode);
                    nodeKey++;
                    break;
                }
                fprintf(stderr, "curl_easy_init() failed\n");
                break;
            case 2:
                //print list
                PrintList(historyList);
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
    FreeList(historyList);
}

int main()
{
	DisplayMenu();
	return 0;
}
