#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a customer in the loyalty program
typedef struct Customer {
    char name[20];
    int points;
    struct Customer* leftChild;
    struct Customer* rightChild;
} Customer;

// Declaration of the findMax function for later use
Customer* findMax(Customer* subtreeRoot);

// Creates a new customer node with given details
Customer* createNewCustomer(char custName[], int loyaltyPoints) {
    Customer* newCust = (Customer*)malloc(sizeof(Customer));
    strcpy(newCust->name, custName);
    newCust->points = loyaltyPoints;
    newCust->leftChild = newCust->rightChild = NULL;
    return newCust;
}

// Adds points to a customer or creates a new one if not found
void addLoyaltyPoints(Customer** treeRoot, char custName[], int loyaltyPoints) {
    // Base case: root is null, create a new customer
    if (*treeRoot == NULL) {
        *treeRoot = createNewCustomer(custName, loyaltyPoints);
        printf("%s %d\n", custName, loyaltyPoints);
    } else if (strcmp(custName, (*treeRoot)->name) < 0) {
        addLoyaltyPoints(&(*treeRoot)->leftChild, custName, loyaltyPoints);
    } else if (strcmp(custName, (*treeRoot)->name) > 0) {
        addLoyaltyPoints(&(*treeRoot)->rightChild, custName, loyaltyPoints);
    } else {
        (*treeRoot)->points += loyaltyPoints;
        printf("%s %d\n", custName, (*treeRoot)->points);
    }
}

// Deducts points from a customer's account
void removeLoyaltyPoints(Customer** treeRoot, char custName[], int loyaltyPoints) {
    if (*treeRoot == NULL) {
        printf("%s 0\n", custName);
    } else if (strcmp(custName, (*treeRoot)->name) < 0) {
        removeLoyaltyPoints(&(*treeRoot)->leftChild, custName, loyaltyPoints);
    } else if (strcmp(custName, (*treeRoot)->name) > 0) {
        removeLoyaltyPoints(&(*treeRoot)->rightChild, custName, loyaltyPoints);
    } else {
        if (loyaltyPoints >= (*treeRoot)->points) {
            (*treeRoot)->points = 0;
        } else {
            (*treeRoot)->points -= loyaltyPoints;
        }
        printf("%s %d\n", custName, (*treeRoot)->points);
    }
}

// Removes a customer from the program
void eraseCustomer(Customer** treeRoot, char custName[]) {
    if (*treeRoot == NULL) {
        printf("not found\n");
    } else if (strcmp(custName, (*treeRoot)->name) < 0) {
        eraseCustomer(&(*treeRoot)->leftChild, custName);
    } else if (strcmp(custName, (*treeRoot)->name) > 0) {
        eraseCustomer(&(*treeRoot)->rightChild, custName);
    } else {
        if ((*treeRoot)->leftChild == NULL) {
            Customer* tempNode = (*treeRoot)->rightChild;
            free(*treeRoot);
            *treeRoot = tempNode;
        } else if ((*treeRoot)->rightChild == NULL) {
            Customer* tempNode = (*treeRoot)->leftChild;
            free(*treeRoot);
            *treeRoot = tempNode;
        } else {
            Customer* maxNode = findMax((*treeRoot)->leftChild);
            strcpy((*treeRoot)->name, maxNode->name);
            (*treeRoot)->points = maxNode->points;
            eraseCustomer(&(*treeRoot)->leftChild, maxNode->name);
        }
        printf("%s deleted\n", custName);
    }
}

// Finds the customer with the highest points in a subtree
Customer* findMax(Customer* subtreeRoot) {
    while (subtreeRoot->rightChild != NULL) {
        subtreeRoot = subtreeRoot->rightChild;
    }
    return subtreeRoot;
}

// Searches for a customer and prints their details
void lookupCustomer(Customer* treeRoot, char custName[], int treeDepth) {
    if (treeRoot == NULL) {
        printf("not found\n");
    } else if (strcmp(custName, treeRoot->name) < 0) {
        lookupCustomer(treeRoot->leftChild, custName, treeDepth + 1);
    } else if (strcmp(custName, treeRoot->name) > 0) {
        lookupCustomer(treeRoot->rightChild, custName, treeDepth + 1);
    } else {
        printf("%s %d %d\n", custName, treeRoot->points, treeDepth);
    }
}

// Counts the number of customers with names lexicographically smaller than the given name
int countPrecedingNames(Customer* treeRoot, char custName[]) {
    if (treeRoot == NULL) {
        return 0;
    }
    if (strcmp(custName, treeRoot->name) <= 0) {
        return countPrecedingNames(treeRoot->leftChild, custName);
    }
    return 1 + countPrecedingNames(treeRoot->leftChild, custName) + countPrecedingNames(treeRoot->rightChild, custName);
}

// Traverses the tree in-order and stores customers in an array
void storeInOrder(Customer* treeRoot, Customer** array, int* idx) {
    if (treeRoot != NULL) {
        storeInOrder(treeRoot->rightChild, array, idx);
        array[*idx] = treeRoot;
        (*idx)++;
        storeInOrder(treeRoot->leftChild, array, idx);
    }
}

// Compares two customers for sorting purposes
int customerComparator(const void* a, const void* b) {
    Customer* custA = *(Customer**)a;
    Customer* custB = *(Customer**)b;

    if (custA->points != custB->points) {
        return custB->points - custA->points;
    }

    return strcmp(custA->name, custB->name);
}

int main() {
    int numOperations;
    scanf("%d", &numOperations);

    Customer* programRoot = NULL;

    for (int i = 0; i < numOperations; i++) {
        char operation[10];
        scanf("%s", operation);

        if (strcmp(operation, "add") == 0) {
            char custName[20];
            int points;
            scanf("%s %d", custName, &points);
            addLoyaltyPoints(&programRoot, custName, points);
        } else if (strcmp(operation, "sub") == 0) {
            char custName[20];
            int points;
            scanf("%s %d", custName, &points);
            removeLoyaltyPoints(&programRoot, custName, points);
        } else if (strcmp(operation, "del") == 0) {
            char custName[20];
            scanf("%s", custName);
            eraseCustomer(&programRoot, custName);
        } else if (strcmp(operation, "search") == 0) {
            char custName[20];
            scanf("%s", custName);
            lookupCustomer(programRoot, custName, 0);
        } else if (strcmp(operation, "count_smaller") == 0) {
            char custName[20];
            scanf("%s", custName);
            int precedingCount = countPrecedingNames(programRoot, custName);
            printf("%d\n", precedingCount);
        }
    }

    Customer* sortedCustArray[numOperations];
    int arrayIndex = 0;
    storeInOrder(programRoot, sortedCustArray, &arrayIndex);

    qsort(sortedCustArray, arrayIndex, sizeof(Customer*), customerComparator);

    for (int i = 0; i < arrayIndex; i++) {
        printf("%s %d\n", sortedCustArray[i]->name, sortedCustArray[i]->points);
    }

    return 0;
}

