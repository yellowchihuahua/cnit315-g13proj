#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "linkedlist.h"


// *needs to be changed if struct Node changes (data received and processed)
struct Node* CreateNode(int key, char *originalUrl, char *shortenedUrl){
	Node *newNode = malloc(sizeof(struct Node));
	if (newNode == NULL) {
		printf("CreateNode(char *firstName, char *lastName, char *major, float GPA); -- Failed memory allocation.\n");
		return NULL;
	}

	newNode->key = key;

	strcpy(newNode->originalUrl, originalUrl);
	strcpy(newNode->shortenedUrl, shortenedUrl);
	newNode->next = NULL;

	return newNode;
}

//ref https://github.com/skorks/c-linked-list/blob/master/linkedlist.c
struct LinkedList* CreateList() {
	LinkedList* llist = malloc(sizeof(struct LinkedList));
	if (llist == NULL) {
		printf("CreateList(); -- Failed memory allocation.\n");
		return NULL;
	}
	llist->head = NULL;
	return llist;
}

struct Node* LookUpByIndex(struct LinkedList* llist, int index){
	struct Node* current = llist->head;
	int count = 0;
	if(index < 0){
		printf("LookUpByIndex(struct LinkedList* llist, int index); -- Given index is less than 0.\n");
		return NULL;
	}
	while (current != NULL && count < index) {
		current = current->next;
		count++;
	}
	if (current != NULL){
		return current; 
	}
	printf("LookUpByIndex(struct LinkedList* llist, int index); -- No node with matching index exists in list.\n");
	return NULL; //reached end of LL, no node with matching data
}

struct Node* LookUpByKey(struct LinkedList* llist, int key) {
	if(key < 1){
		printf("LookUpByKey(struct LinkedList* llist, int key); -- Given key is invalid (less than 1).\n");
		return NULL;
	}
	struct Node* current = llist->head;
	while (current != NULL && current->key != key) {
		current = current->next;
	}
	if (current != NULL){
		return current; 
	}
	printf("LookUpByKey(struct LinkedList* llist, int key); -- No node with matching key exists in list.\n");
	return NULL; //reached end of LL, no node with matching data
}

int GetKeyByIndex(struct LinkedList* llist, int index){
	if (index < 0){
		printf("GetKeyByIndex(struct LinkedList* llist, int index); -- Given index is invalid (less than 0).\n");
		return -1;
	}

	struct Node* current = llist->head;
	int count = 0;
	while (current != NULL && count < index) {
		current = current->next;
		count++;
	}
	if(current != NULL) {
		return current->key;
	}
	printf("GetKeyByIndex(struct LinkedList* llist, int index); -- No node with matching index exists in list.\n");
	return -1;
}

