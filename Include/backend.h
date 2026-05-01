#ifndef BACKEND_H
#define BACKEND_H

#include "common.h"

char* ReadLine(FILE* fl, char* type, int* level);
TreeNode* LoadTreeFile(const char* fileName, int* g, int* ng);
TreeNode* CreateAnswerNode(char* answer);
TreeNode* CreateQuestionNode(char* questionText, char* rightAnswer, char* wrongAnswer);
void SaveNode(FILE* fl, TreeNode* node, int level);
void SaveTreeToFile(TreeNode* root, const char* fileName, int g, int ng);
void FreeTree(TreeNode* root);

#endif
