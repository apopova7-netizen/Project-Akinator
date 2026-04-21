#ifndef FRONT_H
#define FRONT_H

#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>

typedef struct TreeNode{
    char type;
    char* data;             
    struct TreeNode* right; 
    struct TreeNode* left;  
} TreeNode;


char GetAnswer();
char* GetNewWord();
char* GetQuestion(char* wrongAnswer, char* rightAnswer);
void Start();
void PrintQuestion(TreeNode* cur);
void Assumption(TreeNode* cur);
void Victory();
void Mistake();
void PlayAgain();
void EndGame();
int CheckFile(const char* filename);
void StaticSee();
void ShowStatic(int guess, int noguess);
                                              
#endif  