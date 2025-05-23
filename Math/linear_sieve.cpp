#include <bits/stdc++.h>
using namespace std;

#define file(name)  if (fopen(name".inp", "r")) { freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout); }
#define synchronize {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}

#define ll long long
#define pii pair <int, int>

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

vector<int> min_prime, primes;

void linear_sieve(int n){
    min_prime.assign(n + 1, 0);

    for (int i = 2; i <= n; ++i) {
        if (min_prime[i] == 0) {
            min_prime[i] = i;
            primes.push_back(i);
        }
        for (int j = 0; i * primes[j] <= n; ++j) {
            min_prime[i * primes[j]] = primes[j];
            if (primes[j] == min_prime[i]) {
                break;
            }
        }
    }
}

int main() {
}