int GetIndexByKey(struct LinkedList* llist, int key) {
	if(key < 1){
		printf("GetIndexByKey(struct LinkedList* llist, int key); -- Given key is invalid (less than 1).\n");
		return -1;
	}
	
	struct Node* current = llist->head;
	int count = 0;
	while (current != NULL && current->key != key) {
		current = current->next;
		count++;
	}
	if (current != NULL){
		return count; 
	}
	printf("GetIndexByKey(struct LinkedList* llist, int key); -- No node with matching key exists in list.\n");
	return -1; //reached end of LL, no node with matching data
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

//ref https://www.geeksforgeeks.org/convert-floating-point-number-string/#
void ReverseString(char* str, int len) 
{ 
    int i = 0, j = len - 1, temp; 
    while (i < j) { 
        temp = str[i]; 
        str[i] = str[j]; 
        str[j] = temp; 
        i++; 
        j--; 
    } 
} 

//ref https://www.geeksforgeeks.org/convert-floating-point-number-string/#
int IntToStr(int x, char str[], int d) 
{ 
    int i = 0; 
    while (x) { 
        str[i++] = (x % 10) + '0'; 
        x = x / 10; 
    } 
    while (i < d) str[i++] = '0'; 
 
    ReverseString(str, i); 
    str[i] = '\0'; 
    return i; 
} 

//ref https://www.geeksforgeeks.org/convert-floating-point-number-string/#
//returns 0 if unsuccessful, 1 if successful
int ftoa(float n, char* res, int afterpoint) 
{ 
    int ipart = (int)n; 
    float fpart = n - (float)ipart; 
 
    int i = IntToStr(ipart, res, 0); 

    if (afterpoint != 0) { 
        res[i] = '.'; // add dot 
 
        fpart = fpart * pow(10, afterpoint); 
 
        IntToStr((int)fpart, res + i + 1, afterpoint); 
    } 
	return 1;
} 

//ref https://stackoverflow.com/questions/25798977/returning-string-from-c-function
// *needs to be changed if struct Node changes (snprintf statement)
//Converts node to CSV format. Usage:
//char newNodeCsvString[256];
//ToCsv(node, newNodeCsvString);
//returns 0 if unsuccessful, 1 if successful
int ToCsv(struct Node* node, char *string) {
	if(node == NULL){
		printf("ToCsv(struct Node* node, char *string); -- Node is null, nothing to convert.\n");
		return 0;
	}
	
	snprintf(string, 256, "%d, %s, %s\n", node->key, node->originalUrl, node->shortenedUrl);
	return 1;
}

//ref https://stackoverflow.com/questions/25798977/returning-string-from-c-function
// *needs to be changed if struct Node changes (snprintf statement)
//Converts node to human readable format. Usage: //usage:
//char newNodeString[256];
//ToCsv(node, newNodeString);
//returns 0 if unsuccessful, 1 if successful
int ToString(struct Node* node, char *string) {
	//todo: look into snprintf
	if(node == NULL){
		printf("ToString(struct Node* node, char *string); -- Node is null, nothing to convert.\n");
		return 0;
	}
	snprintf(string, 256, "Key: %d | Data: %s, %s\n", node->key, node->originalUrl, node->shortenedUrl);
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
		printf("Index: %d | ", GetIndexByKey(llist, current->key));
		PrintNode(current);
		current = current->next;
	}
}


//ref https://stackoverflow.com/questions/15098936/simple-way-to-check-if-a-string-contains-another-string-in-c
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

//ref https://stackoverflow.com/questions/6417158/c-how-to-free-nodes-in-the-linked-list
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

//InsertFront
//ref ll.c example, TA in person assistance
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

//InsertEnd generalized
//returns 0 if unsuccessful, 1 if successful
int InsertEnd(struct LinkedList* llist, struct Node* nodeToInsert){
	if(nodeToInsert == NULL) {
		printf("InsertEnd(struct LinkedList* llist, struct Node* nodeToInsert); -- Node is null, nothing to insert.\n");
		return 0;
	}
	if (GetListLength(llist) == 0){
		llist->head = nodeToInsert;
		return 1;
	}
	struct Node* current = llist->head;
	while(current->next != NULL){
		current = current->next;
	}
	current->next = nodeToInsert;
	return 1;
}

//param index is the index before node to insert
//returns 0 if unsuccessful, 1 if successful
int InsertMiddle(struct LinkedList* llist, int index, struct Node* nodeToInsert){
	if(nodeToInsert == NULL) {
		printf("InsertMiddle(struct LinkedList* llist, int index, struct Node* nodeToInsert); -- Node is null, nothing to insert.\n");
		return 0;
	}

	//check end cases
	if(index == 0){ //if index is at beginning
		InsertFront(llist, nodeToInsert);
		return 1;
	}
	if (index == GetListLength(llist)) { //if index is at end
		InsertEnd(llist, nodeToInsert);
		return 1;
	}
	
	struct Node* previousNode = LookUpByIndex(llist, index);
	struct Node* nextNode = LookUpByIndex(llist, index+1);
	previousNode->next = nodeToInsert;
	nodeToInsert->next = nextNode; //linking 
	return 1;
}

