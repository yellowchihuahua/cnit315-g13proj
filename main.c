#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct Node {
    char *originalUrl;
    char *shortenedUrl;
    struct Node *next;
} Node;

size_t WriteCallback(void *contents, size_t size, size_t nmemb, char **userp) {
    size_t totalSize = size * nmemb;
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

Node* createNode(char *originalUrl, char *shortenedUrl) {
    Node *newNode = malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Failed to allocate memory for node\n");
        return NULL;
    }
    newNode->originalUrl = strdup(originalUrl);
    newNode->shortenedUrl = strdup(shortenedUrl);
    newNode->next = NULL;
    return newNode;
}

void addHistory(Node **history, char *originalUrl, char *shortenedUrl) {
    Node *newNode = createNode(originalUrl, shortenedUrl);
    if (!newNode) {
        fprintf(stderr, "Failed to add to history\n");
        return;
    }
    newNode->next = *history;
    *history = newNode;
}

void printHistory(Node *history) {
    if (history == NULL) {
        printf("No history available.\n");
        return;
    }
    printf("Shortening History:\n");
    Node *current = history;
    int count = 1;
    while (current != NULL) {
        printf("%d. Original URL: %s, Shortened URL: %s\n", count++, current->originalUrl, current->shortenedUrl);
        current = current->next;
    }
}

void freeHistory(Node *history) {
    Node *current = history;
    while (current != NULL) {
        Node *next = current->next;
        free(current->originalUrl);
        free(current->shortenedUrl);
        free(current);
        current = next;
    }
}

void PrintDeveloperCredits() {
  // Print the information
  printf("Credits:\n");
  printf("Developed Oct. 2023\n");
  printf("Joyanna Hammer, Ryan Cosillo, Hunter King, Chia-Hua Lin\n");
}

int main()
{
    CURL *curl;
    CURLcode res;
    char *data;
    char *shortenedUrl = malloc(1);
    if (!shortenedUrl) {
        fprintf(stderr, "Failed to allocate memory for shortenedUrl\n");
        return 1;
    }
    *shortenedUrl = '\0';

    Node *history = NULL;
    int functionNumber; //ref https://www.programiz.com/c-programming/examples/calculator-switch-case
    while (1){   
        printf("\n\n===============================================================================\n");
        printf("Here are your options: \n");
        printf("(1) Enter a URL to shorten\n");
        printf("(2) Show history of URLs you have shortened while using this program\n");
        printf("(3) Credits\n");
        printf("(4) Exit the program\n\n");
        printf("Enter your choice (1-4): ");
        if (scanf("%d", &functionNumber) != 1) {
            fprintf(stderr, "Failed to read choice\n");
            free(shortenedUrl);
            freeHistory(history);
            return 1;
        }
        getchar(); //To consume the newline character


        switch(functionNumber) {
            case 1:{
                printf("Enter a URL to shorten: ");
                size_t bufsize = 1024;
                data = (char *)malloc(bufsize * sizeof(char));
                if (!data) {
                    fprintf(stderr, "Failed to allocate memory for data\n");
                    free(shortenedUrl);
                    freeHistory(history);
                    return 1;
                }
                if (getline(&data, &bufsize, stdin) == -1) {
                    fprintf(stderr, "Failed to read URL\n");
                    free(data);
                    free(shortenedUrl);
                    freeHistory(history);
                    return 1;
                }
                data[strcspn(data, "\n")] = 0;  // Remove newline character

                curl_global_init(CURL_GLOBAL_DEFAULT);
                curl = curl_easy_init();
                if (curl) {
                    char *encodedUrl = curl_easy_escape(curl, data, 0);
                    if (!encodedUrl) {
                        fprintf(stderr, "URL encoding failed\n");
                        free(data);
                        curl_global_cleanup();
                        continue;
                    }
                    char apiUrl[1024];
                    snprintf(apiUrl, sizeof(apiUrl), "http://tinyurl.com/api-create.php?url=%s", encodedUrl);

                    curl_easy_setopt(curl, CURLOPT_URL, apiUrl);
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &shortenedUrl);

                    res = curl_easy_perform(curl);
                    if (res != CURLE_OK)
                        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                    else {
                        printf("Shortened URL: %s\n", shortenedUrl);
                        addHistory(&history, data, shortenedUrl);
                    }

                    curl_free(encodedUrl);
                    curl_easy_cleanup(curl);
                } 
                else {
                    fprintf(stderr, "curl_easy_init() failed\n");
                }

                curl_global_cleanup();
                free(data);
                free(shortenedUrl);
                shortenedUrl = malloc(1);
                if (!shortenedUrl) {
                    fprintf(stderr, "Failed to allocate memory for shortenedUrl\n");
                    freeHistory(history);
                    return 1;
                }
                *shortenedUrl = '\0';
                break;
            }
            case 2:
                //print history
                printHistory(history);
                break;

            case 3:
                //credits
                PrintDeveloperCredits();
                break;

            case 4:
                //exit program
                free(shortenedUrl);
                freeHistory(history);
                printf("Exiting the program.\n");
                return 0;

            default:
                printf("\nSorry, that is an invalid input.\n");
                break;
        }
    } 
}