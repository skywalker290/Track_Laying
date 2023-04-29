#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

const int MAX_ROWS = 500;
const int MAX_COLS = 200;

int matrix[MAX_ROWS][MAX_COLS]; // 2D array to store the matrix
int rows, cols; // variables to store the number of rows and columns in the matrix

// helper function to check if a cell is valid (within matrix bounds and unblocked)
bool isValid(int i, int j) {
    return i >= 0 && i < rows && j >= 0 && j < cols && matrix[i][j] == 0;
}

// Dijkstra's algorithm for finding shortest path from source to destination
int dijkstra(int src_i, int src_j, int dest_i, int dest_j) {
    int dist[MAX_ROWS][MAX_COLS];
    memset(dist, INT_MAX, sizeof(dist));

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    pq.push({0, {src_i, src_j}});
    dist[src_i][src_j] = 0;

    while (!pq.empty()) {
        pair<int, pair<int, int>> curr = pq.top();
        pq.pop();
        int curr_i = curr.second.first, curr_j = curr.second.second;

        // reached destination
        if (curr_i == dest_i && curr_j == dest_j) {
            return dist[curr_i][curr_j];
        }

        // explore neighboring cells (up, down, left, right, diagonal)
        for (int i = curr_i-1; i <= curr_i+1; i++) {
            for (int j = curr_j-1; j <= curr_j+1; j++) {
                if (isValid(i, j)) {
                    int cost = 1; // cost of moving to neighboring cell
                    if (i != curr_i && j != curr_j) {
                        cost = 2; // cost of diagonal movement
                    }
                    if (dist[curr_i][curr_j] + cost < dist[i][j]) {
                        dist[i][j] = dist[curr_i][curr_j] + cost;
                        pq.push({dist[i][j], {i, j}});
                    }
                }
            }
        }
    }

    // destination not reachable
    return -1;
}

int main() {
    // open the file for reading
    ifstream infile("matrix.txt");

    // read the matrix from the file
    // infile >> rows >> cols;
    rows=200;
    cols=500;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            infile >> matrix[i][j];
        
        }
    }

    ofstream outfile("matrix2.txt");

    // write the matrix to the file
    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 200; j++) {
            outfile << matrix[i][j] << " ";
        }
        outfile << endl;
    }

    // close the file
    infile.close();

    // example usage: find shortest path from (10, 10) to (150, 400)
    int src_i = 0, src_j = 0, dest_i = 0, dest_j = 1;
    int dist = dijkstra(src_i, src_j, dest_i, dest_j);

    if (dist == -1) {
        cout << "Destination not reachable from source" << endl;
    } else {
        cout << "Shortest path length from (" << src_i << ", " << src_j << ") to (" << dest_i << ", " << dest_j << ") = " << dist << endl;
    }

    return 0;
}
