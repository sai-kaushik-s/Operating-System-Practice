//          __  __                               _             __          __
//         / /_/ /_  ___  ____ _____ _____ ___  (_)___  ____ _/ /_  ____  / /_
//        / __/ __ \/ _ \/ __ `/ __ `/ __ `__ \/ / __ \/ __ `/ __ \/ __ \/ __/
//       / /_/ / / /  __/ /_/ / /_/ / / / / / / / / / / /_/ / /_/ / /_/ / /_
//       \__/_/ /_/\___/\__, /\__,_/_/ /_/ /_/_/_/ /_/\__, /_.___/\____/\__/
//                     /____/                        /____/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void merge(int* arr, int l, int m, int r);
void mergeSort(int* arr, int l, int r);
void print(int* arr, int n);

int main(){
    int n;
    printf("Enter the number elements: ");
    fflush(stdin);
    scanf("%d", &n);
    int arr[n];
    for(int i = 0; i < n; i++){
        printf("Enter number %d: ", i + 1);
        fflush(stdin);
        scanf("%d", &arr[i]);
    }

	mergeSort(arr, 0, n - 1);

	printf("\nSorted array: \n");
	print(arr, n);
	return 0;
}

void merge(int* arr, int l, int m, int r){
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int L[n1], R[n2];

	for (i = 0;i < n1;i++)
		L[i] = arr[l + i];
	for (j = 0;j < n2;j++)
		R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(int* arr, int l, int r){
	if (l < r) {
		int m = l + (r - l) / 2;
        pid_t pid = vfork();

        if(pid < 0){
            printf("Fork failed..\n");
            exit(1);
        }
        else if (pid == 0){
            mergeSort(arr, l, m);
            exit(0);
        }
        else{
            mergeSort(arr, m + 1, r);
            wait(NULL);
        }
		merge(arr, l, m, r);
	}
}

void print(int* arr, int n){
	for (int i = 0;i < n;i++) 
		printf("%d ", arr[i]);
	printf("\n");
}