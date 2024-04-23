#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 19
#define TABLESIZE 300007

typedef struct item {
    char name[MAXLEN + 1];
    int quantity;
    int saleprice;
} item;

typedef struct node {
    item* iPtr;
    struct node* next;
} node;

typedef struct hashtable {
    node** lists;
    int size;
} hashtable; 

int main (void) {
    FILE *fp = fopen("market_data.txt", "r");
    if (!fp) {
        printf("File open error.\n");
    }
}

// Function to compute the hash index for a given item name
int computeHash(char* itemName, int hashTableSize) {
    int nameLength = strlen(itemName);
    int hashValue = 0;
    for (int i = 0; i < nameLength; i++)
        hashValue = (1151 * hashValue + (itemName[i] - 'a')) % hashTableSize;
    return hashValue;
}

// Initialize a new hash table with specified size
hashtable* initializeHashTable(int size) {
    hashtable* newTable = (hashtable*)malloc(sizeof(hashtable));
    newTable->lists = (node**)malloc(sizeof(node*) * size);
    for (int i = 0; i < size; i++)
        newTable->lists[i] = NULL;
    newTable->size = size;
    return newTable;
}

// Add a new item to the hash table
void addItem(hashtable* table, item* newItem) {
    int index = computeHash(newItem->name, table->size);
    node* newNode = (node*)malloc(sizeof(node));
    newNode->iPtr = newItem;
    newNode->next = table->lists[index];
    table->lists[index] = newNode;
}

// Locate an item in the hash table
item* searchItem(hashtable* table, char* itemName, int* operationComplexity) {
    int index = computeHash(itemName, table->size);
    node* current = table->lists[index];
    int position = 1;
    
    while (current != NULL) {
        if (strcmp(current->iPtr->name, itemName) == 0) {
            *operationComplexity += position;
            return current->iPtr;
        }
        current = current->next;
        position++;
    }
    *operationComplexity += position;
    return NULL;
}

// Handle the 'buy' operation
void processBuy(hashtable* table, char* itemName, int quantity, int price, int* cashBalance, int* totalOpsComplexity) {
    int complexity = 0;
    item* foundItem = searchItem(table, itemName, &complexity);
    
    if (foundItem) {
        foundItem->quantity += quantity;
    } else {
        item* newItem = (item*)malloc(sizeof(item));
        strcpy(newItem->name, itemName);
        newItem->quantity = quantity;
        newItem->saleprice = price / quantity; 
        addItem(table, newItem);
    }

    *cashBalance -= price;
    *totalOpsComplexity += complexity;
    printf("%s %d %d\n", itemName, (foundItem ? foundItem->quantity : quantity), *cashBalance);
}

// Handle the 'sell' operation
void processSell(hashtable* table, char* itemName, int quantity, int* cashBalance, int* totalOpsComplexity) {
    int complexity = 0;
    item* foundItem = searchItem(table, itemName, &complexity);
    
    if (foundItem) {
        int soldQuantity = (quantity <= foundItem->quantity) ? quantity : foundItem->quantity;
        foundItem->quantity -= soldQuantity;
        *cashBalance += soldQuantity * foundItem->saleprice;
        *totalOpsComplexity += complexity;
        printf("%s %d %d\n", itemName, foundItem->quantity, *cashBalance);
    }
}

// Handle the 'change_price' operation
void processChangePrice(hashtable* table, char* itemName, int newPrice, int* totalOpsComplexity) {
    int complexity = 0;
    item* foundItem = searchItem(table, itemName, &complexity);
    
    if (foundItem) {
        foundItem->saleprice = newPrice;
        *totalOpsComplexity += complexity;
    }
}

int main() {
    int commandCount;
    scanf("%d", &commandCount);

    hashtable* inventory = initializeHashTable(TABLESIZE);
    int currentCash = 100000;
    int operationalComplexity = 0;

    for (int i = 0; i < commandCount; i++) {
        char commandType[15];
        scanf("%s", commandType);

        if (strcmp(commandType, "buy") == 0) {
            char itemName[MAXLEN + 1];
            int quantity, price;
            scanf("%s %d %d", itemName, &quantity, &price);
            processBuy(inventory, itemName, quantity, price, &currentCash, &operationalComplexity);
        } else if (strcmp(commandType, "sell") == 0) {
            char itemName[MAXLEN + 1];
            int quantity;
            scanf("%s %d", itemName, &quantity);
            processSell(inventory, itemName, quantity, &currentCash, &operationalComplexity);
        } else if (strcmp(commandType, "change_price") == 0) {
            char itemName[MAXLEN + 1];
            int newPrice;
            scanf("%s %d", itemName, &newPrice);
            processChangePrice(inventory, itemName, newPrice, &operationalComplexity);
        }
    }

    printf("%d\n%d\n", currentCash, operationalComplexity);
    return 0;
}


