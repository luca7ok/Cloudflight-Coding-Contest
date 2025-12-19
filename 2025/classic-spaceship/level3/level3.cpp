#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int main() {
    ifstream fin;
    ofstream fout;
    fin.open("level3_0_example.in");
    fout.open("output.out");

    string line;
    getline(fin, line);
    const int paces[] = {-1, -2, -3, -4, -5, 0, 5, 4, 3, 2, 1};

    while (getline(fin, line)) {
        stringstream ss(line);
        int position, timeLimit;
        ss >> position >> timeLimit;

        fout << 0 << ' ';
        
        
    }

    return 0;
}