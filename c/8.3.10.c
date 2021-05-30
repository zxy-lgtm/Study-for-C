#include <stdio.h>

static int number = 0;

void str_int(int nums,char str[]){
    if(nums == 0){
        str[number] = nums+48;
        return;
    }

    int r = nums/10;
    int ch = nums%10;
    str[number] = ch+48;
    number++;
    str_int(r,str);
}

void main(){
    char str[100];
    str_int(2345,str);
    for(int i = number-1; i >= 0; i --){
        printf("%c",str[i]);
    }

    printf("\n");
}