// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

int N = 2;

// Struct for the data
struct data{
    int** arr;
    int** temp;
    int p;
    int q;
    int n;
};

struct data initData(int** A, int i, int j, int N);
void* getCofactor(void* params);
int determinant(int** A, int n);
void adjoint(int** A,int** adj);
bool inverse(int** A, float** inverse);
void display(float** A);

// Main driver function
int main(){ 
	// Scan the size of the matrix
    printf("Enter the size of the matrix: ");
    scanf("%d", &N);
    int** A;
    A = (int **) malloc(sizeof(int*)*N);
    for(int k = 0; k < N; k++)
        A[k] = (int*)malloc(sizeof(int)*N);
    // Scan the matrix
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++){
            printf("Enter number [%d][%d]: ", i, j);
            scanf("%d", &A[i][j]);
        }
	printf("The matrix: \n");
	for (int i=0; i<N; i++){ 
		for (int j=0; j<N; j++) 
			printf("%6d", A[i][j]);
		printf("\n");
	}
	float** inv;
    inv = (float **) malloc(sizeof(float*)*N);
    for(int k = 0; k < N; k++)
        inv[k] = (float*)malloc(sizeof(float)*N);
	// If the inverse exists
	printf("\nThe Inverse is :\n"); 
	if (inverse(A, inv))
		// Print the inverse
		display(inv); 
	return 0; 
}

// A function to initialize the structure
struct data initData(int** A, int i, int j, int N){
    struct data params;
    params.arr = (int **) malloc(sizeof(int*)*N);
    for(int k = 0; k < N; k++)
        params.arr[k] = (int*)malloc(sizeof(int)*N);
    params.arr = A;
    params.temp = (int **) malloc(sizeof(int*)*N);
    for(int k = 0; k < N; k++)
        params.temp[k] = (int*)malloc(sizeof(int)*N);
    params.p = i;
    params.q = j;
    params.n = N;
    return params;
}

// A function to get the cofactor of A[p][q]
void* getCofactor(void* params){ 
    struct data* temp = (struct data* )params;
	int i = 0, j = 0; 

	// Looping for each element of the matrix 
	for (int row = 0; row < temp->n; row++){ 
		for (int col = 0; col < temp->n; col++){ 
			// Copying into temporary matrix
			if (row != temp->p && col != temp->q){
				temp->temp[i][j++] = temp->arr[row][col]; 
				// Row is filled, so increase row index and reset col index 
				if (j == temp->n - 1){ 
					j = 0; 
					i++; 
				} 
			} 
		} 
	} 
	//Exit the thread
    pthread_exit(0);
} 

// A function to return the determinant of the matrix
int determinant(int** A, int n){ 
	int D = 0;
	//If matrix contains single element 
	if (n == 1) 
		return A[0][0];
	int sign = 1;
	// Create threads for finding cofactor of each element
    pthread_t tid[n];
    struct data params[n];
    for(int i = 0; i < n; i++){
        params[i] = initData(A, 0, i, n);
        pthread_create(&tid[i], NULL, getCofactor, &params[i]);
    }
	// Wait for the threads to complete
    for(int i = 0; i < n; i++)
        pthread_join(tid[i], NULL);
	// Iterate for each element of first row 
	for (int f = 0; f < n; f++){ 
		// Getting Cofactor of A[0][f] 
		D += sign * A[0][f] * determinant(params[f].temp, n - 1); 
		// Terms are to be added with alternate sign 
		sign = -sign; 
	}
	return D;
} 

// A function to get adjoint of the given matrix
void adjoint(int** A,int** adj){ 
	if (N == 1){ 
		adj[0][0] = 1; 
		return; 
	}
	int sign = 1; 
	// Create threads for finding the cofactors
    pthread_t tid[N][N];
    struct data params[N][N];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            params[i][j] = initData(A, i, j, N);
            pthread_create(&tid[i][j], NULL, getCofactor, &params[i][j]);
        }
    }
	// Wait for the threads to complete
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            pthread_join(tid[i][j], NULL);
	// Compute the adjoint of each element
	for (int i=0; i<N; i++){ 
		for (int j=0; j<N; j++){
			sign = ((i+j)%2==0)? 1: -1; 
			// Interchanging rows and columns to get the transpose of the cofactor matrix 
			adj[j][i] = (sign)*(determinant(params[i][j].temp, N-1)); 
		} 
	} 
} 

// A function to calculate and store inverse, returns false if matrix is singular 
bool inverse(int** A, float** inverse){ 
	// Find determinant of A[][] 
	int det = determinant(A, N); 
	if (det == 0){
		printf("Singular matrix, can't find its inverse\n"); 
		return false; 
	}
	// Find adjoint 
	int** adj;
    adj = (int **) malloc(sizeof(int*)*N);
    for(int k = 0; k < N; k++)
        adj[k] = (int*)malloc(sizeof(int)*N); 
	// Get the adjoint of the matrix
	adjoint(A, adj);
	// Find Inverse using formula "inverse(A) = adj(A)/det(A)" 
	for (int i=0; i<N; i++)
		for (int j=0; j<N; j++)
			inverse[i][j] = adj[i][j]/(float)det;
	return true; 
} 

// A function to display the matrix.
void display(float** A){ 
	for (int i=0; i<N; i++){ 
		for (int j=0; j<N; j++) 
			printf("%.6f ", A[i][j]);
		printf("\n");
	} 
} 