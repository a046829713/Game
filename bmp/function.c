#include<stdlib.h>
#include<stdio.h>
#include "function.h"


long get_file_size(const char *filename){
    // 以二進位讀取模式開啟檔案
    FILE *file = fopen(filename, "rb");

    // 檢查檔案是否成功開啟
    if (file == NULL) {
        perror("錯誤：無法開啟檔案");
        return -1; // 回傳 -1 表示錯誤
    }

    // 1. 將檔案指標移至檔案結尾
    // fseek(file, 0, SEEK_END);
    if (fseek(file, 0, SEEK_END) != 0) {
        perror("錯誤：無法定位檔案指標");
        fclose(file);
        return -1;
    }

    // 2. 取得目前指標的位置，即檔案大小（單位：位元組）
    long size = ftell(file);
    if (size == -1) {
        perror("錯誤：無法取得檔案大小");
        fclose(file);
        return -1;
    }

    // 3. (可選) 如果之後還要讀取檔案，將指標移回開頭
    // rewind(file); 或是 fseek(file, 0, SEEK_SET);

    // 4. 關閉檔案
    fclose(file);


    printf("the sizes is %d\n",size);
    return size;
}

void check_binary_data(unsigned char* data, uint32_t length){

    for (int i = 0; i < length; i++)
    {
       printf("index: %d, %#x\n",i, data[i]);

    }
    
}


void get_extraData(){
    
}