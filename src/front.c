#include "front.h" 

char GetAnswer() {
    char a[10];
    while (1) {
        if (scanf("%9s", a) != 1)  
            return 'e';
        printf("Введите да или нет.\n");
        scanf("%9s", a);
        if (strcmp(a, "да") == 0 || strcmp(a, "Да") == 0 
            || strcmp(a, "ДА") == 0)
            return 'y'; 
        else if (strcmp(a, "нет") == 0 || strcmp(a, "Нет") == 0 
                || strcmp(a, "НЕТ") == 0)
            return 'n';
        else 
            printf("Это недопустимый ответ. Введите да или нет.\n");
    } 
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

char* GetQuestion(char* wrongAnswer, char* rightAnswer) {
    printf("Какой вопрос отличает %s от %s?\n", wrongAnswer, rightAnswer);  
    char* question = malloc(1000);
    if (question == NULL) return NULL;
    
    if (fgets(question, 1000, stdin) == NULL) {
        free(question);
        return NULL;
    }
    
    question[strcspn(question, "\n")] = '\0';
    printf("Как отвечать на этот вопрос для %s?\n", rightAnswer);
    
    return question;
}

void Start() {
    printf("Загадайте слово или словосочетание на тему 'Еда и напитки'.\n");
}

void PrintQuestion(TreeNode* cur) {
    if (cur == NULL)
        return;
    printf("%s\n", cur -> data);
    printf("Введите да или нет.\n");
}

void Assumption(TreeNode* cur) {
    if (cur == NULL)
        return;
    printf("Это %s?\n", cur -> data);
} 

void Victory() {
    printf("Ура, я угадал!\n");
}

void Mistake() {
    printf("Что это было на самом деле? Введите верный ответ.\n");
}

void PlayAgain() {
    printf("Хотите сыграть еще?\n");
}

void EndGame() {
    printf("Спасибо за игру.\n");
}

void StaticSee(){
    printf("Хотите посмотреть статистику?\n");
}

void ShowStatic(int guess, int noguess) {
    printf("Угадано: %d\n", guess);
    printf("Не угадано: %d\n", noguess);
}


int CheckFile(const char* filename) {
    if (filename == NULL) return 0;

    FILE* file = fopen(filename, "r");
    if (file == NULL) return 0;

    char line[256];
    int lineNumber = 0;
    int hasRoot = 0;
    int levels[100] = {0};
    int questions[100] = {0};
    int maxLevel = 0;
    int guess, noguess = 0;

    while (fgets(line, sizeof(line), file)) {
        lineNumber++;
        line[strcspn(line, "\n")] = '\0'; 

        if (lineNumber == 1) {
            int n1, n2;
            char extra;
    
            if (sscanf(line, "|%d|%d|%c", &guess, &noguess, &extra) != 2) {
                printf("Ошибка в строке 1: неверный формат статистики. Ожидается |У|Н|\n");
                fclose(file);
                return 0;
            }
            if (guess < 0 || noguess < 0) {
                printf("Ошибка в строке 1: статистика не может быть отрицательной\n");
                fclose(file);
                return 0;
            }
            continue;
        }

        if (strlen(line) == 0) {
            printf("ОШИБКА: пустая строка в строке %d\n", lineNumber);
            fclose(file);
            return 0;
        }
        
        char firstChar = line[0];
        
        if (lineNumber == 2) {
            if (firstChar != '1') {
                printf("Ошибка в строке %d: корень дерева должен начинаться с '1'\n", lineNumber);
                fclose(file);
                return 0;
            }
        }        
         
        else if (lineNumber > 2) {
            if (firstChar != '*') {
                printf("Ошибка в строке %d: строка должна начинаться с '*'\n", lineNumber);
                fclose(file);
                return 0;
            }
        }

        // For the root level
        if (firstChar == '1') {
            if (lineNumber != 2) {
                printf("Ошибка в строке %d: уровень '1' может быть только на второй строке\n", 
                        lineNumber);
                fclose(file);
                return 0;
            }
            hasRoot = 1; 

            if (strlen(line) < 2) {
                printf("Ошибка в строке %d: нет текста после '1'\n", lineNumber);
                fclose(file);
                return 0;
            }

            levels[0]++;
            questions[0]++; 
        }

        // For the co '*' level
        if (firstChar == '*') {
            int cntStars = 0;
            while (line[cntStars] == '*') {
                cntStars++;
            }

            if (line[cntStars] != '1' && line[cntStars] != '0') {
                printf("Ошибка в строке %d: нет '0' или '1' после '*'\n", lineNumber);
                fclose(file);
                return 0;
            }

            if (strlen(line) <= cntStars + 1) {
                printf("Ошибка в строке %d: должен быть текст после '%c'\n", 
                        lineNumber, line[cntStars]);
                fclose(file);
                return 0;
            }
            
            // Counting nodes and questions
            levels[cntStars]++;
            if (line[cntStars] == '1') {
                questions[cntStars]++;
            }

            if (cntStars > maxLevel) {
                maxLevel = cntStars;
            }
        }
    }

    fclose(file);

    if (!hasRoot) {
        printf("Ошибка: файл пуст или поврежден\n");
        return 0;
    }

    int totalNodes = 0;
    for (int i = 0; i <= maxLevel; i++) {
        totalNodes += levels[i];
    }

    // Checking the minimum size of the tree
    if (totalNodes < 3) {
        printf("Ошибка: минимальный размер дерева - 3 узла (1 вопрос + 2 ответа)\n");
        return 0;
    }

    // Checking that each question has 2 descendants
    for (int i = 0; i < maxLevel; i++) {
        int children = questions[i] * 2;
        if (levels[i+1] != children) {
            printf("Ошибка: на уровне %d есть %d вопросов, поэтому на уровне %d должно быть %d узлов, но обнаружено %d узлов\n",
                   i, questions[i], i+1, children, levels[i+1]);
            return 0;
        }   
    }   
    return 1;
}