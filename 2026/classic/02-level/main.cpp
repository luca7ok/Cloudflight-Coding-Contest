#include <cctype>
#include <fstream>
#include <iostream>
#include <vector>

std::ifstream fin("input/in_level-2_2-large.txt");
std::ofstream fout("output.txt");

int main() {
    int t;
    fin >> t;

    while (t--) {
        int r, n, m;
        fin >> r >> n >> m;

        int emitterX, emitterY, emitterValue;

        std::vector<std::vector<char>> mat(n, std::vector<char>(m, '-'));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                fin >> mat[i][j];
                if (isdigit(mat[i][j])) {
                    emitterX = i;
                    emitterY = j;
                    emitterValue = (int)(mat[i][j] - '0');
                }
            }
        }

        switch (emitterValue) {
            case 1: {
                char c = mat[emitterX][emitterY + 2];
                int x = emitterX;
                int y = emitterY + 2;
                while (c == 'O') {
                    mat[x][y] = 'M';
                    y += 2;
                    c = mat[x][y];
                }
                break;
            }
            case 2: {
                char c = mat[emitterX + 1][emitterY + 1];
                int x = emitterX + 1;
                int y = emitterY + 1;
                while (c == 'O') {
                    mat[x][y] = 'M';
                    x++;
                    y++;
                    c = mat[x][y];
                }
                break;
            }
            case 3: {
                int x = emitterX + 1;
                int y = emitterY - 1;
                char c = mat[emitterX + 1][y];
                while (c == 'O') {
                    mat[x][y] = 'M';
                    x++;
                    y--;
                    c = mat[x][y];
                }
                break;
            }
            case 4: {
                int x = emitterX;
                int y = emitterY - 2;
                char c = mat[x][y];
                while (c == 'O') {
                    mat[x][y] = 'M';
                    y -= 2;
                    c = mat[x][y];
                }
                break;
            }
            case 5: {
                int x = emitterX - 1;
                int y = emitterY - 1;
                char c = mat[x][y];
                while (c == 'O') {
                    mat[x][y] = 'M';
                    x--;
                    y--;
                    c = mat[x][y];
                }
                break;
            }
            case 6: {
                int x = emitterX - 1;
                int y = emitterY + 1;
                char c = mat[x][y];
                while (c == 'O') {
                    mat[x][y] = 'M';
                    x--;
                    y++;
                    c = mat[x][y];
                }
                break;
            }
        }

        for (int i = 0; i < n; i++, fout << '\n') {
            for (int j = 0; j < m; j++) {
                fout << mat[i][j];
            }
        }
        fout << '\n';
    }

    return 0;
}