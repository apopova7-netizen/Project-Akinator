#include "backend.h"
#include <assert.h>

void testsReadLine(){
    FILE* file = fopen("testTree.txt", "r");
    int g, ng;
    int level;
    char type;
    char* line = ReadLine(file, &type, &level);

    if (line == NULL) return;

    line = ReadLine(file, &type, &level);
    assert(strcmp("Нужен мяч?", line) == 0);
    assert(level == 0);
    assert(type == 1);

    line = ReadLine(file, &type, &level);
    assert(strcmp("Играют руками?", line) == 0);
    assert(level = 1);
    assert(type == 1);

    line = ReadLine(file, &type, &level);
    assert(strcmp("баскетбол", line) == 0);
    assert(level = 2);
    assert(type == 0);
    
    line = ReadLine(file, &type, &level);
    assert(strcmp("футбол", line) == 0);
    assert(level = 2);
    assert(type == 0);

    line = ReadLine(file, &type, &level);
    assert(strcmp("Нужна вода?", line) == 0);
    assert(level = 1);
    assert(type == 1);

    free(line);
    fclose(file);
}

void testsLoadTreeFile(){
    int g, ng;
    TreeNode* root = LoadTreeFile("testTree.txt", &g, &ng);
    
    assert(root != NULL);
    
    // Check statistics
    assert(g == 0);
    assert(ng == 0);
    
    // Check root
    assert(root->type == 1);
    assert(strcmp(root->data, "Нужен мяч?") == 0);
    
    // Right subtree: "yes" — Играют руками?
    TreeNode* right = root->right;
    assert(right != NULL);
    assert(right->type == 1);
    assert(strcmp(right->data, "Играют руками?") == 0);
    
    // Right-right: Баскетбол
    assert(right->right != NULL);
    assert(right->right->type == 0);
    assert(strcmp(right->right->data, "баскетбол") == 0);
    
    // Right-left: Футбол
    assert(right->left != NULL);
    assert(right->left->type == 0);
    assert(strcmp(right->left->data, "футбол") == 0);
    
    // Left subtree: "no" — Нужна вода?
    TreeNode* left = root->left;
    assert(left != NULL);
    assert(left->type == 1);
    assert(strcmp(left->data, "Нужна вода?") == 0);
    
    // Left-right: Плавание
    assert(left->right != NULL);
    assert(left->right->type == 0);
    assert(strcmp(left->right->data, "Плавание") == 0);
    
    // Left-left: Бег
    assert(left->left != NULL);
    assert(left->left->type == 0);
    assert(strcmp(left->left->data, "Бег") == 0);
    
    // Check that these are leaves
    assert(right->right->right == NULL);
    assert(right->right->left == NULL);
    assert(right->left->right == NULL);
    assert(right->left->left == NULL);
    assert(left->right->right == NULL);
    assert(left->right->left == NULL);
    assert(left->left->right == NULL);
    assert(left->left->left == NULL);
    
}

void testsSaveTreeToFile(){
    int g = 0, ng = 0;
    TreeNode* t = LoadTreeFile("testTree.txt", &g, &ng);

    SaveTreeToFile(t,"testingtree.txt", g, ng);

    FILE* f = fopen("testingtree.txt", "r");
    
    char buffer[256];
    
    // Line 1: statistics
    fgets(buffer, sizeof(buffer), f);
    assert(strcmp(buffer, "|0|0|\n") == 0);
    
    // Line 2: root
    fgets(buffer, sizeof(buffer), f);
    assert(strcmp(buffer, "1Нужен мяч?\n") == 0);
    
    // Line 3: right subtree
    fgets(buffer, sizeof(buffer), f);
    assert(strcmp(buffer, "*1Играют руками?\n") == 0);
    
    // Line 4: right-right
    fgets(buffer, sizeof(buffer), f);
    assert(strcmp(buffer, "**0баскетбол\n") == 0);
    
    // Line 5: right-left
    fgets(buffer, sizeof(buffer), f);
    assert(strcmp(buffer, "**0футбол\n") == 0);
    
    // Line 6: left subtree
    fgets(buffer, sizeof(buffer), f);
    assert(strcmp(buffer, "*1Нужна вода?\n") == 0);
    
    // Line 7: left-right
    fgets(buffer, sizeof(buffer), f);
    assert(strcmp(buffer, "**0Плавание\n") == 0);
    
    // Line 8: left-left
    fgets(buffer, sizeof(buffer), f);
    assert(strcmp(buffer, "**0Бег\n") == 0);
    
    // Check that the file has ended
    assert(fgets(buffer, sizeof(buffer), f) == NULL);
    
    fclose(f);
    remove("testingtree.txt");
    
}

int main(){

    printf("\ntesting ReadLine");
    testsReadLine();
    printf("\ntests ReadLine passed!\n");

    printf("\ntesting testsLoadTreeFile");
    testsLoadTreeFile();
    printf("\ntests LoadTreeFile passed!\n");
    
    printf("\ntesting SaveTreeToFile\n");
    testsLoadTreeFile();
    printf("tests SaveTreeToFile passed!\n");

    printf("\nall tests backend passed\n");

    return 0;
}