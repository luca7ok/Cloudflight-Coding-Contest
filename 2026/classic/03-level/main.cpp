#include <cctype>
#include <fstream>
#include <iostream>
#include <vector>

std::ifstream fin("input/in_level-3_2-large.txt");
std::ofstream fout("output.txt");

struct emitter {
    int x;
    int y;
    int value;
};

int main() {
    int t;
    fin >> t;

    while (t--) {
        int r, n, m;
        fin >> r >> n >> m;

        std::vector<std::vector<char>> mat(n, std::vector<char>(m, '-'));
        std::vector<std::vector<int>> matInt(n, std::vector<int>(m, 0));
        std::vector<emitter> emitters;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                fin >> mat[i][j];
                if (isdigit(mat[i][j])) {
                    emitter e;
                    e.x = i;
                    e.y = j;
                    e.value = (int)(mat[i][j] - '0');

                    emitters.push_back(e);
                }
            }
        }
        for (auto& e : emitters) {
            switch (e.value) {
                case 1: {
                    char c = mat[e.x][e.y + 2];
                    int x = e.x;
                    int y = e.y + 2;
                    while (isalpha(c)) {
                        matInt[x][y]++;
                        y += 2;
                        c = mat[x][y];
                    }
                    break;
                }
                case 2: {
                    char c = mat[e.x + 1][e.y + 1];
                    int x = e.x + 1;
                    int y = e.y + 1;
                    while (isalpha(c)) {
                        matInt[x][y]++;
                        x++;
                        y++;
                        c = mat[x][y];
                    }
                    break;
                }
                case 3: {
                    int x = e.x + 1;
                    int y = e.y - 1;
                    char c = mat[x][y];
                    while (isalpha(c)) {
                        matInt[x][y]++;
                        x++;
                        y--;
                        c = mat[x][y];
                    }
                    break;
                }
                case 4: {
                    int x = e.x;
                    int y = e.y - 2;
                    char c = mat[x][y];
                    while (isalpha(c)) {
                        matInt[x][y]++;
                        y -= 2;
                        c = mat[x][y];
                    }
                    break;
                }
                case 5: {
                    int x = e.x - 1;
                    int y = e.y - 1;
                    char c = mat[x][y];
                    while (isalpha(c)) {
                        matInt[x][y]++;
                        x--;
                        y--;
                        c = mat[x][y];
                    }
                    break;
                }
                case 6: {
                    int x = e.x - 1;
                    int y = e.y + 1;
                    char c = mat[x][y];
                    while (isalpha(c)) {
                        matInt[x][y]++;
                        x--;
                        y++;
                        c = mat[x][y];
                    }
                    break;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matInt[i][j] == 2) {
                    mat[i][j] = 'M';
                } else if (matInt[i][j] >= 3) {
                    mat[i][j] = 'O';
                }
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