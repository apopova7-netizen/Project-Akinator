#ifndef FRONT_H
#define FRONT_H
#include "common.h"

char GetAnswer();
char* GetNewWord();
char* GetQuestion(char* wrongAnswer, char* rightAnswer);
void Start();
void DefaultTree();
void DefaultTreeError();
void PrintQuestion(TreeNode* cur);
void Assumption(TreeNode* cur);
void Victory();
void Mistake();
void PlayAgain();
void EndGame();
int CheckFile(const char* filename);
void StaticSee();
void ShowStatic(int guess, int noguess);
void CreateTestFile(const char* name, const char* content);
                                              
#endif  
