#include "front.h"
#include "backend.h"

int main(void) {

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setlocale(LC_ALL, ".UTF8");

    //Flag for replaying the game if the user wants to continue.
    //0 = if ending after the game loop, 1 = if continuing.
    int flag1 = 0;

    //The main game loop begins
    do {
        //We print a greeting and ask you to guess a word or phrase
        Start();

        //Load the tree from the file and get a pointer to its root.
        //If the file doesn't exist, is empty, or is invalid, then
        //by default we create a tree with one question and two objects
        //variables to read the guess/miss statistics from the top line
        //of the file.

        int guess = 0;
        int noguess = 0;

        char filename[100] = "main_tree.txt";
        if (!CheckFile(filename)) {
            //we warn that we will use the default file
            DefaultTree();
            strcpy(filename, "default_tree.txt");
            //if the default one is faulty, then we end the game
            if (!CheckFile(filename)) {
                DefaultTreeError();
                return -1;
            }
        }

        TreeNode* root = LoadTreeFile(filename, &guess, &noguess);

        if (root == NULL) {
            MemoryError();
            return -1;
        }

        //Pointer to the current node
        TreeNode* cur = root;

        //Flag for continuing movement through the tree nodes with questions
        //(until we reach the last question (before the tree leaf) - equal
        //to 1, otherwise equal to 0 - meaning the next node is a tree leaf
        //with an object, not a question.
        int flag2 = 0;
        TreeNode* prev = NULL;
        char answer;
        do {
            //Print the question from the current node
            PrintQuestion(cur);
            //We get an answer; if it is invalid
            //(not equal to yes or no), then we ask you to enter it again)

             answer = GetAnswer();

            // If the answer is "yes", then the next node is on the right,
            // otherwise - on the left.
            TreeNode* next = NULL;
            if (answer == 'y')
                next = cur->right;
            else
                 next = cur->left;

            // The type of this next node shows whether we have reached
            // the end or whether further questions remain.
            flag2 = (int)next->type;

            //If the flag is 0, then we've reached the end. Then we need
            //to save the pointer to the current node,
            // because if there are changes, the new node will be attached to it.
            if (flag2 == 0) {
                prev = cur;
            }
            //move to the next node
            cur = next;
        } while (flag2);

        //If we exited the loop, then we ended up at a node with
        //an object (tree literal)
        //Print the assumption (the object in this node)
        Assumption(cur);

        answer = GetAnswer();
        //If the answer is "yes", then victory, we guessed right,
        //the end of one game cycle

        if (answer == 'y') {
            guess++;
            Victory();
            SaveTreeToFile(root,filename, guess, noguess);
        }

        //If you didn't guess
        else {
            noguess++;
            //We ask what it really was and ask to enter the correct
            //answer (the hidden word)
            Mistake();

            // get and remember the hidden word (correct answer)
            // (pointer to it)
            char* rightAnswer = GetNewWord();

            if (rightAnswer == NULL) {
                MemoryError();
                FreeTree(root);
                return -1;
            }

            // pointer to the wrong answer (our guess)
            if (cur->data == NULL) {
                MemoryError();
                free(rightAnswer);
                FreeTree(root);
                return -1;
            }

            char* wrongAnswer = strdup(cur->data);

            if (wrongAnswer == NULL) {
                MemoryError();
                free(rightAnswer);
                FreeTree(root);
                return -1;
            }

            //We ask "What question distinguishes <wrongAnswer>
            //from <rightAnswer>?" And "How should we answer this question
            //for <rightAnswer>?"
            //We get a pointer to the line containing the question
            char* question = GetQuestion(wrongAnswer,rightAnswer);

            if (question == NULL) {
                MemoryError();
                free(rightAnswer);
                free(wrongAnswer);
                FreeTree(root);
                return -1;
            }


            answer = GetAnswer();
            //Create a new node
            //If the answer is "yes," then the new word goes to the right
            //\branch, and our guess goes to the left,
            //otherwise, vice versa

            TreeNode* newNode = NULL;
            if (answer == 'y') {
                newNode = CreateQuestionNode(question, rightAnswer,wrongAnswer);

                if (newNode == NULL) {
                    MemoryError();
                    free(rightAnswer);
                    free(wrongAnswer);
                    free(question);
                    FreeTree(root);
                    return -1;
                }
            }


            else {
                newNode = CreateQuestionNode(question,wrongAnswer,
                                                     rightAnswer);
                if (newNode == NULL) {
                    MemoryError();
                    free(question);
                    free(rightAnswer);
                    free(wrongAnswer);
                    FreeTree(root);
                    return -1;
                }
            }

            //If the pointer to the current node
            //(we need to replace it with a new node) matches the
            //right branch of the previous node, then we attach
            //the new node to it, otherwise to the left
            if (prev == NULL) {
                MemoryError();
                free(question);
                free(rightAnswer);
                free(wrongAnswer);
                FreeTree(root);
                return -1;
            }

            if (cur == prev->right) {
                FreeTree(cur);
                prev->right = newNode;
            }

            else{
            FreeTree(cur);
            prev->left = newNode;
            }

            //overwrite the tree to the file with the changes
            //and update the statistics in the first line
            SaveTreeToFile(root,filename, guess, noguess);
        }

        //The function frees memory and clears the tree
        FreeTree(root);

        //We ask if the user wants to see statistics
        StaticSee();
        answer = GetAnswer();

        if (answer == 'y')
            ShowStatic(guess, noguess);

        //Ask the user if they want to play again.
        //If so, set the flag to 1 and the game is repeated.
        //Otherwise, reset the flag.
        PlayAgain();
        answer = GetAnswer();
        if (answer == 'y')
            flag1 = 1;

        else {
            flag1 = 0;
            EndGame();
        }

    } while (flag1);

    return 0;
}
