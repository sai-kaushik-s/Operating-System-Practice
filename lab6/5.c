// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Struct for the data
struct block{
	int *val;
	int n;
};

struct mode{
	int a;
	int count;
};

// Function definitions
void* mean(void * p);
void* median(void * p);
void* mode(void * p);
int removeDuplicates(int arr[], int n);
void bubbleSort(void* params);
void print(void* params);
void swap(int* x, int* y);

// Main driver function
int main(){
	struct block arr;
	// Scan the length of the array
	printf("Enter size of array : ");
	scanf("%d", &arr.n);
	// Scan the elements
	arr.val = (int*)malloc(sizeof(int)*arr.n);
	for(int i=0; i<arr.n; i++){
		printf("Enter the number %d: ", i + 1);
		scanf("%d", &arr.val[i]);
	}
	// Sort the array
	bubbleSort(&arr);
	print(&arr);
	pthread_t tid[2];
	// Create a thread for computation of the median 
    pthread_create(&tid[0], NULL, median, &arr);
	// Create a thread for the computation of the mode
    pthread_create(&tid[1], NULL, mode, &arr);
	// Compute the mean in the main thread
	mean(&arr);
	//Wait for the threads to complete
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
}

// A function to compute the mean of the given array
void* mean(void* params){
	struct block *temp = (struct block*) params;
	float mean = 0;
	// Loop through the array
	for(int i=0;i<temp->n;i++)
		// Add the elements
		mean = mean + temp->val[i];
	// Compute the mean
	mean = mean / temp->n;
	printf("\nMean: %f\n", mean);
}

// A function to cimpute the median of a given array
void* median(void* params){
	struct block *temp = (struct block*) params;
	int med;
	// If the length of array is odd
	if(temp->n%2 == 1)
		// Get the middle element
		med = temp->val[(temp->n-1)/2];
	// If the length of array is even
	else
		// Get the average of the two middle elements
		med = (temp->val[temp->n/2] + temp->val[temp->n/2 - 1]) / 2;
	printf("\nMedian: %d\n", med);	
	// Exit the thread
	pthread_exit(0);
}

// Get the mode of the given array
void* mode(void* params){
	struct block *temp = (struct block*) params;
	struct block mod;
	mod.n = temp->n;
	mod.val = (int*)malloc(sizeof(int)*mod.n);
	// Duplicate the array
	for (int i = 0; i < temp->n; i++)
		mod.val[i] = temp->val[i];
	// Remove the duplicate
	mod.n = removeDuplicates(mod.val , mod.n);
	int max = 0;
	int count[mod.n];
	// Inititalize the array
	for (int i = 0; i < mod.n; i++)
		count[i] = 0;
	// Get the frequency of the elements
	for(int i = 0 ; i < mod.n ; i++)
		for (int j = 0 ; j < temp->n ; j++){
			if(mod.val[i] == temp->val[j])
				count[i]++;
			if(count[i] > max)
				max = count[i];
		}
	printf("\nMode : ");
	// Print the elements with highest frequency
	for(int i = 0; i < mod.n ; i++)
		if(count[i] == max)
			printf(" %d " , mod.val[i]);
	printf("\n");
	// Exit the thread
	pthread_exit(0);
}

int removeDuplicates(int arr[], int n){ 
    // Return, if array is empty or contains a single element 
    if (n==0 || n==1) 
        return n; 
    int temp[n]; 
    // Start traversing elements 
    int j = 0; 
    for (int i=0; i<n-1; i++) 
        // If current element is not equal to next element then store that current element 
        if (arr[i] != arr[i+1]) 
            temp[j++] = arr[i]; 
    // Store the last element as whether it is unique or repeated, it hasn't stored previously 
    temp[j++] = arr[n-1]; 
    // Modify original array 
    for (int i=0; i<j; i++) 
        arr[i] = temp[i]; 
	for (int i = j; i < n; i++)
		arr[i] = 0;
    return j; 
} 

// A function to sort the array
void bubbleSort(void* params){
	struct block *temp = (struct block*) params;
    for (int i = 0; i < temp->n - 1; i++)
        for (int j = 0; j < temp->n - i - 1; j++)
            if (temp->val[j] > temp->val[j+1])
                swap(&temp->val[j], &temp->val[j+1]);
}

// A function to display the array
void print(void* params){
	struct block *temp = (struct block*) params;
	printf("Sorted array : ");
    for(int i = 0; i < temp->n; i++)
        printf("%d ", temp->val[i]);
    printf("\n");
}

// A function to swap two numbers
void swap(int* x, int* y){
    int c = *x;
    *x = *y;
    *y = c;
}