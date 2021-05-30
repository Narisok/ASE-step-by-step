#include "../AES.h"

#include <stdio.h>

int main()
{

uint8_t block[16] = {
    0x54,
    0x68,
    0x61,
    0x74,
    0x73,
    0x20,
    0x6D,
    0x79,
    0x20,
    0x4B,
    0x75,
    0x6E,
    0x67,
    0x20,
    0x46,
    0x75    
};

uint8_t out[16];

uint8_t keys[11][16];
uint8_t key[16] = {
    0x54,0x68,0x61,0x74,0x73,0x20,0x6D,0x79,
    0x20,0x4B,0x75,0x6E,0x67,0x20,0x46,0x75
};
printf("\e[32m\e[1m");
printf("Input key: ");
for(int i = 0; i < 16; ++i)
    printf("%02x ", key[i]);
printf("\n");
printf("\e[0m");

AES_keys_generate(key, keys);

printf("Round keys >> \n");
for(int j = 0; j < 11; ++j) {
    printf("\tkey [%2i]: ", j);
    for(int i = 0; i < 16; ++i)
        printf("%02x ", keys[j][i]);
    printf("\n");
}
printf("\n");


printf("\e[32m\e[1m");
printf("Input block:  ");
for(int i = 0; i < 16; ++i)
    printf("%02x ", block[i]);
printf("\n");
printf("\e[0m");

AES_steep_add_round_key(block, 0, keys);
printf("Add round key [%2i]: ", 0);

for(int i = 0; i < 16; ++i)
    printf("%02x ", block[i]);
printf("\n");

for(int i = 1; i < 10; ++i) {
    printf("\nRound      [%2i] ______________________________________________\n", i);
    AES_steep_sub_bytes(block);
    printf("Sub bytes:     ");
    for(int i = 0; i < 16; ++i)
        printf("%02x ", block[i]);
    printf("\n");

    AES_steep_shift_row(block);
    printf("Shift row:     ");
    for(int i = 0; i < 16; ++i)
        printf("%02x ", block[i]);
    printf("\n");

    AES_steep_mix_columns(block);

    printf("Mix columns:   ");
    for(int i = 0; i < 16; ++i)
        printf("%02x ", block[i]);
    printf("\n");

    AES_steep_add_round_key(block, i, keys);
    printf("Add round key: ");
    for(int i = 0; i < 16; ++i)
        printf("%02x ", block[i]);
    printf("\n");
}
printf("\nRound      [%2i] ______________________________________________\n", 10);
AES_steep_sub_bytes(block);
printf("Sub bytes:      ");
    for(int i = 0; i < 16; ++i)
        printf("%02x ", block[i]);
    printf("\n");


AES_steep_shift_row(block);
printf("Shift row:      ");
    for(int i = 0; i < 16; ++i)
        printf("%02x ", block[i]);
    printf("\n");
AES_steep_add_round_key(block, 10, keys);

printf("Add round key:  ");
    for(int i = 0; i < 16; ++i)
        printf("%02x ", block[i]);
    printf("\n");
printf("\n");

printf("\e[32m\e[1m");
printf("Encrypted block: ");
for(int i = 0; i < 16; ++i)
    printf("%02x ", block[i]);
printf("\n");
printf("\e[0m");

}