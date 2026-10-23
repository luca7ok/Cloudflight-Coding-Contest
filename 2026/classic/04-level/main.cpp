#include <ctime>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

std::ifstream fin("input/in_level-4_0-example.txt");
std::ofstream fout("output.txt");

std::unordered_map<int, std::pair<int, int>> states = {{0, {-1, 1}}, {1, {0, 2}},  {2, {1, 1}},
                                                       {3, {1, -1}}, {4, {0, -2}}, {5, {-1, -1}}};

struct emitter {
    int x;
    int y;
    int value;
    bool active = false;
    int state;
    int step = 0;
};

void generate_matrix(int r, std::vector<std::vector<char>>& mat) {
    int totalCols = 4 * r + 1;
    int totalRows = 2 * r + 1;

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
}

void clockwise(std::vector<std::vector<char>>& mat, emitter& e, int r) {
    mat[e.x][e.y] = '*';

    e.step++;
    if (e.step % r == 0) {
        e.step = 0;
        e.state = (e.state + 1) % 6;
    }

    e.x += states[e.state].first;
    e.y += states[e.state].second;
    mat[e.x][e.y] = '0' + e.value;
}

void counterclockwise(std::vector<std::vector<char>>& mat, emitter& e, int r) {
    mat[e.x][e.y] = '*';

    e.step--;
    if (e.step < 0) {
        e.step = r;
        e.state = (6 + e.state - 1) % 6;
    }

    e.x -= states[e.state].first;
    e.y -= states[e.state].second;
    mat[e.x][e.y] = '0' + e.value;
}

void showMatrix(int n, int m, std::vector<std::vector<char>>& mat) {
    for (int i = 0; i < n; i++, fout << '\n') {
        for (int j = 0; j < m; j++) {
            fout << mat[i][j];
        }
    }
    fout << '\n';
}

int main() {
    int t;
    fin >> t;

    while (t--) {
        int r;
        fin >> r;

        int m = 4 * r + 1;
        int n = 2 * r + 1;

        int l;
        fin >> l;

        std::vector<std::vector<char>> mat(n, std::vector<char>(m, '-'));
        std::vector<std::vector<int>> matInt(n, std::vector<int>(m, 0));

        std::vector<emitter> emitters(6);
        emitters[0].x = r;
        emitters[0].y = 0;
        emitters[0].value = 1;
        emitters[0].state = 0;

        emitters[1].x = 0;
        emitters[1].y = r;
        emitters[1].value = 2;
        emitters[1].state = 1;

        emitters[2].x = 0;
        emitters[2].y = m - r - 1;
        emitters[2].value = 3;
        emitters[2].state = 2;

        emitters[3].x = r;
        emitters[3].y = m - 1;
        emitters[3].value = 4;
        emitters[3].state = 3;

        emitters[4].x = n - 1;
        emitters[4].y = m - r - 1;
        emitters[4].value = 5;
        emitters[4].state = 4;

        emitters[5].x = n - 1;
        emitters[5].y = r;
        emitters[5].value = 6;
        emitters[5].state = 5;

        generate_matrix(r, mat);

        for (auto& e : emitters) {
            mat[e.x][e.y] = '0' + e.value;
        }

        fin.get();
        while (l--) {
            char s[256];
            fin.getline(s, 256);
            for (int i = 0; s[i]; i += 2) {
                if (s[i] == 'T') {
                    emitters[i / 2].active = !emitters[i / 2].active;
                } else if (s[i] == 'F') {
                    clockwise(mat, emitters[i / 2], r);
                } else if (s[i] == 'B') {
                    counterclockwise(mat, emitters[i / 2], r);
                }
                // fout << s[i] << '\n';
                // showMatrix(n, m, mat);
            }
            // showMatrix(n, m, mat);

            for (auto& e : emitters) {
                if (e.active) {
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
        }

        showMatrix(n, m, mat);
    }
    return 0;
}