#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
    ifstream input("input1.txt");
    int data;
    string line;

    // task 1 = 1 task = 3
    vector<int> max(3);
    
    int current = 0;
    while (getline(input, line)) {
        if (line.size() == 0) {
            if (max[0] < current) {
                max[0] = current;
                sort(max.begin(), max.end());
            }
            current = 0;
            continue;
        }
        stringstream ss(line);
        ss >> data;
        current += data;
    }

    int sum = 0;
    for (auto i : max) {
        sum += i;
    }
    cout << sum << endl;
}