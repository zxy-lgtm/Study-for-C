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

struct list2 (*IniList(struct list2 *L2)){
    L2 = (struct list2*)malloc(sizeof(struct list2));
    L2->next = NULL;
    return L2;
}


struct list InsertElem(struct list *L,ElemType elem,int i){
    
}



void main(){
    
}