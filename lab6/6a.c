// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function definitions
void merge(int* arr, int l, int m, int r);
void* mergeSort(void* lr);
void printArray(int* arr, int n);

int* arr;

// Main driver function
int main(){
	// Scan the length of the array
	int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
	// Scan the array
    arr = (int*) malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        printf("Enter number %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
	// Merge sort the array
    int lr[] = {0, n - 1};
    mergeSort(lr);
	// Print the sorted array
	printf("\nSorted array is: ");
	printArray(arr, n);
	return 0;
}

//A function to merge two arrays
void merge(int* arr, int l, int m, int r){
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int L[n1], R[n2];
	// Copy the array elements to a temp array
	for (i = 0;i < n1;i++)
		L[i] = arr[l + i];
	for (j = 0;j < n2;j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	// Loop till the overflow
	while (i < n1 && j < n2){
		// If L < R
		if (L[i] <= R[j])
			// Copy L
			arr[k++] = L[i++];
		// If L > R
		else
			// Copy R
			arr[k++] = R[j++];
	}

	// Copy the remaining elements
	while (i < n1)
		arr[k++] = L[i++];
	while (j < n2)
		arr[k++] = R[j++];
}

// A function to merge sort an array
void* mergeSort(void* params){
    int* lr = (int*)params;
    int l = lr[0];
    int r = lr[1];
	// If there exits atleast one element in the range l...r
	if (l < r){
		// Split the array at the mid
		int m = l + (r - l)/ 2;
        int llr[] = {l, m};
        int rlr[] = {m + 1, r};
		// Create a thread to the first half of the array
        pthread_t tid;
        pthread_create(&tid, NULL, mergeSort, llr);
		// Sort the second half in the main thread
		mergeSort(rlr);
        pthread_join(tid, NULL);
		// Merge the two halfs
		merge(arr, l, m, r);
	}
}

//A function to print the array
void printArray(int* arr, int n){
	for (int i = 0;i < n;i++)
		printf("%d ", arr[i]);
	printf("\n");
}