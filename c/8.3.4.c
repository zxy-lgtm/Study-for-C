#include <stdio.h>

#define N 8

void JsSort(char ch[],int n){
    for(int i = 1; i < n; i +=2){
        for(int j = 1; j < n; j +=2){
            if(ch[i]>ch[j]){
                int tmp = ch[i];
                ch[i]= ch[j];
                ch[j]= tmp;
            }
        }
    }
}

void main(){
    char ch[N]={'a','b','c','d','e','f','g','h'};
    JsSort(ch,N);
    for(int i = 0; i < N; i ++){
        printf("%c ",ch[i]);
    }
    printf("\n");

}