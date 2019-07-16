#include<bits/stdc++.h>
using namespace std;
// query(treeEven, 0, n-1, 1, l-1, r-1);
int query(int *tree, int si, int ei, int node, int left, int right) {
  if(si > right || ei < left) {
    return 0;
  }
  
  if(si >= left && ei <= right) {
    return tree[node];
  }
  
  int mid = (si+ei)/2;
  int ans1 = query(tree, si, mid, 2*node, left, right);
  int ans2 = query(tree, mid+1, ei, 2*node+1, left, right);
    
  return ans1+ans2;
}

void update(int *a, int *tree, int si, int ei, int node, int idx, int x) {
  if(si == ei) {
    a[idx] = x;
    if(x == 0) {
      tree[node] = 0;
    } else {
      tree[node] = 1;
    }
    return;
  }
  
  int mid = (si+ei)/2;
  
  if(idx>mid) {
    update(a, tree, mid+1, ei, 2*node+1, idx, x);
  } else {
    update(a, tree, si, mid, 2*node, idx, x);
  }
  
  tree[node] = tree[2*node] + tree[2*node+1];
}

void odd(int *a, int *tree, int si, int ei, int node) {
  if(si == ei) {
    if(a[si]&1) {
    //  cout << "aaya" << endl;
      tree[node] = 1;
    }
    return;
  }
  
  int mid = (si+ei)/2;
  
  odd(a, tree, si, mid, 2*node);
  odd(a, tree, mid+1, ei, 2*node+1);
  
  tree[node] = tree[2*node]+tree[2*node+1];
}

void even(int *a, int *tree, int si, int ei, int node) {
  if(si == ei) {
    if(a[si] == 0) {
      return ;
    }
    if(!(a[si] & 1)) {
      tree[node] = 1;
    }
    return ;
  }
  
  int mid = (si+ei)/2;
  
  even(a, tree, si, mid, 2*node);
  even(a, tree, mid+1, ei, 2*node+1);
  
  tree[node] = tree[2*node]+tree[2*node+1];
}

int main() {

	// Write your code here
  
  int n;
  cin >> n;
  int *a = new int[n];
  for(int i = 0;i<n;i++) {
     cin >> a[i]; 
  }
  int *treeOdd = new int[4*n+1];
  int *treeEven = new int[4*n+1];
  for(int i = 0;i<4*n+1;i++) {
    treeOdd[i] = treeEven[i] = 0;
  }
  
  odd(a, treeOdd, 0, n-1, 1);
  even(a, treeEven, 0, n-1, 1);

  int q;
  cin >> q;
  while(q--) {
    int type;
    cin >> type;
    if(type == 0) {
      int i;
      int x;
      cin >> i >> x;
      if(x&1) {
        update(a, treeOdd, 0, n-1, 1, i-1, x);
      } else {
        update(a, treeEven, 0, n-1, 1, i-1, x);
        
      }
    }
    else if(type == 1) {
      int l,r;
      cin >> l >> r;
      int ans = query(treeEven, 0, n-1, 1, l-1, r-1);
      cout << ans << endl;
    } else {
      int l, r;
      cin >> l >> r;
      int ans = query(treeOdd, 0, n-1, 1, l-1, r-1);
      cout << ans << endl;
    }
  }
  return 0;
}