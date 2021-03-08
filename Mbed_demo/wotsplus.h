#pragma once
#define KEY_SIZE_L 67
#define KEY_EACH_NUMBER_BYTE_SIZE 32
typedef uint8_t array_of_32_uint8_t[KEY_EACH_NUMBER_BYTE_SIZE];

int key_size_count;

typedef struct wotsplus_obj
{

    int wots_param_w;
    int digestsize;

    int msg_size_count; //l1
    int checksum_size; //l2

    int total_key_size; //L = l1+l2
    uint8_t seed[KEY_EACH_NUMBER_BYTE_SIZE];

} wotsplus_obj;


wotsplus_obj* init_wots(wotsplus_obj*, int w, int d, uint8_t* seed);
void gen_secret_key(array_of_32_uint8_t secret_key[KEY_SIZE_L], int magic, uint8_t *salt);
int gen_public_key(array_of_32_uint8_t secret_key[KEY_SIZE_L], array_of_32_uint8_t public_key[KEY_SIZE_L], array_of_32_uint8_t seed);
uint8_t* chain(int init, int end, array_of_32_uint8_t value, array_of_32_uint8_t seed);
void bitwise_xor_bytes(uint8_t input[KEY_EACH_NUMBER_BYTE_SIZE], uint8_t bit_mask[KEY_EACH_NUMBER_BYTE_SIZE], uint8_t chaining_variable[KEY_EACH_NUMBER_BYTE_SIZE]);
int get_signature_base_message(char* dest, size_t dest_len, const uint8_t* values, size_t val_len);
int get_checksum(wotsplus_obj* obj, int* value);
int* convert_checksum_hex(int cksm, int checksum_array[], int size);
int* convert_hex_values(char* hex, int hex_array[], int size);

int sign(wotsplus_obj* wots_obj, char* message, uint8_t* secret_key[KEY_SIZE_L], array_of_32_uint8_t signature[KEY_SIZE_L]);
int get_public_key_from_signature(wotsplus_obj* wots_obj, char* message, array_of_32_uint8_t signature[KEY_SIZE_L], array_of_32_uint8_t derived_pub_key[KEY_SIZE_L]);

int verify_signature(wotsplus_obj* wots_obj, char* message, array_of_32_uint8_t signature[KEY_SIZE_L], array_of_32_uint8_t publick_key[KEY_SIZE_L]);