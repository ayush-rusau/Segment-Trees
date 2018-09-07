#include <iostream>
using namespace std;

void buildTree(int *a, int *tree, int startIndex, int endIndex, int treeNodeIndex) {

    if(startIndex == endIndex) {
        tree[treeNodeIndex] = a[startIndex];
        return;
    }

    int mid = (startIndex+endIndex)/2;

    buildTree(a, tree, startIndex, mid, 2*treeNodeIndex);
    buildTree(a, tree, mid+1, endIndex, 2*treeNodeIndex+1);

    tree[treeNodeIndex] = tree[2*treeNodeIndex] + tree[2*treeNodeIndex+1];

    
}

int query(int *tree, int startIndex, int endIndex, int treeNodeIndex, int left, int right) {

    //completely outside the range

    if(startIndex > right || endIndex < left) {
        return 0;
    }

    //completely inside

    if(startIndex >= left && endIndex <= right){
        return tree[treeNodeIndex];
    }

    //partially inside
    int mid = (startIndex+endIndex)/2;
    int ans1 = query(tree, startIndex, mid, 2*treeNodeIndex, left, right);
    int ans2 = query(tree, mid+1, endIndex, 2*treeNodeIndex+1, left, right);

    return ans1+ans2;
}

void updateTree(int *a, int *tree, int startIndex, int endIndex, int treeNodeIndex, int idx, int value) {

    if(startIndex == endIndex) {
        a[idx] = value;
        tree[treeNodeIndex] = value;
        return;
    }

    int mid = (startIndex + endIndex)/2;

    if(idx > mid) {
       updateTree(a, tree, mid+1, endIndex, 2*treeNodeIndex+1, idx, value);
    } else {
       updateTree(a, tree, startIndex, mid, 2*treeNodeIndex, idx, value);
    }

    tree[treeNodeIndex] = tree[2*treeNodeIndex] + tree[2*treeNodeIndex];
}

int main() {
    int n;
    cin >> n;
    int *a = new int[n];
    for(int i = 0;i<n;i++) {
        cin >> a[i];
    }

    int *tree = new int[2*n];

    buildTree(a, tree, 0, n-1, 1);

    for(int i = 1;i<2*n;i++) {
        cout << tree[i] << " ";
    }
    cout << endl;

    int t;
    cin >> t;
    while(t--) {
        //Queries and updation
    }


    delete [] a;
    delete [] tree;
    return 0;
}