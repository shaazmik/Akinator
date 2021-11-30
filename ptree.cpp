#define $ded printf(">>> %d:\n", __LINE__);


#include "ptree.h"


void ptree_akinator_ctor(struct Ptree_akinator* tree)
{
    assert(tree != nullptr);

    tree->tree_size_user = 1;

    tree->tree_size = 0;

    tree->nodes = (Pnode_akinator*)calloc(1, sizeof(Pnode_akinator));

    tree->nodes = add_start_node(tree->nodes);
}



struct Pnode_akinator* add_start_node(struct Pnode_akinator* first)
{
    assert(first != nullptr);

    first->left   = nullptr;
    first->right  = nullptr;
    first->father = nullptr;

    char str[] ="Your mom!";

    strcpy(first->name, str);     

    return first;
}



void game_of_akinator(struct Ptree_akinator* tree)
{

    printf("Do you want to play akinator?\n\n"
           "Yes or No\n\n" 
           );


    char answer[30] = "";

    struct Pnode_akinator* now_place = tree->nodes;

    gets(answer);

    //можно попробовать scanf("%s ", str) + gets
    //или scanf + getchar + gets;

    printf("\n");

    while (stricmp(answer, "No")  != 0)
    {

        if (stricmp(answer, "Yes") != 0)
        {
            printf("Wrong answer!\n\n");

            scanf("%s", answer);

            printf("\n");
        }
        else
        {
            start_game(tree->nodes, tree);

            printf("Do you want to play again?\n\n"
                   "Yes or No?\n\n");

            gets(answer);
        }

    }

    input_data(tree);

    return;
}



void start_game(struct Pnode_akinator* node, struct Ptree_akinator* tree)
{
    char answer[30] = "";

    char new_answer[30] = "";

    printf("Is it \" %s \"?\n\n"
           "Yes or No\n\n", node->name);
    
    gets(answer);

    printf("\n");
    
    if (stricmp(answer, "Yes") == 0)
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            printf("Gotcha!\n");
            return;
        }
        else
        {
            start_game(node->left, tree);
        }
    }
    else if (stricmp(answer, "No") == 0)
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            printf("What is your character's name?\n\n");
            
            gets(new_answer);

            ptree_add_node(node, Left,  new_answer);
            ptree_add_node(node, Right, node->name);

            tree->tree_size++;
            tree->tree_size_user++;
            
            printf("\nWhat is difference between %s and %s?\n\n", new_answer, node->name);

            gets(node->name);

            return;
        }
        else
        {
            start_game(node->right, tree);
        }
    }
    else
    {
        printf("Wrong answer\n\n");
        start_game(node, tree);
    }
    return;
}



void ptree_add_node(struct Pnode_akinator* node, size_t arg, char* answer)
{
    assert(node != nullptr);

    if (arg == Left)
    {
        node->left = (Pnode_akinator*)calloc(1, sizeof(Pnode_akinator));
        assert(node->left != nullptr);
        node->left->father = node;
        strcpy(node->left->name, answer);
    }

    if (arg == Right)
    {
        node->right = (Pnode_akinator*)calloc(1, sizeof(Pnode_akinator));
        assert(node->right != nullptr);
        node->right->father = node;
        strcpy(node->right->name, answer);
    }
}



struct Pnode_akinator* seek_ptree(struct Ptree_akinator* tree)
{
    printf("Enter a search word:\n");

    char search_word[30] = "";

    gets(search_word);

    printf("\n");
    
    struct Pnode_akinator* tmp = check_pnode(tree->nodes, search_word);

    if (tmp == nullptr)
    {
        printf("Object not found\n\n");
    }
    else
    {
        printf("GOTCHA!\n\n");
    }

    return tmp;
}


struct Pnode_akinator* check_pnode(struct Pnode_akinator* node, char* search_word)
{

    if (strcmp(search_word, node->name) == 0)
    {
        return node;
    }

    struct Pnode_akinator* tmp = {};

    if (node->left != nullptr)
    {
        tmp = check_pnode(node->left, search_word);

        if (tmp != nullptr)
        {
            return tmp;   
        }

        tmp = check_pnode(node->right, search_word);

        if (tmp != nullptr)
        {
            return tmp;
        }
    }

    if (node->right != nullptr)
    {
        tmp = check_pnode(node->left, search_word);

        if (tmp != nullptr)
        {
            return tmp;   
        }

        tmp = check_pnode(node->right, search_word);

        if (tmp != nullptr)
        {
            return tmp;
        }
    }

    return nullptr;
}


void comparison(struct Ptree_akinator* tree)
{
    assert(tree != nullptr);
    
    printf("Input first object for comparison:\n");

    char object_one[30] = "";

    gets(object_one);

    printf("\nInput second object for comparison:\n");

    char object_two[30] = "";

    gets(object_two);

    printf("\n");

    struct Pnode_akinator* object_one_node = check_pnode(tree->nodes, object_one);

    struct Pnode_akinator* object_two_node = check_pnode(tree->nodes, object_two);


    if (object_one_node != nullptr && object_two_node != nullptr)
    {
        struct stack_info object_one_stack = {};

        struct stack_info object_two_stack = {};

        stack_construct(&object_one_stack, Max_l);

        stack_construct(&object_two_stack, Max_l);  

        input_properties(object_one_node->father, &(object_one_stack));

        input_properties(object_two_node->father, &(object_two_stack));       
    }
    else
    {
        printf("Objects not found!\n");
        return;
    }
}


