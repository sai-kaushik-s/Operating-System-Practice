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

void swap(int* a, int* b);
int partition (int* arr, int l, int r);
void quickSort(int* arr, int l, int r);
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

	quickSort(arr, 0, n-1);

	printf("\nSorted array: \n");
	print(arr, n);
	return 0;
}

void swap(int* a, int* b){
	int c = *a;
	*a = *b;
	*b = c;
}

int partition (int* arr, int l, int r){
	int pivot = arr[r];
	int i = (l - 1);

	for (int j = l;j <= r- 1;j++){
		if (arr[j] < pivot){
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[r]);
	return (i + 1);
}

void quickSort(int* arr, int l, int r){
	if (l < r){
		int pi = partition(arr, l, r);
        pid_t pid = vfork();

        if(pid < 0){
            printf("Fork failed..\n");
            exit(1);
        }
        else if (pid == 0){
            quickSort(arr, l, pi - 1);
            exit(0);
        }
        else{
            quickSort(arr, pi + 1, r);
            wait(NULL);
        }
	}
}

void print(int* arr, int n){
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}