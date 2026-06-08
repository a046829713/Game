#include <stdio.h>
#include <stdlib.h>
#include "function.h"

typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef int int32_t;

#pragma pack(1)
// BMP 檔案標頭 (14 bytes)
typedef struct
{
    uint16_t bfType;      // 檔案類型，必須為 'BM' (0x4D42)
    uint32_t bfSize;      // 整個檔案的大小 (bytes)
    uint16_t bfReserved1; // 保留字，必須為 0
    uint16_t bfReserved2; // 保留字，必須為 0
    uint32_t bfOffBits;   // 從檔案開頭到像素資料的偏移量 (bytes)
} BITMAPFILEHEADER;

// BMP 資訊標頭 (40 bytes for V3)
typedef struct
{
    uint32_t biSize;         // 這個結構的大小 (40 bytes)
    int32_t biWidth;         // 圖片寬度 (pixels)
    int32_t biHeight;        // 圖片高度 (pixels)
    uint16_t biPlanes;       // 必須為 1
    uint16_t biBitCount;     // 每個像素的位元數 (bits per pixel)，例如 1, 4, 8, 24, 32
    uint32_t biCompression;  // 壓縮類型 (0 為不壓縮)
    uint32_t biSizeImage;    // 像素資料的大小 (bytes)，如果未壓縮可為 0
    int32_t biXPelsPerMeter; // 水平解析度 (pixels per meter)
    int32_t biYPelsPerMeter; // 垂直解析度 (pixels per meter)
    uint32_t biClrUsed;      // 調色盤中使用的顏色數，0 表示所有顏色
    uint32_t biClrImportant; // 重要的顏色數，0 表示都重要
} BITMAPINFOHEADER;
#pragma pack()

/**
 * @brief 將 BMP 檔案資料寫入新檔案
 * @param filename 輸出檔案的路徑
 * @param fileHeader 檔案標頭
 * @param infoHeader 資訊標頭
 * @param extraData 標頭和像素資料之間的額外資料 (例如調色盤)
 * @param extraDataSize 額外資料的大小
 * @param pixelData 像素資料
 * @return 0 表示成功, 1 表示失敗
 */
int save_bmp(const char *filename,
             const BITMAPFILEHEADER *fileHeader,
             const BITMAPINFOHEADER *infoHeader,
             const unsigned char *extraData,
             long extraDataSize,
             const unsigned char *pixelData)
{
    FILE *outFile = fopen(filename, "wb");
    if (outFile == NULL)
    {
        perror("無法建立輸出檔案");
        return 1;
    }

    // 計算每一行的實際儲存長度 (必須是 4 的倍數)
    uint32_t stride = (infoHeader->biWidth * (infoHeader->biBitCount / 8) + 3) & ~3;
    uint32_t pixelDataSize = stride * abs(infoHeader->biHeight);

    // --- 【關鍵修正】 ---
    // 我們不修改 bfOffBits，保留原始值。
    // 檔案總大小 bfSize 是固定的，因為我們只是修改像素顏色，沒有增刪像素。
    // 如果未來會修改圖片尺寸，才需要重新計算 bfSize。
    // bfSize = bfOffBits + pixelDataSize

    // 1. 寫入檔案標頭
    fwrite(fileHeader, sizeof(BITMAPFILEHEADER), 1, outFile);

    // 2. 寫入資訊標頭
    fwrite(infoHeader, sizeof(BITMAPINFOHEADER), 1, outFile);

    // 3. 【重要】寫回標頭和像素資料之間的「額外資料」
    if (extraData != NULL && extraDataSize > 0)
    {
        fwrite(extraData, 1, extraDataSize, outFile);
    }

    // 4. 寫入處理過的像素資料
    fwrite(pixelData, 1, pixelDataSize, outFile);

    // 5. 關閉檔案
    fclose(outFile);

    printf("檔案已成功儲存至: %s\n", filename);
    return 0;
}