void input_properties(struct Pnode_akinator* node, struct stack_info* stack)
{
    assert(node  != nullptr);
    assert(stack != nullptr);

    while (node->father != nullptr)
    {
        stack_pushka(stack, node);
    }

    return;
}



void input_data(struct Ptree_akinator* tree)
{
    assert(tree != nullptr);

    struct Pnode_akinator* tmp = tree->nodes;

    FILE* data_base = fopen("data_base.txt", "wb");

    assert(data_base != nullptr);

    write_pnode(tree->nodes, data_base);

    fclose(data_base);
}


void write_pnode(struct Pnode_akinator* node, FILE* data_base)    
{
    fprintf(data_base, "{\n"
                        "%s!\n", node->name);
    
    if (node->left != nullptr)
    {
        write_pnode(node->left, data_base);
    }
    if (node->right != nullptr)
    {
        write_pnode(node->right, data_base);
    }

    fprintf(data_base, "}\n");
}



void input_ptree(struct Ptree_akinator* tree)
{
    assert(tree != nullptr);

    strcpy(tree->nodes->name, "");

    FILE* data_base = fopen("data_base.txt", "rb");

    assert(data_base != nullptr);

    struct Text text = {};

    input_struct(data_base, &text);

    input_pnode(tree->nodes, &(text.text_array));

    //free_memory(&text);

    fclose(data_base);

    return;
}


int input_pnode(struct Pnode_akinator* node, char** data)
{
    assert(data != nullptr);
    assert(node != nullptr);
    
    int res = 1337;
    
    *data = skip_symbols(*data);

    if (**data != '{' && **data != '}') 
    {
        printf("Wrong file syntax.\n");
        return res;
    }

    (*data)++;

    *data = skip_symbols(*data);

    int i = 0;

    while (**data != '!' && i < Max_l)
    {
        node->name[i] = **data;
        i++;
        (*data)++;
    }

    node->name[i] = '\0';

    (*data)++;

    *data = skip_symbols(*data);

    if (**data == '{') 
    {

        node->left =  (Pnode_akinator*)calloc(1, sizeof (Pnode_akinator));

        node->left->father = node;

        res = input_pnode(node->left, data);

        node->right = (Pnode_akinator*)calloc(1, sizeof(Pnode_akinator));

        node->right->father = node;

        res = input_pnode(node->right, data);
    }

    if (**data == '}') 
    {
        (*data)++;
        
        *data = skip_symbols(*data);

        return 0;
    }

    printf("FiLe SyNtAx ErRoR!!!\n");

    return res;
}


char* skip_symbols(char* data)
{
    while (isspace(*data) || *data == '\0' || *data == '\r' || *data == '\n')
        data++;
    
    return data;
}

void print_ptree(struct Ptree_akinator* tree)
{
    assert(tree != nullptr);

    FILE* out = fopen("graph.txt", "wb");

    fputs("digraph structs {\n", out);
    fputs("node [style = diagonals, color = \" cyan4\"];\n", out);

    print_pnode(tree->nodes, out);
    
    fputs ("}", out);

    fclose (out);

    system ("dot -Tpng graph.txt -o graph.png");

    system ("graph.png");
}


void print_pnode(struct Pnode_akinator* node, FILE* out)
{
    assert(node != nullptr);
    assert(out  != nullptr);

    if (node->left != nullptr)
    {
        fprintf(out, "\"%s\" -> \"%s\" [label = \"Yes\"];\n", node->name, node->left->name);
        print_pnode(node->left, out);
        
    }

    if (node->right != nullptr)
    {
        fprintf(out, "\"%s\" -> \"%s\" [label =\"No\"];\n", node->name, node->right->name);
        print_pnode(node->right, out);
    }

    if (node->left == nullptr && node->right == nullptr)
    {
        fprintf(out, "\"%s\";\n", node->name);
        return;
    }
    
    return;
}


void ptree_akinator_dtor(struct Ptree_akinator* tree)
{
    assert(tree != nullptr);

    clear_nodes(tree->nodes);

    tree->tree_size = 0;
    tree->tree_size_user = 0;
}


void clear_nodes(struct Pnode_akinator* node)
{
    if (node->left != nullptr && node->right != nullptr)
    {
        clear_nodes(node->left);
        clear_nodes(node->right);
    }

    free(node);

    return;
}


int main()
{
    struct Ptree_akinator akinator_tree = {};

    ptree_akinator_ctor(&akinator_tree);

    input_ptree(&akinator_tree);
    
    //seek_ptree(&akinator_tree);

    game_of_akinator(&akinator_tree);

    print_ptree(&akinator_tree);

    ptree_akinator_dtor(&akinator_tree);

    return 0;
}