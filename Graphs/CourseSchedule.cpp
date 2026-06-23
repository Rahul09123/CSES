#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

/*
CONCEPT:
Use Kahn's algorithm for topological sorting in a directed graph.
If all nodes are not processed, the graph contains a cycle and the schedule is impossible.
*/

using ll = long long;
using pii = pair<ll,ll>;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    ll n , m;
    cin >> n >> m;

    vector<vector<ll>>adj(n+1);

    for(int i = 0 ; i < m ; i++){
        ll u , v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    // Using Kahn's Algo
    vector<ll>indeg(n+1,0);
    for(int i = 1 ;i <= n ;i++){
        for(auto v : adj[i]){
            indeg[v]++;
        }
    }
    // Apply bfs first pushing all the nodes having indeg == 0
    queue<ll>q;
    for(int i = 1 ;i <=n ;i++){
        if(indeg[i] == 0){
            q.push(i);
        }
    } 
    vector<ll>ans;  
    while(!q.empty()){
        auto u = q.front(); q.pop();
        ans.push_back(u);

        for(auto v : adj[u]){
            indeg[v]--;
            if(indeg[v] == 0){
                q.push(v);
            }
        }
    }
    if(ans.size() != n){
        cout << "IMPOSSIBLE" << endl;
    }
    else{
        for(auto x : ans){
            cout << x << " ";
        }
    }
    cout << endl;
    return 0;
}