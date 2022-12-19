#include <emmintrin.h>
#include <immintrin.h>
#define NONS (0x98)
/* Convert any 8bit ASCII-compatible encoding to any other ASCII-compatible encoding. 
   Beware: 
   1) you need additional at least 64 bytes allocated after \0 in source array. 
   2) source & dest pointers must be alined to 64. Icc makes proper code without it, but gcc not:
   https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1AB9U8lJL6yAngGVG6AMKpaAVxYM9DgDJ4GmADl3ACNMYhAAdlIAB1QFQlsGZzcPPVj4mwFffyCWUPCoy0xrRKECJmICZPdPLgtMK0yGMoqCbMCQsMiLcsrq1LqFXra/DryuiIBKC1RXYmR2DgBSACYAZj9kNywAaiW1x0wWFj8CYj8AOgR97CWNAEFVjYYt1139xzxj0/OGK5u7o91lgaP4dgEAPIBIQ7CAaVQATgAHJNAQB6ABUO2cDAAbmECDtDABPHZI4KEHb3ISOACStIAtGgWNEmDZgvQdow0PgjDsiESGKTUAQEGEqTT6UzUCy2XgOZguS8MH5gBc9g8dlqAEKYADuFXYGvuWp2XEmO2Jsx2/kw6CJ6HwTTERMJ9CYQx2ADZJDtgsSCJgFETaLRUKJA/amFRA8Q9gBWRwaHZ%2BHYKWbzRUVYhMYnqwGmlYW9NzBZ7FZenZYT2xU5hYMsVye0Ih0b2gU%2B9W05DIHYsJgAayDO2ixFQ0XFPMVesICFmhMIpD9rkJwB7NpFIALWoASpgCHMGMH4gAvRWoKj8sVps6q9UYtGA1xHvDAfz2sN8z/AFOCP0BzBjBWYx/UDYx7gANQADXjLgVggNAj0JZAEAqHYMRLTMlxQtCMWrAgLUBJYIm1U1ty1TEqWIHNiWDfg4wHVA8CRflUB2GcGHQVA9WDODYJ2RD8UqOUBHVABNa1RAYHZiEwaIDDLUUjlYwVSWpOlGWZVl2U5bkVSMBR70fTVTUQz1TBYWCVjwHZvDkAAVZN9gAER2Yxjis4wlAIYw5OY2FIWhUhAqEYKoVCkKwqCyKYvCqKIri2LosSlLkqC8jTUyrLspy3LsqShK0sK4r4tKgrSHhe4NFK%2BFtWqyLaqiSKMry1q2ty8qGtUbUkTK1KSs6/q%2BqK0qWva8b2sGoLKt6qaBqGubhtCyqEVRNZtQyszCQsqybLs%2ByuD2NZXPcyy4K8/dfOify4VUAAxbAKtUbBqvhbA6nhO6vSe7BpDe%2BMnruv7nrWQGAbe3q3oRH77h%2B7UfscH7nJ%2Bx6xom9Gcreu7Aexz7Xvuj77pWQHQbe763uJz7Ec%2B%2BG3qiT7Iee8H7uhz76fu2G0Yx7mtXhZzHvhJMnscQnnPJ1RHGBxxmecqXSdUZzmccRnHFZiXYcF2mJepiXkcF1GTJ5o3TUF3GFbN5z8ec0XKYV%2BXHHFxxbecnXnK1xx2eclWZbV5zPfuNbSONTKtrc9zdvQhR5iO1yIB2uC8AxC0IEwhZA4y%2BPrJyvDPRc2FM8T5P8PTw2dmfeI3ztHZv2rgQf1OFMY52DR9lIiz%2BwUAcfT7D0B1bjKuL2Ejg6y9AhiWeNtTwCfXLz07PI7gdgInYhG0DVQVlxCorpu/bqrTeYJ6nmel3n86WFQfFrqRdze9hKPkCP6f42c6ZbIc81W5HzLF7I463I8udQMQwd431/inQ%2Bk9n7IwPo/KBM9A4plWBtFYG11oZWIq5PUCA6CKggL/FyecoDl1fO%2BWuX466/gIrCBk5pJglxNKaWSB5iDSQgDZD4HxvSEVQWHYIrg6A2AYMYLYJ5QwQAAH6LwYZgwEHBpi0E4PGXgngOBaFIKgTgjg0wZjLE8HgpACCaHkdMAcIA1gIguF6NYSIkRcGsV6FYGh4wWK9N9RRHBJAqOMRozgvAFAgGqkYtR8jSBwFgEgLSuCyAUAQjKa69BwjIDwD2JxKwuARDqFgXEKTMAQTwPqCEE5VEGJoLQWMASIDBB8RSZgxBiScAMcyNgggIQMFoA0kJpAsD9iMOILp%2BBZIlHxAErpmBVDFBXIsAxdYPHqNoPKHM9TnBYB8beFgjTQlUAMMABQ%2BTCnFM2TIQQIgxDsCkMc%2BQSg1A%2BN0HUAwRgQCmBEfoeUATIDTHHE0UZDIIRrC1AyfsuJVBWVxMEE4KwdiAqYMC0F4K8D%2BIaMUJo9hOL9FqKQHwoxcj5DSHEBIAh0V4oyIkdoOKuiDCRSUAQLQ%2BguBqHoIo1LmjDDJZ0cIgxhhEs5a0Nl4wOXTFTuchRSjvFdM0RwHYqgkRegZN3FJvY0lcAuBEC4h0IC4EICQcsaxzS8GCVoehpAxRMCwOECApjzErCsfYiICIvQIg0FwR1kgNBRA8V40gqj1ESv8YEwxxjpjhMQCgeJ0TyCUCiYklAwA4LE2ybk/ZeoimMCOWUiplBqldNqRUTpTSZQtIIG0jpPiemGGAP09RgzkV4BGT48ZkzAxHNmT4hZwQlnEhWYsdR6zNnTG2UwXZSaU0lN4PwE5ohxAXPHVclQ6gum6GJg8kwZhXnBHeRajR0RvmcF%2Bf8qFQKQVwTBRCg9MKj2b3hYixoiRUVOHpQMTFnE%2BW4rqOkAlSQH0YvfU0F9FL6g3ppVyr9jKqVNFpSMHI7LGXAZSBioYvLsXQfNDMUswr9Ciq9T4iVUqZVyt9GuXscELiQo1U6bV%2BjJj6sDZalYqqIiSEkDYr0EQ1heg0JIZ1DGMOeLFT6vxFh/UGpMTxlYfHeC%2BoDSEo1Ql4h2EkEAA%3D
   Returns size of the string. */
