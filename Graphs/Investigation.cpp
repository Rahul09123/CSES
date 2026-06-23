/*
==================== CSES Investigation ====================

Goal:
For node n, find:

1. Shortest distance from 1 -> n
2. Number of shortest paths
3. Minimum flights among all shortest paths
4. Maximum flights among all shortest paths

Observation:
- Edge weights are positive.
- Graph may contain cycles.
- Therefore Dijkstra is applicable.

State Definition:

dist[u]      = shortest distance to u
ways[u]      = number of shortest paths to u
minFlight[u] = minimum edges used among shortest paths to u
maxFlight[u] = maximum edges used among shortest paths to u

Transition:

Case 1: Better path found

    dist[u] + w < dist[v]

    => New shortest path discovered.

    dist[v]      = dist[u] + w
    ways[v]      = ways[u]
    minFlight[v] = minFlight[u] + 1
    maxFlight[v] = maxFlight[u] + 1

    Push into pq.

------------------------------------------------------------

Case 2: Another shortest path found

    dist[u] + w == dist[v]

    => Merge information.

    ways[v]      += ways[u]
    minFlight[v] = min(minFlight[v], minFlight[u] + 1)
    maxFlight[v] = max(maxFlight[v], maxFlight[u] + 1)

------------------------------------------------------------

Dijkstra Template:

Pop (d,u)

if (d > dist[u]) continue

Process all outgoing edges.

------------------------------------------------------------

Important Pattern:

BETTER PATH:
    overwrite everything

EQUAL PATH:
    merge information

This pattern appears in many shortest-path problems:
- Counting shortest paths
- Min/max edges on shortest paths
- Number of ways to reach destination
- Restricted shortest path problems

Complexity:
O((N + M) log N)

============================================================
*/

#include <bits/stdc++.h>
using namespace std;


using ll = long long;
using pii = pair<ll,ll>;
const ll INF = 1e18;
const ll mod = 1e9 + 7;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n , m;
    cin >> n >> m;

    vector<vector<pii>>adj(n+1);

    for(int i = 0 ;i < m ;i++){
        ll u, v,wt;
        cin >> u >> v >> wt;

        adj[u].push_back({v,wt});
    }

    // Why toposort will not work? Because the edges have weights and toposort only take care about the dependency
    // it doesn't care about the weights, In question it is also given that the edge weights are positive so we can
    // use dijkstra and it will take care of the dp states while processing the smaller subproblems

    vector<vector<ll>>dp(n+1,vector<ll>(4,INF));
    /*
    dp[i][0] = minimum distance to reach from 1 to i
    dp[i][1] = number of min cost path from 1 to i
    dp[i][2] = min number of flights(edges) of min cost from 1 to i 
    dp[i][3] = max number of flights(edges) of min cost from 1 to i
    */
   dp[1][0] = 0;
   dp[1][1] = 1;
   dp[1][2] = 0;
   dp[1][3] = 0;

   priority_queue<pii,vector<pii>,greater<pii>>pq;
   pq.push({0,1}); // pushing the source weight and node.

   while(!pq.empty()){
    auto [d,u] = pq.top(); pq.pop();

    if(d > dp[u][0]) continue;

    for(auto [v,w] : adj[u]){
        if(d + w < dp[v][0]){ // relax the edge
            dp[v][0] = d + w;
            dp[v][1] = dp[u][1];
            dp[v][2] = dp[u][2] + 1;
            dp[v][3] = dp[u][3] + 1;
            pq.push({dp[v][0],v});
        }
        else if(d+w == dp[v][0]){ // same cost path
            dp[v][1] = (dp[u][1] + dp[v][1])%mod;
            dp[v][2] = min(dp[v][2],dp[u][2] + 1);
            dp[v][3] = max(dp[v][3],dp[u][3] + 1);
        }
    }
   }

   for(int i = 0 ;i < 4 ;i++){
        cout << dp[n][i] << " ";
   }
   cout << endl;




    return 0;
}  