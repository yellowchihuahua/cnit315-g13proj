#ifndef LINKEDLIST_HEADER
#define LINKEDLIST_HEADER

typedef struct Node {
	int key;
    char *originalUrl;
    char *shortenedUrl;
    struct Node *next;
} Node;


typedef struct LinkedList{
	Node* head;
} LinkedList;


struct Node* CreateNode(int key, char *originalUrl, char *shortenedUrl);
struct LinkedList* CreateList();
struct Node* LookUpByIndex(struct LinkedList* llist, int index);
struct Node* LookUpByKey(struct LinkedList* llist, int key);
int GetKeyByIndex(struct LinkedList* llist, int index);
int GetIndexByKey(struct LinkedList* llist, int key);
int GetListLength(struct LinkedList* llist);
void ReverseString(char* str, int len);
int IntToStr(int x, char str[], int d);
int ftoa(float n, char* res, int afterpoint);
int ToCsv(struct Node* node, char *string);
int ToString(struct Node* node, char *string);
void PrintNode(struct Node* node);
void PrintList(struct LinkedList* llist);
void PrintSearch(struct LinkedList* llist, char* searchRequest);
void FreeList(struct LinkedList* llist);
int InsertFront(struct LinkedList* llist, struct Node* nodeToInsert);
int InsertEnd(struct LinkedList* llist, struct Node* nodeToInsert);
int InsertMiddle(struct LinkedList* llist, int index, struct Node* nodeToInsert);
int ToComparisonString(struct Node* node, char* string);
int InsertInOrder(struct LinkedList* llist, struct Node* nodeToInsert);
int DeleteFront(struct LinkedList* llist);
int DeleteEnd(struct LinkedList* llist);
int DeleteMiddle(struct LinkedList* llist, int index);



#endif