#include <stdio.h>
#include <stdlib.h>

int main(){


    int r,c;
    printf("please type the first :");
    scanf("%d",&r);


    printf("%d\n",r);
    printf("please type the second :");
    scanf("%d",&c);
    printf("%d\n",c);

    
    double Sale_data[r][c];
    

    int *mytest = (int *)malloc(5 * sizeof( int));

    mytest[0] = 1;
    mytest[1] = 2;
    mytest[2] = 3;
    mytest[3] = 4;
    mytest[4] = 5;

    int i,j;

    for (i = 0 ; i <5; i++){
        printf("%d",mytest[i]);
    }

    free(mytest);

    // for (i = 0; i< r; i++){
    //     for (j = 0; j<c; j++){
    //         printf("Set Amt for salesperson number %d, product nubmer %d :",i,j);
    //         // lf -> long float
    //         scanf("%lf",&Sale_data[i][j]);
    //     }
    // }
    // for (i = 0; i< r; i++){
    //     for (j = 0; j<c; j++){
    //         printf("value Check %f",Sale_data[i][j]);
            
    //     }
    // }

    return 0;
}