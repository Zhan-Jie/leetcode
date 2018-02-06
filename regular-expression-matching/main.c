#include <stdio.h>
#define bool int
#define true 1
#define false 0


bool isMatch(char* s, char* p) {
    char lastPattern = '\0';
    char currentPattern = *p;
    char currentWord = *s;
    while (currentPattern != '\0') {
        if (currentPattern == '.') {
            lastPattern = currentPattern;
            currentWord = *(++s);
            currentPattern = *(++p);
        } else if (currentPattern == '*') {
            if (lastPattern == '.') {
                return *(p+1) == '\0';
            }
            while (currentWord == lastPattern) {
                currentWord = *(++s);
            }
            currentPattern = *(++p);
        } else {
            if (*(p+1) == '*') {
                lastPattern = currentPattern;
                currentPattern = *(++p);
            } else {
                if (currentPattern != currentWord) {
                    return false;
                } else {
                    currentPattern = *(++p);
                    currentWord = *(++s);
                }
            }
        }
        if (currentWord == '\0') {
            return currentPattern == '\0' || currentPattern == '*';
        }
    }
    return currentWord == '\0';
}

int main() {
    if (isMatch("aaa", "a*a")) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    return 0;
}