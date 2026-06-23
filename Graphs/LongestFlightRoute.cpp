/*
=========================================
CSES - Longest Flight Route
=========================================

PROBLEM:
Find the longest path from city 1 to city n
in a Directed Acyclic Graph (DAG).

--------------------------------------------------
KEY OBSERVATION
--------------------------------------------------

Longest Path in a general graph is NP-Hard.

But in a DAG:

    Topological Order exists

and every edge goes:

    earlier -> later

So we can process nodes in topo order and
perform DP relaxation.

--------------------------------------------------
WHY TOPO SORT?
--------------------------------------------------

Suppose:

1 -> 2 -> 4
 \         ^
  \-> 3 ---|

To compute answer for node 4,
answers for nodes 2 and 3 must already be known.

Topo order guarantees:

all parents processed before child.

Hence DP becomes possible.

--------------------------------------------------
DP STATE
--------------------------------------------------

dp[v] = maximum number of vertices
        in a path from 1 to v

Initially:

dp[i] = -1      (unreachable)

dp[1] = 1       (path contains city 1)

--------------------------------------------------
TRANSITION
--------------------------------------------------

For every edge:

u -> v

If u is reachable:

dp[v] = max(dp[v], dp[u] + 1)

Meaning:

If longest path reaches u,
extend it using edge (u,v).

--------------------------------------------------
PARENT ARRAY
--------------------------------------------------

par[v] = node from which best dp[v]
         was obtained.

Whenever:

dp[v] < dp[u] + 1

update:

par[v] = u

Used later for path reconstruction.

--------------------------------------------------
ALGORITHM
--------------------------------------------------

1. Build graph

2. Topological Sort (Kahn's)

3. DP over topo order

4. If dp[n] == -1
      => IMPOSSIBLE

5. Otherwise:
      reconstruct path using parent array

--------------------------------------------------
PATH RECONSTRUCTION
--------------------------------------------------

Start from n:

n -> par[n] -> par[par[n]] ...

until 1

Reverse the obtained sequence.

--------------------------------------------------
TIME COMPLEXITY
--------------------------------------------------

Topological Sort:
O(V + E)

DP Relaxation:
O(E)

Total:
O(V + E)

--------------------------------------------------
SPACE COMPLEXITY
--------------------------------------------------

Adjacency List:
O(V + E)

DP + Parent + Indegree:
O(V)

Total:
O(V + E)

--------------------------------------------------
PATTERN TO REMEMBER
--------------------------------------------------

DAG + Longest Path

=> Topological Sort
=> DP on topo order

Template:

dp[source] = base

for u in topo:
    for v in adj[u]:
        dp[v] = max(dp[v], dp[u] + weight)

--------------------------------------------------
INTERVIEW ONE-LINER
--------------------------------------------------

"Whenever I see a longest path problem in a DAG,
I immediately think Topological Sort + DP."
*/

#include <bits/stdc++.h>
using namespace std;


using ll = long long;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n , m;
    cin >> n >> m;
    vector<vector<ll>>adj(n+1);
    for(int i = 0 ;i < m ;i++){
        ll u , v;
        cin >> u >> v;
        adj[u].push_back(v); // directed graph
    }
    // Why toposort ?
    // applying topo sort to find the order

    // Using Kahn's algo
    vector<ll>indeg(n+1,0);
    for(int i = 1 ; i<= n ;i++){
        for(auto v : adj[i]){
            indeg[v]++;
        }
    }
    // apply bfs
    queue<ll>q;
    for(int i = 1 ;i <= n ;i++){
        if(indeg[i] == 0){
            q.push(i);
        }
    }
    vector<ll>order;
    while(!q.empty()){
        ll u = q.front() ; q.pop();
        order.push_back(u);
        for(auto v : adj[u]){
            indeg[v]--;
            if(indeg[v] == 0){
                q.push(v);
            }
        }
    }

    // then apply dp to order and find the longest path
    vector<ll>dp(n+1,-1);
    // dp[n] = longest path from 1 to n 
    vector<ll>par(n+1,-1); // to store the path
    dp[1] = 1; // 1st city is visited
    // we simply check for every neighbor of u and updates it's longest path from 1 to n.
    for(int i = 0 ; i < order.size() ;i++){
        int u = order[i];
        for(auto v : adj[u]){
            if(dp[u] != -1 && dp[v] < dp[u] + 1){
                dp[v] = dp[u] + 1;
                par[v] = u; // update the parent
            }
        }
    }
    if(dp[n] == -1){
        cout << "IMPOSSIBLE" << endl;
    }
    else{
        cout << dp[n] << endl;
        vector<ll>cycle;
        int curr = n;
        while(curr != 1){
            cycle.push_back(curr);
            curr = par[curr];
        }
        cycle.push_back(curr);
        reverse(cycle.begin(),cycle.end());
        for(auto x : cycle){
            cout << x << " ";
        }
        cout<<endl;
    }
    return 0;
}