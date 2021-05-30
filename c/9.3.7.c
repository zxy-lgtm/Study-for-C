#include <stdio.h>
#include <string.h>

int totsubstrnum(char *str, char *substr){
    int size_str2 = strlen(substr),num = 0;
    for(int i = 0; str[i] != '\0';i ++){
        int n = 0;
       for(int j = 0; substr[j] != '\0';j ++){
           if(str[i+j]!= substr[j]){
               break;
           }
           n ++;
           if(n == size_str2){
               num ++;
           }
       }
    }
    return num;
}

void main(){
    printf("%d\n",totsubstrnum("do you do some homework?","do"));
}