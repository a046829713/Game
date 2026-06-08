#include <windows.h>
#include <stdio.h>
#include "mylib.h"
#define MYTEST 4
typedef struct 
{
    /* data */
}IplImage;




int main(){

    printf("%d\n",MYTEST);

    SetConsoleCP(CP_UTF8);


    // 3. 調用函數
    double result = add(3, 4);
    printf("3 + 4 = %f\n", result);



    return 0;
}