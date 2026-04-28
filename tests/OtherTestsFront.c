#include "front.h" 
#include <assert.h>


void CreateTestFile(const char* name, const char* content) {
    FILE* f = fopen(name, "w");
    fprintf(f, "%s", content);
    fclose(f);
}

void TestGetQuestion(){
    CreateTestFile("testNQ1.txt", "он красный?\nОн жёлтый?\n");
    freopen("testNQ1.txt", "r", stdin);

    char* answer1 = GetQuestion("дыня", "арбуз");
    char* answer2 = GetQuestion("арбуз", "дыня");
 
    assert(strcmp(answer1, "он красный?") == 0);
    assert(strcmp(answer2, "Он жёлтый?") == 0);

    free(answer1);
    free(answer2);

    fclose(stdin);
}

void TestGetNewWord() {
    char* str;

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
    
}


int main() {
    printf("\ntesting GetQuestion");

    #ifdef _WIN32
        freopen("nul", "w", stdout);   // Windows
    #else
        freopen("/dev/null", "w", stdout);  // Linux
    #endif

    TestGetQuestion();
    
    #ifdef _WIN32
    // Windows
        freopen("CON", "w", stdout);
    #else
    // Linux
        freopen("/dev/tty", "w", stdout);
    #endif

    printf("\ntests passed!\n");
    printf("\ntesting GetNewWord");

    TestGetNewWord();
    
    printf("\ntests passed!\n");
    printf("\nall tests passed\n");
    return 0;
}