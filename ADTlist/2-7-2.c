#include <stdio.h>

typedef struct node{
    int value;
    struct node* next;
    
}Node;

void InsertB(Node*P,Node *S){
    S->next=P->next;
    P->next=S;
}

void Print(Node*head){
    Node *p = head;
    if (head == NULL){
        return;
    }
    while(p!= NULL){
        printf("%d ",p->value);
        p=p->next;
    }
    printf("\n");
    return;
}


int main(){
    Node q,w,e,r;
    q.value = 1;
    w.value = 2;
    e.value = 4;
    r.value = 3;
    q.next =&w;
    w.next =&e;
    e.next =NULL;
    Print(&q);
    InsertB(&w,&r);
    Print(&q);

}