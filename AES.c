#include "AES.h"
#include <stdlib.h>
#include <stdio.h>

static uint8_t SBox[] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, 
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, 
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, 
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, 
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, 
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, 
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, 
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, 
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, 
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, 
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, 
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, 
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, 
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, 
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, 
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

static uint8_t RCon[11][4] = {
        {0x00, 0x00, 0x00, 0x00},
        {0x01, 0x00, 0x00, 0x00},
        {0x02, 0x00, 0x00, 0x00},
        {0x04, 0x00, 0x00, 0x00},
        {0x08, 0x00, 0x00, 0x00},
        {0x10, 0x00, 0x00, 0x00},
        {0x20, 0x00, 0x00, 0x00},
        {0x40, 0x00, 0x00, 0x00},
        {0x80, 0x00, 0x00, 0x00},
        {0x1b, 0x00, 0x00, 0x00},
        {0x36, 0x00, 0x00, 0x00}
    };


static void shiftWord(uint8_t* word) 
{
    uint8_t tmp = word[0];
    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = tmp;
}

static void subWord(uint8_t * word)
{
    word[0] = SBox[word[0]];
    word[1] = SBox[word[1]];
    word[2] = SBox[word[2]];
    word[3] = SBox[word[3]];
}

static void roundConst(uint8_t * word, size_t round)
{
    word[0] ^= RCon[round][0];
    word[1] ^= RCon[round][1];
    word[2] ^= RCon[round][2];
    word[3] ^= RCon[round][3];
}

void AES_keys_generate(uint8_t key[16], uint8_t keys[11][16])
{

    for(int x = 0; x < 16; ++x) 
        keys[0][x] = key[x];

    int N = 4;
    for(int i = 1; i < 11; ++i) {
        keys[i][0] = keys[i-1][12];
        keys[i][1] = keys[i-1][13];
        keys[i][2] = keys[i-1][14];
        keys[i][3] = keys[i-1][15];
        shiftWord(&keys[i][0]);
        subWord(&keys[i][0]);
        roundConst(&keys[i][0], (i*4)/N);

        keys[i][0] ^= keys[i-1][0];
        keys[i][1] ^= keys[i-1][1];
        keys[i][2] ^= keys[i-1][2];
        keys[i][3] ^= keys[i-1][3];

        keys[i][4] = keys[i][0] ^ keys[i-1][4];
        keys[i][5] = keys[i][1] ^ keys[i-1][5];
        keys[i][6] = keys[i][2] ^ keys[i-1][6];
        keys[i][7] = keys[i][3] ^ keys[i-1][7];

        keys[i][8] = keys[i][4] ^ keys[i-1][8];
        keys[i][9] = keys[i][5] ^ keys[i-1][9];
        keys[i][10] = keys[i][6] ^ keys[i-1][10];
        keys[i][11] = keys[i][7] ^ keys[i-1][11];

        keys[i][12] = keys[i][8] ^ keys[i-1][12];
        keys[i][13] = keys[i][9] ^ keys[i-1][13];
        keys[i][14] = keys[i][10] ^ keys[i-1][14];
        keys[i][15] = keys[i][11] ^ keys[i-1][15];
    }
}

void AES_steep_add_round_key(uint8_t block[16], const size_t round_key, const uint8_t keys[11][16])
{
    for(size_t i = 0; i < 16; ++i) {
        block[i] = block[i] ^ keys[round_key][i];
    }
}

void AES_steep_sub_bytes(uint8_t block[16])
{
    for(size_t i = 0; i < 16; ++i) {
        block[i] = SBox[block[i]];
    }
}

void AES_steep_shift_row(uint8_t block[16])
{
    uint8_t tmp;

    tmp = block[1];
    block[1] = block[4+1];
    block[4+1] = block[8+1];
    block[8+1] = block[12+1];
    block[12+1] = tmp;

    tmp = block[2];
    block[2] = block[8+2];
    block[8+2] = tmp;
    tmp = block[4+2];
    block[4+2] = block[12+2];
    block[12+2] = tmp;

    tmp = block[12+3];
    block[12+3] = block[8+3];
    block[8+3] = block[4+3];
    block[4+3] = block[3];
    block[3] = tmp;
}

static uint8_t Mult[16] = {
    0x02, 0x03, 0x01, 0x01,
    0x01, 0x02, 0x03, 0x01,
    0x01, 0x01, 0x02, 0x03,
    0x03, 0x01, 0x01, 0x02
};

void AES_steep_mix_columns(uint8_t block[16])
{
    uint8_t result[16]={};
    for(size_t i = 0; i < 16; ++i) {
        for(size_t m = 0; m < 4; ++m) {
            size_t idx = i/4*4+m;
            switch(Mult[i%4*4+m]) {
                case 0x01:
                    result[i] ^= block[idx];
                    break;
                case 0x02:
                    result[i] ^= block[idx]&0x80 ? (block[idx]<<1) ^ 0x1b : block[idx]<<1;
                    break;
                case 0x03:
                    result[i] ^= (block[idx]&0x80 ? (block[idx]<<1) ^ 0x1b : block[idx] <<1) 
                        ^ block[idx];
                    break;
                }
        }
    }
    for(size_t i = 0; i < 16; ++i) {
        block[i] = result[i];
    }
}


void AES_encrypt_block(uint8_t block[16], const uint8_t keys[11][16])
{

}