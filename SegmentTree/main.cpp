#include "bits/stdc++.h"

using namespace std;

// Segment Tree to get the maximum value in a given range while allowing point updates in an array
class SegmentTree {
private:
    vector<int> t;
    int n;

    void build(vector<int>& a, int v, int tl, int tr) {
        if(tl == tr) {
            t[v] = a[tl];
        } else {
            int mid = (tl + tr) / 2;
            build(a, 2*v, tl, mid);
            build(a, 2*v+1, mid+1, tr);
            t[v] = max(t[2*v], t[2*v+1]);
        }
    }

    int maxQuery(int v, int tl, int tr, int l, int r) {
        int mid = (tl + tr) / 2;
        if(tl==l && tr==r) {
            return t[v];
        } else if(r <= mid) {
            return maxQuery(2*v, tl, mid, l, r);
        } else if(l > mid) {
            return maxQuery(2*v+1, mid+1, tr, l, r);
        } else {
            int leftMax = maxQuery(2*v, tl, mid, l, mid);
            int rightMax = maxQuery(2*v+1, mid+1, tr, mid+1, r);
            return max(leftMax, rightMax);
        }
    }

    void pointUpdate(int v, int tl, int tr, int i, int val) {
        if(tl == tr) {
            t[v] = val;
        } else {
            int mid = (tl + tr) / 2;
            if (i <= mid)
                pointUpdate(2*v, tl, mid, i, val);
            else
                pointUpdate(2*v+1, mid+1, tr, i, val);
            t[v] = max(t[2*v], t[2*v+1]);
        }
    }
public:
    SegmentTree(int n) {
        this->n = n;
        t = vector<int> (4*n);
    }
    SegmentTree(vector<int>& a, int n) {
        this->n = n;
        t = vector<int> (4*n);
        build(a, 1, 0, n-1);
    }

    int getMax(int l, int r) {
        return maxQuery(1, 0, n-1, l, r);
    }

    // Update the value at the specified index with the given new value
    void update(int i, int val) {
        return pointUpdate(1, 0, n-1, i, val);
    }

};


int main() {

    int n;
    cout <<"Enter the maximum size of the array\n";
    cin >>n;
    cout <<"Enter the array elements\n";
    vector<int> a(n);
    for(int i=0; i<n; i++) {
        cin >> a[i];
    }
    cout <<'\n';

    SegmentTree segTree(a, n);

    int option,l,r,index,val;
    while(1) {
        cout <<"Choose one of the below options\n";
        cout <<"Option-1 : Range Query to get the maximum value\n";
        cout <<"Option-2 : Point Update to update the array with the given new value\n";
        cin >>option;
        if(option == 1) {
            cout <<"Enter the range l and r \n";
            cin >>l >>r;
            if(l<0 || l>=n || r<0 || r>=n || l>r ) {
                cout <<"Invalid range provided \n";
                continue;
            }
            int mx = segTree.getMax(l, r);
            cout <<"Max value in the provided range is :" <<mx <<endl;
        } else if(option == 2) {
            cout <<"Enter the index and value to be updated \n";
            cin >>index >> val;
            if(index<0 || index >= n) {
                cout <<"Invalid index provided \n";
                continue;
            }
            segTree.update(index, val);
            cout <<"Value updated successfully \n";
        } else {
            cout <<"Invalid Option selected\n";
        }
    }
    return 0;
}
