#pragma once
// h
// 2^(h-1)

#define TREE_HEIGHT_GLOBAL tree_height;

#define SHA2_DIGEST_LENGTH 64
#define STD_HASH_SIZE_BYTES 32

typedef uint8_t array_of_32_uint8_t[STD_HASH_SIZE_BYTES];


void GenerateLeafs(int count, char* leaves[]);
char* Rand_string(char* str, size_t size);

int tree_height;
int leaves_count;

uint8_t seed_global[STD_HASH_SIZE_BYTES];

void init_tree_height_leaves(int h, int cnt);
int get_leaf(uint8_t* seed, array_of_32_uint8_t hash_pub_key, int magic_number);

