#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

/*
CONCEPT:
Find connected components in an undirected graph with BFS/DFS.
If there are k components, the minimum roads needed to connect the graph is k - 1.
*/

void bfs(int i ,vector<int>&vis,vector<int>adj[]);
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<pair<int,int>>edges;
    for(int i = 0 ;i < m ;i++){
        int a , b;
        cin >> a >> b;
        edges.push_back({a,b});
    }
    // create the adjacencty list
    vector<int>adj[n+1]; // vertices are from 1 ... n
    for(int i = 0 ;i < edges.size() ; i++){
        int e1 = edges[i].first;
        int e2 = edges[i].second;

        adj[e1].push_back(e2);
        adj[e2].push_back(e1);
    }
    // count the number of components
    int cnt = 0;
    vector<int>vis(n+1,false);
    vector<int>roads;
    for(int i = 1 ;i <= n; i++){
        if(!vis[i]){
            roads.push_back(i);
            bfs(i,vis,adj);
            // iterate over the vis array and find the next possible non visited vertex
        }
    }
    cout<<roads.size()-1<<endl; 
    for(int i = 1; i < roads.size(); i++){
        cout<<roads[i-1]<<" "<<roads[i]<<endl;
    }
    return 0;
}


void bfs(int i ,vector<int>&vis,vector<int>adj[]){
    queue<int>q;
    q.push(i);
    vis[i] = true;
    while(!q.empty()){
        int x = q.front();
        q.pop();
        for(auto v : adj[x]){
            if(!vis[v]){
                vis[v] = true;
                q.push(v);
            }
        }
    }
}