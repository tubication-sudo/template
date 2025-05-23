#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll mod = 1e9 + 7;

struct matrix {
    vector<vector<ll>> mat;

    int row() const { return mat.size(); }
    int col() const { return mat[0].size(); }

    auto& operator[](int i) { return mat[i]; }
    const auto& operator[](int i) const { return mat[i]; }

    matrix() = default;
    matrix(int n, int m) : mat(n, vector<ll>(m)) {}
    matrix(const vector<vector<ll>> &v): mat(v) {}

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
