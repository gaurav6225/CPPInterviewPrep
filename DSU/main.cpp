#include "bits/stdc++.h";

using namespace std;

class DSU {
private:
    int n;
    vector<int> leader;
    vector<int> group_count;
public:
    DSU(int n) {
        this->n = n;
        leader = vector<int> (n);
        group_count = vector<int> (n);
        for(int i=0;i<n;i++) {
            leader[i] = i;
            group_count[i] = 1;
        }
    }

    int find(int u) {
        if(leader[u] == u) return u;
        return (leader[u] = find(leader[u]));
    }

    void union_set(int u, int v) {
        int pu = find(u);
        int pv = find(v);
        if(pu == pv) return;
        if(group_count[pu] < group_count[pv]) {
            int temp = pu;
            pu = pv; pv = temp;
        }
        leader[pv] = pu;
        group_count[pu] += group_count[pv];
        return;
    }

};


int main() {
    std::cout << "DSU!" << std::endl;
    return 0;
}
