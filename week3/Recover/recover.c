#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    
    // відкриття файлу для читання якщо у файлі немає даних вивести помилку
    FILE *file = fopen(argv[1], "rb");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open file.\n");
        return 1;
    }
    //створення буферу для даних
    unsigned char buffer[512];
    // bool змінна для керування в середині циклу
    bool foundJPEG = false;
    //лічильний для фото
    int jpegCount = 0;
    // створення нового файлу
    FILE *output = NULL;
    foundJPEG = false;
    // цикл який записує потрібні файли у output з файлу file
    while (fread(buffer, 1, 512, file))
    {   // перевіряємо чи це зображення
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {   // якщо умова вірна значіть це зображення створюєм масив для запису нових файлів 
            char filename[8];
            sprintf(filename, "%03d.jpg", jpegCount++);
            output = fopen(filename, "wb");
            foundJPEG = true;
        }
        // створюєм нове зображення якщо foundJPEG true 
        if (foundJPEG)
        {
            fwrite(buffer, 1, 512, output);
        }
    }
    // якщо вихідний файл не нуль закрити його
    if (output != NULL)

        fclose(output);
    //закрити початковий файл
    fclose(file);
}
