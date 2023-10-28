#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct Node {
    char originalUrl[1024];
    char shortenedUrl[1024];
    struct Node *next;
};


struct LinkedList{
	struct Node* head;
};

struct Node* CreateNode(char *originalUrl, char *shortenedUrl){
	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
	printf("allocation attempted");
	if (newNode == NULL) {
		printf("CreateNode(char *originalUrl, char *shortenedUrl); -- Failed memory allocation.\n");
		return NULL;
	}
	printf("allocation succeeded");

	strcpy(newNode->originalUrl, originalUrl);
	strcpy(newNode->shortenedUrl, shortenedUrl);
	newNode->next = NULL;

	return newNode;
}

struct LinkedList* CreateList() {
	struct LinkedList* llist = malloc(sizeof(struct LinkedList));
	if (llist == NULL) {
		printf("CreateList(); -- Failed memory allocation.\n");
		return NULL;
	}
	llist->head = NULL;
	return llist;
}

int GetListLength(struct LinkedList* llist){
	int count = 0;
	struct Node* head = llist->head;
	if (head == NULL){
		return count;
	}
	count++;
	struct Node* current = head;
	while(current->next != NULL){
		current = current->next;
		count++;
	}

	return count;
}

int ToCsv(struct Node* node, char *string) {
	if(node == NULL){
		printf("ToCsv(struct Node* node, char *string); -- Node is null, nothing to convert.\n");
		return 0;
	}
	
	snprintf(string, 2100, "%s, %s\n", node->originalUrl, node->shortenedUrl);
	return 1;
}

int ToString(struct Node* node, char *string) {
    if(node == NULL){
        printf("ToCsv(struct Node* node, char *string); -- Node is null, nothing to convert.\n");
        return 0;
	}
    snprintf(string, 2100, "Data: %s, %s\n", node->originalUrl, node->shortenedUrl);
    return 1;
}

void PrintNode(struct Node* node){
	if (node == NULL) {
		printf("PrintNode(struct Node* node); -- Given node is NULL, nothing to print.\n");
		return;
	}
	char nodeStr[256];
	ToString(node, nodeStr);
	printf("%s", nodeStr);
}

void PrintList(struct LinkedList* llist){
	if(GetListLength(llist) == 0){
		printf("PrintList(struct LinkedList* llist); -- Empty list, nothing to print.\n");
		return;
	}
	struct Node* current = llist->head;
	while (current != NULL) {
		PrintNode(current);
		current = current->next;
	}
}

void PrintSearch(struct LinkedList* llist, char* searchRequest) {
	struct Node* current = llist->head;
	char nodeString[256];

	while(current != NULL) {
		ToCsv(current, nodeString);
		if(strstr(nodeString, searchRequest) != NULL){
			PrintNode(current);
		}
		current = current->next;
	}
}

void FreeList(struct LinkedList* llist){
//traverse through and free allocated memory
	struct Node* temp = llist->head;
    while ((llist->head) != NULL) {
        temp = (llist->head);
		(llist->head) = (llist->head)->next;
		free(temp);
    }
	free(llist);
}

int InsertFront(struct LinkedList* llist, struct Node* nodeToInsert){
	if(nodeToInsert == NULL) {
		printf("InsertFront(struct LinkedList* llist, struct Node* nodeToInsert); -- Node is null, nothing to insert.\n");
		return 0;
	}
	if (GetListLength(llist) == 0){
		llist->head = nodeToInsert;
		return 1;
	}
	nodeToInsert->next = llist->head; //points next var to front of list, global variable
	llist->head = nodeToInsert; //inserts node and sets pointer of new front, global varaible
	return 1;
}


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
    struct LinkedList* historyList = NULL;
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
        fprintf(stderr, "Failed to allocate memory for shortenedUrl.\n");
        return;
    }
    *shortenedUrl = '\0';
    


    do {
        char functionNumber = 0; //ref https://www.programiz.com/c-programming/examples/calculator-switch-case
        printf("\n===============================================================================\n");
        printf("Here are your options: \n");
        printf("(1) Enter a URL to shorten\n");
        printf("(2) Show history of URLs you have shortened while using this program\n");
        printf("(3) Search in historyfor a URL you have shortened\n");
        printf("(4) Credits\n");
        printf("(5) Exit the program\n");
        printf("\nEnter the number of the function you would like to use (1-5): ");
        scanf("%s", input); //receiving as string then converting to int validates value
		functionNumber = atoi(input);

        switch(functionNumber) {
            case 1:
                //shorten URL (Maybe allow them to create custom URL not just a random shortened one)
                printf("Ender a URL to shorten: "); 

                char urlToShorten[1024];
                scanf("%s", urlToShorten);

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
                    struct Node* newNode = NULL;
                    newNode = CreateNode(urlToShorten, shortenedUrl);
                    InsertFront(historyList, newNode);
                    nodeKey++;
                    break;
                }
                fprintf(stderr, "curl_easy_init() failed\n");
                break;
            case 2:
                printf("Here is your URL shortening history: --------------------------------------------\n");
                PrintList(historyList);
                printf("END OF HISTORY ------------------------------------------------------------------\n");
                break;

            case 3:
                printf("\nEnter the string you would like to search.\n");
                char searchString[256];
				printf("Your search request: ");
				scanf("%s", searchString);

				printf("\nYour search results: ----------------------------------------------------------\n");
				PrintSearch(historyList, searchString);
				printf("\nEND OF LIST--------------------------------------------------------------------\n");

                break;

            case 4:
                //credits
                PrintDeveloperCredits();
                break;

            case 5:
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
