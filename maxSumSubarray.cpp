// Possibilities of maximum sum are:-
// 1. leftMaxSum
// 2. rightMaxSum
// 3. leftSum + rightPrefixSum
// 4. rightSum + leftSuffixSum
// 5. leftSuffixSum + rightPrefixSum
// Needed quantities:- maxSum, totalSum, bestPrefixSum, bestSuffixSum
//sum = LS + RS
//bestPrefSum = max(BLPS, LS+BRPS)
//BSS = max(BRSS, rightSum+BLSS)


#include <iostream>
using namespace std;

struct node {
    long long maxSum;
    long long sum;
    long long bps;
    long long bss;
};

node query(int *a, node* tree, int si, int ei, int idx, int l, int r) {
    if(si > r || ei < l) {
        struct node temp;
        temp.maxSum = INT_MIN;
        temp.sum = INT_MIN;
        temp.bps = INT_MIN;
        temp.bss = INT_MIN;
        return temp;
    }

    if(si >= l && ei <= r) {
        return tree[idx];
    }

    int mid = (si+ei)/2;

    struct node left = query(a, tree, si, mid, l, r, 2*idx);
    struct node right = query(a, tree, mid+1, ei, l, r, 2*idx+1);

    struct node ans;
    ans[idx].maxSum = max(left.maxSum, max(right.maxSum, max(left.sum+right.bps, max(right.sum+left.bss, left.bss+right.bps))));
    ans[idx].sum = left.sum+right.sum;
    ans[idx].bps = max(left.bps, left.sum+right.bps);
    ans[idx].bss = max(right.bss, right.sum + left.bss);

    return ans;

}


void update(int *a, node *tree, int si, int ei, int idx, int i, int x) {
    if(si == ei) {
        a[i] =x;
        tree[idx].sum = a[si];
        tree[idx].maxSum = a[si];
        tree[idx].bps = tree[idx].bss = a[si];
        return;
    }
    
    int mid = (si+ei)/2;
    update(a, tree, si, mid, idx, i, x);
    update(a, tree, mid+1, ei, idx, i, x);

    struct node left = tree[node*2];
    struct node right = tree[2*node+1];

    tree[idx].maxSum = max(left.maxSum, max(right.maxSum, max(left.sum+right.bps, max(right.sum+left.bss, left.bss+right.bps))));
    tree[idx].sum = left.sum+right.sum;
    tree[idx].bps = max(left.bps, left.sum+right.bps);
    tree[idx].bss = max(right.bss, right.sum + left.bss);
    return ;

}

void build(int *a, node *tree, int si, int ei, int idx) {

    if(si == ei) {
       tree[idx].sum = a[si];
       tree[idx].maxSum = a[si];
       tree[idx].bps = tree[idx].bss = a[si];
       return;
    }

    int mid = (si+ei)/2;
    build(a, tree, si, mid, idx*2);
    build(a, tree, mid+1, ei, idx*2+1);

    struct node left = tree[node*2];
    struct node right = tree[2*node+1];

    tree[idx].maxSum = max(left.maxSum, max(right.maxSum, max(left.sum+right.bps, max(right.sum+left.bss, left.bss+right.bps))));
    tree[idx].sum = left.sum+right.sum;
    tree[idx].bps = max(left.bps, left.sum+right.bps);
    tree[idx].bss = max(right.bss, right.sum + left.bss);
    return ;
}


int main() {
    int n;
    cin >> n;
    long long *a = new long long[n];
    for(int i= 0;i<n;i++) {
        cin >> a[i];
    }

    long long *tree = new node[3*n];

    build(a, tree, 0, n-1, 1);

    int q;
    cin >> q;
    while(q--) {
        // char c;
        // cin >> c;
        int i,j;
        cin >> i >> j;
     
             struct node ans = query(a, tree, 0, n-1, 1, i-1, r-1);
             cout << ans.maxSum << endl;
    }
    return 0;
}