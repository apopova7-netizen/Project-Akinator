#ifndef AKINATOR_COMMON_H
#define AKINATOR_COMMON_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

#define STACK_SIZE 256
#define QUESTION 1
#define ANSWER 0

typedef struct TreeNode {
    char type;
    char* data;
    struct TreeNode* right;
    struct TreeNode* left;
} TreeNode;

#endif //AKINATOR_COMMON_H
