#include <bits/stdc++.h>

using namespace std;

const int MAX_SIZE = 100;

struct Node {
    int x, y;
    double distance;
    vector<pair<int, int>> path;
    
    Node(int x, int y, double distance): x(x), y(y), distance(distance) {}
};

bool isValid(int x, int y, int N) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

double shortestPath(int matrix[][MAX_SIZE], int srcX, int srcY, int destX, int destY, int N) {
    vector<pair<int, int>> directions = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    priority_queue<Node*, vector<Node*>, function<bool(Node*, Node*)>> pq([](Node* a, Node* b) { return a->distance > b->distance; });
    pq.push(new Node(srcX, srcY, 0.0));
    
    while (!pq.empty()) {
        Node* curr = pq.top();
        pq.pop();
        
        int x = curr->x;
        int y = curr->y;
        
        if (x == destX && y == destY) {
            cout << "Shortest path: ";
            for (auto p : curr->path) {
                cout << "(" << p.first << "," << p.second << ") ";
            }
            cout << "(" << x << "," << y << ")\n";
            
            double shortestDist = curr->distance;
            delete curr;
            return shortestDist;
        }
        
        if (visited[x][y]) {
            delete curr;
            continue;
        }
        
        visited[x][y] = true;
        for (auto dir : directions) {
            int nextX = x + dir.first;
            int nextY = y + dir.second;
            if (isValid(nextX, nextY, N) && matrix[nextX][nextY] == 1 && !visited[nextX][nextY]) {
                double nextDist = curr->distance + (dir.first == 0 || dir.second == 0 ? 1.0 : sqrt(2.0));
                Node* nextNode = new Node(nextX, nextY, nextDist);
                nextNode->path = curr->path;
                nextNode->path.push_back({x, y});
                pq.push(nextNode);
            }
        }
        
        delete curr;
    }
    
    return INT_MAX;
}

int main() {
    int matrix[MAX_SIZE][MAX_SIZE] = {{1, 1, 0}, {0, 0, 1}, {1, 1, 1}};
    int N = 3;
    int srcX = 0, srcY = 0, destX = 2, destY = 2;
    double shortestDist = shortestPath(matrix, srcX, srcY, destX, destY, N);
    if (shortestDist == INT_MAX) {
        cout << "Destination not reachable\n";
    } else {
        cout << "Shortest distance: " << shortestDist << endl;
    }
    return 0;
}
