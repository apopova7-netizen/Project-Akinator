# Akinator Project Testing Report

## 1. General information

As part of the project, a comprehensive testing of the Akinator console application, implemented in the C language, was carried out.

The purpose of testing is to verify:

* correct guessing of objects;
* the correctness of the tree traversal algorithm;
* correctness of further education;
* saving and loading the tree;
* User input operation;
* maintaining statistics.

---

##2. Unit testing

The following unit tests were implemented and successfully passed:

### testGetAnswer

Checks:

* correct recognition of yes/no answers;
* processing of various registers ('Да', `да`, `нет`, etc.);
* repeating the request in case of incorrect input.

Result:
All scenarios have been worked out correctly.
---

### testCheckFile

Checks:

* correctness of the tree file format;
* the presence of a root node;
* matching the tree structure (each question has 2 descendants);
* correctness of statistics.

Result:
Incorrect files are detected, and the correct ones are checked.

---

### testBack

Checks:

* creating tree nodes;
* adding a new question and object;
* the correctness of the tree reconstruction.

Result:
The tree is changing correctly.

---

### OtherTestsFront

Checks:

* the correctness of the message output;
* operation of user interaction functions;
* String processing.

The result:
The interface is stable.

---

##3. Manual testing

### 3.1 Goal

Check the full user script:

* Guessing;
* error;
* additional training;
* Re-play;
* checking the save;
* Checking statistics.

---

## 3.2 Initial conditions

A tree file with initial data is used.:

```
|26|25|
```

* Guessed: 26
* Not guessed: 25

---

## 3.3 Test Scenario

---

### ▶️ Scenario 1 — correct guessing

The user makes a wish: **компот**

Sequence:
1. Это напиток? → да
2. Холодный? → да
3. Сладкий? → да
4. Может быть со вкусом фруктов? → да
5. Его варят? → да
6. В него обычно добавляют курагу? → да

Program:

Загадайте слово или словосочетание на тему 'Еда и напитки'.

Это напиток?

Введите да или нет: да

Холодный?

Введите да или нет: да

Сладкий?

Введите да или нет: да

Может быть со вкусом фруктов? 

Введите да или нет: да

Его варят? 

Введите да или нет: да

В него обычно добавляют курагу?

Введите да или нет: да

Вы загадали: Компот?

Введите да или нет: да

Ура, я угадал!

Хотите посмотреть статистику?

Введите да или нет: да

Угадано: 28

Не угадано: 25

Хотите сыграть еще?

Введите да или нет:

Verified:

* correct tree traversal;
* reaching the sheet;
* Confirmation of guessing.

---

### ▶️ Scenario 2 — error and post-training
The user makes a wish: **Текила**


Sequence:

1. Это напиток? → да
2. Холодный? → да
3. Сладкий? → нет
4. Кисломолочный? → нет
5. Получают с помощью коровы? → нет
6. Это алкогольный напиток? → да
7. Из хмеля? -> нет
8. тёмное? -> нет
9. вы загадали Водка? -> нет
10. Что это было на самом деле? Введите верный ответ.
    -> Текила
11. Какой вопрос отличает Водка от Текила? Введите вопрос, на который можно ответить только да или нет.
    -> Сделана из агавы
12. Как отвечать на этот вопрос для Текила? -> да

Program:

Загадайте слово или словосочетание на тему 'Еда и напитки'.

Это напиток?

Введите да или нет: да

Холодный?

Введите да или нет: да

Сладкий?

Введите да или нет: нет

Кисломолочный?

Введите да или нет: нет

Получают с помощью коровы?

Введите да или нет: нет

Это алкогольный напиток?

Введите да или нет: да

Из хмеля?

Введите да или нет: нет

темное?

Введите да или нет: нет

Вы загадали: Водка?

Введите да или нет: нет

Что это было на самом деле? Введите верный ответ.

Текила

Какой вопрос отличает Водка от Текила? Введите вопрос, на который можно ответить только да или нет.

Сделана из агавы

Как отвечать на этот вопрос для Текила?

Введите да или нет: да

Хотите посмотреть статистику?

Введите да или нет: да

Угадано: 28

Не угадано: 26
---

Result:

A new node is being created in the tree:

Verified:

* adding a new node;
* correct branching logic;
* Rebuilding the tree.

---

### ▶️ Scenario 3 — replay (save check)

The user makes a wish again: **Текила**

Way:

1. Это напиток? → да
2. Холодный? → да
3. Сладкий? → нет
4. Ксломолочный? → нет
5. Получают с помощью коровы? → нет
6. Это алкогольный напиток? → да
7. Из хмеля? → нет
8. темное? → нет
9. Сделана из агавы? → да


Program:

Загадайте слово или словосочетание на тему 'Еда и напитки'.

Это напиток?

Введите да или нет: да

Холодный?

Введите да или нет: да

Сладкий?

Введите да или нет: нет

Кисломолочный?

Введите да или нет: нет

Получают с помощью коровы?

Введите да или нет: нет

Это алкогольный напиток?

Введите да или нет: да

Из хмеля?

Введите да или нет: нет

темное?

Введите да или нет: нет

Сделана из агавы?

Введите да или нет: да

Вы загадали: Текила?

Введите да или нет: да

Ура, я угадал!

Хотите посмотреть статистику?

Введите да или нет: да

Угадано: 29

Не угадано: 26

Verified:

* the tree has been updated;
* the changes have been saved;
* New logic is being used.

---

### ▶Completion and statistics

After completion:
```
Хотите сыграть еще?
```

→ нет

```
Хотите посмотреть статистику?
```

→ да

The program outputs:

```
Угадано: 28
Не угадано: 26
```

Verified:

* statistics are updated correctly:

* +2 guesses
* +1 error

---

## 4. Checking for saving and uploading

Verified:

* the file is being overwritten correctly;
* New data is saved;
* the structure of the tree is not broken;
* When you restart, the changes are saved.

---

## 5. Error handling check

The following cases have been tested:

* ❗ entering incorrect data (not "yes"/"no")
→ the program repeats the request;

* ❗ corrupted file
→ error message is displayed;

* ❗ empty file
  → the default tree is created;

* ❗ incorrect tree structure
  → detected by the `CheckFile' function.

---

## 6. Result

During testing, it was established:

* All basic functions are working correctly;
* the guessing algorithm is implemented correctly;
* the retraining mechanism is functioning correctly;
* saving and loading the tree are stable;
* Statistics are error-free;
* unit tests are fully completed.
