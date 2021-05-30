#include <stdio.h>
#include <string.h>

void strshif(char *s, int n){
    int len = strlen(s);
    
    for(int i =0; i < n ; i++){
        char ch = s[0];
        strncpy(s,s+1,len-1);
        s[len-1]=ch;
    }
}

void main(){
    char str[] = "0123";
    strshif(str,3);
    printf("%s\n",str);
}

