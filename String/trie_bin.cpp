#include <bits/stdc++.h>
using namespace std;

#define ll long long


struct Trie{
    const int lg = 31;

    struct Node{
        int child[2];
        int exist, cnt;
        
        Node() {
            child[0] = child[1] = -1;
            exist = cnt = 0;
        }
    };

    int cur, sz;
    vector <Node> nodes;

    Trie() : cur(0) {
        nodes.resize(1);
        nodes[0] = Node();
    };

    int new_node() {
        cur++;
        if (cur + 1 > nodes.size()) nodes.push_back(Node());
        nodes[cur] = Node();
        return cur;
    }

    void add_number(int x) {
        int pos = 0; sz++;
        for (int i = lg; i >= 0; i--) {
            int c = (x >> i) & 1;
            if (nodes[pos].child[c] == -1) nodes[pos].child[c] = new_node();
            pos = nodes[pos].child[c];
            nodes[pos].cnt++;
        }
        nodes[pos].exist++;
    }

    void delete_number(int x) {
        if (find_number(x) == false) return;
        int pos = 0; sz--;
        for (int i = lg; i >= 0; i--) {
            int c = (x >> i) & 1;

            int tmp = nodes[pos].child[c];
            nodes[tmp].cnt--;
            if (nodes[tmp].cnt == 0) {
                nodes[pos].child[c] = -1;
                return;
            }

            pos = tmp;
        }
        nodes[pos].exist--;
    }

    bool find_number(int x) {
        int pos = 0;
        for (int i = lg; i >= 0; i--) {
            int c = (x & (1 << i) ? 1 : 0);
            if (nodes[pos].child[c] == -1) return false;
            pos = nodes[pos].child[c];
        }
        return (nodes[pos].exist != 0);
    }

    int cal_max(int x) {
        int pos = 0, ans = 0;
        for (int i = lg; i >= 0; i--) {
            int c = (x & (1 << i) ? 1 : 0);
            if (nodes[pos].child[1 - c] != -1) {
                ans += (1 << i);
                pos = nodes[pos].child[1 - c];
            }
            else if (nodes[pos].child[c] != -1) pos = nodes[pos].child[c];
            else return -1;
        }
        return ans;
    }

    int min_k(int k) {
        if (k > sz) return -1;

        int pos = 0, ans = 0;
        for (int i = lg; i >= 0; i--) {
            int zero_cnt = (nodes[pos].child[0] != -1) ? nodes[nodes[pos].child[0]].cnt : 0;
            
            if (zero_cnt >= k) pos = nodes[pos].child[0];
            else {
                k -= zero_cnt;
                pos = nodes[pos].child[1];
                ans |= (1 << i);
            }
        }

        return ans;
    }
};

int n, q, x;
int ans = 0;
Trie tr;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> q >> x;
        if (q == 1) tr.add_number(x);
        else cout << tr.min_k(x) << '\n';
    }
}