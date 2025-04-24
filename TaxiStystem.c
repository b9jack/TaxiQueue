#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node
{
    int value;
    char name[50];
    struct Node* next;
}Node;

typedef struct
{
    Node* head;
    Node* tail;
    int size;
}Queue;

Queue *createQueue()
{
    Queue *queue = malloc(sizeof(Queue));

    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;


    return queue;
}
int size(Queue *queue)
{
    return queue->size;
}
bool isEmpty(Queue *queue)
{
    return (queue->size == 0);
}
void enqueuePassenger(Queue *queue, int ID, const char *name)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = ID;
    strcpy(newNode->name, name);

    newNode->next = NULL;

    if(isEmpty(queue))
    {
        queue->head = newNode;
        queue->tail = newNode;
    }else{
        queue->tail->next = newNode;
        queue->tail = newNode;
    }

    queue->size++;
}

void dequeue(Queue *queue, bool *status)
{
    if (isEmpty(queue))
    {
        *status = false; 
        return;
    }
    *status = true;
    
    Node* oldHead = queue->head;
    if (queue->size == 1)
    {
        queue->head = NULL;
        queue->tail = NULL;
    }else{
        queue->head = queue->head->next;
    }
    
    free(oldHead);
    queue->size--;
}
void destroyQueue(Queue *queue)
{
    Node *currentNode = queue->head;
    while (currentNode != NULL)
    {
        Node* temp = currentNode;
        currentNode = currentNode->next;
        free(temp);
    }
    free(queue);

    queue->size = 0;
}
void printQueue(Queue *queue)
{
    if (isEmpty(queue)) 
    {
        printf("\nThe queue is empty.\n");
        return;
    }

    Node *currentNode = queue->head;

    printf("\nPassengers in the queue:\n");
    while (currentNode != NULL)
    {
        printf("Taxi ID: %d, Passenger Name: %s\n", currentNode->value, currentNode->name);
        currentNode = currentNode->next;
    }
    printf("\n");
}

int main()
{
    Queue *passengerQueue = createQueue();
    
    int choice;
    int taxiCount;
    int passengersPerTaxi;
    int totalPassengers = 0;
    bool status = false;

    do
    {
        printf("==== Taxi Dispatch System ====");
        printf("\n1. Book Taxi(Enter 1)");
        printf("\n2. Exit Program(Press key)");
        printf("\nBook Taxi: ");
        scanf("%d", &choice);

        if (choice != 1) break;
        

        printf("How many taxis would you like to book?: ");
        scanf("%d", &taxiCount);

    printf("How many passengers per vehicle?: ");
    scanf("%d", &passengersPerTaxi);
    for (int i = 0; i < taxiCount * passengersPerTaxi; i++)
    {
        char name[50];
        printf("Enter the name of passenger[%d]: ", i+1);
        scanf("%s", name);

        enqueuePassenger(passengerQueue, i + 1, name);
    }
    totalPassengers = taxiCount * passengersPerTaxi;
    

    printf("You have booked %d taxi(s) for %d people.\n", taxiCount, totalPassengers);
    
    for (int i = 0; i < taxiCount; i++)
    {
        int taxiID = i+1;
        printf("\nTaxi[%d] Passengers: ", taxiID);

        for (int j = 0; j < passengersPerTaxi; j++)
        {
            if (!isEmpty(passengerQueue))
            {
                printf("%s", passengerQueue->head->name);
                dequeue(passengerQueue, &status);
                if (j < passengersPerTaxi - 1)
                {
                    printf(", ");
                }
                
            }
            
        }

        printf("\n");      
    }
    printf("\n");

    } while (choice == 1);
    

    

    

    destroyQueue(passengerQueue);
    return 0;
}