#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

/*
CONCEPT:
Use BFS in an unweighted graph to find the shortest path from 1 to n.
Store parent nodes so the route can be reconstructed after reaching the destination.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n , m;
    cin >> n >> m;

    vector<vector<int>>adj(n+1);
    vector<int>par(n+1,-1);
    vector<bool>vis(n+1,false);

    //input
    for(int i = 0; i <  m; i++){
        int u , v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // applying bfs
    queue<int>q;
    int src = 1;
    q.push(src);
    par[src] = src; // starting node is itself is parent
    vis[src] = true;

    while(!q.empty()){
        int u = q.front();
        q.pop();

        // for all neighbors
        for(auto& v : adj[u]){
            if(!vis[v]){
                q.push(v);
                vis[v] = true;
                par[v] = u; // v parent is u
            }
        }
    }
    if(par[n] == -1){
        cout<<"IMPOSSIBLE"<<endl;
    }
    else{
        int i = n;
        vector<int>ans;
        ans.push_back(n);
        while(par[i] != i){
            ans.push_back(par[i]);
            i = par[i];
        }
        cout<<ans.size()<<endl;
        for(int i = ans.size()-1 ;i >= 0 ;i--){
            cout<<ans[i]<<" ";
        }
    }

    return 0;
}