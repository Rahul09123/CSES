#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<long long,long long>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n , m;
    cin >> n >> m;

    vector<vector<pii>>adj(n+1);
    for(int i = 0 ;i < m ;i++){
        ll u , v , w;
        cin >> u >> v  >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    // find the mst using Prim's Algoritm
    vector<ll>mstSet(n+1,0);
    int src = 1;
    priority_queue<pii,vector<pii>,greater<pii>>pq;

    pq.push({0,src});
    ll cost = 0;
    while(!pq.empty()){
        auto [wt, u] = pq.top(); pq.pop();
        // if(mstSet[u]) continue; // this node is already in our set we simply skip this
        if(mstSet[u] == 0){
            cost += wt;
            mstSet[u] = true;
        }
        for(auto [v,w] : adj[u]){
            if(mstSet[v] == 0) pq.push({w,v});
        }
    }
    for(int i = 1 ;i <= n ;i++){
        if(!mstSet[i]){
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }
    cout << cost << endl;
    return 0;
}