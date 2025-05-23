#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair <ll, ll>

#define fi first
#define se second

const ll mod = 1e9 + 7;

ll n;
ll cnt, lim, pre;
deque <deque <pii>> dq;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
vector <ll> a, lis, sum;

ll cal_lis(vector<ll> &a){
    vector<ll> b;
    for (ll i = 0; i < a.size(); i++) {
        auto it = lower_bound(b.begin(), b.end(), a[i]);
        lis[i] = (ll)(it - b.begin()) + 1;
        if (it == b.end()) b.push_back(a[i]);
        else *it = a[i];
    }
    return b.size();
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    a.resize(n); lis.resize(n);

    for (auto &x: a) cin >> x;
    lim = cal_lis(a);
    sum.resize(lim + 1);

    dq.resize(lim + 1);
    dq[0].push_back({0, 1});
    sum[0] = 1;

    for (ll i = 0; i < n; i++){
        while (!dq[lis[i] - 1].empty() && dq[lis[i] - 1].front().fi >= a[i]) {
                sum[lis[i] - 1] -= dq[lis[i] - 1].front().se;
                sum[lis[i] - 1] = (sum[lis[i] - 1] + mod) % mod;
                dq[lis[i] - 1].pop_front();
            }
            dq[lis[i]].push_back({a[i], sum[lis[i] - 1]});
            sum[lis[i]] += sum[lis[i] - 1];
            sum[lis[i]] %= mod;
    }
    cout << sum[lim];
}