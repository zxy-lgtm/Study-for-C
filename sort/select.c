#include <stdio.h>

void main(){
    int arry[5] = {1,4,2,3,5};
    int size = 5; 

    for (int i = 0; i < size; i ++){
        int min = arry[i];
        for(int j = i; j < size ; j ++){
            if(arry[j] < min){
                arry[i] = arry[j];
                arry[j] = min;
                min = arry[i];
            }
        }
    }

    for (int i = 0; i < size; i ++){
        printf("%d",arry[i]);
    }
}