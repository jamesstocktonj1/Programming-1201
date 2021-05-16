#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* 
ASCII Character "A" = 65
*/

#define A_VALUE 65
#define Z_VALUE 90



void calculateHistogram(char *fileName, int *numChar);
void printHistogram(const int *numChar);
void graphHistogram(const int *numChar);

void encipher(const char *p, char *c, const unsigned int offset);
void decipher(const char *c, char *p, const unsigned int offset);


int main() {
    FILE *f;

    int charNumbers[26] = {0, };

    char word[20] = "Hello World!";
    char temp[20] = "";

    encipher(word, temp, 4);
    decipher(temp, word, 4);

    //calculateHistogram("new.txt", charNumbers);
    //printHistogram(charNumbers);
    //graphHistogram(charNumbers);

    return 0;
}



void calculateHistogram(char *fileName, int *numChar) {
    FILE *f = fopen(fileName, "r");
    char buf;
    int bufNum;

    while((buf = fgetc(f)) != EOF) {

        //gets rid of any characters that arent alpha
        if(isalpha(buf)) {
            bufNum = (int)toupper(buf) - A_VALUE;
            //printf("%c, %d\n", toupper(buf), bufNum);

            numChar[bufNum]++;
        }
    }
    fclose(f);
}

void printHistogram(const int *numChar) {

    for(int i=0; i<26; i++) {
        printf("%c: %d\n", i+A_VALUE, numChar[i]);
    }
}

void graphHistogram(const int *numChar) {

    for(int i=0; i<26; i++) {

        if(numChar[i] != 0) {
            printf("%c: ", i + A_VALUE);

            for(int c=0; c<numChar[i]; c++) {
                printf("*");
            }
            printf("\n");
        }
    }
}

void encipher(const char *p, char *c, const unsigned int offset) {
    int buf;

    printf(p);
    printf("\n");

    for(int i=0; i<strlen(p); i++) {

        buf = (int)toupper(p[i]);

        if(isalpha(buf)) {

            
            buf += offset;

            if(buf > Z_VALUE) {
                buf -= 26;
            }
            else if(buf < A_VALUE) {
                buf += 26;
            }
        }

        printf("%c => %c\n", p[i], (char)buf);
        c[i] = (char)buf;
    }

    printf(c);
    printf("\n\n");
}

void decipher(const char *c, char *p, const unsigned int offset) {
    int buf;

    printf(c);
    printf("\n");

    for(int i=0; i<strlen(c); i++) {

        buf = (int)toupper(c[i]);

        if(isalpha(buf)) {

            
            buf += (offset * -1);

            if(buf > Z_VALUE) {
                buf -= 26;
            }
            else if(buf < A_VALUE) {
                buf += 26;
            }
        }

        printf("%c => %c\n", c[i], (char)buf);
        p[i] = (char)buf;
    }

    printf(p);
    printf("\n");
}
