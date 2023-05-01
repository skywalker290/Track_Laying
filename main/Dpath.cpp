#include <bits/stdc++.h>
using namespace std;
void bfs(int sx,int sy,vector<array<int,2>> &markedPath);
const int matmax1=500;
const int matmax2=200;
const int MAXN = 1005; 
float dist[100000];
float parent[100000];
int mat[matmax1][matmax2];
//vector<vector<int>>mat;
vector<int>x_cr={5,92,150,195,241};
vector<int>y_cr={7,20,167,158,15};

void makecities()
{
    int i;
    for(i=0;i<x_cr.size();i++)
    {
        if(mat[x_cr[i]][y_cr[i]]=='*')
        {
            mat[x_cr[i]][y_cr[i]]='C';
        }
    }
}



bool isValid(int x, int y, int m, int n,int var) {
    return (x >= 0 && x < m && y >= 0 && y < n && (mat[x][y] == 0 || mat[x][y] == '*' || mat[x][y] == var));
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
        cout<<path[i]<<endl;
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
        // mat[x][y]='@';

        // dist+=mat[x][y];

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




void algo1()
{
    //vector<int>x_cr;
    //vector<int>y_cr;
    int m=300;
    int n=169;
    int n1=x_cr.size();
    vector<array<int,2>>t;
    vector<array<int,2>>lp;
    int i,k=INT_MIN,st,ed,j,d;
    for(i=0;i<n1;i++)
    {
        for(j=i;j<n1;j++)
        {
            t=shortestPath(x_cr[i],y_cr[j],x_cr[j],y_cr[j],m,n,'*');
            d=Dist(t);
            if(k<d)
            {
                st=i;
                ed=j;
                k=d;
                lp=t;
            }
        }
    }
    for(i=0;i<lp.size();i++)
    {
        mat[lp[i][0]][lp[i][1]]='@';
    }
    

    for(i=0;i<n1;i++)
    {
        if(i!=st && i!=ed )
        {
            bfs(x_cr[i],y_cr[i],lp);
        }
    }

}


void bfs(int sx,int sy,vector<array<int,2>> &markedPath)
{
    int m=300, n=169; // dimensions of the matrix
    bool visited[MAXN][MAXN]; // keep track of visited cells
    int dist[MAXN][MAXN]; // distance from starting point to each cell
    pair<int, int> prev[MAXN][MAXN]; // previous cell in the shortest path
    memset(visited, false, sizeof visited);
    memset(dist, -1, sizeof dist);
    // initialize starting point
    queue<pair<int, int>> q;
    q.push({sx, sy});
    visited[sx][sy] = true;
    dist[sx][sy] = 0;
    // perform BFS
    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        // check if current cell is on the marked path
        for (auto p : markedPath) {
            int px = p[0], py = p[1];
            if (x == px && y == py)
            {
                break;
                break;
            } 
                
        }
        // explore neighbors
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                int nx = x + dx, ny = y + dy;
                if (isValid(nx, ny,m,n,0) && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    dist[nx][ny] = dist[x][y] + 1;
                    prev[nx][ny] = {x, y}; // update previous cell
                    q.push({nx, ny});
                }
            }
        }
    }
    // if no path found, return -1
    //vector<pair<int, int>> path;
    int px,py;
    int x = markedPath[markedPath.size()-1][0], y =  markedPath[markedPath.size()-1][1];
    //path.push_back({x, y});
    while (x != sx || y != sy) {
        tie(px, py) = prev[x][y];
        mat[x][y]='@';
        //path.push_back({px, py});
        x = px;
        y = py;
    }
    //reverse(path.begin(), path.end());
    return;
}




void inputmatrix(){
    ifstream infile("kanishkjob.txt");
    int m=300;
    int n=169;
    char ch;
    int i=0;
    int j=0;
    infile.get(ch);
    //while(!infile.eof()){
      //  mat[i].push_back(ch);
    //}

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            infile.get(ch); mat[i][j]=ch;
        }
    }
}

void outputmatrix(){
    ofstream outfile("output.txt");
    int m=300;
    int n=169;
    char ch='*';


    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            outfile.put(char(mat[i][j]));
        }
    }

}












int main() {
    cout<<"\n=============================\n";
    
    ifstream infile("kanishkjob.txt");
    ofstream outfile("output.txt");


    int m, n;
    m=300;
    n=169;
    char ch;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            infile.get(ch); mat[i][j]=ch;
        }
    }
    
    int startX, startY, endX, endY;
    startX=0;
    startY=0;
    endX=234;
    endY=76;
    for(int var=1;var<4;var++){
        if(var==1){
            var='*';
            cout<<"Normal Path:\n";
        }
        else if(var==2){
            var='W';
            cout<<"River Path:\n";
        }
        else if(var==3){
            var='X';
            cout<<"Mountai Path:\n";
        }
        vector<array<int,2>> path = shortestPath( startX, startY, endX, endY, m, n,var);
        
        int x=0,y=0;
        int x1=0,y1=0;
        float dist=0.00;

        if (path.empty()) {
            cout << "No path found" << endl;
        }
        else{
            
            for (int i = 0; i < path.size(); i++) {
                
                x = path[i][0];
                y = path[i][1];
                mat[x][y]='@';

                // dist+=mat[x][y];

                if(x1+1==x && y1+1==y){
                    dist+=1.414;
                }

                else{
                    dist+=1;
                }

                x1=x;y1=y;
                cout << "(" << x << "," << y << ")";
                if (i != path.size() - 1) {
                    cout << " -> ";
                }
            }
            cout << endl;

            cout<<"distance:"<<dist<<endl<<endl;
        }
    }

    makecities();
    algo1();

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            //outfile.put(char(mat[i][j]));
            cout<<char(mat[i][j]);
        }
        
    }
    
    cout<<"\n=============================\n";
 

    return 0;
}


