#pragma once

typedef uint8_t array_of_32_uint8_t[32];

struct element {
    uint8_t hash[32];
    char* data;
    int level;
    int index;
    struct element* next;
};

struct element* leafPtr;

int begin_treehash_index;
int indx;
bool first_update;
int maxheight;

array_of_32_uint8_t stacks[7];
array_of_32_uint8_t auths[6];

void push(struct element* nodetoPushIn, struct element** stack);
void pop(struct element** stack);
void top(struct element* stack);
int Update(int t, int h);
int Initialize(int startnode_index, int h, struct element*);
int Treehash();
int Init_stack_auth_nodes();
