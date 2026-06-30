#include <bits/stdc++.h>
using namespace std;

vector<int>parent;
vector<int>sz;

int maxSize = 1;
int components = INT_MIN;


/*
1. Are they already in the same component?
    * Yes → return.
2. Decide which root survives.
    * Usually the larger one.
3. Make the smaller root point to the larger root.
4. Increase the size of the surviving root.

*/

int findPar(int x){
    if(parent[x] == x){
        return x;
    }
    return parent[x] = findPar(parent[x]); // lazy propagation
}

void unionBySize(int a ,int b){
    int parA = findPar(a);
    int parB = findPar(b);

    if(parA == parB){
        return;
    }
    // if both have the same size the make parB as parA and increase the size of parA
    // also the component size will also be decreased
    // if the size of parA > parB, typically we append the smaller tree to the larger one
    if(sz[parA] >= sz[parB]){
        parent[parB] = parA;
        sz[parA] += sz[parB];
        maxSize = max(maxSize,sz[parA]);
        if(components > 0)components--;
    }
    else{
        parent[parA] = parB;
        sz[parB] += sz[parA];
        maxSize = max(maxSize , sz[parB]);
        if(components > 0)components--;
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    components = n;
    // 1. no. of components
    // 2. size of the largest component

    parent.resize(n+1,0);
    sz.resize(n+1,0);

    // initializing the components , every node is parent of itself
    // size of each component is 1

    for(int i = 1 ;i <= n ; i++){
        parent[i] = i;
        sz[i] = 1;
    }

    int m;
    cin >> m;
    while(m > 0){
        int a , b;
        cin >> a >> b;
        unionBySize(a,b);
        cout << components << " " << maxSize << endl;
        m--;
    }

    return 0;
}