#include "common.h"

struct vec2 {
    int x;
    int y;

    struct vec2 operator-(struct vec2 other) {
        struct vec2 res = {};

        res.x = x - other.x;
        res.y = y - other.y;

        return res;
    }

    struct vec2 operator+(struct vec2 other) {
        struct vec2 res = {};

        res.x = x + other.x;
        res.y = y + other.y;

        return res;
    }
};

struct Element {
    Element(int _x, int _y, int s) : x(_x), y(_y), steps(s) {}
    int x;
    int y;
    int steps;
};

struct node {
    char c;
    bool visited = false;
};

void task1() {
    ifstream input("input12.txt");
    string line;
    vector<vector<node>> map;
    int x = 0;
    int y = 0;
    bool found = false;

    while (getline(input, line)) {
        vector<node> row;
        stringstream ss(line);
        char c;
         while (ss >> c) {
            if (c == 'S') {
                found = true;
                row.push_back({'a', true});
            } else {
                row.push_back({c, false});
                if (!found)
                    x++;
            }
         }

         map.push_back(row);
         if (!found) {
            y++;
            x = 0;
         }
    }

    list<Element> queue;
    queue.push_back(Element(x, y, 0));

    while (!queue.empty()) {
        Element e = queue.front();
        queue.pop_front();
        vector<vec2> deltas = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};

        for (auto& d : deltas) {
            vec2 index = d + vec2{e.x, e.y};

            if (index.y < 0 || index.y >= map.size() || index.x < 0 || index.x >= map[y].size()) {
                continue;
            } else if (map[index.y][index.x].c == 'E' && map[e.y][e.x].c + 1 >= 'z') {
                cout << e.steps + 1 << endl;
            } else if (map[e.y][e.x].c + 1 < map[index.y][index.x].c || map[index.y][index.x].visited) {
                continue;
            } else {
                queue.push_back(Element(index.x, index.y, e.steps + 1));
                map[index.y][index.x].visited = true;
            }
        }
    }
}

void task2() {
    ifstream input("input12.txt");
    string line;
    vector<vector<node>> map;
    vector<vector<node>> originalmap;
    int x;
    int y;
    bool found = false;

    while (getline(input, line)) {
        vector<node> row;
        stringstream ss(line);
        char c;
         while (ss >> c) {
            if (c == 'S') {
                found = true;
                row.push_back({'a', true});
            } else {
                row.push_back({c, false});
                if (!found)
                    x++;
            }
         }

         map.push_back(row);
         if (!found) {
            y++;
            x = 0;
         }
    }

    originalmap = map;
    int min = 1000;
    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[y].size(); x++) {
            if (map[y][x].c != 'a')
                continue;

            list<Element> queue;
            queue.push_back(Element(x, y, 0));
            map = originalmap;

            while (!queue.empty()) {
                Element e = queue.front();
                queue.pop_front();
                vector<vec2> deltas = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};

                for (auto& d : deltas) {
                    vec2 index = d + vec2{e.x, e.y};

                    if (index.y < 0 || index.y >= map.size() || index.x < 0 || index.x >= map[y].size()) {
                        continue;
                    } else if (map[index.y][index.x].c == 'E' && map[e.y][e.x].c + 1 >= 'z') {
                        if (e.steps + 1 < min) {
                            min = e.steps + 1;
                        }
                    } else if (map[e.y][e.x].c + 1 < map[index.y][index.x].c || map[index.y][index.x].visited) {
                        continue;
                    } else {
                        queue.push_back(Element(index.x, index.y, e.steps + 1));
                        map[index.y][index.x].visited = true;
                    }
                }
            }
        }
    }

    cout << min << endl;
}

int main() {
    task1();
    task2();
}