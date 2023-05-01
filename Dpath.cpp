#include <bits/stdc++.h>
// using namespace std;


// // shortest path using bfs;

// const int MAX_SIZE = 100;

// struct Node {
//     int x, y;
//     double distance;
//     vector<pair<int, int>> path;
    
//     Node(int x, int y, double distance): x(x), y(y), distance(distance) {}
// };

// bool isValid(int x, int y, int N) {
//     return (x >= 0 && x < N && y >= 0 && y < N);
// }

// double shortestPath(int matrix[][MAX_SIZE], int srcX, int srcY, int destX, int destY, int N) {
//     vector<pair<int, int>> directions = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
//     vector<vector<bool>> visited(N, vector<bool>(N, false));
//     priority_queue<Node*, vector<Node*>, function<bool(Node*, Node*)>> pq([](Node* a, Node* b) { return a->distance > b->distance; });
//     pq.push(new Node(srcX, srcY, 0.0));
    
//     while (!pq.empty()) {
//         Node* curr = pq.top();
//         pq.pop();
        
//         int x = curr->x;
//         int y = curr->y;
        
//         if (x == destX && y == destY) {
//             cout << "Shortest path: ";
//             for (auto p : curr->path) {
//                 cout << "(" << p.first << "," << p.second << ") ";
//             }
//             cout << "(" << x << "," << y << ")\n";
            
//             double shortestDist = curr->distance;
//             delete curr;
//             return shortestDist;
//         }
        
//         if (visited[x][y]) {
//             delete curr;
//             continue;
//         }
        
//         visited[x][y] = true;
//         for (auto dir : directions) {
//             int nextX = x + dir.first;
//             int nextY = y + dir.second;
//             if (isValid(nextX, nextY, N) && matrix[nextX][nextY] == 1 && !visited[nextX][nextY]) {
//                 double nextDist = curr->distance + (dir.first == 0 || dir.second == 0 ? 1.0 : sqrt(2.0));
//                 Node* nextNode = new Node(nextX, nextY, nextDist);
//                 nextNode->path = curr->path;
//                 nextNode->path.push_back({x, y});
//                 pq.push(nextNode);
//             }
//         }
        
//         delete curr;
//     }
    
//     return INT_MAX;
// }

// int main() {
//     int matrix[MAX_SIZE][MAX_SIZE] = {{1, 1, 0}, {0, 0, 1}, {1, 1, 1}};
//     int N = 3;
//     int srcX = 0, srcY = 0, destX = 2, destY = 2;
//     double shortestDist = shortestPath(matrix, srcX, srcY, destX, destY, N);
//     if (shortestDist == INT_MAX) {
//         cout << "Destination not reachable\n";
//     } else {
//         cout << "Shortest distance: " << shortestDist << endl;
//     }
//     return 0;
// }

// #include <bits/stdc++.h>
// #include <iostream>
// #include <vector>
// #include <queue>
// #include <cmath>
// #include <limits>
// using namespace std;

// int dist[9];
// int parent[9];

// bool isValid(int x, int y) {
//     return x >= 0 && x < 3 && y >= 0 && y < 3;
// }

// bool isBlocked(int x, int y, int mat[3][3]) {
//     return mat[x][y] == 0;
// }

// int getNodeId(int x, int y) {
//     return x * 3 + y;
// }

