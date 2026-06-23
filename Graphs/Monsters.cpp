#include <bits/stdc++.h>
using namespace std;


#include <bits/stdc++.h>
using namespace std;

/*
CONCEPT:
First run multi-source BFS from all monsters to compute their arrival times.
Then run BFS for A only through cells where A reaches strictly before any monster.
*/

using pii  = pair<int,int>;
const int INF = 1e8;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n , m ;
    cin >> n >> m; //vertices and edges

    vector<vector<char>>grid(n,vector<char>(m,'.'));
    vector<vector<int>>monster_dist(n,vector<int>(m,INF));
    int sr = -1, sc = -1;

    // input the grid
    for(int i = 0 ; i< n ;i++){
        for(int j = 0 ; j < m ;j++){
            cin >> grid[i][j];
            if(grid[i][j] == 'A'){ // saving the source row and column
                sr = i;
                sc = j;
            }
            if(grid[i][j] == 'M'){
                monster_dist[i][j] = 0;
            }
        }
    }

    vector<pii>dir = {{-1,0},{1,0},{0,1},{0,-1}};
    vector<char>dirName = {'U','D','R','L'};

    //applying multisource BFS
    queue<pii>q;
    for(int i = 0 ;i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            if(grid[i][j] == 'M'){
                q.push({i,j});
            }
        }
    }

    while(!q.empty()){
        auto [r,c] = q.front(); q.pop();

        // for all the neighbors
        for(auto d : dir){
            int nr = r + d.first;
            int nc = c + d.second;

            if(nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if(grid[nr][nc] == '#') continue;
            if(monster_dist[nr][nc] != INF) continue; // this cell is already reached

            monster_dist[nr][nc] = 1 + monster_dist[r][c];
            q.push({nr,nc});
        }
    }

    // source row and  columns are already on the boundary
    if(sr == 0 || sc == 0 || sr == n-1 || sc == m-1){
        cout << "YES" << endl;
        cout << 0 << endl;
        return 0;
    }

    vector<vector<int>>myDist(n,vector<int>(m,INF)); // storing the distance of the 'A'
    vector<vector<char>>par(n,vector<char>(m,'?'));// Helps in buildign the path

    // applying bfs from 'A'
    q.push({sr,sc});
    myDist[sr][sc] = 0;
    bool escaped = false; // checking if we have reached the boundary
    int er = -1 , ec = -1;

    while(!q.empty() && !escaped){ // missed the !escaped
        auto [r,c] = q.front(); q.pop();

        for(int i = 0 ;i < 4 ; i++){

            int nr = r + dir[i].first;
            int nc = c + dir[i].second;

            if(nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if(grid[nr][nc] == '#')continue;
            int time = myDist[r][c] + 1;
            if(myDist[nr][nc] != INF) continue; // missed this
            if(time >= monster_dist[nr][nc]) continue;

            myDist[nr][nc] = time;
            par[nr][nc] = dirName[i];
            q.push({nr,nc});

            if(nr == 0 || nr == n-1 || nc == 0 || nc == m-1){ //error in typo
                escaped = true;
                er = nr;
                ec = nc; // error
                break;
            }
        }
    }
    if(!escaped){
        cout << "NO"<<endl;
        return 0;
    }
    // constructing the path
    string path;
    int r = er;
    int c = ec;

    while(!(r == sr && c == sc)){
        char currDir = par[r][c];
        path.push_back(currDir);
        // now we backtrack
        if(currDir == 'U') r++;
        else if(currDir == 'D') r--;
        else if(currDir == 'L') c++;
        else if(currDir == 'R') c--;
    }

    reverse(path.begin(),path.end());
    cout<<"YES"<<endl;
    cout<<path.size()<<endl;
    cout<<path<<endl;

    return 0;
}