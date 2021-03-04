#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include <stdbool.h>
#include <time.h>
#include "treehash.h"
#include "m_sha256.h"
#include "leafs.h"



void push(struct element* nodetoPushIn, struct element** stack) {
    nodetoPushIn->next = *stack;
    (*stack) = nodetoPushIn;
    // HashValuePrint((*stack)->hash);
    // printf("Element pushed: %d%d\n",(*stack) -> level, (*stack) -> index);   
}

void pop(struct element** stack) {

    if (*stack != NULL) {
        // printf("Element popped: %d%d\n",(*stack) -> level, (*stack) -> index);
        // HashValuePrint((*stack)->hash);

        if ((*stack)->index == 0 && first_update) {
            memcpy(stacks[(*stack)->level], (*stack)->hash, STD_HASH_SIZE_BYTES);
        }
        else if ((*stack)->index == 1 && first_update) {
            memcpy(auths[(*stack)->level], (*stack)->hash, STD_HASH_SIZE_BYTES);
        }

        struct element* tempPtr = *stack;
        *stack = (*stack)->next;
        free(tempPtr);
        
    }
    else {
        printf("The stack is empty.\n");
    }
}


void top(struct element* stack) {
    if (stack != NULL) {
        printf("Element on top: %d%d\n", stack->level, stack->index);
        // HashValuePrint(stack->hash);
    }
    else {
        printf("The stack is empty.\n");
    }
}

int Initialize(int startnode_index, int h, struct element* leafPtr) {

    begin_treehash_index = startnode_index + 1;
    maxheight = h;

    uint8_t shaValue[STD_HASH_SIZE_BYTES];
    get_leaf(seed_global, shaValue, startnode_index);
    if (leafPtr == NULL) {
        printf("ERROR: pointer not initialized");
        return 0;
    }
    for (int i = 0; i < STD_HASH_SIZE_BYTES; i++)
        leafPtr->hash[i] = shaValue[i];

    // HashValuePrint(leafPtr->hash);

    leafPtr->next = NULL;
    leafPtr->index = startnode_index;
    leafPtr->level = 0;

    return 1;
}

int Update(int t, int h) {
    int runCtr = 0;
    maxheight = h;

    time_t start, end;
    double elapsed = 0.0;

    time(&start);

    while (runCtr < t) {
        time(&end);

        elapsed = difftime(end, start);
        if (Treehash() == 0) {
            return 0;
        }
        runCtr++;
    }
    printf("Time elapsed: %lf\n", elapsed);
    // stacks[h] = leafPtr; 
    memcpy(stacks[h], leafPtr->hash, STD_HASH_SIZE_BYTES);
    return 0;
}

int Treehash() {

    if (leafPtr == NULL) {
        printf("ERROR: leafptr is null");
        return 0;
    }

    if (leafPtr->level == maxheight) {
        printf("INFO: max height was reached");
        return 0;
    }
    // if same height
    if (leafPtr->next != NULL && (leafPtr->level == leafPtr->next->level)) {
        printf("is same height\n");

        struct element* parent = (struct element*)malloc(sizeof(struct element));
        if (parent == NULL) {
            printf("Error: could not allocate memory to parent");
            return 0;
        }

        parent->level = leafPtr->level + 1;
        parent->next = NULL;
       
        // pop right
        uint8_t right[STD_HASH_SIZE_BYTES];
        memcpy(right, leafPtr->hash, STD_HASH_SIZE_BYTES);
        pop(&leafPtr);

        if (right == NULL) {
            free(parent);
            printf("ERROR: no sibling, tree was not balanced");
            return 0;
        }
        // pop left
        uint8_t left[STD_HASH_SIZE_BYTES];
        memcpy(left, leafPtr->hash, STD_HASH_SIZE_BYTES);
        pop(&leafPtr);

        if (left == NULL) {
            free(parent);
            printf("ERROR: no sibling, tree was not balanced");
            return 0;
        }

        uint8_t buffer[2 * STD_HASH_SIZE_BYTES];
        if (ConcatHashes(left, right, buffer) == 0) {
            free(parent);
            free(buffer);
            printf("ERROR: concat unsuccessful");
            return 0;
        }

        uint8_t shaValueParent[STD_HASH_SIZE_BYTES];
        DoSha256_parent(buffer, shaValueParent, 2*STD_HASH_SIZE_BYTES);
        HashValuePrint(shaValueParent);

        //DoSha256(buffer, shaValueParent);

        
        for (int i = 0; i < STD_HASH_SIZE_BYTES; i++)
            parent->hash[i] = shaValueParent[i];

        
        // push parent
        if (leafPtr == NULL) {
            parent->index = 0;
            leafPtr = parent;
            top(leafPtr);
        }
        else {
            int h = tree_height - 1 - parent->level;
            if (indx >= (1 << h)) {
                indx = 1;
            }
            parent->index = indx;
            push(parent, &leafPtr);
            indx++;
        }

    }
    else {

        // if not same height
        printf("\nin leaves treehash %d\n", begin_treehash_index);

        if (begin_treehash_index >= leaves_count) {
            printf("overflow leaves count %d", begin_treehash_index);
            return 0;
        }
        struct element *newLeaf = (struct element *)malloc(sizeof(struct element));
        if (newLeaf == NULL){
            printf("ERROR: could not allocate memory");
            return 0;
        }
        newLeaf->level = 0;
        newLeaf->index = begin_treehash_index;

        uint8_t shaValue[STD_HASH_SIZE_BYTES];
        get_leaf(seed_global, shaValue, begin_treehash_index);

        for (int i = 0; i < STD_HASH_SIZE_BYTES; i++)
            newLeaf->hash[i] = shaValue[i];

        newLeaf->next = NULL;

        // push hash of newLeaf
        // increment newLeaf
        push(newLeaf, &leafPtr);
        begin_treehash_index++;
    }

    return 1;
}

int Init_stack_auth_nodes() {
    first_update = true;
    indx = 1;
    return 0;
}
