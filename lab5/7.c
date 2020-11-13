#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int binarysearch(int *a, int n, int x);
void bubbleSort(int *arr, int n);
void swap(int *a, int *b);
void print(int *arr, int n);

int main()
{
    int n, mid, x, count = 0;
    printf("Enter the number elements: ");
    fflush(stdin);
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter number %d: ", i + 1);
        fflush(stdin);
        scanf("%d", &arr[i]);
    }
    printf("\nEnter the search key: ");
    fflush(stdin);
    scanf("%d", &x);

    bubbleSort(arr, n);
    printf("\nThe sorted array\n");
    fflush(stdin);
    print(arr, n);

    pthread_t tid;
    // pthread_create(tid)
}

int binarysearch(int *a, int n, int x)
{
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        if (a[m] == x)
            return m;
        else if (a[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}

void bubbleSort(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

void print(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        printf("Index %d: %d\n", i, arr[i]);
}
