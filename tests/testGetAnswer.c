#include "front.h" 
#include <assert.h>

  
void CreateTestFile(const char* name, const char* content) {
    FILE* f = fopen(name, "w");
    fprintf(f, "%s", content);
    fclose(f);
}

int main() {
    // test 1: yes/no
    CreateTestFile("t1.txt", "да\nнет\n");
    freopen("t1.txt", "r", stdin);
    assert(GetAnswer() == 'y');
    assert(GetAnswer() == 'n');
    printf("Test 1 passed\n");
    
    // Test 2: End of file
    CreateTestFile("t2.txt", "");
    freopen("t2.txt", "r", stdin);
    assert(GetAnswer() == 'e');
    printf("Test 2 passed\n");
    
    // Test 3: Incorrect → correct
    CreateTestFile("t3.txt", "неверно\nда\n");
    freopen("t3.txt", "r", stdin);
    assert(GetAnswer() == 'y');
    printf("Test 3 passed\n");


    printf("\nAll tests passed!\n");
    return 0;
}