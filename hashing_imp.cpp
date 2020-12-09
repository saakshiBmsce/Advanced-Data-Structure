#include<stdio.h>
#include<iostream>
#include<vector>
#include<list>

using namespace std;

class HashTable{

    public:
     vector<list<pair<int,int>>>hash;
     int max_idx;
     int getValue(int);
     void insert(int,int);
     void PrintHash();
     HashTable(int);

};

HashTable :: HashTable(int max_idx)
{
    this->max_idx=max_idx;
    this->hash=vector<list<pair<int,int>>>(max_idx);
}

int HashTable :: getValue(int key)
{
    int hash_val=key%this->max_idx;
    for(auto it=hash[hash_val].begin();it!=hash[hash_val].end();it++)
    {
        if(it->first==key)return it->second;
    }
    return -1;
}

void HashTable::insert(int key,int val)
{
    int hash_val=key%max_idx;
    hash[hash_val].push_back({key,val});
}

void HashTable:: PrintHash()
{
    for(int i=0;i<max_idx;i++)
    {
        cout<<"hash "<<i<<":"<<endl;
        for(auto it=hash[i].begin();it!=hash[i].end();it++)
        {
            cout<<it->first<<"->"<<it->second<<endl;
        }
    }
}

int main()
{
    HashTable *h1=new HashTable(5);
    h1->insert(1,5);
    h1->insert(2,6);
    h1->insert(3,8);
    h1->insert(8,5);
    h1->insert(10,6);
    h1->PrintHash();
    cout<<"1=>"<<h1->getValue(1)<<endl;
    cout<<"2=>"<<h1->getValue(2)<<endl;
    cout<<"3=>"<<h1->getValue(3)<<endl;
    cout<<"8=>"<<h1->getValue(1)<<endl;
    cout<<"10=>"<<h1->getValue(2)<<endl;

}

