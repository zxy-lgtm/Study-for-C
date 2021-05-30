#include <stdio.h>

#define LIST_INIT_SIZE 100
#define LISTNCREMENT 10

typedef int ElemType ;

typedef struct list
{
    ElemType *elem;
    int length;
    int listsize;
}SQList;

struct list IniList(struct list *L){
    L->length = LIST_INIT_SIZE;
    L->listsize = LIST_INIT_SIZE;
    return *L;
}

struct list InsertElem(struct list *L,ElemType elem,int i){
    
}



void main(){
    
}