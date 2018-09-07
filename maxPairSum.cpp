#include <bits/stdc++.h>
using namespace std;

struct node{
    int max;
    int smax;
};

node query(node *tree, int si, int ei, int l, int r, int idx) {
    if(si > r || ei < l) {
        struct node temp;
        temp.max = INT_MIN;
        temp.smax = INT_MIN;
        return temp;
    }

    if(si >= l && ei <= r) {
        return tree[idx];
    }

    int mid = (si+ei)/2;

    struct node ans1 = query(tree, si, mid, l, r, 2*idx);
    struct node ans2 = query(tree, mid+1, ei, l, r, 2*idx+1);

    struct node ans;
    ans.max = max(ans1.max, ans2.max);
    ans.smax = min(max(ans1.max, ans2.smax), max(ans1.smax, ans2.max));

    return ans;

}

void updation(int *a, node *tree, int si, int ei, int x, int val, int idx) {
    if(si == ei) {
        a[x] = val;
        tree[idx].max = val;
        tree[idx].smax = INT_MIN;
        return;
    }

    int mid = (si+ei)/2;

    if(x <= mid) 
        updation(a, tree, si, mid, x, val, idx*2);
    else
        updation(a, tree, mid+1, ei, x, val, idx*2+1);

    
    struct node left = tree[2*idx];
    struct node right = tree[2*idx+1];

    tree[idx].max = max(left.max, right.max);
    tree[idx].smax = min(max(left.max, right.smax), max(left.smax, right.max));

    return ;
}

void build(int *a, node* tree, int idx, int si, int ei) {
    
    if(si == ei) {
        tree[idx].max = a[si];
        tree[idx].smax = INT_MIN;
        return ;
    }
    
    int mid = (si+ei)/2;
    build(a, tree, 2*idx, si, mid);
    build(a, tree, 2*idx+1, mid+1, ei);

    struct node left = tree[2*idx];
    struct node right = tree[2*idx+1];

    tree[idx].max = max(left.max, right.max);
    tree[idx].smax = min(max(left.max, right.smax), max(left.smax, right.max));
    
    return ;
}

int main() {

    int n;
    cin >> n;
    int *a = new int[n];
    for(int i = 0;i<n;i++) {
        cin >> a[i];
    }

    node *tree = new node[3*n];
    build(a, tree, 1, 0, n-1);
    
    //  for(int i = 0;i<3*n;i++) {
    //      cout << tree[i].max << " " << tree[i].smax << endl;
    //  }

    int q;
    cin >> q;
    while(q--) {
        char c;
        cin >> c;
        int i, j;
        cin >> i >> j;
        if(c == 'Q') {
            struct node ans = query(tree, 0, n-1, i-1, j-1, 1);
            cout << ans.max+ans.smax << endl;

        } else {
            updation(a, tree, 0, n-1, i-1, j, 1);
            // for(int i = 0;i<3*n;i++) {
            //   cout << tree[i].max << " " << tree[i].smax << endl;
            // }
        }
    }

    return 0;
}