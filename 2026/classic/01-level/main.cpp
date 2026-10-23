#include <fstream>
#include <iostream>
#include <vector>

std::ifstream fin("input/in_level-1_2-large.txt");
std::ofstream fout("output.txt");

int main() {
    int t;
    fin >> t;

    while (t--) {
        int r;
        fin >> r;

        int totalCols = 4 * r + 1;
        int totalRows = 2 * r + 1;
        std::vector<std::vector<char>> mat(totalRows, std::vector<char>(totalCols, '-'));

        int j = r;
        int count = 0;
        while (count < r + 1) {
            mat[0][j] = '*';
            mat[totalRows - 1][j] = '*';
            j += 2;
            count++;
        }

        for (int i = 1; i <= totalRows / 2; i++) {
            mat[i][r - i] = '*';
            mat[i][totalCols - r + i - 1] = '*';
            mat[totalRows / 2 + i][i] = '*';
            mat[totalRows / 2 + i][totalCols - i - 1] = '*';

            int j = r - i + 2;
            int count = 0;
            while (count < r + i - 1) {
                mat[i][j] = 'O';
                mat[totalRows - i - 1][j] = 'O';
                count++;
                j += 2;
            }
        }

        for (int i = 0; i < totalRows; i++, fout << '\n') {
            for (int j = 0; j < totalCols; j++) {
                fout << mat[i][j];
            }
        }
        fout << '\n';
    }
    return 0;
}