int main()
{
    //  filename record the first char address.
    char *filename = "C:\\workspace\\C\\bmp\\sky.bmp";
    char *output_filename = "C:\\workspace\\C\\bmp\\sky_no_red.bmp"; // 處理後要儲存的路徑


    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        perror("Can't open the file");
        return 1;
    }

    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    // 1. 讀取檔案標頭
    fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, file);

    if (fileHeader.bfType != 0x4D42)
    {
        printf("this program only paser bmp img,please change other image.");
        fclose(file);
        return 1;
    }

    fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, file);

    // 檢查是否為 24-bit 圖片，這是此範例處理的類型
    if (infoHeader.biBitCount != 24)
    {
        printf("此範例僅支援 24-bit BMP 圖片。\n");
        fclose(file);
        return 1;
    }

    // 2. 【關鍵】讀取標頭和像素之間的「中間資料」
    long currentPos = ftell(file);
    long extraDataSize = fileHeader.bfOffBits - currentPos;
    unsigned char *extraData = NULL;

    if (extraDataSize < 0)
    {
        printf("錯誤: 檔案標頭中的偏移量 (bfOffBits) 無效。\n");
        fclose(file);
        return 1;
    }

    if (extraDataSize > 0)
    {
        extraData = (unsigned char *)malloc(extraDataSize);
        if (extraData == NULL)
        {
            fclose(file);
            return 1;
        }
        // 從目前位置讀取這段資料
        fread(extraData, 1, extraDataSize, file);
    }

    // 3. 定位並讀取像素資料
    // 使用 fseek 將檔案指標移動到像素資料的起始位置
    fseek(file, fileHeader.bfOffBits, SEEK_SET);

    // 計算像素資料的大小
    uint32_t pixelDataSize = infoHeader.biSizeImage;
    uint32_t stride = (infoHeader.biWidth * infoHeader.biBitCount / 8 + 3) & ~3;

    printf("strdie : %d\n",stride);


    // 分配記憶體來存放像素資料
    unsigned char *pixelData = (unsigned char *)malloc(pixelDataSize);
    if (pixelData == NULL)
    {
        printf("記憶體分配失敗！\n");
        fclose(file);
        return 1;
    }

    // 從檔案讀取所有像素資料到記憶體中
    fread(pixelData, 1, pixelDataSize, file);

    // 檔案讀取完畢，可以關閉了
    fclose(file);




    // 遍歷每一個像素
    // abs(infoHeader.biHeight) 是為了處理 biHeight 可能為負值的情況 (top-down bitmap)
    for (int y = 0; y < abs(infoHeader.biHeight); y++)
    {
        // 取得目前這一行的起始指標
        unsigned char *row = pixelData + y * stride;
        
        for (int x = 0; x < infoHeader.biWidth; x++)
        {
            // 取得目前這個像素的起始指標
            // 在 24-bit BMP 中，每個像素佔 3 bytes
            // 儲存順序是 Blue, Green, Red
            unsigned char *pixel = row + x * 3;
            
            // 讀取 B, G, R 的值
            unsigned char blue = pixel[0];
            unsigned char green = pixel[1];
            unsigned char red = pixel[2];
            
            // 計算灰階值 (使用簡單的平均法)
            unsigned char gray = (blue + green + red) / 3;
            
            // 將 B, G, R 都設定為這個灰階值
            pixel[0] = gray; // Blue
            pixel[1] = gray; // Green
            pixel[2] = gray; // Red
        }
    }
    printf("灰階轉換完成。\n");
    // =================================================================
    // 【【【 處理邏輯結束 】】】
    // =================================================================
    // 4. 使用您的函式儲存修改後的圖片
    if (save_bmp(output_filename, &fileHeader, &infoHeader, extraData, extraDataSize, pixelData) == 0)
    {
        printf("SAVE file succeess : %s\n", output_filename);
    }
    else
    {
        printf("儲存檔案失敗。\n");
    }

    // 5. 釋放之前分配的記憶體
    free(pixelData);

    return 0;
}