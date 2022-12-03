#include "common.h"

void task1() {
    ifstream input("input3.txt");
    string line;
    int sum = 0;

    while (getline(input, line)) {
        int items[256] = {0};
        
        for (int i = 0; i < line.size() / 2; i++) {
            items[line[i]]++;
        }

        for (int i = line.size() / 2; i < line.size(); i++) {
            if (items[line[i]]) {
                if (line[i] >= 'a') {
                    sum += line[i] - 'a' + 1;
                } else {
                    sum += line[i] - 'A' + 27;
                }
                break;
            }
        }
    }

    cout << sum << endl;
}

void task2() {
    ifstream input("input3.txt");
    string line;
    int sum = 0;

    while (getline(input, line)) {
        int badge[256] = {0};

        for (auto c : line) {
            badge[c] |= 1;
        }

        getline(input, line);
        for (auto c : line) {
            badge[c] |= 2;
        }

        getline(input, line);
        for (auto c : line) {
            badge[c] |= 4;
        }

        for (int i = 0; i < 256; i++) {
            if (badge[i] == 7) {
                if (i >= 'a') {
                    sum += i - 'a' + 1;
                } else {
                    sum += i - 'A' + 27;
                }
            }
        }
    }

    cout << sum << endl;
}

int main() {
    task1();
    task2();
}