// *needs to be changed if struct Node changes (snprintf usage)
//Created to streamline InsertByGPA. Converts entire node to a string in order of comparison priority to use strcmp to sort entire thing alphabetically
//Usage: refer to ToString and ToCsv usage
//returns 0 if unsuccessful, 1 if successful
int ToComparisonString(struct Node* node, char* string){
	if(node == NULL){
		printf("ToComparisonString(char *string, struct Node* node); -- Node is null, nothing to convert.\n");
		return 0;
	}

	//ORDER OF COMPARISON:
	//inverted gpa, last name, first name, major
	snprintf(string, 256, "%s%s%d\n", node->originalUrl, node->shortenedUrl, node->key);
	return 1;
}

// *needs to be changed if struct Node changes
//not transferable to general linked list functionality?
//returns 0 if unsuccessful, 1 if successful
int InsertInOrder(struct LinkedList* llist, struct Node* nodeToInsert) {	

	if (GetListLength(llist) == 0) {
		InsertFront(llist, nodeToInsert);
		return 1;
	} 

	char nodeToInsertStr[256]; //convert it to a string to compare entir ething alphabetically
	ToComparisonString(nodeToInsert, nodeToInsertStr);

	struct Node* current = llist->head;
	char currentStr[256]; 
	ToComparisonString(current, currentStr);

	int comp = strcmp(nodeToInsertStr, currentStr);
	if(comp < 0) {//smaller alphabetically
		InsertFront(llist, nodeToInsert);
		return 1;
	}

	current = (current)->next; //start iterating from second item to utilize InsertMiddle()
	int count = 0; //counter, index to use InsertMiddle() on
	while (current != NULL) {
		currentStr[0] = '\0'; //clear strings
		ToComparisonString(current, currentStr);

		comp = strcmp(nodeToInsertStr, currentStr);
		if(comp < 0) { //alphabetically smaller, inserting before current node
			InsertMiddle(llist, count, nodeToInsert);
			return 1;
		}
		current = current->next;
		count++;
	}
	//reached the end of list and it's not bigger than anything, so inserting at end
	InsertEnd(llist, nodeToInsert);
	return 1;
}

//returns 0 if unsuccessful, 1 if successful
int DeleteFront(struct LinkedList* llist) {
	if (GetListLength(llist) == 0) {
		printf("DeleteFront(struct LinkedList* llist); -- Empty list, nothing to delete\n");
		return 0;
	}
	struct Node* temp = llist->head; //temp pointer to hold current head
	llist->head = llist->head->next; //make head point to 2nd item in list
	free(temp); //free temp pointer

	return 1;
}

//returns 0 if unsuccessful, 1 if successful
int DeleteEnd(struct LinkedList* llist){
	if (GetListLength(llist) == 0) {
		printf("DeleteEnd(struct LinkedList* llist); -- Empty list, nothing to delete\n");
		return 0;
	}
	if (llist->head->next == NULL) { //free head if head is only item
		FreeList(llist);
	}
	struct Node* current = llist->head;
	while (current->next->next != NULL) {
		current = current->next;
	}
	free(current->next);
	current->next = NULL;
	return 1;
}

//returns 0 if unsuccessful, 1 if successful
int DeleteMiddle(struct LinkedList* llist, int index){
	if (GetListLength(llist) == 0) {
		printf("DeleteMiddle(struct LinkedList* llist, int index); -- Empty list, nothing to delete.\n");
		return 0;
	}
	struct Node* nodeToDelete = LookUpByIndex(llist, index);
	if(nodeToDelete == NULL) {
		printf("DeleteMiddle(struct LinkedList* llist, int index); -- No node exists at given index to delete.\n");
		return 0;
	}
	
	//check ends
	if(index == 0) { 
		DeleteFront(llist);
		return 1;
	}
	if (index == GetListLength(llist)) { 
		DeleteEnd(llist);
		return 1;
	}
	struct Node* nodeBefore = LookUpByIndex(llist, index-1);
	struct Node* nodeAfter = LookUpByIndex(llist, index+1);
	nodeBefore->next = nodeAfter;
	free(nodeToDelete);
	return 1;
}
