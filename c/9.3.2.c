#include <stdio.h>

#define SIZE 100

void main(){
    char str1[] = "12345";
    char str2[] = "54321";
    char str3[SIZE] = {'\0'};
    int i = 0;

    for(;str1[i] != '\0';i ++){
        str3[i] = str1[i];
    }

    for(int j = 0; str2[j] != '\0'; j ++){
        str3[i] = str2[j];
        i ++;
    }

    str3[++i] = '\0';

    for(int j = 0; str3[j] != '\0';j ++ ){
        printf("%c",str3[j]);
    }
    printf("\n");
}