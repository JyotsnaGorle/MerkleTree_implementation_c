#pragma once
typedef uint8_t array_of_32_uint8_t[32];

int DoHMAC(array_of_32_uint8_t payload, array_of_32_uint8_t key, array_of_32_uint8_t hmacResult);
