#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

#define MAX 1000

struct length
{
    int len1;
    int len2;
};

char s1[MAX], s2[MAX];

void *LCS(void *arg);
int max(int a, int b);

int main()
{
    printf("\nEnter the string 1: ");
    fgets(s1, sizeof(s1), stdin);
	strcpy(s1, strtok(s1, "\n"));
    printf("\nEnter the string 2: ");
    fgets(s2, sizeof(s2), stdin);
	strcpy(s2, strtok(s2, "\n"));
}

int max(int a, int b){
	if(a > b)
		return a;
	return b;
}
