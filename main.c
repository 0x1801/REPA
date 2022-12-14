#include <filesystem>
#include <windows.h>

/* Часть кода ниже написана для проверки функции utf8_2_win1251 наспех на коленке. Потому не претендует на красоту и скорость. Но вроде проверяет. 
   В целом она не нужна. */
#define SIZE 10000000
void main ()
{
    unsigned int res;
    SetConsoleCP(1251); SetConsoleOutputCP(1251);
    char *Utf8 = (char*)malloc((SIZE * 4 + 1 + 2) * sizeof(char)); 
    char *Wincp = (char*)malloc((SIZE + 1) * sizeof(char));
    unsigned int i, j, k;
    for (k = 1, j = 0; k < SIZE; k++)
    {
        i = 0;
        while (i == 0)
        {
            i = rand() % 1000000;
        }
//        printf("i = %d", i);
        if (i < 0x80)
        {
            Utf8[j] = i;
            j++;
        }
        if ((i >= 0x80) && (i < 0x800))
        {
            Utf8[j] = (i >> 6) + 0xC0;
            Utf8[j + 1] = (i & 0x3F) + 0x80;
            j += 2;
        }
        if ((i >= 0x800) && (i < 0x10000))
        {
            Utf8[j] = (i >> 12) + 0xE0;
            Utf8[j + 1] = ((i >> 6) & 0x3F) + 0x80;
            Utf8[j + 2] = (i & 0x3F) + 0x80;
            j += 3;
        }
        if (i >= 0x10000)
        {
            Utf8[j] = (i >> 18) + 0xF0;
            Utf8[j + 1] = ((i >> 12) & 0x3F) + 0x80;
            Utf8[j + 2] = ((i >> 6) & 0x3F) + 0x80;
            Utf8[j + 3] = (i & 0x3F) + 0x80;
            j += 4;
        }
    }
    Utf8[j] = '\0';
    size_t time = clock();
    res = utf8_2_win1251 (Utf8, Wincp);
    time = clock() - time;
    Wincp[res] = 0;
    printf("%s\n\ntime = %d", Wincp, time);
    free(Utf8); free(Wincp);
    scanf("%d",&i);
    return;
}
