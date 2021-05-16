#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* 
ASCII Character "A" = 65
*/

#define A_VALUE 65
#define Z_VALUE 90

//source http://randomtextgenerator.com/
char feedText[] = "StatsFile.txt";
int feedStrength[26] = {0, };

void calculateHistogram(char *fileName, int *numChar);
void squareHistogram(int *numChar);
void printHistogram(const int *numChar);
void graphHistogram(const int *numChar);

void calculateWordHistogram(char *word, int *numChar);

int strengthFactor(const int *sourceNumChar, const int *numChar);

void encipher(const char *p, char *c, const unsigned int offset);
void decipher(const char *c, char *p, const unsigned int offset);


int main() {


    //calculate source text histogram
    calculateHistogram(feedText, feedStrength);
    squareHistogram(feedStrength);

    char originalWord[150] = "This is my original text which is quite long";
    char originalEncrypt[150] = "";

    encipher(originalWord, originalEncrypt, 15);



    char testWord[150] = "";
    int testWordInts[26] = {0, };



    //i = 0 so it includes the strength of the first word
    for(int i=0; i<26; i++) {

        for(int num=0; num<26; num++) {
            testWordInts[num] = 0;
        }

        encipher(originalEncrypt, testWord, i);
        calculateWordHistogram(testWord, testWordInts);

        printf(testWord);
        printf("\t %d\n", strengthFactor(feedStrength, testWordInts));
    }

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
#ifdef VERBOSE
    printf(p);
    printf("\n");
#endif

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
#ifdef VERBOSE
        printf("%c => %c\n", p[i], (char)buf);
#endif
        
        c[i] = (char)buf;
    }

#ifdef VERBOSE
    printf(c);
    printf("\n\n");
#endif
}

void decipher(const char *c, char *p, const unsigned int offset) {
    int buf;

#ifdef VERBOSE
    printf(c);
    printf("\n");
#endif

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

#ifdef VERBOSE
        printf("%c => %c\n", c[i], (char)buf);
#endif
        p[i] = (char)buf;
    }

#ifdef VERBOSE
    printf(p);
    printf("\n");
#endif
}

int strengthFactor(const int *sourceNumChar, const int *numChar) {
    int total = 0;

    for(int i=0; i<26; i++) {
        total += sourceNumChar[i] * numChar[i];
    }

    return total;
}

void calculateWordHistogram(char *word, int *numChar) {
    int bufNum;

    for(int i=0; i<strlen(word); i++) {

        if(isalpha(word[i])) {
            bufNum = (int)toupper(word[i]) - A_VALUE;
            //printf("%c, %d\n", toupper(buf), bufNum);

            numChar[bufNum]++;
        }
    }
}

void squareHistogram(int *numChar) {
    int temp;

    for(int i=0; i<26; i++) {
        temp = numChar[i];
        numChar[i] = temp * temp;
    }
}