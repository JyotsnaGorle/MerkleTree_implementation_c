#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "leafs.h"
#include "m_sha256.h"
#include "wotsplus.h"

typedef uint8_t array_of_32_uint8_t[STD_HASH_SIZE_BYTES];

int get_leaf(uint8_t* seed, array_of_32_uint8_t hash_pub_key, int magic_number) {

    wotsplus_obj *wots_obj = (wotsplus_obj*)malloc(sizeof(wotsplus_obj));
    init_wots(wots_obj, 16, 256, seed_global);
    // gen priv key
    array_of_32_uint8_t secret_key[KEY_SIZE_L];
    
    gen_secret_key(secret_key, magic_number);

    // gen pub key
    array_of_32_uint8_t pk[KEY_SIZE_L];
   
    gen_public_key(secret_key, pk, seed_global);

    uint8_t pub_key[STD_HASH_SIZE_BYTES * KEY_SIZE_L];

    int k = 0;
    for (int i = 0; i < KEY_SIZE_L; i++) {
        for (int j = 0; j < STD_HASH_SIZE_BYTES; j++) {
            pub_key[k] = pk[i][j];
            k++;
        }
    }

    int pub_key_size = KEY_SIZE_L * STD_HASH_SIZE_BYTES;

    // hash pub key
    DoSha256_bytes(pub_key, hash_pub_key, pub_key_size);

    return 0;
}

void GenerateLeafs(int count, char* leaves[]) {

    for (int i = 0; i < count; i++) {
        leaves[i] = (char*)malloc(sizeof(char) * 5 + 1);
        Rand_string(leaves[i], sizeof(leaves[i]));
    }
}

char* Rand_string(char* str, size_t size) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyz";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int)(sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}

void init_tree_height_leaves(int h, int cnt) {
    for (int i = 0; i < STD_HASH_SIZE_BYTES; i++) seed_global[i] = (uint8_t)i;
    tree_height = h;
    leaves_count = cnt;
}
