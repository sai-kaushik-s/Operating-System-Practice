// Include the required libraries
#include<stdio.h> 
#include <stdlib.h>
#include <pthread.h>

// Function declaration 
void swap(int* x, int* y);
void* quickSort(void* params);
int partition (int* arr, int low, int high);
void print(int* arr, int size);

int* arr;

// Main function
int main(){
	int n;
	// Taking the size of array from user
    printf("Enter the number of elements: ");
    scanf("%d", &n);
	// Allocating memory for arr
    arr = (int*) malloc(sizeof(int) * n);
	// Taking the input elemets from user
    for(int i = 0; i < n; i++){
        printf("Enter number %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
	// Print the given array
	printf("Given array is: ");
	print(arr, n);
	// Storing the low and high in lr[]
    int lr[] = {0, n - 1};
    quickSort(lr);
	// Printing the sorted array
	printf("\nSorted array is: ");
	print(arr, n);
	return 0; 
}

// This function takes last element as pivot, places the pivot element at its correct position in sorted array, and places all smaller (smaller than pivot) to left of pivot and all greater elements to right of pivot 
int partition (int* arr, int low, int high){ 
	// Pivot 
	int pivot = arr[high];
	// Index of smaller element 
	int i = (low - 1); 

	for (int j = low; j <= high- 1; j++){ 
		// If current element is smaller than the pivot 
		if (arr[j] < pivot){ 
			// Increment index of smaller element 
			i++;
			swap(&arr[i], &arr[j]); 
		} 
	} 
	// Swap function called
	swap(&arr[i + 1], &arr[high]); 
	return (i + 1); 
} 

// The main function that implements QuickSort arr[] --> Array to be sorted, low --> Starting index, high --> Ending index 
void* quickSort(void* params){
	// Storing the data from params to lr
    int* lr = (int*)params;
    int low = lr[0];
    int high = lr[1];
	if (low < high){ 
		// pi is partitioning index, arr[p] is now at right place
		int pi = partition(arr, low, high); 
        int llr[] = {low, pi-1};
        int rlr[] = {pi + 1, high};
        pthread_t tid;
		// Separately sort elements before partition and after partition 
		// Creating the thread
        pthread_create(&tid, NULL, quickSort, llr);
		// Calling the quickSort function recursively
		quickSort(rlr); 
		// Joining the thread
        pthread_join(tid, NULL);
	} 
} 

// Print the array
void print(int* arr, int size){
	for (int i=0; i < size; i++) 
		printf("%d ", arr[i]); 
	printf("\n"); 
} 

// Swap two variables
void swap(int* x, int* y){ 
	int t = *x; 
	*x = *y; 
	*y = t; 
} 