#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uint8_t;

typedef struct
{
    uint8_t code;
    const char *name;
} JpegMarker;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "method:%s input.jpg\n", argv[0]);
        return 1;
    }

    // 1. 打開檔案
    FILE *fp = fopen(argv[1], "rb");
    if (!fp)
    {
        perror("無法開啟檔案");
        return 1;
    }

    // 2. 讀取整個檔案到記憶體
    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    printf("%d\n",filesize);
    fseek(fp, 0, SEEK_SET);

    


    // 為甚麼這邊也可以丟入long int size_t 是因為他只在意非負整數.
    // 以bytes 為單位.
    uint8_t *data = malloc(filesize);

    if (!data) {
        fprintf(stderr, "記憶體配置失敗\n");
        fclose(fp);
        return 1;
    }

    fread(data, 1, filesize, fp);
    fclose(fp);



    for (int i = 0; i < filesize; i++)
    {
        /* code */
    }
    
}