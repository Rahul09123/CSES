#include <bits/stdc++.h>
using namespace std;


#include <bits/stdc++.h>
using namespace std;

/*
CONCEPT:
Detect a cycle in a directed graph using DFS with a recursion stack.
When a back edge is found, reconstruct the cycle using parent pointers.
*/

// cycle detection in directed graph

int cycleStart = 0, cycleEnd = 0;
bool dfs(int src, vector<vector<int>>&adj,vector<bool>&vis,vector<bool>&pathVis,vector<int>&parent){
    vis[src] = true;
    pathVis[src] = true;
    for(auto& v : adj[src]){
        if(!vis[v]){ // first time visiting
            parent[v] = src;
            if(dfs(v,adj,vis,pathVis,parent)){
                return true;
            }
        }
        else if(pathVis[v]){ // found a backedge
            cycleStart = v; //starting node of the cycle is the 'v' ndde which we found
            cycleEnd = src; //ending node of the cycle is the current node
            return true;
        }
    }
    pathVis[src] = false;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n , m;
    cin >> n >> m;

    vector<vector<int>>adj(n+1);

    //input
    for(int i = 0; i <  m; i++){
        int u , v;
        cin >> u >> v;
        adj[u].push_back(v);
        // adj[v].push_back(u);
    }

    // simply the question is asking if there is a cycle present in graph
    // if yes then print the cycle

    vector<bool>vis(n+1,false),pathVis(n+1,false);
    vector<int>parent(n+1,-1);
    bool flag = 0;

    for(int i = 1 ;i <= n ;i++){
        if(!vis[i]){
            if(dfs(i,adj,vis,pathVis,parent)){
                flag = 1;
                break;
            }
        }
    }
    if(flag){
        vector<int>cycle;
        int curr = cycleEnd;
        // build the path using backtracking
        cycle.push_back(cycleStart);
        while(curr != cycleStart){
            cycle.push_back(curr);
            curr = parent[curr];
        }
        cycle.push_back(cycleStart);
        reverse(cycle.begin(),cycle.end());
        cout<<cycle.size()<<endl;
        for(int i = 0 ; i < cycle.size() ;i++){
            cout<<cycle[i]<<" ";
        }
    }
    else{
        cout<<"IMPOSSIBLE"<<endl;
    }

    return 0;
}