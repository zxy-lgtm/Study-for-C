#include <stdio.h>

void main(){
    char str[100];
    int i=0,num = 0;
    while (1)
    {
        
        str[i] =getchar();
        i ++;
        num ++;
        if(getchar() == '\n'){
            break;
        }
    }

    for(int j = 0; j < i /2; j ++){
        if(str[j] != str[i-1]){
            printf("NO!");
            return;
        }
        i --;
    }
    printf("YES!");    
}