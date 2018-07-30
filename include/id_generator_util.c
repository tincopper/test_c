//
// Created by tangzy on 18-7-30.
//

#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

#if RAND_MAX/256 >= 0xFFFFFFFFFFFFFF
#define LOOP_COUNT 1
#elif RAND_MAX/256 >= 0xFFFFFF
#define LOOP_COUNT 2
#elif RAND_MAX/256 >= 0x3FFFF
#define LOOP_COUNT 3
#elif RAND_MAX/256 >= 0x1FF
#define LOOP_COUNT 4
#else
  #define LOOP_COUNT 5
#endif

/* bin to hex */
void b2hex(char **output, const unsigned char *input, int input_len)
{
    static const char hexits[17] = "0123456789abcdef";
    int i;
    *output = (char *)malloc(input_len * 2 + 1);
    for (i = 0; i < input_len; i++) {
        *(*output + i*2) = hexits[*(input+i) >> 4];
        *(*output + i*2 + 1) = hexits[*(input+i) & 0x0F];
    }
    *(*output + input_len *2) = '\0';
}

/* bin2hex64 */
void bin2hex64(char **output, const uint64_t *input)
{
    b2hex(output, (const unsigned char *)input, 8);
}

/* rand uini64 */
uint64_t rand_uint64(void)
{
    uint64_t r = 0;
    int i = 0;
    struct timeval tv;
    int seed = gettimeofday(&tv, NULL) == 0 ? tv.tv_usec * getpid() : getpid();
    srandom(seed);
    for (i = LOOP_COUNT; i > 0; i--) {
        r = r*(RAND_MAX + (uint64_t)1) + random();
    }
    return r;
}

/* random 64 and change to hex */
void rand64hex(char **output)
{
    uint64_t num = rand_uint64();
    return bin2hex64(output, &num);
}