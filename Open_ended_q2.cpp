#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a;int b;
    cin>>a>>b;
    for(int i=a;i<b;i++)
    {
        bool rep=false;
        vector<bool>hash(9,false);
        int n=i;
        while(n>0)
        {
            if(hash[n%10]){
                rep=true;
                break;
            }
            hash[n%10]=true;
            n=n/10;
        }
        if(!rep)cout<<i<<"  ";
    }
    cout<<endl;
    return 0;
}