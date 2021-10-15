#include<stdio.h>

void Reverse(int nums[],int n){
   int temp;
   for(int i = 0; i < n/2; i++){
       temp = nums[n-i-1];
       nums[n-i-1]=nums[i];
       nums[i] = temp;
   }
   return;

}

int main(){
    int nums[]={1,2,3,4,5,6,7,8,9};
    Reverse(nums,9);
    for(int i = 0;i < 9;i ++){
        printf("%d",nums[i]);
    }
}