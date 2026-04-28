#ifndef BACKEND_H
#define BACKEND_H

#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 256
enum Type { QUESTION = 1, ANSWER = 0}; 

typedef struct TreeNode{
    char type;
    char* data;             // text
    struct TreeNode* right; // yes
    struct TreeNode* left;  // no
} TreeNode;

TreeNode* LoadTreeFile(const char* fileName, int* g, int* ng);
TreeNode* CreateQuestionNode(char* questionText, char* rightAnswer, char* wrongAnswer);
void SaveTreeToFile(TreeNode* root, const char* fileName, int g, int ng);
void FreeTree(TreeNode* root);

#endif
