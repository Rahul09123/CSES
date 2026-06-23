#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

/*
CONCEPT:
Count the number of routes in a DAG using dynamic programming over topological order.
Each node contributes its path count to its outgoing neighbors, modulo 1e9+7.
*/


/*
SIMILAR PROBLEM TO LONGEST FLIGHT ROUTE
 Only change is in dp state dp[i] = number of ways to go from 1 to n 
 number of ways to reach dp[v] = dp[u] + dp[v] 
*/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // dp[i] = number of ways to go from 1 to n
    const long long int mod = 1e9 + 7;
    // input
    int n , m;
    cin >> n >> m;
    vector<vector<int>>adj(n+1);
    for(int i = 0 ;i < m ; i++){
        int u , v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    // find the toposort (using kahn's algorithm)
    vector<int>indeg(n+1,0);
    for(int i = 1 ;i <= n ;i++){
        for(auto v : adj[i]){
            indeg[v]++;
        }
    }
    // Apply bfs first pushing all the nodes having indeg == 0
    queue<int>q;
    for(int i = 1 ;i <=n ;i++){
        if(indeg[i] == 0){
            q.push(i);
        }
    } 
    vector<int>topo;  
    while(!q.empty()){
        auto u = q.front(); q.pop();
        topo.push_back(u);

        for(auto v : adj[u]){
            indeg[v]--;
            if(indeg[v] == 0){
                q.push(v);
            }
        }
    }
    vector<long long>dp(n+1,0);
    dp[1] = 1; // 1 way to reach 1 -> 1
    for(int i = 0 ; i < topo.size(); i++){
        int u = topo[i];
        for(auto v : adj[u]){
            dp[v] = (dp[u] + dp[v])%mod; // only change
        }
    }
    cout << dp[n] << endl;
    return 0;
}