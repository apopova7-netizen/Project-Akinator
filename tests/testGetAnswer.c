#include "front.h" 

int main() {
    // test : yes/no
    CreateTestFile("t1.txt", "да\nнет\n");
    freopen("t1.txt", "r", stdin);

    assert(GetAnswer() == 'y');
    assert(GetAnswer() == 'n');
    
    printf("\nTest 1 passed\n");
    fclose(stdin);

    // Test : Incorrect → correct
    CreateTestFile("t2.txt", "неверно\nда\n");
    freopen("t2.txt", "r", stdin);

    assert(GetAnswer() == 'y');

    printf("\nTest 2 passed\n");

    remove("t1.txt");
    fclose(stdin);

    printf("\nAll tests passed!\n");
    remove("t2.txt");
    return 0;
}