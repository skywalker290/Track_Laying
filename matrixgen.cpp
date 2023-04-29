#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    // create a 500 x 200 matrix with random values
    vector<vector<int>> matrix(500, vector<int>(200));
    for (int i = 1; i < 499; i++) {
        for (int j = 1; j < 199; j++) {
            matrix[i][j] = rand() % 4;
        }
    }

    // set the first row, first column, last row, and last column to 1
    for (int i = 0; i < 500; i++) {
        matrix[i][0] = 1;
        matrix[i][199] = 1;
    }
    for (int j = 0; j < 200; j++) {
        matrix[0][j] = 1;
        matrix[499][j] = 1;
    }

    // open a file for writing
    ofstream outfile("matrix.txt");

    // write the matrix to the file
    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 200; j++) {
            outfile << matrix[i][j] << " ";
        }
        outfile << endl;
    }

    // close the file
    outfile.close();

    return 0;
}
