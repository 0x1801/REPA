#include <emmintrin.h>
#include <immintrin.h>
#define NONS (0x98)
/* Convert any 8bit ASCII-compatible encoding to any other ASCII-compatible encoding. 
   Beware: 
   1) you need additional at least 64 bytes allocated after \0 in source and dest arrays. 
   2) source & dest pointers must be alined to 64. Icc makes proper code without it, but gcc not:
   https://godbolt.org/z/xcP9sqvj3
   Returns size of the string. */
unsigned long long int byte_2_byte_AVX512(const char *source, char *dest) 
{   
    /* Arrays for koi8 to windows 1251 convertation. You can replace them to any ASCII-compatible encodings. */
    const __m512i LUT0 = _mm512_set_epi8 (0xA9,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,0xA8,NONS,NONS,NONS,
                                          NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,0xB8,NONS,NONS,NONS,
                                          NONS,0xB7,NONS,0xB0,NONS,0xA0,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,
                                          NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS);
    const __m512i LUT1 = _mm512_set_epi8 (0xDA,0xD7,0xD9,0xC5,0xD8,0xC7,0xDB,0xDC,0xC2,0xC6,0xD3,0xD2,0xD1,0xD0,0xDF,0xCF,
                                          0xCE,0xCD,0xCC,0xCB,0xCA,0xC9,0xC8,0xD5,0xC3,0xD4,0xC5,0xC4,0xD6,0xC1,0xC0,0xDE,
                                          0xFA,0xF7,0xF9,0xE5,0xF8,0xE7,0xFB,0xFC,0xE2,0xE6,0xF3,0xF2,0xF1,0xF0,0xFF,0xEF,
                                          0xEE,0xED,0xEC,0xEB,0xEA,0xE9,0xE8,0xF5,0xE3,0xF4,0xE5,0xE4,0xF6,0xE1,0xE0,0xFE);  
    const __m512i *src = (__m512i*) (source);
    __m512i       *dst = (__m512i*) (dest);
    unsigned long long int i = 0; __mmask64 mask;
    do { 
      dst[i] = _mm512_mask2_permutex2var_epi8 (LUT0, src[i], _mm512_movepi8_mask (src[i]), LUT1); 
      mask   = _mm512_test_epi8_mask (src[i], src[i]); i++;
    } while (mask == ((unsigned long long int) (-1)));
    return (i << 6) + __builtin_clzll(~mask);
}
