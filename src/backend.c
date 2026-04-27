#include "backend.h"

char* ReadLine(FILE* fl, char* type, int* level){
    long position = ftell(fl);
    size_t lineLen = 0;
    int sym;
    int cntAst = 0;

    while (((sym = fgetc(fl)) == '*'))
        cntAst++;
    *type = sym - '0';
    *level = cntAst;

    position = ftell(fl);
    while ((sym = fgetc(fl)) != '\n' && sym != EOF)
        lineLen++;
    char* buffer = (char*)malloc(lineLen + 1);
    if (buffer == NULL)
        return NULL;
    fseek(fl, position, SEEK_SET);
    fread(buffer, 1, lineLen, fl);
    buffer[lineLen] = '\0';

    if (sym != EOF)
        fgetc(fl);

    return buffer;
}

//загружает дерево из уже верного файла
TreeNode* LoadTreeFile(const char* fileName, int* g, int* ng){
    FILE* tree = fopen(fileName, "r");
    if (tree == NULL)
        return NULL;
    TreeNode* stack[128]; // fix late
    char* text;
    int level;
    char type;

    if (fscanf(tree, "|%d|%d|", g, ng) != 2){
        fclose(tree);
        return NULL;
    }
    
    while((text = ReadLine(tree, &type, &level)) != NULL){
        if (level > 128)
            return NULL;    // нужно освобождение памяти
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        if (newNode == NULL)
            return NULL;
        newNode->data = text;
        newNode->type = type;
        newNode->right = newNode->left = NULL;
        stack[level] = newNode;

        if (level != 0){
            if (stack[level - 1]->right == NULL)
                stack[level - 1]->right = stack[level];
            else
                stack[level - 1]->left = stack[level];
        }
    }
    fclose(tree);
    return stack[0];
}

TreeNode* CreateAnswerNode(char* answer){
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL)
        return NULL;
    node->type = 0; // Fix it later!
    node->right = NULL;
    node->left = NULL;
    return node;
}

// может вернуть null или ответы как нулл 
TreeNode* CreateQuestionNode(char* question, char* rightAnswer, char* wrongAnswer){
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL)
        return NULL;
    node->type = 1; // Fix it later!
    node->data = question;
    node->right = CreateAnswerNode(rightAnswer);
    node->left = CreateAnswerNode(wrongAnswer);
    return node;
}

void SaveNode(FILE* fl, TreeNode* node, int level){
    if (node == NULL)
        return;
    for (int i = 0; i < level; i++)
        fprintf(fl, "*");
    fprintf(fl, "%c%s\n", node->type, node->data);
    SaveNode(fl, node->right, level + 1);
    SaveNode(fl, node->left, level + 1);
}

void SaveTreeToFile(TreeNode* root, const char* fileName, int g, int ng){
    FILE* fl = fopen(fileName, "w");
    if(fl == NULL)
        return;
    fprintf(fl, "|%d|%d|\n", g, ng);
    SaveNode(fl, root, 0);
    fclose(fl);
}

/*Recursive algorithm
effective for small-depth trees (balanced)
*/
void FreeTree(TreeNode* root){
    if (root == NULL)
        return;
    FreeTree(root->right);
    FreeTree(root->left);
    free(root->data);
    free(root);
}
