#include<bits/stdc++.h>
using namespace std;

vector<int> getWithoutMax(vector<int>nums,int n)
{
    vector<int>ans;
    int max1=0;int max2=0;
    for(int i=0;i<n;i++)
    {
        if(nums[i]>=nums[max1])
        {
            max2=max1;
            max1=i;
        }
        else if(nums[i]>=nums[max2])
        {
            max2=i;
        }
    }
    cout<<"without max: "<<endl;
    for(int i=0;i<n;i++)
    {
        if((i!=max1)&&(i!=max2))
        {
            ans.push_back(nums[i]);
            cout<<nums[i]<<" ";
        }
    }

    
    return ans;

}

int main(){

    int t;
    cout<<"Enter test cases"<<endl;
    cin>>t;
    while(t--){
        int n=8;
        vector<int>ques(n,0);
        cout<<"Enter n"<<endl;
        cin>>n;
        // vector<int>nums={2,4,1,5,4,1,8,8};
        cout<<"Enter the elements"<<endl;
        int x=0;
        int i=0;
        while (i!=n)
        {
            cin>>ques[i];
            i++;
        }

        for(int i=0;i<n;i++)cout<<ques[i]<<" ";
        vector<int> withoutMax=getWithoutMax(ques,n);

    }
    return 1;
}