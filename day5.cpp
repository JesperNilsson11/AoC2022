#include "common.h"

void task1() {
    ifstream input("input5.txt");
    string line;
    vector<vector<char>> columns(9);

    while (getline(input, line)) {
        if (line.size() == 0)
            break;
        char c = line[1];
        if (c >= '0' && c <= '9')
            break;

        for (int i = 1; i < line.size(); i += 4) {
            if (line[i] >= 'A' && line[i] <= 'Z')
                columns[i / 4].insert(columns[i / 4].begin(), line[i]);
        }
    }

    while (getline(input, line)) {
        if (line.size() == 0)
            continue;
        stringstream ss(line);
        int move, from, to;
        char trash;
        for (int i = 0; i < 4; i++)
            ss >> trash;
        ss >> move;
        for (int i = 0; i < 4; i++)
            ss >> trash;
        ss >> from;
        for (int i = 0; i < 2; i++)
            ss >> trash;
        ss >> to;

        for (int i = 0; i < move; i++) {
            char c = columns[from - 1].back();
            columns[from - 1].pop_back();
            columns[to - 1].push_back(c);
        }
    }

    for (auto& c : columns) {
        cout << c.back();
    }
    cout << endl;
}

void task2() {
    ifstream input("input5.txt");
    string line;
    vector<vector<char>> columns(9);

    while (getline(input, line)) {
        if (line.size() == 0)
            break;
        char c = line[1];
        if (c >= '0' && c <= '9')
            break;

        for (int i = 1; i < line.size(); i += 4) {
            if (line[i] >= 'A' && line[i] <= 'Z')
                columns[i / 4].insert(columns[i / 4].begin(), line[i]);
        }
    }

    while (getline(input, line)) {
        if (line.size() == 0)
            continue;
        stringstream ss(line);
        int move, from, to;
        char trash;
        for (int i = 0; i < 4; i++)
            ss >> trash;
        ss >> move;
        for (int i = 0; i < 4; i++)
            ss >> trash;
        ss >> from;
        for (int i = 0; i < 2; i++)
            ss >> trash;
        ss >> to;

        vector<char> temp;
        for (int i = 0; i < move; i++) {
            char c = columns[from - 1].back();
            columns[from - 1].pop_back();
            temp.push_back(c);
        }
        for (int i = temp.size() - 1; i >= 0; i--) {
            columns[to - 1].push_back(temp[i]);
        }
    }

    for (auto& c : columns) {
        cout << c.back();
    }
    cout << endl;
}

int main() {
    task1();
    task2();
}