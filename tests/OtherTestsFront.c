
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <assert.h>

void CreateTestFile(const char* name, const char* content) {
    FILE* f = fopen(name, "w");
    fprintf(f, "%s", content);
    fclose(f);
}

char* GetQuestion(char* wrongAnswer, char* rightAnswer) {
    printf("Какой вопрос отличает %s от %s?\n", wrongAnswer, rightAnswer);  
    char* question  = malloc(200 * sizeof(char));
    if (question  == NULL) return NULL;
    scanf("%199s", question );
    printf("Как отвечать на этот вопрос для %s?\n", rightAnswer);

    return question;
}

char* GetNewWord() {
    char* a = malloc(100 * sizeof(char));
    if (a == NULL) return NULL;

     if (scanf("%99s", a) != 1) { 
        free(a);
        return NULL;
    }
 
    return a;
}


void TestGetQuestion(){
    char* str = GetQuestion("арбуз", "дыня");

    printf("%s", str);
}



void TestGetNewWord() {
    char* str;

    printf("testing GetNewWord\n");
    // Test 1:
    CreateTestFile("testNW1.txt", "дыня\nарбуз\n");
    freopen("testNW1.txt", "r", stdin);

    str = GetNewWord();
    assert(str != NULL);
    assert(strcmp(str, "дыня") == 0);
    free(str);

    str = GetNewWord();
    assert(str != NULL);
    assert(strcmp(str, "арбуз") == 0);
    free(str);

    fclose(stdin);
    
    // Test 2:
    CreateTestFile("testNW2.txt", "");
    freopen("testNW2.txt", "r", stdin);

    str = GetNewWord();
    assert(str == NULL);  

    fclose(stdin);
    
    printf("tests passed!\n");
}


int main() {
    //TestGetQuestion();
    TestGetNewWord();

    printf("all tests passed!");
    return 0;
}