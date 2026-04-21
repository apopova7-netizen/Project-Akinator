#include "front.h"

typedef struct {
    const char* file;
    int expected;
    const char* message;
} Test;

int main() {
    Test tests[] = {
        {"test_files/empty.txt", 0, "Empty file"},
        {"test_files/only_root.txt", 0, "Only root (no objects)"},
        {"test_files/no_root.txt", 0, "No root question"},
        {"test_files/root_not_first.txt", 0, "Root is not on the first line"},
        {"test_files/root_with_star.txt", 0, "Root cannot start with *"},
        {"test_files/root_no_text.txt", 0, "No text after '1'"},
        {"test_files/star_no_type.txt", 0, "No '0'/'1' after '*'"},
        {"test_files/star_no_text.txt", 0, "No text after '*1'"},
        {"test_files/star_bad_type.txt", 0, "Invalid character after '*'"},
        {"test_files/bad_first_char.txt", 0, "Wrong first character in line"},
        {"test_files/empty_line.txt", 0, "Empty line in file"},
        {"test_files/no_children.txt", 0, "Question does not have two children"},
        {"test_files/correct_small.txt", 1, "Correct minimal tree"},
        {"test_files/correct_full.txt", 1, "Correct full tree"},
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