// void dijkstra(int mat[3][3], int startX, int startY, int endX, int endY) {
//     for (int i = 0; i < 9; i++) {
//         dist[i] = numeric_limits<int>::max();
//         parent[i] = -1;
//     }
//     dist[getNodeId(startX, startY)] = 0;
//     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
//     pq.push(make_pair(0, getNodeId(startX, startY)));
//     while (!pq.empty()) {
//         int u = pq.top().second;
//         pq.pop();
//         int x = u / 3;
//         int y = u % 3;
//         if (x == endX && y == endY) {
//             return;
//         }
//         for (int dx = -1; dx <= 1; dx++) {
//             for (int dy = -1; dy <= 1; dy++) {
//                 if (dx == 0 && dy == 0) continue;
//                 int newX = x + dx;
//                 int newY = y + dy;
//                 if (isValid(newX, newY) && !isBlocked(newX, newY, mat)) {
//                     int v = getNodeId(newX, newY);
//                     int weight = abs(dx) + abs(dy);
//                     if (dist[u] + weight < dist[v]) {
//                         dist[v] = dist[u] + weight;
//                         parent[v] = u;
//                         pq.push(make_pair(dist[v], v));
//                     }
//                 }
//             }
//         }
//     }
// }

// vector<int> shortestPath(int mat[3][3], int startX, int startY, int endX, int endY) {
//     dijkstra(mat, startX, startY, endX, endY);
//     vector<int> path;
//     int curr = getNodeId(endX, endY);
//     while (curr != -1) {
//         path.push_back(curr);
//         curr = parent[curr];
//     }
//     reverse(path.begin(), path.end());
//     return path;
// }

// int main() {
//     int mat[3][3] = {{1, 1, 0}, {0, 0, 1}, {1, 1, 1}};
//     int startX = 0, startY = 0, endX = 2, endY = 1;
//     vector<int> path = shortestPath(mat, startX, startY, endX, endY);
//     cout << "Shortest path: ";
//     for (int p : path) {
//         cout << "(" << p / 3 << ", " << p % 3 << ") ";
//     }
//     cout << endl;
//     return 0;
// }




#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>
using namespace std;

const int matmax1=500;
const int matmax2=200;

int dist[100000];
int parent[100000];



bool isValid(int x, int y, int m, int n, int mat[][matmax2],int var) {
    return (x >= 0 && x < m && y >= 0 && y < n && (mat[x][y] == 0 || mat[x][y] == 1 || mat[x][y] == var));
}


bool isBlocked(int x, int y, int mat[][matmax2]) {
    return mat[x][y] == 0;
}

int getNodeId(int x, int y, int n) {
    return x * n + y;
}

void dijkstra(int mat[][matmax2], int startX, int startY, int endX, int endY, int m, int n,int var) {
    for (int i = 0; i < m * n; i++) {
        dist[i] = numeric_limits<int>::max();
        parent[i] = -1;
    }
    dist[getNodeId(startX, startY, n)] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
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
                if (isValid(newX, newY, m, n, mat,var) && !isBlocked(newX, newY, mat)) {
                    int v = getNodeId(newX, newY, n);
                    int weight = abs(dx) + abs(dy);
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

vector<array<int,2>> shortestPath(int mat[][matmax2], int startX, int startY, int endX, int endY, int m, int n,int var) {
    dijkstra(mat, startX, startY, endX, endY, m, n,var);
    vector<int> path;
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
            arr[1] = path[i] % n;
            // cout << "(" << x << "," << y << ")";

            pp.push_back(arr);
        }




    return pp;
}
int main() {
    cout<<"\n=============================\n";
    
    ifstream infile("samplematrix.txt");
    int m, n;
    // cout << "Enter the dimensions of the matrix: ";
    // cin >> m >> n;
    m=50;
    n=50;

    int mat[matmax1][matmax2];
    // cout << "Enter the matrix elements (0 or 1):" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j]=1;
        }
    }
    int startX, startY, endX, endY;
    startX=0;
    startY=0;
    endX=10;
    endY=10;
    for(int var=1;var<4;var++){
        if(var==1){
            cout<<"Normal Path:\n";
        }
        else if(var==2){
            cout<<"River Path:\n";
        }
        else if(var==3){
            cout<<"Mountai Path:\n";
        }
        vector<array<int,2>> path = shortestPath(mat, startX, startY, endX, endY, m, n,var);
        
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
    
    cout<<"\n=============================\n";
    return 0;
}


