#pragma once
#define STD_HASH_SIZE_BYTES 32

int DoSha256(char* payload, uint8_t* shaHashString);
int HashValuePrint(uint8_t* digest);
int ConcatHashes(uint8_t* left, uint8_t* right, uint8_t parent[64]);
int DoSha256_bytes(uint8_t payload[32], uint8_t shaHashString[32], int size);

int DoSha256_parent(uint8_t payload[64], uint8_t shaHashString[32], int size);