#include "common.h"

void task1() {
    ifstream input("input6.txt");
    string letters;

    getline(input, letters);
    for (int i = 3; i < letters.size(); i++) {
        bool found = false;

        for (int j = i - 3; j < i; j++) {
            for (int k = j + 1; k <= i; k++) {
                if (letters[j] == letters[k]) {
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }

        if (!found) {
            cout << i+1 << endl;
            break;
        }
    }
}

void task2() {
    ifstream input("input6.txt");
    string letters;

    getline(input, letters);
    for (int i = 13; i < letters.size(); i++) {
        bool found = false;

        for (int j = i - 13; j < i; j++) {
            for (int k = j + 1; k <= i; k++) {
                if (letters[j] == letters[k]) {
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }

        if (!found) {
            cout << i+1 << endl;
            break;
        }
    }
}

int main() {
    task1();
    task2();
}