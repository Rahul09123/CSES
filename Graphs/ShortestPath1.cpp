#include <bits/stdc++.h>
using namespace std;


#include <bits/stdc++.h>
using namespace std;

/*
CONCEPT:
Apply Dijkstra's algorithm for single-source shortest paths on a weighted directed graph.
Use a min-heap to always expand the currently smallest tentative distance.
*/

using pii = pair<long ,long>;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const long int INF = 1e18;
    int n , m;
    cin >> n >> m;

    // shortest parth from 1 to n-1 other cities -> single source shortest path

    // input
    vector<vector<pii>>adj(n+1);
    for(int i = 0 ;i < m ;i++){
        int u ,  v  ,w ;
        cin >> u >> v >> w;
        adj[u].push_back({v,w}); // directed graph
    }

    // min heap (wt,v)
    priority_queue<pii,vector<pii>,greater<pii>>pq;
    vector<long>dis(n+1,INF); //stores the minimum dist
    int src = 1; //source nodes
    dis[src] = 0;
    pq.push({0,src});

    while(!pq.empty()){
        auto [w,u] = pq.top(); pq.pop();

        if(w > dis[u])continue;
        // relax the neighbors
        for(auto x : adj[u]){
            int v = x.first;
            int wt = x.second;
            if(dis[u] + wt < dis[v]){
                dis[v] = dis[u] + wt;
                // this line got me error. inplace of pushing the current shortest dis[v]
                // i pushed the weight
                pq.push({dis[v],v}); //push that node which got relaxed
            }
        }
    }
    for(int i = 1 ; i <= n ;i++){
        cout<<dis[i]<<" ";
    }

    return 0;
}