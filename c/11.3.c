#include <stdio.h>
#include <stdlib.h>

typedef struct studentinfo {
    struct studentinfo * next;
    int score;
}NODE;

NODE *Create_LinkList(){
    NODE *head,*tail,*pnew;
    int score;

    head = (NODE*)malloc(sizeof(NODE));
    if(head == NULL){
        printf("malloc is in error !");
        return NULL;
    }

    head->next = NULL;
    tail = head;

    printf("please input students' scores and if you want to exit, you can input -1 in any time!\n");
    while(1){
        scanf("%d",&score);
        if(score == -1){
            return head;
        }

        pnew = (NODE*)malloc(sizeof(NODE));
        if(pnew == NULL){
            printf("malloc is in  error !");
            return head;
    }
        pnew->score = score;
        tail->next = pnew;
        pnew->next = NULL;
        tail = pnew;
    }

    return head;
}

void Insert_LinkList(NODE *head, NODE *pnew, int i){
    NODE *p = head;
    
    for(int j = 0; j < i && p != NULL; j ++){
        p = p->next;
        if(p == NULL){
            printf("the %d NODE is not exist!",j);
            return;
        }
    }

    //此操作顺序不可颠倒！
    pnew->next = p->next;
    p->next = pnew;
}

void Delete_LinkList(NODE *head, int i){
    NODE *p = head,*q;

    if(i == 0){
        printf("head NODE can not be deleted!");
        return;
    }
    
    for(int j = 1; j < i && p->next != NULL; j ++){
        p = p->next;
        if(p = NULL){
            printf("the %d NODE is not exist!",j-1);
            return;
        }
    }

    q = p->next;
    p->next = q->next;
    free(q);
}

void Display_LinkList(NODE *head){
    NODE *p;

    for(p = head->next; p != NULL;p = p->next){
        printf("%d ",p->score);
    }
    printf("\n");
}

void Free_LinkList(NODE *head){
    NODE *p=head,*q;

    while (p->next != NULL){
        q = p->next;
        p->next = q->next;
        free(q);
    }
    free(head);
}

void main(){
    NODE *head, *pnew;
    head =Create_LinkList();
    if(head == NULL){
        return;
    }
    printf("after create:");
    Display_LinkList(head);

    pnew = (NODE*)malloc(sizeof(NODE));
    if(pnew == NULL){
        printf("malloc is in error!");
        return;
    }

    int i,score;
    printf("please input the insert score and the set you want to insert:");
    scanf("%d%d",&score,&i);
    pnew->score = score;

    Insert_LinkList(head,pnew,i);

    printf("now:");
    Display_LinkList(head);

    Delete_LinkList(head,i);
    Display_LinkList(head);

    Free_LinkList(head);

}