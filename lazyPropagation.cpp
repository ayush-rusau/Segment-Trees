#include <bits/stdc++.h>
using namespace std;

void buildTree(int *arr, int *tree, int start, int end, int treeNode){
    if(start == end){
        tree[treeNode] = arr[start];
        return ;
    }

    int mid = (start + end)/2;

    buildTree(arr, tree, start, mid, 2*treeNode);
    buildTree(arr, tree, mid+1, end, 2*treeNode+1);
    tree[treeNode] = min(tree[2*treeNode], tree[2*treeNode+1]);
}

void update(int *tree, int *lazy, int low, int high, int startR, int endR, int currPos, int inc) {

    if(low > high) return ;

    if(lazy[currPos] != 0) {
        tree[currPos] += lazy[currPos];
        if(high != low) {
            lazy[2*currPos] += lazy[currPos];
            lazy[2*currPos+1] += lazy[currPos];
        }

        lazy[currPos] = 0;
    }
    // No Overlapping
    if(startR > high || endR < low) return ;

    // Complete overlap
    if(startR <= low && endR>=high) {
        tree[currPos] += inc;
        if(high != low) {
            lazy[2*currPos] += inc;
            lazy[2*currPos+1] += inc;
        }
        return;
    }

    // partial overlapping
    int mid = (low+high)/2;
    update(tree, lazy, low, mid, startR, endR, currPos*2, inc);
    update(tree, lazy, mid+1, high, startR, endR, currPos*2+1, inc);

    tree[currPos] = min(tree[2*currPos], tree[2*currPos+1]);
}

int query(int *tree, int *lazy, int low, int high, int startR, int endR, int currPos) {
    if(high < low) {
        return INT_MAX;
    }

    if(lazy[currPos] != 0) {
        tree[currPos] += lazy[currPos];
        if(high != low) {
            tree[currPos*2] += lazy[currPos];
            tree[currPos*2+1] += lazy[currPos];
        }
        lazy[currPos] = 0;
    }

    if(startR > high || endR < low) {
        return INT_MAX;
    }

    if(startR <= low && endR >= high) {
        return tree[currPos];
    }

    int mid = (high+low)>>1;
    int ans1 = query(tree, lazy, low, mid, startR, endR, 2*currPos);
    int ans2 = query(tree, lazy, mid+1, high, startR, endR, currPos*2+1);

    int ans = min(ans1, ans2);
    return ans;

}

int main() {

    int arr[] = {1, 3, -2, 4};
    int *tree = new int[12]();
    buildTree(arr, tree, 0, 3, 1);
    
    int *lazy = new int[12]();
    update(tree, lazy, 0, 3, 0, 3, 1, 3);
    update(tree, lazy, 0, 3, 0, 1, 1, 2);

    cout << query(tree, lazy, 0, 3, 1, 3, 1) << endl;
    
    return 0;
}