#include <emmintrin.h>
#include <immintrin.h>
#define NONS (0x98)
/* Convert any 8bit ASCII-compatible encoding to any other ASCII-compatible encoding. 
   Beware: 
   1) you need additional at least 64 bytes allocated after \0 in source and dest arrays. 
   2) source & dest pointers must be alined to 64. Icc makes proper code without it, but gcc not:
   https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1AB9U8lJL6yAngGVG6AMKpaAVxYM9DgDJ4GmADl3ACNMYhAAJgBOUgAHVAVCWwZnNw89eMSbAV9/IJZQ8OiLTCtshiECJmICVPdPLhKy5MrqglzAkLDImIUqmrr0xr62jvzCnoBKC1RXYmR2DgBSCIBmP2Q3LABqJdXHTBYWPwJiPwA6BD3sJY0AQRX1hk3XHb3HPCOTs4ZL69uHmssDR/NsAgB5AJCbYQDSqKIADkmAIA9AAqbbOBgANzCBG2hgAntsEcFCNs7kJHABJakAWjQLFiTBswXo20YaHwRm2RAJDGJqAICDCFKptIZqCZLLwbMwHOeGD8wHOu3u2w1ACFMAB3arsNV3DXbLiTbaE2bbfyYdAE9D4cpiAn4%2BhMPrbABskm2wUJBEwCgJtFoqFE/ttTCo/uIuwArI4NNs/NsFLN5vLqsQmITVQDjREzam5gtdhEPdssO74icwoGWK53aEg34bbzUJ7JKrqchkNsWEwANYB7axYioWKirnynWEBCzfGEUg%2B1z44A9q1CkB5jUAJUwBDmDEDiQAXvLUFReSKU6dlaq0SiAa4j3hgP5bSGeZ/gEnBD6/ZgxgRMYvr%2BsYdwAGoABqxlwEQQGgR74sgCDVNsaJFumS4oWhaKVgQZoAksADsmrGtuGrohSxBZoSgb8DGA6oHgCJttsM4MOgqA6oGcGwdsiG4jUMoCKqACalqiAw2zEJgsQGCWwqHGxRJijS9KMsyrLspySpGAo96PuqxqIe6pgsLBER4Ns3hyAAKomewACLbMYRyWcYSgEMYcksTCcJ3DEEJQqQwVCKFkLhWFEUhdFcWRTFUUJdFAUIol6XRRRxrZTluV5fluXxbFyUlcVZVJeVGWleFcKamlRUVeFWUFS1rX5SlqiasR6W1RoPWqHcfUNVVlXDWNCXNW1U1teNo3VSNjULUts1CMiqyallpn4uZlnWbZdlcLsqwuW5FlwZ5%2B4%2BbEfmwqoTl3KQcJOd1T0xHCjixo9d1pe9L13ZqX1OY4X2OBEIMeoDqyA2DT2NE9fVPQAYiDyOTdN6N5e92Ag05IPA%2B9APvQ971vaojg/Xdn3vVDT3SO9VNk3Td0Q%2B9cNkwjd3Y2jGM8xqcKI8TqiI39iOk9gDOIxT2Ai4TQv46o2AwwrLNCzTQtK4jbOIxziPI3C2Co8ZvPG8a%2BvY/ruP6/L2Cy9ggvYGLFOIwz2Bq4jTPi192BM4jKvYGz2A69ga1kYa2Vba5bm7ehCjzEdLkQDtcF4GiZoQJhCwh1lSdWXleHus5MI5ynaf4VnRvbM%2BiRvq237bHXJxJvH2waHsZHmf2CgDl6fZugObdZVxuykWHOXoH0SyxpqeCTy5henR5ncDsBE7EPW/qqBE2LVFdN37X1KbzJP0%2Bz0uC/nSwqC4tdCJuX3MKx8gx8z7GTnTDZ9mmm3o/ZUv5HHa5dy51/R9F3rfP%2B6cj5TxfrjQ%2BT9oGzxDkmFYG0IgbXWllEiLkdQIDoPKCAf9nKFygFXV87564CB/A3QQac6SmkmOXI0xpZIHmINJCA1l3jvE9IRNBkdgiuDoDYBgxhNgnmDBAAAfkvRhWCAQcGmLQTgsZeCeA4FoUgqBOCOBTGmEsjweCkAIJoBR0wBwgEkLGc4sZiJcGIgiYiURLEegiJYxoSiOCSFUSYzRnBeAKBAH1Yx6iFGkDgLAJAmk8FkAoAhKU116DhGQHgHsEQNARDsY0LA2IUmYAgngXU4IJxqMMTQWg0YAkQGCD4skzBiCEk4IYxkbBBDggYLQBpITSBYH7EYcQXT8CyWsHgXEASumYFUJgZAK5FiGJrB4jRtBZRZnqc4LAPjbwsEaaEqgBhgAKHyYU4p2yZCCBEGIdgUhTnyCUGoHxuh3GGBMGYfQsoAmQGmOOcoYy6TglWBqOk/ZsSqEstiYIxwIjbEBUwYFoLwV4H8aUKZ5R7CcUGA0UgPgWzjG6I0TISQBDooyAkAlDAxhdHCMMJFwyBCtAGC4eoehLDIpaP0do2KKVMrZUS4YbLyUFFxdMDOlzFHKO8V0rRHBtiqARB6OkPcUm9jSRk84xFziHQgLgQgJBSyrFNLwYJWgGGkBFEwLA4QIBmMiB6c4HoESrARBEWMer7WrFWLGCIYMPFeNIGojRkr/GBKMSY6Y4TEAoHidE8glAomJJQMAOCYNsm5MOTqIpjATllIqZQapXTanVE6U0qULSCBtI6T4npTz%2BkaMGSy0ZPiJlTJmSc%2BZPilnBBWYSNZiwNGbO2dMXZTB9mpvTSU3g/AzmiHEFcidNyVDqC6boL1TyQCmFEa84I7zLWaNiN8zgvz/lQqBSCuCYKIVHphSere8LEXNDsBABwPLMWcX5RMPFJLyhPvxeUV9uKmgstpdyhlQx/00oqHyjlArKUWCA2kDFIwai/spUKvRIr9Bit9T4yV0rZXyu9GuXscFziQs1Q6HVBjJgGpDVaiIariKSEkA6j0xFVgeg0JILgUR6Poc8eK/1fiLBBsNaYnjEQ%2BO8ADcGkJxqhKJDsJIIAA%3D
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
