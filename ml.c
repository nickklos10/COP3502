#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Customer {
    char name[51];
    int numTickets;
    int arrivalTime;
    int lineNumber;
} Customer;
typedef struct Node {
    Customer *customer;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *front;
    Node *back;
    int size;
} Queue;

Customer *createCustomer(char *name, int numTickets, int arrivalTime) {
    Customer *newCustomer = (Customer *)malloc(sizeof(Customer));
    strcpy(newCustomer->name, name);
    newCustomer->numTickets = numTickets;
    newCustomer->arrivalTime = arrivalTime;
    return newCustomer;
}

Queue *createQueue() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = q->back = NULL;
    q->size = 0;
    return q;
}

void enqueue(Queue *q, Customer *customer) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->customer = customer;
    newNode->next = NULL;
    if (q->back == NULL) {
        q->front = q->back = newNode;
    } else {
        q->back->next = newNode;
        q->back = newNode;
    }
    q->size++;
}

Customer *dequeue(Queue *q) {
    if (q->front == NULL) return NULL;
    Node *temp = q->front;
    Customer *customer = temp->customer;
    q->front = q->front->next;
    if (q->front == NULL) q->back = NULL;
    free(temp);
    q->size--;
    return customer;
}

Customer *peek(Queue *q) {
    if (q->front == NULL) return NULL;
    return q->front->customer;
}

int isEmpty(Queue *q) {
    return q->front == NULL;
}

int size(Queue *q) {
    return q->size;
}

int main() {
    int n, b;
    scanf("%d %d", &n, &b);

    Queue *queues[12];
    for (int i = 0; i < 12; i++) {
        queues[i] = createQueue();
    }

    for (int i = 0; i < n; i++) {
        char name[51];
        int numTickets, arrivalTime;
        scanf("%s %d %d", name, &numTickets, &arrivalTime);
        int p = name[0] - 'A';
        int q = p % 13;
        if (q == 0 && !isEmpty(queues[q])) {
            int minSize = size(queues[0]);
            for (int j = 1; j < 12; j++) {
                if (size(queues[j]) < minSize) {
                    q = j;
                    minSize = size(queues[j]);
                }
            }
        }
        Customer *customer = createCustomer(name, numTickets, arrivalTime);
        customer->lineNumber = q + 1;
        enqueue(queues[q], customer);
    }

    int k = 0;
    for (int i = 0; i < 12; i++) {
        if (!isEmpty(queues[i])) k++;
    }

    int extra = k % b;
    int base = k / b;
    int assigned = 0;
    for (int i = 0; i < b; i++) {
        printf("Booth %d\n", i + 1);
        int numQueues = base + (i < extra ? 1 : 0);
        int currentTime = 0;
        for (int j = 0; j < numQueues; j++) {
            while (!isEmpty(queues[assigned])) {
                Customer *customer = dequeue(queues[assigned]);
                currentTime = customer->arrivalTime > currentTime ? customer->arrivalTime : currentTime;
                currentTime += 30 + customer->numTickets * 5;
                printf("%s from line %d checks out at time %d.\n", customer->name, customer->lineNumber, currentTime);
                free(customer);
            }
            assigned++;
        }
        if (i < b - 1) printf("\n");
    }

    for (int i = 0; i < 12; i++) {
        free(queues[i]);
    }

    return 0;
}








