#ifndef BACKEND_H
#define BACKEND_H

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
    char type;
    char* data;             // text
    struct TreeNode* right; // yes
    struct TreeNode* left;  // no
} TreeNode;

TreeNode* LoadTreeFile(const char* fileName, int* g, int* ng);
TreeNode* CreateQuestionNode(char* question, char* rightAnswer, char* wrongAnswer);
void SaveTreeToFile(TreeNode* root, const char* fileName, int g, int ng);
void FreeTree(TreeNode* root);

#endif
