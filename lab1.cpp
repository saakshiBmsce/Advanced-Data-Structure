#include<iostream>
#include<stdio.h>
#include<map>
#include<vector>
using namespace std;

struct ListNode{
    int val;
    ListNode* next;
};

ListNode* XOR (ListNode *a, ListNode *b)  
{  
    return (ListNode*) ((uintptr_t) (a) ^ (uintptr_t) (b));  
}

ListNode* getNode(int x)
{
    ListNode* p=(ListNode*)malloc(sizeof(ListNode*));
    p->val=x;
    p->next=NULL;
    return p;
}

ListNode* DeleteAtBegin(ListNode* head)
{

}

ListNode* addAtBegin(ListNode* head,int x)
{
    ListNode* p=getNode(x);

    if(head==NULL)return p;
    p->next=XOR(head,NULL);
    head->next=XOR(XOR(head->next,NULL),p);
    head=p;
    //cout<<head->val<<"->";
    return head;
}

ListNode* AddAtEnd(ListNode* head,int x)
{
    ListNode* p=getNode(x);
    if(head==NULL)return p;
    ListNode* t=head;
    ListNode* pvs=NULL;
    ListNode* tnxt=XOR(t->next,pvs);
    while(tnxt!=NULL)
    {
        //cout<<t->val<<"->";
        tnxt=XOR(t->next,pvs);
        pvs=t;
        t=tnxt;
    }
    ListNode* tail=pvs;
    p->next=XOR(NULL,tail);
    tail->next=XOR(XOR(tail->next,NULL),p);
    return head;
}

int main()
{
    ListNode* head=getNode(1);
    head=addAtBegin(head,2);
    head=addAtBegin(head,3);
    head=addAtBegin(head,4);
    head=addAtBegin(head,5);
    head=AddAtEnd(head,6);
    cout<<endl;
    ListNode* t=head;
    ListNode* pvs=NULL;
    ListNode* tnxt=XOR(t->next,pvs);
    while(tnxt!=NULL)
    {
        cout<<t->val<<"->";
        tnxt=XOR(t->next,pvs);
        pvs=t;
        t=tnxt;
    }
    cout<<endl;
    return 0;
}