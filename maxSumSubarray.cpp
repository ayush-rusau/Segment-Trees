// Possibilities of maximum sum are:-
// 1. leftMaxSum
// 2. rightMaxSum
// 3. leftSum + rightPrefixSum
// 4. rightSum + leftSuffixSum
// 5. leftSuffixSum + rightPrefixSum
// Needed quantities:- maxSum, totalSum, bestPrefixSum, bestSuffixSum
//sum = LS + RS
//bestPrefSum = max(BLPS, LS+BRPS)
//bestSuff = max(BRSS, rightSum+BLSS)


#include <bits/stdc++.h>
using namespace std;

struct node {
    long long maxSum;
    long long sum;
    long long bestPre;
    long long bestSuff;
};

node query(long long *a, node* tree, int si, int ei, int idx, int l, int r) {
    if(si > r || ei < l) {
        struct node temp;
        temp.maxSum = INT_MIN;
        temp.sum = INT_MIN;
        temp.bestPre = INT_MIN;
        temp.bestSuff = INT_MIN;
        return temp;
    }

    if(si >= l && ei <= r) {
        return tree[idx];
    }

    int mid = (si+ei)/2;

    struct node left = query(a, tree, si, mid, 2*idx, l, r);
    struct node right = query(a, tree, mid+1, ei, 2*idx+1, l, r);

    struct node ans;
    ans.maxSum = max(left.maxSum, max(right.maxSum, max(left.sum+right.bestPre, max(right.sum+left.bestSuff, left.bestSuff+right.bestPre))));
    ans.sum = left.sum+right.sum;
    ans.bestPre = max(left.bestPre, left.sum+right.bestPre);
    ans.bestSuff = max(right.bestSuff, right.sum + left.bestSuff);

    return ans;

}


/*void update(int *a, node *tree, int si, int ei, int idx, int i, int x) {
    if(si == ei) {
        a[i] =x;
        tree[idx].sum = a[si];
        tree[idx].maxSum = a[si];
        tree[idx].bestPre = tree[idx].bestSuff = a[si];
        return;
    }
    
    int mid = (si+ei)/2;
    update(a, tree, si, mid, idx, i, x);
    update(a, tree, mid+1, ei, idx, i, x);

    struct node left = tree[idx*2];
    struct node right = tree[2*idx+1];

    tree[idx].maxSum = max(left.maxSum, max(right.maxSum, max(left.sum+right.bestPre, max(right.sum+left.bestSuff, left.bestSuff+right.bestPre))));
    tree[idx].sum = left.sum+right.sum;
    tree[idx].bestPre = max(left.bestPre, left.sum+right.bestPre);
    tree[idx].bestSuff = max(right.bestSuff, right.sum + left.bestSuff);
    return ;

}*/

void build(long long *a, node *tree, int si, int ei, int idx) {

    if(si == ei) {
       tree[idx].sum = a[si];
       tree[idx].maxSum = a[si];
       tree[idx].bestPre = tree[idx].bestSuff = a[si];
       return;
    }

    int mid = (si+ei)/2;
    build(a, tree, si, mid, idx*2);
    build(a, tree, mid+1, ei, idx*2+1);

    struct node left = tree[idx*2];
    struct node right = tree[2*idx+1];

    tree[idx].maxSum = max(left.maxSum, max(right.maxSum, max(left.sum+right.bestPre, max(right.sum+left.bestSuff, left.bestSuff+right.bestPre))));
    tree[idx].sum = left.sum+right.sum;
    tree[idx].bestPre = max(left.bestPre, left.sum+right.bestPre);
    tree[idx].bestSuff = max(right.bestSuff, right.sum + left.bestSuff);
    return ;
}


int main() {
    int n;
    cin >> n;
    long long *a = new long long[n];
    for(int i= 0;i<n;i++) {
        cin >> a[i];
    }

    node *tree = new node[4*n];

    build(a, tree, 0, n-1, 1);
    for(int i = 0;i<4*n;i++) {
        cout << tree[i].maxSum << " ";
    }
    cout << endl;
    int q;
    cin >> q;
    while(q--) {
        // char c;
        // cin >> c;
        int i,j;
        cin >> i >> j;
     
             struct node ans = query(a, tree, 0, n-1, 1, i-1, j-1);
             
             cout << ans.maxSum << endl;
    }
    return 0;
}