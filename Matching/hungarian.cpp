#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define file(name)  if (fopen(name".inp", "r")) { freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout); }
#define synchronize {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}

#define ll long long
#define pii pair <int, int>
#define pll pair <ll, ll>

#define fi first
#define se second

template<class X, class Y>
    bool maximize(X &x, const Y &y) {
        if (x < y) {
            x = y;
            return true;
        }
        else return false;
    }

template <class X, class Y>
    bool minimize(X &x, Y y) {
        if (x > y) {
            x = y;
            return true;
        }
        return false;
    }   

const int nmax = 3e5 + 5;
const ll mod = 1e9 + 7;
const ll inf = 1e18;

struct matrix {
    vector<vector<ll>> mat;

    int row() const { return mat.size(); }
    int col() const { return mat[0].size(); }

    auto& operator[](int i) { return mat[i]; }
    const auto& operator[](int i) const { return mat[i]; }

    matrix() = default;
    matrix(int n, int m) : mat(n, vector<ll>(m)) {}
    matrix(const vector<vector<ll>>& v) : mat(v) {}

    static matrix identity(int n) {
        matrix ans(n, n);
        for (int i = 0; i < n; i++) ans[i][i] = 1;
        return ans;
    }

    matrix operator+(const matrix& B) const {
        matrix A = *this;
        assert(A.col() == B.col());
        assert(A.row() == B.row());
        matrix ans(A.row(), A.col());

        for (int i = 0; i < A.row(); i++) {
            for (int j = 0; j < A.col(); j++) {
                ans[i][j] = (A[i][j] + B[i][j]) % mod;
            }
        }

        return ans;
    }

    matrix operator*(const matrix& B) const {
        matrix A = *this;
        assert(A.col() == B.row());
        matrix ans(A.row(), B.col());

        for (int i = 0; i < A.row(); i++) {
            for (int j = 0; j < B.col(); j++) {
                for (int k = 0; k < A.col(); k++) {
                    ans[i][j] = (ans[i][j] + (A[i][k] * B[k][j]) % mod) % mod;
                }
            }
        }

        return ans;
    }

    bool operator==(const matrix& B) const {
        const matrix& A = *this;

        if (A.col() != B.col()) return false;
        if (A.row() != B.row()) return false;

        for (int i = 0; i < A.row(); i++) {
            for (int j = 0; j < A.col(); j++) {
                if (A[i][j] != B[i][j]) return false;
            }
        }

        return true;
    }

    bool operator!=(const matrix& B) const {
        return !(*this == B);
    }

    matrix power(ll k) const {
        assert(row() == col());

        matrix base = *this;
        matrix ans = identity(row());
        if (k == 0) return ans;

        while (k > 0) {
            if (k & 1) ans = ans * base;
            base = base * base;
            k >>= 1;
        }

        return ans;
    }

    friend ostream& operator<<(ostream& out, const matrix& d) {
        for (const auto& x : d.mat) {
            for (const auto& y : x) out << y << ' ';
            out << '\n';
        }
        return out;
    }
};

ll hungarian_min(matrix A) {
    assert(A.row() == A.col());
    int n = A.row();
    vector<ll> u(n + 1, 0), v(n + 1, 0), p(n + 1, 0), way(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        p[0] = i;
        vector<ll> minv(n + 1, inf);
        vector<bool> used(n + 1, false);
        int j0 = 0;

        do {
            used[j0] = true;
            int i0 = p[j0];
            ll delta = inf;
            int j1 = 0;

            for (int j = 1; j <= n; j++) {
                if (!used[j]) {
                    ll cur = A[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }

            for (int j = 0; j <= n; j++) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }

            j0 = j1;
        } while (p[j0] != 0);

        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    return -v[0];
}

ll hungarian_max(matrix A) {
    int n = A.row();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] *= -1;
        }
    }

    return -hungarian_min(A);
}

int main() {
}