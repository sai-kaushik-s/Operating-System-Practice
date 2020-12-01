// Include the required libraries
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <stdlib.h>

// Structure for the dictionary node
struct node{
    char* word;
    char* primary;
    char* secondary;
    struct node* next;
};

struct data{
    char* value;
    struct node* start;
    struct node* end;
};

// Global variables
struct node* root = NULL, *output = NULL;
int size = 0;
pthread_mutex_t lock;

// Function declaration
struct node* birth();
void sortedInsertion(struct node** head, struct node* new);
void removeDuplicates();
void findSize();
void createDictionary();
struct node* middle(struct node* start, struct node* last);
void* binarySearch(void* params);
struct node* search(char* data);
void *producer();
void *consumer();

// Main driver function
int main(){
    // Initialize the mutex
    pthread_mutex_init(&lock, NULL);
    pthread_t ptid, ctid;
    // Create threads for producer and consumer
    pthread_create(&ptid, NULL, producer, NULL);
    pthread_create(&ctid, NULL, consumer, NULL);
    // Wait for the threat execution
    pthread_join(ptid, NULL);
    pthread_join(ctid, NULL);
    // Destroy the mutex
    pthread_mutex_destroy(&lock);
    return 0;
}

// A function to create a new node
struct node* birth(){
    struct node* temp = (struct node *)malloc(sizeof(struct node));
    temp->word = (char*) malloc(sizeof(char) * 40);
    temp->primary = (char*) malloc(sizeof(char) * 1000);
    temp->secondary = (char*) malloc(sizeof(char) * 1000);
    temp->next = NULL;
    return temp;
}

// A function to insert a node in sorted order
void sortedInsertion(struct node** head, struct node* new){
    struct node* temp;
    // Special case for the head
    if (*head == NULL || strcmp((*head)->word, new->word) > 0) {
        new->next = *head;
        *head = new;
    }
    // If not head
    else {
        temp = *head;
        // Locate the node before the point of insertion
        while (temp->next != NULL && strcmp(temp->next->word, new->word) < 0)
            temp = temp->next;
        // Insert in the next position
        new->next = temp->next;
        temp->next = new;
    }
}

// A function to remove duplicates in a sorted linked list
void removeDuplicates(){
    struct node* current = root;
    struct node* next;
    if (current == NULL)  
        return;
    // For each element
    while (current->next != NULL){
        // Compare with next node (as it is sorted)
        if (current->word == current->next->word){          
            next = current->next->next;
            free(current->next);
            current->next = next;
        }
        // No match
        else
            // Go to next node
            current = current->next;
    }
}

// A function to find the number of entries for the dictionary
void findSize(){
    FILE *fp=fopen("dict.txt", "r");
    char c;
    // Increment for each \n
    for (c = getc(fp); c != EOF; c = getc(fp)) 
        if (c == '\n')
            size += 1; 
    fclose(fp);
}

// A function to create a dictionary
void createDictionary(){
    // Get the number of lines
    findSize();
    FILE *fp = fopen("dict.txt", "r");
    char c = fgetc(fp);
    // Loop through the lines in the file
    for(int i = 0; i < size; i++){
        // Initialize a new node
        struct node* temp = birth();
        int index = 0;
        // Format: "word/primary_meaning/secondary_meaning/"
        while(c != '/'){
            temp->word[index++] = c;
            c = fgetc(fp);
        }
        index = 0;
        c = fgetc(fp);
        while(c != '/'){
            temp->primary[index++] = c;
            c = fgetc(fp);
        }
        index = 0;
        c = getc(fp);
        while(c != '/'){
            temp->secondary[index++] = c;
            c = fgetc(fp);
        }
        for(int j = 0; j < 2; j++)
            c = fgetc(fp);
        // Insert the node in the linked list
        sortedInsertion(&root, temp);
    }
    // Remove duplicates, if any
    removeDuplicates();
}

// A function to get the middle of a linked list
struct node* middle(struct node* start, struct node* last){ 
    if (start == NULL) 
        return NULL;
    // Run two pointers, one at double the speed of the other
    struct node* slow = start;
    struct node* fast = start -> next;
    while (fast != last){
        // When fast is null,
        // Slow is the middle node
        fast = fast -> next;
        if (fast != last){
            slow = slow -> next;
            fast = fast -> next;
        }
    }
    return slow; 
}

// A binary search function on a linked list
void* binarySearch(void* params){
    // Get the value, start and end
    struct data* temp = (struct data *)params;
    char* value = temp->value;
    struct node* start = temp->start;
    struct node* last = temp->end;
    do{
        // Find middle 
        struct node* mid = middle(start, last);
        // If middle is empty
        if (mid == NULL)
            return NULL;
        // If value is present at middle
        if (strcmp(mid->word, value) == 0){
            output = mid;
            return mid;
        }
        // If value is more than mid
        else if (strcmp(mid->word, value) < 0)
            start = mid -> next;
        // If the value is less than mid
        else
            last = mid;
    }while (last == NULL || last != start);
    // value not present
    return NULL;
}

// A function to search a word
struct node* search(char* data){
    // Get the middle of the linked list
    struct node* mid = middle(root, NULL);
    pthread_t ltid, rtid;
    // Data structure for passing in multithreaded binary search
    struct data lr[2];
    lr[0].value = data;
    lr[0].start = root;
    lr[0].end = mid;
    lr[1].value = data;
    lr[1].start = mid->next;
    lr[1].end = NULL;
    // Create 2 threads for left and right half of the linked list
    pthread_create(&ltid, NULL, binarySearch, &lr[0]);
    pthread_create(&rtid, NULL, binarySearch, &lr[1]);
    pthread_join(ltid, NULL);
    pthread_join(rtid, NULL);
    return output;
}

// A function for the producer (creating a dictionary)
void *producer(){
    // Lock the dictionary
    pthread_mutex_lock(&lock);
    // Create the dictionary
    createDictionary();
    // Unlock the dictionary
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

// A function for the consumer (binary searching the dictionary)
void *consumer(){
    while(1){
        // Get user search string
        char* data = (char*) malloc(sizeof(char) * 40);
        printf("Enter the word to find in the dictionary: ");
        scanf("%s", data);
        getchar();
        // Lock the dictionary
        pthread_mutex_lock(&lock);
        // Search the string in the linked list
        struct node* result = search(data);
        // Unlock the dictionary
        pthread_mutex_unlock(&lock);
        if(result)
            printf("Word: %s\nPrimary Meaning: %s\nSecondary meaning: %s\n", result->word, result->primary, result->secondary);
        else
            printf("Word not present in the dictionary\n");
        char c;
        printf("Do you want to search another word (y/n): ");
        scanf("%c", &c);
        if(c == 'n')
            break;
    }
    pthread_exit(NULL);
}