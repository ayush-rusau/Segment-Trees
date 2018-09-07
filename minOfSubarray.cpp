#include<bits/stdc++.h>
using namespace std;


void build(int *a, int *tree, int n, int si, int ei, int node) {
  if(si == ei) {
    tree[node] = a[si];
    return ;
  }
  
  int mid = (si+ei)/2;
  
  build(a, tree, n, si, mid, 2*node);
  build(a, tree, n, mid+1, ei, 2*node+1);
  
  tree[node] = min(tree[2*node], min(tree[2*node+1], tree[2*node] + tree[2*node+1]));
}

int query(int *tree, int si, int ei, int treeNode, int left, int right) {
  
  if(si > right || ei < left) {
    return INT_MAX;
  }
  
  else if(si >= left && ei <= right) {
    return tree[treeNode];
  }
  
  int mid = (si+ei)/2;
  
  int ans1 = query(tree, si, mid, treeNode*2, left, right);
  
  int ans2 = query(tree, mid+1, ei, treeNode*2+1, left, right);
  
  return min(ans1, ans2);
  
}

void update(int *a, int *tree, int si, int ei, int node, int idx, int x) {
  
  if(si > ei || si > idx || ei < idx) {
      return ;
  }
  
  if(si == ei) {
    a[idx] = x;
    tree[node] = x;
    return;
  }
  
  int mid = (si+ei)/2;
  
  update(a, tree, si, mid, 2*node, idx, x);
  update(a, tree, mid+1, ei, 2*node+1, idx, x);
  
  tree[node] = min(tree[2*node], tree[2*node+1]);
  
}

int main() {
  
  int n, q;
  cin >> n >> q;
  int *a = new int[n];
  for(int i = 0;i<n;i++) {
    cin >> a[i];
  }
  
  int *tree = new int[2*n];
  
  build(a, tree, n, 0, n-1, 1);
  
  /*for(int i = 0;i<2*n;i++) {
    cout << tree[i] << " ";
  }*/
  
  
  while(q--) {
    char c;
    cin >> c;
    if(c == 'q') {
      int l, r;
      cin >> l >> r;
      
      cout << query(tree, 0, n-1, 1, l-1, r-1) << endl;
    } else {
      int idx, x;
      cin >> idx >> x;
      update(a, tree, 0, n-1, 1, idx-1, x);

     /* for(int i = 0;i<2*n;i++) {
          cout << tree[i] << " ";
      }
      cout << endl;
      for(int i = 0;i<n;i++) {
          cout << a[i] << " ";
      }
      cout << endl;
      */
    }
  }
  
  return 0;

	// Write your code here
}