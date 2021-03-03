#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "wotsplus.h"
#include "m_hmac.h"
#include "m_sha256.h"

const char hex_digits[16] = "0123456789abcdef";


wotsplus_obj* init_wots(wotsplus_obj* this_wots_obj, int w, int d, uint8_t* seed)
{
    if (!(w <= 2 || w >= (1 << d))) {
        printf("ERROR: Rule broken: 2 <= w <= 2^digestsize");
        return NULL;
    }

    int msg_size = 64;
    int checksum = 3;
    key_size_count = msg_size + checksum;

    this_wots_obj->wots_param_w = w;
    this_wots_obj->digestsize = d;

    this_wots_obj->msg_size_count = msg_size; //l1
    this_wots_obj->checksum_size = checksum; //l2

    this_wots_obj->total_key_size = key_size_count; //L = l1+l2
    for(int i = 0; i< KEY_EACH_NUMBER_BYTE_SIZE; i++)
        this_wots_obj->seed[i] = seed[i];

    return this_wots_obj;
}

void gen_secret_key(array_of_32_uint8_t secret_key[KEY_SIZE_L], int magic) {
    // 0 to 30 = 31
    for (int i = 0; i < KEY_SIZE_L - 1; i++) {

        const unsigned char charset[] = "mnopqrstabcdefgluvwxyz12345hijk";
        
        for (size_t n = 0; n < KEY_EACH_NUMBER_BYTE_SIZE; n++) {
            int key = (magic++) % (int)(sizeof charset);
            secret_key[i][n] = charset[key];
        }
    }

    // 32

    const char salt[] = "SALTSALTSALTSALTSALTSALTSALTSALT";
    for (int k = 0; k < KEY_EACH_NUMBER_BYTE_SIZE; k++)
        secret_key[KEY_SIZE_L - 1][k] = salt[k];
}


void bitwise_xor_bytes(uint8_t input[KEY_EACH_NUMBER_BYTE_SIZE], uint8_t bit_mask[KEY_EACH_NUMBER_BYTE_SIZE], uint8_t chaining_variable[KEY_EACH_NUMBER_BYTE_SIZE]) {
    // xor input and bitmask
    for (int i = 0; i < KEY_EACH_NUMBER_BYTE_SIZE; i++) {
        chaining_variable[i] = input[i] ^ bit_mask[i];
    }
}

uint8_t* chain(int init, int end, array_of_32_uint8_t value, array_of_32_uint8_t seed) {
    
    for (int i = init; i < end; i++) {
        uint8_t bit_mask[KEY_EACH_NUMBER_BYTE_SIZE];
        HashValuePrint(value);
        DoHMAC(value, seed, bit_mask);

        uint8_t chain_var[KEY_EACH_NUMBER_BYTE_SIZE];
        bitwise_xor_bytes(value, bit_mask, chain_var);

        uint8_t sha[KEY_EACH_NUMBER_BYTE_SIZE];
        DoSha256_bytes(chain_var, sha, KEY_EACH_NUMBER_BYTE_SIZE);

        // value = NULL;
        // value = malloc(sizeof(uint8_t)*KEY_EACH_NUMBER_BYTE_SIZE);
        // memcpy(value, sha, KEY_EACH_NUMBER_BYTE_SIZE);
        for (int j = 0; j < KEY_EACH_NUMBER_BYTE_SIZE; j++) {
            value[j] = sha[j];
        }
    }
    return value;
}

int gen_public_key(array_of_32_uint8_t secret_key[KEY_SIZE_L], array_of_32_uint8_t public_key[KEY_SIZE_L], array_of_32_uint8_t seed) {

    // each number in priv key is chained
    for (int i = 0; i < KEY_SIZE_L; i++) {
        chain(0, 16, secret_key[i], seed);

        for (int j = 0; j < KEY_EACH_NUMBER_BYTE_SIZE; j++) {
            public_key[i][j] = secret_key[i][j];
        }
    }

    return 0;
}

int get_checksum(wotsplus_obj* obj, int* value) {
    int result = 0;
    // sum upto l1
    for (int i = 0; i < obj->msg_size_count; i++) {
        result += obj->wots_param_w - 1 - value[i];
    }
    return result;
}

int* convert_hex_values(char* hex, int hex_array[], int size) {

    for (int i = 0; i < size; i++) {
        char* hexCharset = "0123456789ABCDEF";
        char* each;
        int index;

        each = strchr(hexCharset, hex[i]);
        index = (int)(each - hexCharset);
        hex_array[i] = index;
    }
    return hex_array;
}

