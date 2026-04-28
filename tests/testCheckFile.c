#include "front.h"

typedef struct {
    const char* file;
    int expected;
    const char* message;
} Test;

int main() {
    Test tests[] = {
        {"tests/trees/forCheckFile/empty.txt", 0, "Empty file"},
        {"tests/trees/forCheckFile/star_root.txt", 0, "Star before root"},
        {"tests/trees/forCheckFile/only_root.txt", 0, "Only root (no objects)"},
        {"tests/trees/forCheckFile/no_root.txt", 0, "No root question"},
        {"tests/trees/forCheckFile/root_not_first.txt", 0, "Root is not on the first line"},
        {"tests/trees/forCheckFile/root_with_star.txt", 0, "Root cannot start with *"},
        {"tests/trees/forCheckFile/root_no_text.txt", 0, "No text after '1'"},
        {"tests/trees/forCheckFile/star_no_type.txt", 0, "No '0'/'1' after '*"},
        {"tests/trees/forCheckFile/star_no_text.txt", 0, "No text after '*1'"},
        {"tests/trees/forCheckFile/star_bad_type.txt", 0, "Invalid character after '*"},
        {"tests/trees/forCheckFile/bad_first_char.txt", 0, "Wrong first character in line"},
        {"tests/trees/forCheckFile/empty_line.txt", 0, "Empty line in file"},
        {"tests/trees/forCheckFile/no_children.txt", 0, "Question does not have two children"},
        {"tests/trees/forCheckFile/correct_small.txt", 1, "Correct minimal tree"},
        {"tests/trees/forCheckFile/correct_full.txt", 1, "Correct full tree"},
        {"tests/trees/forCheckFile/no_statistics.txt", 0, "No statistics line"},
        {"tests/trees/forCheckFile/wrong_statistics_format1.txt", 0, "Statistics without vertical bars"},
        {"tests/trees/forCheckFile/negative_statistics.txt", 0, "Statistics with negative numbers"},
        {"tests/trees/forCheckFile/extra_numbers.txt", 0, "Statistics with extra numbers"},
        {"tests/trees/forCheckFile/empty_statistics.txt", 0, "Empty statistics line"},
    };
    
    int passed = 0;
    int failed = 0;
    int total = sizeof(tests) / sizeof(tests[0]);
    
    printf("=== CheckFile TESTING ===\n\n");
    
    for (int i = 0; i < total; i++) {
        int result = CheckFile(tests[i].file);
        
        printf("Test %d: %s\n", i + 1, tests[i].message);
        printf("  File: %s\n", tests[i].file);
        printf("  Result: %d (expected: %d)\n", result, tests[i].expected);
        
        if (result == tests[i].expected) {
            printf("PASSED\n\n");
            passed++;
        } else {
            printf("FAILED\n\n");
            failed++;
        }
    }
    
    printf("=== SUMMARY ===\n");
    printf("Passed: %d/%d\n", passed, total);
    printf("Failed: %d\n", failed);
    
    return 0;
}