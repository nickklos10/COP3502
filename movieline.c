#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct {
    char name[20];
    int arrivalTime;
    int checkoutTime;
} Customer;

typedef struct Node {
    Customer data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

void initializeQueue(Queue* q) {
    q->front = q->rear = NULL;
}

void enqueue(Queue* q, Customer c) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = c;
    newNode->next = NULL;
    if(q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

Customer dequeue(Queue* q) {
    if(q->front == NULL) return (Customer){"", -1, -1}; // Empty Queue
    Node* temp = q->front;
    Customer c = temp->data;
    q->front = q->front->next;
    if(q->front == NULL) q->rear = NULL;
    free(temp);
    return c;
}

void interpreter() {
    
}

int isEmpty(Queue* q) {
    return q->front == NULL;
}

int main() {
    int n, b;
    scanf("%d %d", &n, &b);
    
    Queue queues[b];
    for(int i = 0; i < b; i++) initializeQueue(&queues[i]);
    
    // Input Customers and Assign Queues
    for(int i = 0; i < n; i++) {
        Customer c;
        scanf("%s %d %d", c.name, &c.arrivalTime, &c.checkoutTime);
        int queueNumber = (c.arrivalTime + c.checkoutTime) % b;
        enqueue(&queues[queueNumber], c);
    }
    
    // Process each booth
    for(int i = 0; i < b; i++) {
        printf("Booth %d\n", i + 1);
        int currentTime = 0;
        while(!isEmpty(&queues[i])) {
            Customer c = dequeue(&queues[i]);
            currentTime = currentTime < c.arrivalTime ? c.arrivalTime : currentTime;
            currentTime += c.checkoutTime;
            printf("%s from line %d checks out at time %d.\n", c.name, ((c.arrivalTime + c.checkoutTime) % b) + 1, currentTime);
        }
    }
    
    return 0;
}