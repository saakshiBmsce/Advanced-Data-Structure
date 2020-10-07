#include<iostream>
#include<stdio.h>
#include<vector>
#include<list>
using namespace std;

struct node{
    int val;
    node* l0_next;
    node* l1_next;
};

node* getNode(int x)
{
    node* p=(node*)malloc(sizeof(node));
    p->l0_next=NULL;
    p->l1_next=NULL;
    p->val=x;
    return p;
}

void Print(node* head)
{
    node* t=head;
    while(t!=NULL)
    {
        cout<<t->val<<" --> ";
        t=t->l1_next;
    }
    cout<<endl;
    t=head;
    while(t!=NULL)
    {
        cout<<t->val<<" -> ";
        t=t->l0_next;
    }
    cout<<endl;
}

node* deleteNode(node* head,int x)
{
   node* t=head;
   cout<<"deleting "<<x<<endl;
    int level=rand()%2;
    node* p=getNode(x);
    while(true)
    {
        if(t->l1_next==NULL)break;
        if(t->l1_next->val>=x)break;
        t=t->l1_next;
    }
    if(t->l1_next!=NULL)
    {
        while(true)
        {
            if(t->l0_next==NULL)break;
            if(t->l0_next->val>=x)break;
            t=t->l0_next;
        }   
    }
    node* tnxtl0=t->l0_next;node* tnxtl1=t->l1_next;
    if(tnxtl0==NULL){cout<<"No such element"<<endl;return head;}
    if(tnxtl1==NULL){t->l0_next=tnxtl0->l0_next;free(tnxtl0);}
    if(tnxtl0->val==tnxtl1->val)
    {
        t->l0_next=tnxtl0->l0_next;
        t->l1_next=tnxtl1->l1_next;
    }
    else{
        t->l0_next=tnxtl0->l0_next;
    }
    Print(head);
    return head;
}

node* insert(node* head,int x,int level)
{
    node* t=head;
    cout<<"inserting "<<x<<"  at level "<<level<<endl;
    node* p=getNode(x);
    while(true)
    {
        if(t->l1_next==NULL)break;
        if(t->l1_next->val>x)break;
        t=t->l1_next;
    }
    if(t->l1_next!=NULL)
    {
        while(true)
        {
            if(t->l0_next==NULL)break;
            if(t->l0_next->val>x)break;
            t=t->l0_next;
        }   
    }
    
    cout<<t->val<<endl;
    node* tnxtl0=t->l0_next;node* tnxtl1=t->l1_next;
    if(level==0)
    {
        t->l0_next=p;
        p->l0_next=tnxtl0;
    }
    if(level==1)
    {
        t->l0_next=p;
        p->l0_next=tnxtl0;
        t->l1_next=p;
        p->l1_next=tnxtl1;
        
    }
    Print(head);
}




int main()
{
    node* head=getNode(10);
    node* l1_1=getNode(28);head->l0_next=l1_1;
    node* l1_2=getNode(58);head->l1_next=l1_2;l1_1->l0_next=l1_2;
    node* l1_4=getNode(65);l1_2->l0_next=l1_4;
    node* l1_3=getNode(70);l1_2->l1_next=l1_3;l1_4->l0_next=l1_3;
    Print(head);
    insert(head,30,0);
    insert(head,63,1);
    deleteNode(head,63);
    return 0;
}
