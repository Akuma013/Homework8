#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

int main() {
    char str1[MAX_LENGTH], str2[MAX_LENGTH], str_copy[MAX_LENGTH];
    int len1, len2;


    printf("Enter the first string: ");
    fgets(str1, MAX_LENGTH, stdin);

    str1[strcspn(str1, "\n")] = '\0';

    printf("Enter the second string: ");
    fgets(str2, MAX_LENGTH, stdin);

    str2[strcspn(str2, "\n")] = '\0';


    char concatenated[MAX_LENGTH * 2];
    strcpy(concatenated, str1);
    strcat(concatenated, str2);
    printf("\nConcatenated string: %s\n", concatenated);

 
    if (strcmp(str1, str2) == 0) {
        printf("\nThe two strings are the same.\n");
    } else {
        printf("\nThe two strings are different.\n");
    }

    len1 = strlen(str1);
    len2 = strlen(str2);
    printf("\nLength of the first string: %d\n", len1);
    printf("Length of the second string: %d\n", len2);


    strcpy(str_copy, str1);
    printf("\nCopy of the first string: %s\n", str_copy);

    return 0;
} 