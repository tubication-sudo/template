#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair <ll, ll>
#define pli pair <ll, int>
#define pil pair <int, ll>

#define fi first
#define se second

const ll inf = 1e18;

int n, m, u, v;
ll w, dist[100001];
vector <pll> adj[100001];

void dijkstra(int s) {
    for (int i = 1; i <= n; i++) dist[i] = inf;

    vector <bool> mark(n + 1, false);
    priority_queue <pli, vector <pli>, greater <pli>> pq;
    dist[s] = 0; pq.push({dist[s], s});

    while (!pq.empty()) {
        pli node = pq.top(); pq.pop();
        int u = node.se;

        if (mark[u]) continue;
        mark[u] = true;

        for (pil tmp: adj[u]) {
            if (dist[tmp.fi] > dist[u] + tmp.se) {
                dist[tmp.fi] = dist[u] + tmp.se;
                pq.push({dist[tmp.fi], tmp.fi});
            }
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    dijkstra(n);

}