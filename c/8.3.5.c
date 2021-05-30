#include <stdio.h>

#define SIZE 100

int StrLoc(char str1[],char str2[]){
    int size_str2 = 0;
    for (int j = 0 ; str2[j] != '\0';j ++){
        size_str2++;
    }
    for(int i = 0; str1[i] != '\0';i ++){
        int num = 0;
       for(int j = 0; str2[j] != '\0';j ++){
           if(str1[i+j]!= str2[j]){
               break;
           }
           num ++;
           if(num == size_str2){
               return i;
           }
       }
    }
    return -1;
}

void main(){
    char str1[SIZE] = "how do you do?";
    char str2[SIZE] = "do";
    int loc = StrLoc(str1,str2);
    printf("%d\n",loc);
}