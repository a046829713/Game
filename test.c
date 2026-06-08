#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[]){

    int **AllNumber;
    int size = 1024;

    AllNumber = malloc(size * sizeof(int*));


    for (int i =0 ; i<1024;i++){
        AllNumber[i] = malloc(sizeof(int));
        *AllNumber[i] = i;
    }
    
    for (int i =0 ; i<1024;i++){
        printf("%d\n",*AllNumber[i]);
    }

    return 0;
}