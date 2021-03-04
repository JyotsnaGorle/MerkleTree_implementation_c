#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdlib.h>
#include <stdio.h>
#define mbedtls_printf       printf
#define mbedtls_exit         exit
#define MBEDTLS_EXIT_SUCCESS EXIT_SUCCESS
#define MBEDTLS_EXIT_FAILURE EXIT_FAILURE
#endif

#include "mbedtls/md.h"
#include "mbedtls/sha256.h"

#include "m_sha256.h"

int DoSha256(char* payload, uint8_t* shaHashString) {

    mbedtls_md_context_t ctx;
    mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;

    const size_t payloadLength = strlen(payload);

    mbedtls_md_init(&ctx);
    mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 0);
    mbedtls_md_starts(&ctx);
    mbedtls_md_update(&ctx, (const unsigned char*)payload, payloadLength);
    mbedtls_md_finish(&ctx, shaHashString);
    mbedtls_md_free(&ctx);
    return 1;
}

int DoSha256_bytes(uint8_t payload[32], uint8_t shaHashString[32], int size) {

    mbedtls_md_context_t ctx;
    mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;

    const size_t payloadLength = size;

    mbedtls_md_init(&ctx);
    mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 0);
    mbedtls_md_starts(&ctx);
    mbedtls_md_update(&ctx, payload, payloadLength);
    mbedtls_md_finish(&ctx, shaHashString);
    mbedtls_md_free(&ctx);
    return 1;
}


int DoSha256_parent(uint8_t payload[64], uint8_t shaHashString[32], int size) {

    mbedtls_md_context_t ctx;
    mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;

    const size_t payloadLength = size;

    mbedtls_md_init(&ctx);
    mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 0);
    mbedtls_md_starts(&ctx);
    mbedtls_md_update(&ctx, payload, payloadLength);
    mbedtls_md_finish(&ctx, shaHashString);
    mbedtls_md_free(&ctx);
    return 1;
}

int HashValuePrint(uint8_t* digest)
{

    if (!digest) {
        printf("<empty hash>\n");
        return -1;
    }
    for (int i = 0; i < STD_HASH_SIZE_BYTES; i++)
        printf("%02x", digest[i]);
    printf("\n");

    return 0;
}

int ConcatHashes(uint8_t* left, uint8_t* right, uint8_t parent[64])
{
    if (left != NULL && right != NULL && parent != NULL) {
        for (int i = 0; i < STD_HASH_SIZE_BYTES; i++) {
            parent[i] = left[i];
        }

        for (int i = 0; i < STD_HASH_SIZE_BYTES; i++) {
            parent[STD_HASH_SIZE_BYTES + i] = right[i];
        }
    }

    return 0;
}