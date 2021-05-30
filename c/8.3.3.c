#include <stdio.h>

int (*GetData(int n))[]{
    int *p;
    
    int nums[n];
    p = nums;
    for (int i = 0; i < n; i ++){
        scanf("%d",&nums[i]);
    }

    return p;
}

void Sort(int nums[],int n){
    for(int i = 0; i < n ;i ++){
        int max = nums[i];
        for (int j = i;j < n;j ++){
            if(nums[j]> max){
                nums[i]= nums[j];
                nums[j]= max;
                max = nums[i];
            }
        }
    }
}

void main(){
    int n;
    printf("请输入你需要输入的数组的个数：");
    scanf("%d",&n);
    int *p;
    p = GetData(n);

    Sort(p,n);
    for(int i = 0; i < n; i ++){
        printf("%d ",*p++);
    }
}