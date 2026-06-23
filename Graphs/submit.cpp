#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

/*
CONCEPT:
Grid pathfinding with BFS and parent tracking.
Mark visited cells, store the move used to enter each cell, and reconstruct the route.
*/

#define nl '\n'

void printMatrix(vector<vector<char>>&v){
    for(int i = 0 ;i < v.size();i++){
        for(int  j = 0 ; j < v[0].size() ;j++){
            cout<<v[i][j]<<" ";
        }
        cout<<nl;
    }
}

bool isValid(vector<vector<char>>&adj,vector<vector<bool>>&vis,int r , int c){
    int n = adj.size();
    int m = adj[0].size();
    if(r >= n || c >= m || r < 0 || c < 0){ //out of bounds
        return false;
    }
    // not a valid box
    else if(vis[r][c] || adj[r][c] == '#'){
        return false;
    }
    else{
        return true;
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n , m;
    cin >> n >> m;
    vector<vector<char>>adj(n,vector<char>(m,'.'));

    int r = 0 , c = 0; //start point
    for(int i = 0 ;  i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            cin>>adj[i][j];
            if(adj[i][j] == 'A'){
                r = i;
                c = j;
            }
        }
    }

    vector<vector<bool>>vis(n,vector<bool>(m,false)); // to track the cells
    vector<vector<char>>parentMove(n,vector<char>(m,'.'));// track the moves
    vector<pair<int,int>>neighbors = {{-1,0},{1,0},{0,1},{0,-1}};
    vector<char>moves = {'U','D','R','L'};//possible moves
    
    

    return 0;
}