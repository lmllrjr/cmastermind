#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int generateRandomNumber() {
    // Seed the random number generator with current time
    srand(time(NULL));
    // Generate a random number between 1000 and 9999
    int randomNumber = rand() % 9000 + 1000;

    return randomNumber;
}

void generateRandomDigits(int* digits) {
  int randomNumber = generateRandomNumber();

  digits[0] = randomNumber / 1000;
  digits[1] = (randomNumber / 100) % 10;
  digits[2] = (randomNumber / 10) % 10;
  digits[3] = randomNumber % 10;
}

void stringToDigits(const char* str, int* digits) {
    int length = strlen(str);

    for (int i = 0; i < length; i++) {
        // Convert character to integer
        digits[i] = str[i] - '0';
    }
}

void shuffleString(char* str) {
    int length = strlen(str);

    srand(time(NULL));

    for (int i = length - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        // Swap characters
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

void collectFeedback(const int* codeMaker, int* codeBreaker, char* fdbk) {
    int tmpCodeBreaker[4];
    for (int i = 0; i < 4; i++) {
        tmpCodeBreaker[i] = codeBreaker[i];
    }

    for (int i = 0; i <= 3; i++) {
      if (codeMaker[i] == codeBreaker[i]) {
        fdbk[i]  =  '*';
        continue;
      } else {
        for (int j = 0; j <= 3; j++) {
          if (codeMaker[i] == tmpCodeBreaker[j]) {
            fdbk[i] = '+';
            codeBreaker[j] = 'X'; // set element to something irrelevant to not trigger again
            break;
          } else {
            fdbk[i] = '.';
          }
        }
      }
    }
    fdbk[4] = '\0';
    shuffleString(fdbk);
}

int main() {
  uint8_t count = 0;
  int codeMaker[4];
  generateRandomDigits(codeMaker);

  while (1)
  {
    char str[1024];

    if (count > 12) {
      printf("\n{%d %d %d %d}\n", codeMaker[0], codeMaker[1], codeMaker[2], codeMaker[3]);
      printf("Code not cracked 🔒\n");
      break;
    }

    fgets(str, sizeof(str), stdin);

    int length = strlen(str);
    if (length > 5 || length < 5) {
      continue;
    }

    int codeBreaker[4];
    stringToDigits(str, codeBreaker);

    count++;

    char fdbk[5];
    collectFeedback(codeMaker, codeBreaker, fdbk);
    printf("[%c %c %c %c]\n", fdbk[0], fdbk[1], fdbk[2], fdbk[3]);

    if (strcmp(fdbk, "****") == 0) {
      printf("\n{%d %d %d %d}\n", codeMaker[0], codeMaker[1], codeMaker[2], codeMaker[3]);
      printf("Code cracked 🔓\n");
        return 0;
    }
  }

	return 0;
}
