#include <stdio.h>
#include "bmp.h"

// http://www.ue.eti.pg.gda.pl/fpgalab/zadania.spartan3/zad_vga_struktura_pliku_bmp_en.html
int main(void)
{
    FILE *inptr = fopen("input.bmp", "rb");   // open BMP for reading
    FILE *outptr = fopen("output.bmp", "wb"); // open BMP for writing

    if (!inptr || !outptr)
    {
        printf("Error opening files.\n");
        return 1;
    }

    // Read headers
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    printf("Width: %d, Height: %d\n", bi.biWidth, bi.biHeight);
    printf("bfType: %X\n", bf.bfType);
    printf("biSize: %u\n", bi.biSize);
    printf("biBitCount: %d\n", bi.biBitCount);

    // Write headers to new file
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Copy pixel data one row at a time
    int width = bi.biWidth;
    int height = bi.biHeight;
    RGBTRIPLE pixel;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            fread(&pixel, sizeof(RGBTRIPLE), 1, inptr);
            if (pixel.rgbtRed > 50 &&
                pixel.rgbtGreen < 100 &&
                pixel.rgbtBlue < 50)
            {
                // робимо його білим
                pixel.rgbtRed = 255;
                pixel.rgbtGreen = 255;
                pixel.rgbtBlue = 255;
            }
            fwrite(&pixel, sizeof(RGBTRIPLE), 1, outptr);
        }
    }

    fclose(inptr);
    fclose(outptr);

    printf("BMP copied successfully!\n");
    return 0;
}