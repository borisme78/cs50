// resize.c
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // Перевірка аргументів
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // Масштаб
    int n = atoi(argv[1]);
    if (n < 1 || n > 100)
    {
        fprintf(stderr, "n must be a positive integer <= 100\n");
        return 1;
    }

    char *infile = argv[2];
    char *outfile = argv[3];

    // Відкриття файлів
    FILE *inptr = fopen(infile, "r");
    if (!inptr)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    FILE *outptr = fopen(outfile, "w");
    if (!outptr)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // Читання заголовків
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Перевірка формату BMP
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(inptr);
        fclose(outptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // Старі розміри
    int oldWidth = bi.biWidth;
    int oldHeight = bi.biHeight;

    // Нові розміри
    bi.biWidth *= n;
    bi.biHeight *= n;

    // Padding для старого та нового зображення
    int oldPadding = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Оновлення розміру файлу
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + newPadding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // Запис заголовків у вихідний файл
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Масштабування
    for (int i = 0, absOldHeight = abs(oldHeight); i < absOldHeight; i++)
    {
        // Зчитуємо рядок у масив
        RGBTRIPLE *row = malloc(sizeof(RGBTRIPLE) * oldWidth);
        for (int j = 0; j < oldWidth; j++)
        {
            fread(&row[j], sizeof(RGBTRIPLE), 1, inptr);
        }

        // Пропуск старого padding
        fseek(inptr, oldPadding, SEEK_CUR);

        // Записуємо рядок n разів
        for (int v = 0; v < n; v++)
        {
            for (int j = 0; j < oldWidth; j++)
            {
                // Записуємо кожен піксель n разів горизонтально
                for (int h = 0; h < n; h++)
                {
                    fwrite(&row[j], sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // Додаємо новий padding
            for (int p = 0; p < newPadding; p++)
            {
                fputc(0x00, outptr);
            }
        }

        free(row);
    }

    // Закриваємо файли
    fclose(inptr);
    fclose(outptr);

    return 0;
}