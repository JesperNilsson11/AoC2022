#include "common.h"

int main() {
    ifstream input("input25.txt");
    string line;
    long long result = 0;

    while (getline(input, line)) {
        long long num = 0;

        for (int i = 0; i < line.size(); i++) {
            num *= 5;
            if (line[i] == '-') {
                num -= 1;
            } else if (line[i] == '=') {
                num -= 2;
            } else {
                num += line[i] - '0';
            }
        }

        result += num;
    }

    list<char> snafu;
    while (result != 0) {
        long long t = result % 5;

        if (t < 3) {
            snafu.push_front(t+'0');
        } else {
            t = 5 - t;
            result += t;

            if (t == 1) {
                snafu.push_front('-');
            } else {
                snafu.push_front('=');
            }
        }

        result /= 5;
    }

    for (auto c : snafu) {
        cout << c;
    }

    cout << endl;
}
