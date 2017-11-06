#include<stdio.h>

int main(void)
{
    int size=3, Matrix[size][size];

    printf("Enter 9 elements of the matrix: \n");

    for (int i=0; i<size; i++){
        for (int j=0; j<size; j++){
            scanf("%d", &Matrix[i][j]);
        }
    }
    
    printf("\n");
    
    display(Matrix, size);
    
    return 0;
}

int display(int Matrix1[3][3], int size)
{
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            printf("%d", Matrix1[i][j]);
            printf(" ");
        }
    }
    
    return 0;
}