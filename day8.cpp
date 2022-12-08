#include "common.h"

bool visable(vector<vector<int>>& grid, int x, int y) {
    int cx = x, cy = y;
    bool left = true;

    while (cx > 0) {
        cx--;

        if (grid[y][x] <= grid[cy][cx]) {
            left = false;
            break;
        }
    }

    if (left) {
        return true;
    }

    cx = x;
    cy = y;
    bool right = true;
    while (cx < grid[y].size() - 1) {
        cx++;

        if (grid[y][x] <= grid[cy][cx]) {
            right = false;
            break;
        }
    }

    if (right) {
        return true;
    }

    cx = x;
    cy = y;
    bool up = true;
    while (cy > 0) {
        cy--;

        if (grid[y][x] <= grid[cy][cx]) {
            up = false;
            break;
        }
    }

    if (up) {
        return true;
    }

    cx = x;
    cy = y;
    bool down = true;
    while (cy < grid.size() - 1) {
        cy++;

        if (grid[y][x] <= grid[cy][cx]) {
            down = false;
            break;
        }
    }

    if (down) {
        return true;
    }

    return false;
}

int score(vector<vector<int>>& grid, int x, int y) {
    int cx = x, cy = y;
    int left = 0;

    while (cx > 0) {
        cx--;

            left++;
        if (grid[y][x] <= grid[cy][cx]) {
            break;
        }
    }

    cx = x;
    cy = y;
    int right = 0;
    while (cx < grid[y].size() - 1) {
        cx++;

            right++;
        if (grid[y][x] <= grid[cy][cx]) {
            break;
        }
    }

    cx = x;
    cy = y;
    int up = 0;
    while (cy > 0) {
        cy--;

            up++;
        if (grid[y][x] <= grid[cy][cx]) {
            break;
        }
    }

    cx = x;
    cy = y;
    int down = 0;
    while (cy < grid.size() - 1) {
        cy++;

            down++;
        if (grid[y][x] <= grid[cy][cx]) {
            break;
        }
    }

    return left * right * up * down;
}

void task1() {
    ifstream input("input8.txt");
    string line;
    int sum = 0;
    vector<vector<int>> grid;
    
    while (getline(input, line)) {
        stringstream ss(line);
        vector<int> temp;
        char c;
        while (ss >> c) {
            temp.push_back(c - '0');
        }

        grid.push_back(temp);
    }

    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            if (visable(grid, x, y)) {
                sum++;
            }
        }
    }

    cout << sum << endl;
}

void task2() {
    ifstream input("input8.txt");
    string line;
    int max = 0;
    vector<vector<int>> grid;
    
    while (getline(input, line)) {
        stringstream ss(line);
        vector<int> temp;
        char c;
        while (ss >> c) {
            temp.push_back(c - '0');
        }

        grid.push_back(temp);
    }

    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            int temp = score(grid, x, y);
            if (temp > max)
                max = temp;
        }
    }
    cout << max << endl;
}

int main() {
    task1();
    task2();
}