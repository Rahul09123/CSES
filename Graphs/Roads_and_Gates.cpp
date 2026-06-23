#include <bits/stdc++.h>
using namespace std;



// Decompose the pair wise weights into the virtual nodes
#include <bits/stdc++.h>
using namespace std;

/*
CONCEPT:
Use virtual nodes to transform pair-wise connection costs into a shortest path graph.
After modeling the extra states, run Dijkstra on the expanded graph.
*/

// Decompose the pair wise weights into the virtual nodes
using ll = long long;
using pii = pair<ll,ll>;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // input
    ll n , m, y;
    cin >> n >> m >> y;
    // we are adding 2 dummy nodes as ws and wt 
    vector<vector<pii>>adj(n+3);
    for(int i = 0; i < m ;i++){
        ll u , v , t;
        cin >> u >> v >> t;
        adj[u].push_back({v,t});
        adj[v].push_back({u,t});
    }
    vector<ll>x(n+1);
    for(int i = 1 ;i <= n ;i++){
        cin >> x[i];
    }
    ll WS = n+1;
    ll WT = n+2;

    for(int i = 1 ;i <= n; i++){
        adj[i].push_back({WS,x[i]});
        adj[WT].push_back({i,x[i]});
    }
    // connection between ws and wt
    adj[WS].push_back({WT,y});
    // applying dijkstra's
     // dis[v][s] travel to city v using either of the 2 states
    vector<ll>dis(n+3,LLONG_MAX);
    priority_queue<pii,vector<pii>,greater<pii>>pq;

    int src = 1;
    dis[src] = 0;
    pq.push({0,src});
    while(!pq.empty()){
        auto [d,u] = pq.top(); pq.pop();
        if(d != dis[u]) continue;
        for(auto [v,wt] : adj[u]){
            if(dis[u] != LLONG_MAX && dis[u] + wt < dis[v]){
                dis[v] = dis[u] + wt;
                pq.push({dis[v],v});
            } 
        }
    }
    // print the answer
    for(int i = 2 ;i <= n ; i++){
        cout << dis[i] << " ";
    }
    cout << endl;



    return 0;
}