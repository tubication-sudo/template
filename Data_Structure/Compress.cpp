#include <bits/stdc++.h>
using namespace std;

template <class type>
struct Compress {
    vector<type> c;
    void compress() {
        sort(c.begin(), c.end());
        c.erase(unique(c.begin(), c.end()), c.end());
    }
    void add(type x) { c.push_back(x); }
    int operator[](type x) const { return lower_bound(c.begin(), c.end(), x) - c.begin() + 1; }
    int size() const { return c.size(); }
};

int main() {
    
}