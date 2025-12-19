#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int main() {
    ifstream fin;
    ofstream fout;
    fin.open("level2_2_large.in");
    fout.open("output.out");

    string line;
    getline(fin, line);
    while (getline(fin, line)) {
        stringstream ss(line);
        long long totalTime = 0;
        long long position = 0;
        long long num;
        while (ss >> num) {
            if (num == 0) {
                totalTime++;
            } else {
                totalTime += abs(num);
                position = num < 0 ? position - 1 : position + 1;
            }
        }
        fout << position << ' ' << totalTime << '\n';
    }

    return 0;
}