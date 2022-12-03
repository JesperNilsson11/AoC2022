#include "common.h"

void task(int elves) {
    ifstream input("input1.txt");
    int data;
    string line;
    vector<int> max(elves);
    
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

int main() {
    task(1);
    task(3);
}