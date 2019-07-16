#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
void build(int *arr,int *tree,int start,int end,int treenode,int *hash)
{
    if(start==end)
    {
        tree[treenode]=arr[start];
        return;
        
    }
    int mid=(start+end)/2;
    build(arr,tree,start,mid,2*treenode,hash);
    build(arr,tree,mid+1,end,2*treenode+1,hash);
    tree[treenode]=(tree[2*treenode+1]+(tree[2*treenode]*hash[end-mid])%3)%3;
    return;
    
}
void update(int *arr,int *tree,int start,int end,int treenode,int idx,int *hash)
{
    if(start==end)
    {
        if(tree[treenode]==0)
        {
            arr[idx]=1;
            tree[treenode]=1;
        }
        return;
    }
    int mid=(start+end)/2;
    if(idx>mid &&idx<=end)
    {
        update(arr,tree,mid+1,end,2*treenode+1,idx,hash);
    }
    else
    {
        update(arr,tree,start,mid,2*treenode,idx,hash);
    }
    tree[treenode]=(tree[2*treenode+1]+(tree[2*treenode]*hash[end-mid])%3)%3;
    return;
}
int query(int *arr,int *tree,int start,int end,int treenode,int left,int right,int *hash)
{
    if(start>=left && end<=right)
    {
        return (tree[treenode]*hash[right-end])%3;
    }
    if(start>right || end<left)
    {
        return 0;
    }
    int mid=(start+end)/2;
    int ans1=query(arr,tree,start,mid,2*treenode,left,right,hash);
    int ans2=query(arr,tree,mid+1,end,2*treenode+1,left,right,hash);
    int ans3;
    ans3=((ans2%3)+(ans1%3))%3;
    return ans3;
}
 
int main() {
 
	// Write your code here
    int n;
    cin>>n;
    string s;
    cin>>s;
    int x[n];
    for(int i=0;i<n;i++)
    {
        x[i]=s[i]-'0';
    }
    int *tree=new int[4*n];
    ll q;
    cin>>q;
    int* hash=new int[100001];
    hash[0]= 1;
    for(int i=1;i<100001;i++)
    {
        hash[i]=(hash[i-1]*2)%3;
        
    }
    build(x,tree,0,n-1,1,hash);
    // for(int i = 0;i<4*n;i++) cout << tree[i] << " ";
    // cout << endl;
    while(q--)
    {
        int a,b,c;
        cin>>a>>b;
        if(a==0)
        {
            cin>>c;
            int h=query(x,tree,0,n-1,1,b,c,hash);
            cout<<h<<endl;
        }
        else if(a==1)
        {
            update(x,tree,0,n-1,1,b,hash);
            // for(int i = 0;i<4*n;i++) cout << tree[i] << " ";
            // cout << endl;
        }
    }
    
}