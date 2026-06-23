#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

/*
CONCEPT:
Detect a cycle in an undirected graph using DFS and parent tracking.
When a visited neighbor is not the parent, reconstruct the cycle path.
*/

// Stores the edge that detected the cycle:
// cycleStart <-- ... <-- cycleEnd
int cycleStart = 0, cycleEnd = 0;

/*
DFS for cycle detection in an UNDIRECTED graph

Observation:
In an undirected graph, a cycle exists if we reach an already
visited node that is NOT our parent.

Example:

1 -- 2
|    |
4 -- 3

While exploring 4, if we see 1 again and 1 is not parent,
then a cycle exists.
*/
bool dfs(int src,
         vector<vector<int>>& adj,
         vector<bool>& vis,
         vector<int>& par,
         int parent)
{
    vis[src] = true;

    for(auto& v : adj[src])
    {
        // Tree edge
        if(!vis[v])
        {
            par[v] = src;

            if(dfs(v, adj, vis, par, src))
                return true;
        }

        // Back edge in undirected graph
        // v is already visited and is not the node
        // from which we entered src
        else if(v != parent)
        {
            cycleStart = v;
            cycleEnd = src;
            return true;
        }
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Adjacency list
    vector<vector<int>> adj(n + 1);

    // Undirected graph
    for(int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> vis(n + 1, false);

    /*
    parent[x] = node from which x was reached

    Needed later for reconstructing the cycle.
    */
    vector<int> par(n + 1, -1);

    bool cycleFound = false;

    // Graph may be disconnected
    for(int i = 1; i <= n; i++)
    {
        if(!vis[i])
        {
            if(dfs(i, adj, vis, par, -1))
            {
                cycleFound = true;
                break;
            }
        }
    }

    if(cycleFound)
    {
        vector<int> cycle;

        /*
        Reconstruction idea:

        Suppose DFS found:

        cycleStart = 2
        cycleEnd   = 5

        Parent chain:

        5 <- 4 <- 3 <- 2

        Then cycle is:

        2 -> 3 -> 4 -> 5 -> 2
        */

        int curr = cycleEnd;

        // Add first occurrence of cycle start
        cycle.push_back(cycleStart);

        // Walk backwards using parent array
        while(curr != cycleStart)
        {
            cycle.push_back(curr);
            curr = par[curr];
        }

        // Close the cycle
        cycle.push_back(cycleStart);

        // Reverse because we built it backwards
        reverse(cycle.begin(), cycle.end());

        cout << cycle.size() << '\n';

        for(auto& city : cycle)
            cout << city << " ";
    }
    else
    {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}