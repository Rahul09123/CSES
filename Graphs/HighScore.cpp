#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

/*
CONCEPT:
Run Bellman-Ford for maximum path score instead of minimum distance.
If a positive cycle can still affect the path from 1 to n, the answer is -1.
*/

using ll = long long;
class Edge{
public:
    ll u , v, wt;
    Edge(ll u ,ll v ,ll wt){
        this->u = u;
        this->v = v;
        this->wt = wt;
    }
};

const ll INF = 1e18;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // input
    int n , m;
    cin >> n >> m;

    vector<Edge>edges;
    for(int i = 0 ;i < m ;i++){
        ll u , v , wt;
        cin >> u >> v >>wt;
        edges.emplace_back(Edge(u,v,wt));
    }
    
    // since the edges weights can be -ve so we cna't use dijkstra
    // We try to use bellman ford as we want to maximize the score from 1 .. n
    // Also the relaxation condition changes as we want to maximize the scores
    // dis[v] < dis[u] + wt -> then we relax
    // To make answer -1, both 1 and n should be the path of cycle and they are getting relaxed

    // Bellman ford says-> relax all edges v-1 times
    vector<ll>dis(n+1,-INF);
    int src = 1;
    dis[src] = 0;
    for(int i = 0 ;i < n - 1 ;i++){
        for(auto e : edges){
            if(dis[e.u] != -INF && dis[e.v] < dis[e.u] + e.wt){
                dis[e.v] = dis[e.u] + e.wt;
            }
        }
    }
    // we again check if we can relax one more time
    // Mark the nodes which still can be relaxed
    set<int>cycle_nodes;

    for(auto e : edges){
        if(dis[e.u] != -INF && dis[e.v] < dis[e.u] + e.wt){
            dis[e.v] = dis[e.u] + e.wt;
            cycle_nodes.insert(e.v);
        }
    }
    // if the cycle is part of the 1...n path then we can't maximize it as max will be INF
    // first finding the nodes that we can reach from 1 to the cycle then cycle to n

    // Better approach to check this is
    // Reverse the graph and then we simply run bfs/dfs from the nth node.
    // if it reaches one of the cycle nodes then we can say cycle is reached from node.

    // Running bfs from 1 
    vector<vector<int>>adj(n+1);
    for(int i = 0 ;i < m ; i++){
        adj[edges[i].u].push_back(edges[i].v);
    }

    vector<bool>vis1(n+1,false),vis2(n+1,false);
    queue<int>q , cycle_q;
    q.push(1);
    vis1[1] = true;

    while(!q.empty()){
        int x = q.front(); q.pop();

        if(cycle_nodes.count(x)){
            cycle_q.push(x);
            vis2[x] = true;
        }
        for(auto v : adj[x]){
            if(!vis1[v]){
                q.push(v);
                vis1[v] = true;
            }
        }
    }
    //now running the bfs from the cycle nodes to n
    bool is_cycle_n = false;
    while(!cycle_q.empty()){
        int x = cycle_q.front(); cycle_q.pop();

        if(x == n){
            is_cycle_n = true;
            break;
        }
        for(auto v : adj[x]){
            if(!vis2[v]){
                cycle_q.push(v);
                vis2[v] = true;
            }
        }
    }
    if(is_cycle_n){
        cout << -1 <<endl;
    }else{
        cout << dis[n] <<endl;
    }
    return 0;
}