int get_signature_base_message(char* dest, size_t dest_len, const uint8_t* values, size_t val_len) {
    // 85AF = 8, 5, 10, 16 as hexadecimal
    //if (dest_len < (val_len * 2 + 1)) /* check that dest is large enough */
    //    return 1;
    //*dest = '\0'; /* in case val_len==0 */
    //while (val_len--) {
    //    /* sprintf directly to where dest points */
    //    sprintf(dest, "%02X", *values);
    //    dest += 2;
    //    ++values;
    //}
    return 1;
}

int* convert_checksum_hex(int cksm, int checksum_array[], int size) {
    // convert checksum into array[int] |l2|
    int counter = size - 1;

    while (cksm != 0 || counter >= 0)
    {
        checksum_array[counter] = cksm % 16;
        cksm /= 16;
        counter--;
    }
    return checksum_array;
}


int sign(wotsplus_obj* wots_obj, char* message, uint8_t* secret_key[KEY_SIZE_L], uint8_t* signature[KEY_SIZE_L]) {

    uint8_t msg_hash[KEY_EACH_NUMBER_BYTE_SIZE];
    DoSha256(message, msg_hash);

    char msg_base_w[sizeof(msg_hash) * 2 + 1];
    if (get_signature_base_message(msg_base_w, sizeof(msg_base_w), msg_hash, sizeof(msg_hash)))
        printf("---- %s\n", msg_base_w);

    int msg_to_sign[sizeof(msg_base_w) - 1];
    convert_hex_values(msg_base_w, msg_to_sign, sizeof(msg_base_w));

    // get checksum
    int cksm = get_checksum(wots_obj, msg_to_sign);

    int checksum_array[3];
    convert_checksum_hex(cksm, checksum_array, 3);

    int final_msg[67];
    for (int i = 0; i < wots_obj->msg_size_count; i++) {
        final_msg[i] = msg_to_sign[i];
        printf("%d ", final_msg[i]);
    }
    printf("\n");
    int ctr = 0;
    for (int i = wots_obj->msg_size_count; i < 67; i++) {
        final_msg[i] = checksum_array[ctr++];
        printf("%d ", final_msg[i]);
    }

    printf("\n");
    printf("%d", 67);

    puts("signature:");

    for (int i = 0; i < 67; i++) {
        chain(0, final_msg[i], secret_key[i], wots_obj->seed);
        signature[i] = malloc(sizeof(uint8_t) * KEY_EACH_NUMBER_BYTE_SIZE);
        memcpy(signature[i], secret_key[i], KEY_EACH_NUMBER_BYTE_SIZE);
    }

    return 0;
}

int get_public_key_from_signature(wotsplus_obj* wots_obj, char* message, uint8_t* signature[KEY_SIZE_L], uint8_t* derived_pub_key[KEY_SIZE_L]) {
    uint8_t msg_hash[KEY_EACH_NUMBER_BYTE_SIZE];
    DoSha256(message, msg_hash);

    char msg_base_w[sizeof(msg_hash) * 2 + 1];
    if (get_signature_base_message(msg_base_w, sizeof(msg_base_w), msg_hash, sizeof(msg_hash)))
        printf("---- %s\n", msg_base_w);

    int msg_to_verify[sizeof(msg_base_w) - 1];
    convert_hex_values(msg_base_w, msg_to_verify, sizeof(msg_base_w));

    // get checksum
    int cksm = get_checksum(wots_obj, msg_to_verify);

    int checksum_array[3];
    convert_checksum_hex(cksm, checksum_array, 3);

    int final_msg[67];
    for (int i = 0; i < wots_obj->msg_size_count; i++) {
        final_msg[i] = msg_to_verify[i];
    }
    int ctr = 0;
    for (int i = wots_obj->msg_size_count; i < 67; i++) {
        final_msg[i] = checksum_array[ctr++];
    }

    for (int i = 0; i < 67; i++) {
        chain((int)final_msg[i], wots_obj->wots_param_w, signature[i], wots_obj->seed);
        derived_pub_key[i] = malloc(sizeof(uint8_t) * KEY_EACH_NUMBER_BYTE_SIZE);
        memcpy(derived_pub_key[i], signature[i], KEY_EACH_NUMBER_BYTE_SIZE);
    }
    return 0;
}

int verify_signature(wotsplus_obj* wots_obj, char* message, uint8_t* signature[KEY_SIZE_L], uint8_t* publick_key[KEY_SIZE_L]) {
    uint8_t* derived_pub_key[KEY_SIZE_L];
    get_public_key_from_signature(wots_obj, message, signature, derived_pub_key);

    for (int i = 0; i < 67; i++) {
        for (int j = 0; j < KEY_EACH_NUMBER_BYTE_SIZE; j++) {
            if (derived_pub_key[i][j] != publick_key[i][j]) {
                return 1;
            }
        }
    }

    return 0;
}
