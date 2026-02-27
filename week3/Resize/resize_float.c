#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include <math.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    float n = atof(argv[1]);
    if (n <= 0 || n > 100)
    {
        fprintf(stderr, "n must be a positive number <= 100\n");
        return 1;
    }

    FILE *inptr = fopen(argv[2], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[2]);
        return 2;
    }

    FILE *outptr = fopen(argv[3], "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", argv[3]);
        return 3;
    }

    // Читаємо заголовки
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Перевірка формату
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 ||
        bi.biSize != 40 || bi.biBitCount != 24 ||
        bi.biCompression != 0)
    {
        fclose(inptr);
        fclose(outptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    int oldWidth = bi.biWidth;
    int oldHeight = bi.biHeight;

    int newWidth = round(oldWidth * n);
    int newHeight = round(abs(oldHeight) * n);

    int oldPadding = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newPadding = (4 - (newWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Оновлюємо заголовок
    bi.biWidth = newWidth;
    bi.biHeight = (oldHeight < 0) ? -newHeight : newHeight;

    bi.biSizeImage = (newWidth * sizeof(RGBTRIPLE) + newPadding) * newHeight;

    // ГОЛОВНЕ ВИПРАВЛЕННЯ
    bf.bfSize = bf.bfOffBits + bi.biSizeImage;

    // Записуємо нові заголовки
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    RGBTRIPLE *row = malloc(sizeof(RGBTRIPLE) * oldWidth);
    if (row == NULL)
    {
        fclose(inptr);
        fclose(outptr);
        return 5;
    }

    int absOldHeight = abs(oldHeight);

    for (int i = 0; i < newHeight; i++)
    {
        int oldRow = floor(i / n);
        if (oldRow >= absOldHeight)
            oldRow = absOldHeight - 1;

        // Переходимо до потрібного рядка
        long offset = bf.bfOffBits +
                      oldRow * (oldWidth * sizeof(RGBTRIPLE) + oldPadding);

        fseek(inptr, offset, SEEK_SET);

        fread(row, sizeof(RGBTRIPLE), oldWidth, inptr);

        for (int j = 0; j < newWidth; j++)
        {
            int oldCol = floor(j / n);
            if (oldCol >= oldWidth)
                oldCol = oldWidth - 1;

            fwrite(&row[oldCol], sizeof(RGBTRIPLE), 1, outptr);
        }

        for (int k = 0; k < newPadding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    free(row);
    fclose(inptr);
    fclose(outptr);

    return 0;
}