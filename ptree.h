#ifndef PTREE_H
#define PTREE_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include ".\libr\Hamlet.h"

struct Ptree_akinator
{
    struct Pnode_akinator*  nodes = nullptr;

    size_t tree_size = 0;

    size_t tree_size_user = 0;
};


struct Pnode_akinator
{
    char name[30];

    struct Pnode_akinator* father = nullptr;

    struct Pnode_akinator* right = nullptr;

    struct Pnode_akinator* left  = nullptr;
};


#include ".\libr\Stack.h"

const size_t Left  = 'left';

const size_t Right = 'right';

const size_t Max_l = 29;

//===========================================================


void ptree_akinator_ctor(struct Ptree_akinator* tree);


struct Pnode_akinator* add_start_node(struct Pnode_akinator* first);


void ptree_add_node(struct Pnode_akinator* node, size_t arg, char* answer);


void start_game(struct Pnode_akinator* node, struct Ptree_akinator* tree);


void game_of_akinator(struct Ptree_akinator* tree);


struct Pnode_akinator* seek_ptree(struct Ptree_akinator* tree);


struct Pnode_akinator* check_pnode(struct Pnode_akinator* node, char* search_word);


void comparison(struct Ptree_akinator* tree);


void input_properties(struct Pnode_akinator* node, struct stack_info stack);


void input_data(struct Ptree_akinator* tree);


void write_pnode(struct Pnode_akinator* node, FILE* data_base);


void input_ptree(struct Ptree_akinator* tree, FILE* data_base);


int input_pnode(struct Pnode_akinator* node, char** data);


char* skip_symbols(char* data);


void print_ptree(struct Ptree_akinator* tree);


void ptree_akinator_dtor(struct Ptree_akinator* tree);


void clear_nodes(struct Pnode_akinator* node);


void print_pnode(struct Pnode_akinator* node, FILE* out);


//===========================================================

#endif