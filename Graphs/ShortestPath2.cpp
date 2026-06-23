#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

/*
CONCEPT:
Use Floyd-Warshall to compute all-pairs shortest paths.
Answer each query directly from the precomputed distance matrix.
*/

using ll = long long;
const ll INF = 1e18;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<ll>> dis(n + 1, vector<ll>(n + 1, INF));

    for (int i = 1; i <= n; i++)
        dis[i][i] = 0;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;

        dis[u][v] = min(dis[u][v], w);
        dis[v][u] = min(dis[v][u], w);
    }

    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (dis[i][k] == INF || dis[k][j] == INF)
                    continue;
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }

    while (q--)
    {
        int u, v;
        cin >> u >> v;

        cout << (dis[u][v] == INF ? -1 : dis[u][v]) << '\n';
    }
}