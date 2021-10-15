#include<iostream>

typedef struct node{
    char value;
    struct node* next;
    
}Node;

// 将需要插入的node节点插入到flag后面
void Insert(Node * head,Node *node,char flag){

    Node*g=head;

    while(g->next != NULL){
        g=g->next;
        if(g->value==flag){
            node->next =g->next;
            g->next = node;
        }
    }
    return;
}