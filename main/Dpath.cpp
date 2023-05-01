#include <bits/stdc++.h>
using namespace std;

const int matmax1=500;
const int matmax2=200;

float dist[100000];
float parent[100000];
// int mat[matmax1][matmax2];
vector<vector<int>>mat;



bool isValid(int x, int y, int m, int n,int var) {
    return (x >= 0 && x < m && y >= 0 && y < n && (mat[x][y] == 0 || mat[x][y] == '*' || mat[x][y] == var ||mat[x][y]=='@'));
}







bool isBlocked(int x, int y) {
    return mat[x][y] == 0;
}





int getNodeId(int x, int y, int n) {
    return x * n + y;
}






void dijkstra(int startX, int startY, int endX, int endY, int m, int n,int var) {
    for (int i = 0; i < m * n; i++) {
        dist[i] = numeric_limits<float>::max();
        parent[i] = -1;
    }
    dist[getNodeId(startX, startY, n)] = 0;
    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> pq;
    pq.push(make_pair(0, getNodeId(startX, startY, n)));
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        int x = u / n;
        int y = u % n;
        if (x == endX && y == endY) {
            return;
        }
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                int newX = x + dx;
                int newY = y + dy;
                if (isValid(newX, newY, m, n,var) && !isBlocked(newX, newY)) {
                    int v = getNodeId(newX, newY, n);
                    float weight = dx != 0 && dy != 0 ? 1.414 : 1.0;
                    if (dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        parent[v] = u;
                        pq.push(make_pair(dist[v], v));
                    }
                }
            }
        }
    }
}






vector<array<int,2>> shortestPath(int startX, int startY, int endX, int endY, int m, int n,int var) {
    dijkstra( startX, startY, endX, endY, m, n,var);
    vector<float> path;
    int curr = getNodeId(endX, endY, n);
    while (curr != -1) {
        path.push_back(curr);
        curr = parent[curr];
    }
    reverse(path.begin(), path.end());
    array<int,2>arr;
    vector<array<int,2>>pp;
    for (int i = 0; i < path.size(); i++) {
        arr[0] = path[i] / n;
        arr[1] = int(path[i]) % n;
        // cout << "(" << x << "," << y << ")";

        pp.push_back(arr);
    }
    return pp;
}







float Dist(vector<array<int,2>>path){
    float dist=0.00;
    int x=0,y=0;
    int x1=0,y1=0;
    for (int i = 0; i < path.size(); i++) {
                
        x = path[i][0];
        y = path[i][1];

        if(x1+1==x && y1+1==y){
            dist+=1.414;
        }
        else{
            dist+=1;
        }

        x1=x;y1=y;
    }
    return dist;
}






void inputmatrix(){
    ifstream infile("kanishkjob.txt");

    char ch;
    int i=0;
    infile.get(ch);
    mat.push_back({});
    while(!infile.eof()){
        mat[i].push_back(ch);
        if(ch=='\n'){
            mat.push_back({});
            i++;
        }
        infile.get(ch);

    }
}






void outputmatrix(){
    ofstream outfile("output.txt");
    int m=mat.size()-1;
    int n=mat[0].size();
    char ch='*';


    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            outfile.put(char(mat[i][j]));
        }
    }

}




void setpath(vector<array<int,2>> path){
    int x,y;
    for (int i = 0; i < path.size(); i++) {
        x = path[i][0];
        y = path[i][1];
        mat[x][y]='@';
    }
}





int main() {
    cout<<"\n=============================\n";
    
    ifstream infile("kanishkjob.txt");
    ofstream outfile("output.txt");
    inputmatrix();


    int m, n;
    m=mat.size()-1;
    n=mat[0].size();
    char ch;

    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < n; j++) {
    //         infile.get(ch); mat[i][j]=ch;
    //     }
    // }

    

    int startX, startY, endX, endY;
    startX=0;
    startY=160;
    endX=234;
    endY=76;
    int par='*';
    for(int var=1;var<4;var++){
        if(var==1){
            par='*';
            cout<<"Normal Path:\n";
        }
        else if(var==2){
            par='W';
            cout<<"River Path:\n";
        }
        else if(var==3){
            par='X';
            cout<<"Mountai Path:\n";
        }
        vector<array<int,2>> path = shortestPath( startX, startY, endX, endY, m, n,par);
        setpath(path);
        outputmatrix();
        cout<<Dist(path)<<endl;
    }
    // return 0;



    outputmatrix();
    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < n; j++) {
    //         outfile.put(char(mat[i][j]));
    //     }
    // }
    
    cout<<"\n=============================\n";
    return 0;
}


