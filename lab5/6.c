#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

struct variables{
    int* a;
    int n;
};

void* runner (void* args);
void bubbleSort(int* arr, int n, bool fun(const void*, const void*));
void print(int* arr, int n);
bool asc(const void* a, const void* b);
bool desc(const void* a, const void* b);
void swap(int* a, int* b);

int main(){
    struct variables data[2];
    printf("Enter the number of elements: ");
    scanf("%d", &data[0].n);
    data[1].n = data[0].n;
    data[0].a = malloc(data[0].n * sizeof(int));
    data[1].a = malloc(data[1].n * sizeof(int));
    for (int i = 0; i < data[0].n; i++){
        printf("Enter the data at index %d: ", i + 1);
        scanf("%d", &data[0].a[i]);
        data[1].a[i] = data[0].a[i];
    }
    pthread_t tid;
    pthread_create(&tid, NULL, runner, &data[0]);
    pthread_join(tid, NULL);

    printf("\nDescending sort: ");
    bubbleSort(data[1].a, data[1].n, desc);
    print(data[1].a, data[1].n);
    
    return 0;
}

void* runner (void* args){
    struct variables* data = (struct variables *) args;
    printf("\nAscending sort: ");
    bubbleSort(data->a, data->n, asc);
    print(data->a, data->n);
    pthread_exit(0);
}

void bubbleSort(int* arr, int n, bool fun(const void*, const void*)){
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (fun(&arr[j], &arr[j+1])){
                swap(&arr[j], &arr[j+1]);
            }
}

void print(int* arr, int n){
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

bool asc(const void* a, const void* b){
    return *(int*)a > *(int*)b;
}

bool desc(const void* a, const void* b){
    return *(int*)a < *(int*)b;
}

void swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}