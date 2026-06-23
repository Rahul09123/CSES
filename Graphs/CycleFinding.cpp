/*
CSES - Cycle Finding

Goal:
Find ANY negative weight cycle in a directed graph.

Key Observation:
Bellman-Ford normally finds cycles reachable from a source.
Here cycle can be in ANY component.

Trick:
Initialize all distances to 0.
Equivalent to adding a super source connected to every node.

Bellman Ford:
1. Relax all edges N times.
2. Reset x = -1 before every iteration.
3. If some node gets relaxed in the Nth iteration:
      => Negative cycle exists.
      => Store last relaxed node in x.

Why move x back N times?
x may not lie on the cycle.
It may only be affected by the cycle.

Cycle Reconstruction:
1. Move x = parent[x] N times.
      => Guaranteed to enter the cycle.
2. Start from x and keep following parent[]
   until x appears again.

Template:

x = -1

for i = 1..N:
    x = -1
    relax all edges
    if relaxed:
        x = relaxed vertex

if x == -1:
    No cycle

for i = 1..N:
    x = parent[x]

cycle_start = x

Complexity:
O(N*M)

Memory Trick:
"Nth relaxation => cycle exists"
"Move N parents => enter cycle"
*/




#include <bits/stdc++.h>
using namespace std;

/*
Advance Bellman ford to detect the -ve cycle in the graph withe the cycle length
    1. In this problem we are only concerned about the -ve cycle not relaxing the edges
    We try to create a super node 0 that connects all the other nodes .
    2. We use distance array and initialze it to 0 as cycle can start with any of the node.
    3. We are using the relaxant array to find the start of the cycle 
     2 cases
        1.node is part of cycle. 
        2. node not part of cycle but got relaxed
*/

using ll = long long;
using Edge = tuple<ll , ll , ll>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //input
    ll n , m;
    cin >> n >> m;

    vector<Edge>edges;
    // (u,v,wt)
    for(int i = 0 ;i < m ;i++){
        ll u, v , wt;
        cin >> u >> v >> wt;
        edges.push_back(Edge(u,v,wt));
    }

    // Now we are only concerned about finding the cycle not the distance
    vector<ll>dis(n+1,0);
    vector<ll>realxant(n+1,-1); // no one is realxing any other node, it is simlar to finding the parent

    ll x;
    for(int i = 0 ;i < n ;i++){
        x = -1; // storing the node which got relaxed due to the -ve cycle
        // this needs to be reset after every iteration as for the n't iteration we need to check
        // if there is a cycle or not
        for(auto e : edges){
            auto [u ,v , w] = e;
            if(dis[u] + w < dis[v]){
                dis[v] = dis[u] + w;
                realxant[v] = u; // the v got relaxed by u
                x = v; // this node can be the starting node of cycle
            }
        }
    }
    if(x == -1){ // no edge got relaxed, there is no -ve cycle
        cout << "NO" << endl;
        return 0;
    }

    // move x back atmost x times so that it reaches the cycle
    for(int i = 0 ; i < n; i++){
        x = realxant[x];
    }

    vector<ll>cycle;
    for(ll curr = x ; ; curr = realxant[curr]){
        cycle.push_back(curr);
        if(curr == x && cycle.size() > 1){
            break;
        }
    }
    reverse(cycle.begin(),cycle.end());

    cout<<"YES"<<endl;
    for(auto node : cycle){
        cout << node <<" ";
    }
    cout << '\n';


    return 0;
}