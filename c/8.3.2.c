#include <stdio.h>

int MaxCommonFactor(int a,int b){
    int r =a%b;
    int q = a/b;
    if (r == 0){
        return b;
    }
    MaxCommonFactor(b,r);
}

void main(){
    printf("MaxCommonFactor(10,8)=%d\n",MaxCommonFactor(10,5));
}