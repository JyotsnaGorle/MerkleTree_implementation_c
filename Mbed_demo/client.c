/*
 *  Classic "Hello, world" demonstration program
 *
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#define mbedtls_printf       printf
#define mbedtls_exit         exit
#define MBEDTLS_EXIT_SUCCESS EXIT_SUCCESS
#define MBEDTLS_EXIT_FAILURE EXIT_FAILURE

#include "mbedtls/md.h"
#include "m_sha256.h"
#include "leafs.h"
#include "m_hmac.h"
#include "wotsplus.h"
#include "treehash.h"



int main(void)
{

    init_tree_height_leaves(19, 262144);
    
    const int h = tree_height - 1;
    array_of_32_uint8_t stacks_array[TREE_HEIGHT_GLOBAL-1];
    array_of_32_uint8_t auths_array[TREE_HEIGHT_GLOBAL-1];

    Init_stack_auth_nodes(stacks_array, auths_array);

    leafPtr = (struct element*)malloc(sizeof(struct element));
    Initialize(0, tree_height - 1, leafPtr);

    // for root : total nodes in tree - 1
    int n_leaves = (1 << (tree_height - 1));
    int n = n_leaves + leaves_count - 1;
    Update(n - 1, tree_height - 1);

#if defined(_WIN32)
    mbedtls_printf("  Press Enter to exit this program.\n");
    fflush(stdout); getchar();
#endif

   return 0;
}
