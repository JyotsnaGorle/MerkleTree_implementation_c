// h
// 2^(h-1)

#define TREE_HEIGHT_GLOBAL 16

#define SHA2_DIGEST_LENGTH 64
#define STD_HASH_SIZE_BYTES 32

void GenerateLeafs(int count, char* leaves[]);
char* Rand_string(char* str, size_t size);

int tree_height;
int leaves_count;

uint8_t seed_global[STD_HASH_SIZE_BYTES];

void init_tree_height_leaves(int h, int cnt);
int get_leaf(uint8_t* seed, uint8_t hash_pub_key[32], int magic_number);
#pragma once
