#include "bits/stdc++.h"

using namespace std;

class LazyPropagation {
private:
    int n;
    vector<int> t;

    void build(vector<int>& a, int v, int tl, int tr) {
        if(tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, 2*v, tl, tm);
            build(a, 2*v+1, tm+1, tr);
            t[v] = 0;
        }
    }
    // point query
    int getPointQuery(int v, int tl, int tr, int pos) {
        if(tl == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        if(pos <= tm) {
            return t[v] + getPointQuery(2*v, tl, tm, pos);
        } else {
            return t[v] + getPointQuery(2*v+1, tm+1, tr, pos);
        }
    }
    // range update
    void lazyUpdate(int v, int tl, int tr, int l, int r, int add) {
        if(l > r) return;
        if(tl==l && tr==r){
            t[v] += add;
        } else {
            int tm = (tl + tr) / 2;
            lazyUpdate(2*v, tl, tm, l, min(tm, r), add);
            lazyUpdate(2*v+1, tm+1, tr, max(tm+1,l), r, add);
        }
    }
public:
    LazyPropagation(int n) {
        this->n = n;
        t = vector<int> (4*n);
    }
    LazyPropagation(vector<int>& a, int n) {
        this->n = n;
        t = vector<int> (4*n);
        build(a, 1, 0, n-1);
    }

    int getValue(int i) {
        return getPointQuery(1, 0, n-1, i);
    }
    // add to all elements in the range
    void update(int l, int r, int add) {
        lazyUpdate(1, 0, n-1, l, r, add);
        return;
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

    LazyPropagation lazyProp(a, n);

    int option,l,r,index,add;
    while(1) {
        cout <<"Choose one of the below options\n";
        cout <<"Option-1 : point Query to get the value\n";
        cout <<"Option-2 : Range Update to increment all the elements in the specified range \n";
        cin >>option;
        if(option == 1) {
            cout <<"Enter the index to get the value \n";
            cin >>index;
            if(index<0 || index >= n) {
                cout <<"Invalid index provided \n";
                continue;
            }
            int mx = lazyProp.getValue(index);
            cout <<"Max value in the provided range is :" <<mx <<endl;
        } else if(option == 2) {
            cout <<"Enter the range l , r and value to be added\n";
            cin >>l >>r >>add;
            if(l<0 || l>=n || r<0 || r>=n || l>r ) {
                cout <<"Invalid range provided \n";
                continue;
            }
            lazyProp.update(l, r, add);
            cout <<"Value updated successfully \n";
        } else {
            cout <<"Invalid Option selected\n";
        }
    }
    return 0;
}
