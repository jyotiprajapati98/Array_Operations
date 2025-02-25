#include<stdio.h>
#include<cstdio>

void printArray(int arr[][2], int r, int c){
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            printf("The 2D Array for the [%d][%d] is: %d \n", i, j, arr[i][j]);
        }
    }
    
}
int main(){
    int arr2d[2][2] = {{1,2}, {3,4}};
    int arr2d_1[3][2] = {{1,2}, {3,4}, {32,44}};
    printArray(arr2d, 2, 2);
    printf("3x2 2D array: \n");
    printArray(arr2d_1, 3, 2);
}


