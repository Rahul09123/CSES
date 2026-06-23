#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

/*
CONCEPT:
Check whether the graph is bipartite using BFS coloring.
Assign alternating colors to adjacent nodes; if a conflict appears, the answer is impossible.
*/

bool bfs(int src, vector<vector<int>>&adj,vector<int>&color){
    bool flag = 0;
    queue<int>q;
    q.push(src);
    color[src] = 0;

    // if we can color the whole graph with just 2 colors
    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(auto& v : adj[u]){
            if(color[v] == -1){ //still not visited
                q.push(v);
                color[v] = !color[u];
            }
            else{
                if(color[u] == color[v]){
                    cout<<"IMPOSSIBLE"<<endl;
                    return 1;
                }
            }
        }
    }
    return flag;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n , m;
    cin >> n >> m;

    vector<vector<int>>adj(n+1);
    vector<int>color(n+1,-1);

    //input
    for(int i = 0; i <  m; i++){
        int u , v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    //applying bfs
    for(int i = 1 ;i <= n ;i++){
        if(color[i] == -1){
            if(bfs(i,adj,color)){
                return 0;
            }
        }
    }
    for(int i = 1; i<= n ;i++){
        if(color[i] == 0){
            cout<<1<<" ";
        }
        else{
            cout<<2<<" ";
        }
    }
    cout<<endl;

    return 0;
}