unsigned long long int byte_2_byte_AVX512(const char *source, char *dest) 
{   
    /* Arrays for koi8 to windows 1251 convertation. You can replace them to any ASCII-compatible encodings. */
    const __m512i LUT0 = _mm512_set_epi8 (NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,
                                          NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,0xA0,NONS,0xB0,NONS,0xB7,NONS,
                                          NONS,NONS,NONS,0xB8,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,
                                          NONS,NONS,NONS,0xA8,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,NONS,0xA9);
    const __m512i LUT1 = _mm512_set_epi8 (0xFE,0xE0,0xE1,0xF6,0xE4,0xE5,0xF4,0xE3,0xF5,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,
                                          0xEF,0xFF,0xF0,0xF1,0xF2,0xF3,0xE6,0xE2,0xFC,0xFB,0xE7,0xF8,0xE5,0xF9,0xF7,0xFA,
                                          0xDE,0xC0,0xC1,0xD6,0xC4,0xC5,0xD4,0xC3,0xD5,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,
                                          0xCF,0xDF,0xD0,0xD1,0xD2,0xD3,0xC6,0xC2,0xDC,0xDB,0xC7,0xD8,0xC5,0xD9,0xD7,0xDA);  
    const __m512i *src = (__m512i*) (source);
    __m512i       *dst = (__m512i*) (dest);
    unsigned long long int i = 0; __mmask64 mask;
    do { 
      dst[i] = _mm512_mask2_permutex2var_epi8 (LUT0, src[i], _mm512_movepi8_mask (src[i]), LUT1); 
      mask   = _mm512_test_epi8_mask (src[i], src[i]); i++;
    } while (mask == ((unsigned long long int) (-1)));
    return (i << 6) + __builtin_clzll(~mask);
}
