#include<stdio.h>
#include<iostream>

typedef struct node{
    int value;
    struct node* next;
    
}Node;

int Getlens(Node*head){

    Node*p = head;
    int len = 0;

    while(p->next != NULL){
        p = p->next;
        len ++;
    }

    return len;
}

void Insert(Node * head,int number){
    Node*p=new Node;
    Node*g=head;
    p->value = number;
    p->next =NULL;

    while(g->next != NULL){
        g=g->next;
    }
    g->next=p;
    return;
}

int main(){

    Node *head = new Node;
    head->next=NULL;

    int n,m;
    std::cout<<"请输入整数的个数："<<endl;
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        scanf("%d",&m);
        Insert(head,m);
    }
    int len = Getlens(head);
    printf("%d",len);
}