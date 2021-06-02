#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100
#define LISTNCREMENT 10

typedef int ElemType ;

typedef struct list
{
    ElemType *elem;
    int length;
    int listsize;
}SQList;

typedef struct list2
{
    ElemType elem;
    struct list2 *next;
}List;


struct list (*IniList(struct list *L)){
    L->length = LIST_INIT_SIZE;
    L->listsize = LIST_INIT_SIZE;
    return L;
}

struct list2 (*IniList()){
    List *head;
    head = (struct list2*)malloc(sizeof(struct list2));
    head->next = NULL;

    while(1){
        List *pnew;
        pnew = (List*)malloc(sizeof(List));
        printf("请输入学生的成绩：");
        scanf("%d",&pnew->elem);

        if(pnew->elem < 0){
            break;
        }
        pnew->next = NULL;
        head->next = pnew;

    }
    return head;
}


struct list InsertElem(struct list *L,ElemType elem,int i){
    
}



void main(){
    
}