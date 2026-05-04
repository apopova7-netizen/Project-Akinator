# Akinator

A C-language console game that guesses hidden words on the topic of "Food and Drink" using a binary question tree.

## Description

The program asks the user questions to be answered with "yes" or "no", and based on the answers moves through the question tree to guess the hidden word. If the program doesn't guess correctly, it learns: it remembers a new word and asks the user a question that will help distinguish the new word from the old one.
## Functionality

- Loading the question tree from a text file
- Checking the correctness of the tree file
- Interactive dialogue with the user
- Learning: adding new words and questions
- Saving the updated tree to a file
- Guessing statistics

## File format with a tree

The file should have the following structure:
```bash
|0|0|
1Какой это фрукт?
*0лимон
*0апельсин
```

## Compilation and launch
```bash
mingw32-make         # build the main program
mingw32-make run     # build and run the main program
mingw32-make tests   # build and run all tests
mingw32-make clean   # delete everything
```
