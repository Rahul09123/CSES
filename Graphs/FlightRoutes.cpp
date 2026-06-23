/*
CSES - Flight Routes (K Shortest Paths)

Problem:
Find the K shortest paths from 1 -> N.

Why normal Dijkstra fails?
Normal Dijkstra stores only ONE best distance per node.
Here we need the first K best distances.

Key Observation:
In a min-heap:
    1st time node is popped -> shortest path
    2nd time node is popped -> 2nd shortest path
    ...
    Kth time node is popped -> Kth shortest path

Idea:
For every node u:
    dist[u] = vector storing K shortest distances.

Algorithm:
1. Push (0,1) into min heap.
2. Pop (d,u).
3. If u already has K distances:
       continue.
4. Store d in dist[u].
5. Push all neighbors.

Why does this work?
Heap always gives the globally smallest available path.
Therefore distances are inserted into dist[u]
in increasing order automatically.

Stopping Condition:
If dist[u].size() == K:
    Ignore future occurrences of u.

Answer:
dist[n][0 ... K-1]

Complexity:
O(K * M * log(KM))

Memory:
O(K * N)

Mental Model:
Normal Dijkstra:
    Each node can be processed once.

K-Shortest Dijkstra:
    Each node can be processed K times.
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<ll,int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n , m , k;
    cin >> n  >> m >> k;
    // <cost,v>
    vector<vector<pii>>adj(n+1);

    for(int i = 0 ;i < m ; i++){
        ll u, v , w;
        cin >> u >> v >> w;
        adj[u].push_back({w,v}); // directed graph
    }
    // Concept: Since dijkstra only finds the shortest path from source but
    // we need to store the shortest k path for a nodes so we need to modify it.

    // We maintain a 2d array for each node which stores the k shortest distance for node u.
    // It always guarantee that after we fill the array with the k smallest distances 
    // we will not find the shortest one as we are using min-heap so we just continue to next node 
    
    priority_queue<pii,vector<pii>,greater<pii>>pq;
    vector<vector<ll>>dis(n+1);
    ll src = 1;
    pq.push({0,1});

    while(!pq.empty()){
        auto [d,u] = pq.top(); pq.pop();

        if(dis[u].size() >= k) continue; // we found the k smallest distances for the node 'u'
        dis[u].push_back(d); // push this distance to the node u.

        for(auto [wt, v] : adj[u]){
            ll distance = wt + d;
            pq.push({distance,v});
        }
    }

    for(int i = 0 ;i < dis[n].size() ; i++){
        cout << dis[n][i] << " ";
    }
    cout<< endl;
    
    return 0;
}