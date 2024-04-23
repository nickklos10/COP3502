#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HASH_SIZE 100003

// Structure to represent a list node
typedef struct ListNode {
    char* entry;
    struct ListNode* next;
} ListNode;

// Hash function to generate hash index
int generateHash(char* entry) {
    int length = strlen(entry);
    int hashValue = 0;
    for (int i = 0; i < length; i++)
        hashValue = (26 * hashValue + entry[i] - 'a') % MAX_HASH_SIZE;
    return hashValue;
}

// Function to create a new list node
ListNode* createListNode(char* entry) {
    ListNode* newListNode = (ListNode*)malloc(sizeof(ListNode));
    if (newListNode == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    newListNode->entry = strdup(entry);
    newListNode->next = NULL;
    return newListNode;
}

// Function to insert a node into the hash table
void addListNode(ListNode** hashTable, char* entry) {
    int index = generateHash(entry);
    ListNode* newListNode = createListNode(entry);
    newListNode->next = hashTable[index];
    hashTable[index] = newListNode;
}

// Function to search for a node in the hash table
int findListNode(ListNode** hashTable, char* entry) {
    int index = generateHash(entry);
    ListNode* current = hashTable[index];
    while (current != NULL) {
        if (strcmp(current->entry, entry) == 0) {
            return 1; // Entry found
        }
        current = current->next;
    }
    return 0; // Entry not found
}

// Function to free memory allocated to the hash table
void clearHashTable(ListNode** hashTable) {
    for (int i = 0; i < MAX_HASH_SIZE; i++) {
        ListNode* current = hashTable[i];
        while (current != NULL) {
            ListNode* temp = current;
            current = current->next;
            free(temp->entry);
            free(temp);
        }
    }
    free(hashTable);
}

int main() {
    int numOfWords;
    scanf("%d", &numOfWords);

    ListNode** hashTable = (ListNode**)malloc(MAX_HASH_SIZE * sizeof(ListNode*));
    if (hashTable == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < MAX_HASH_SIZE; i++) {
        hashTable[i] = NULL;
    }

    int gameStatus = 1;
    char lastWord[121];
    char newWord[121];

    for (int i = 0; i < numOfWords; i++) {
        scanf("%s", newWord);

        if (i > 0 && newWord[0] != lastWord[strlen(lastWord) - 1]) {
            gameStatus = 0;
            printf("Player %d lost\n", (i % 2) + 1);
            break;
        }

        if (findListNode(hashTable, newWord)) {
            gameStatus = 0;
            printf("Player %d lost\n", (i % 2) + 1);
            break;
        }

        addListNode(hashTable, newWord);
        strcpy(lastWord, newWord);
    }

    if (gameStatus) {
        printf("Fair Game\n");
    }

    clearHashTable(hashTable);

    return EXIT_SUCCESS;
}
