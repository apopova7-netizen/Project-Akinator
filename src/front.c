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
    scanf("%99s", a); 
    return a;
}

char* GetQuestion(char* wrongAnswer, char* rightAnswer) {
    printf("Какой вопрос отличает %s от %s?\n", wrongAnswer, rightAnswer);  
    char* question  = malloc(200 * sizeof(char));
    if (question  == NULL) return NULL;
    scanf("%199s", question );
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

    while (fgets(line, sizeof(line), file)) {
        lineNumber++;
        line[strcspn(line, "\n")] = '\0'; 
        if (strlen(line) == 0) 
            return 0;

        char firstChar = line[0];
        if (firstChar != '*' &&  firstChar != '1') {
            printf("Error in line %d: must start with '*' or '1'\n", lineNumber);
            fclose(file);
            return 0;
        }

        //For the root level 
        if (firstChar == '1') {
            if (lineNumber != 1) {
                printf("Error in line %d: level '1' can only be in the first line\n", 
                        lineNumber);
                fclose(file);
                return 0;
            }
            hasRoot = 1; 

            if (strlen(line) < 2) {
                printf("Error in line %d: there is no text after 1\n", lineNumber);
                fclose(file);
                return 0;
            }

            levels[0]++;
            questions[0]++; 
        }

        //For level c '*'
        if (firstChar == '*') {
            int cntStars = 0;
            while (line[cntStars] == '*') {
                cntStars++;
            }

            if (line[cntStars] != '1' && line[cntStars]!= '0') {
                printf("Error in line %d: there is no '0' or '1' after *.\n", lineNumber);
                fclose(file);
                return 0;
            }

            if (strlen(line) <= cntStars + 1){
                printf("Error in line %d: there should be text after '%c'\n", 
                        lineNumber, line[cntStars]);
                fclose(file);
                return 0;
            }
            
            //Counting nodes and questions
            levels[cntStars]++;
            if (line[cntStars] == '1'){
                questions[cntStars]++;
            }

            if (cntStars > maxLevel) {
                maxLevel = cntStars;
            }
        
        }
    }

    fclose(file);

    if (!hasRoot) {
        printf("Error: The file is empty or faulty.\n");
        return 0;
    }

    int totalNodes = 0;
    for (int i = 0; i <= maxLevel; i++) {
        totalNodes += levels[i];
    }

    if (totalNodes < 3) {
        printf("Error: the minimum size of the tree is 3 nodes (1 question + 2 objects)\n");
        return 0;
    }

    // Checking that each parent has 2 children
    for (int i = 0; i < maxLevel; i++) {
        int children = questions[i] * 2;
        if (levels[i+1] != children) {
            printf("Error: at the level of %d%d questions, there should be %d descendants, but at the level of %d - %d nodes\n",
                   i, questions[i], children, i+1, levels[i+1]);
            return 0;
        }   
    }
    
    return 1;
}
  