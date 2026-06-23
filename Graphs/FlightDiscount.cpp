#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,ll>;
using tii = tuple<ll,int,int>;

/*
CONCEPT:
GRAPH MODELING: VIRTUAL NODE TRICK

Trigger:
1. Complete graph appears implicitly.
2. Cost(i,j) can be decomposed.
3. O(N²) edges are impossible.

Examples:

Cost(i,j)=A[i]+B[j]
Cost(i,j)=A[i]+C+B[j]

Create virtual nodes representing shared parts.

Example:

i -> VS (A[i])
VS -> VT (C)
VT -> j (B[j])

Then:

i -> VS -> VT -> j

has cost:

A[i]+C+B[j]

Reduces O(N²) edges to O(N).
*/

/*
Main Idea:
(node , state)
(u,0) -> (v,0) weight w 
(u,0) -> (v,1) weight w/2
(u,1) -> (v,1) weight w
Then we run dijkstra
*/

const ll INF = 1e18;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n , m;
    cin >> n >> m;

    vector<vector<pii>>adj(n+1);

    for(int i = 0 ; i < m; i++){
        int u, v;
        ll cost;
        cin >> u >> v >> cost;

        adj[u].push_back({v,cost}); //directed graph
    }

    // we create the distance array with 2 states
    // dis[0][node] = best cost reaching node without using discount
    // dis[1][node] = best cost reaching node after using discount

    vector<vector<ll>>dis(2,vector<ll>(n+1,INF));
    dis[0][1] = 0; // we are at node 1 and we have not used discount

    priority_queue<tii,vector<tii>,greater<tii>>pq; // min heap (cost,node,state)
    pq.push({0,1,0}); // we are node 1 with cost 0 and state 0

    while(!pq.empty()){
        auto [currCost , node , state] = pq.top(); pq.pop();

        if(currCost > dis[state][node])continue;

        for(auto v : adj[node]){ // for all neighbors
            // 2cases 
            // 1. we have not used the discount
            // so we have 2 choices either so don't use the discount or use it
            if(state == 0){
                if(currCost + v.second < dis[0][v.first]){
                    dis[0][v.first] = currCost + v.second;
                    pq.push({dis[0][v.first],v.first,0}); // we still not used the discount 
                }
                if(currCost + (v.second >> 1) < dis[1][v.first]){
                    dis[1][v.first] = currCost + (v.second >> 1);
                    pq.push({dis[1][v.first],v.first,1}); // now we have used the discount
                }
            }
            // 2. we have used the discount so we just need to move forward
            else{
                if(currCost + v.second < dis[1][v.first]){
                    dis[1][v.first] = currCost + v.second;
                    pq.push({dis[1][v.first],v.first,1}); // we have already used the discount
                }
            }
        }
    }
    cout << dis[1][n] <<endl;


    return 0;
}


/*
BUGS Encountered
1. Using the correct variable name in the continue part
2. The transitions are independent so we need to use if in place of else if
3. When we already used the discount earlier, we cannot move move back to 0th state, 
we need to continue in the current discount state


*/