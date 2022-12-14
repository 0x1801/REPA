#include <stdio.h>
#include <string.h>
#include <iostream>
#include <io.h>
#include <filesystem>
#include <windows.h>

#define NONS (0x98)
//#define SKIP_OR_NOT 1
#define SKIP_OR_NOT (dest != NONS)
#define M(W40, W45, W201) ((((W40) - 0x80) << 10) | (((W45) - (W40)) << 5) | ((W201) - 0x80))

/* Функция конвертирует utf8 строку в win 1251. Символы, не имеющие отображения, или переходят в 0x98 или пропускаются. 
   Вариант работы выбирается версией макроса SKIP_OR_NOT. ВНИМАНИЕ: массив utf8 должен быть выделен с запасом по памяти в 2 байта. 
   Т.е. за символом конца строки '\0' должно быть как минимум 2 байта памяти. 
   В этих 2х байтах может лежать любой муcор. В противном случае программа может падать из-за доступа к не своей памяти. */
unsigned int utf8_2_win1251(const char *utf8, char *win)
{
    unsigned int dest, p, l1, l2, l3, inc, i, j, b1, b2, b3;
    const unsigned int D = 0xF71C852E;
    const unsigned short AR[16] = { M(NONS,NONS,0x86),M(0xA8,0xB8,0x87),M(0x80,0x90,0x95),M(0x81,0x83,0x96),
                                    M(0xAA,0xBA,0x97),M(0xBD,0xBE,NONS),M(0xB2,0xB3,NONS),M(0xAF,0xBF,NONS),
                                    M(0xA3,0xBC,0x91),M(0x8A,0x9A,0x92),M(0x8C,0x9C,0x82),M(0x8E,0x9E,NONS),
                                    M(0x8D,0x9D,0x93),M(NONS,NONS,0x94),M(0xA1,0xA2,0x84),M(0x8F,0x9F,NONS) };
    for (i = 0, j = 0; utf8[i] != '\0'; i += inc)
    {
        b1 = utf8[i]; b2 = utf8[i + 1]; b3 = utf8[i + 2];
        /* Utf8 переводим в Unicode. */
        inc = (0xE5000000u >> (((b1) >> 4) << 1)) & 0x3;
        p = ((((b1) << 12) + (((b2) & 0x3F) << 6) + ((b3) & 0x3F)) & (0x7FFFF >> inc)) >> (((0xC5FFAAAAu >> (((b1) >> 4) << 1)) & 0x3) * 6);
        /* Добавляем все остающиеся на месте. */
        dest = (((inc != 0) & (((p >> 5) != 0x5) | (D >> b2))) - 1) & p; inc++;
        /* Добавляем русские буквы кроме ё и Ё.*/
        dest += ((((p - 0x10) >> 6) != 0x10) - 1) & (p - 0x350);
        /* Добавляем символы из диапазонов: 0x401-0x40F, 0x451-0x45F, 0x2013-0x2022. */
        l1 = ((p >> 4) != 0x40) - 1; l2 = ((p >> 4) != 0x45) - 1; l3 = (((p - 3) >> 4) != 0x201) - 1;
        dest += ((((l2 & (AR[p & 0xF] >> 5)) | (l3 & AR[p & 0xF])) & 0x1F) + ((l1 | l2) & (AR[p & 0xF] >> 10))) + ((l1 | l2 | l3) & 0x80);
        /* Добавляем оставшиеся. */
        dest += (((p !=  0x490) - 1) & 0xA5) | (((p !=  0x491) - 1) & 0xB4) | (((p != 0x2026) - 1) & 0x85) |
                (((p != 0x2030) - 1) & 0x89) | (((p != 0x2039) - 1) & 0x8B) | (((p != 0x203A) - 1) & 0x9B) |
                (((p != 0x20AC) - 1) & 0x88) | (((p != 0x2116) - 1) & 0xB9) | (((p != 0x2122) - 1) & 0x99);
        /* Отличаем настоящий 0 от просто отсутствующих в win 1251 символов. */
        dest += (((b1 == 0) | (dest != 0)) - 1) & NONS;
        win[j] = dest;
        j += SKIP_OR_NOT;
    }
    win[j] = '\0';
    return j;
}

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
