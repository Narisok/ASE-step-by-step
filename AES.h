#ifndef AES_NARISOK_GUARD
#define AES_NARISOK_GUARD

#include <stdint.h>
#include <stddef.h>

void AES_keys_generate(uint8_t input_key[16], uint8_t output_keys[11][16]);


//operations for encrypt
    void AES_steep_add_round_key(uint8_t block[16], const size_t input_key_round, const uint8_t keys[11][16]);
    void AES_steep_sub_bytes(uint8_t block[16]);
    void AES_steep_shift_row(uint8_t block[16]);
    void AES_steep_mix_columns(uint8_t block[16]);

void AES_encrypt_block(uint8_t block[16], const uint8_t keys[11][16]);

#endif //AES_NARISOK_GUARD