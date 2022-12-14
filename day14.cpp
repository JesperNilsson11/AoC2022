#include "common.h"

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;  
    }
};

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

    bool operator!=(struct vec2 other) {
        return x != other.x || y != other.y;
    }
};

void task1() {
    ifstream input("input14.txt");
    string line;
    unordered_map<pair<int, int>, char, pair_hash> map;

    while (getline(input, line)) {
        vec2 current = {};
        char c;
        int steps;
        vec2 move = {};
        string arrow;
        stringstream ss(line);

        ss >> current.x;
        ss >> c;
        ss >> current.y;

        while (ss >> arrow) {
            vec2 coord;
            ss >> coord.x;
            ss >> c;
            ss >> coord.y;

            vec2 delta = coord - current;
            if (delta.x != 0) {
                delta.x = delta.x / abs(delta.x);
            }
            if (delta.y != 0) {
                delta.y = delta.y / abs(delta.y);
            }

            map[pair<int, int>(current.x, current.y)] = '#';

            while (current != coord) {
                current = current + delta;
                map[pair<int, int>(current.x, current.y)] = '#';
            }
        }
    }

    int xmax = 500;
    int xmin = 500;
    int ymax = 0;
    int ymin = 0;

    for (auto& p : map) {
        if (p.first.first > xmax) {
            xmax = p.first.first;
        } else if (p.first.first < xmin) {
            xmin = p.first.first;
        }

        if (p.first.second > ymax) {
            ymax = p.first.second;
        } else if (p.first.second < ymin) {
            ymin = p.first.second;
        }
    }

    for (int y = ymin; y <= ymax; y++) {
        for (int x = xmin; x <= xmax; x++) {
            if (map.find(pair<int, int>(x, y)) == map.end()) {
                map[pair<int, int>(x, y)] = '.';
            }
            map[pair<int, int>(x, y)];
        }
    }

    int sum = 0;
    vec2 dd = {0, 1};
    vec2 dl = {-1, 1};
    vec2 dr = {1, 1};
    vec2 sand = {500, 0};
    while (true) {
        vec2 newSand = sand + dd;
        char c = map[pair<int, int>(newSand.x, newSand.y)];

        if (c == '.') {
            sand = newSand;
            continue;
        } if (c != '#' && c != 'o') {
            break;
        }

        newSand = sand + dl;
        c = map[pair<int, int>(newSand.x, newSand.y)];

        if (c == '.') {
            sand = newSand;
            continue;
        } if (c != '#' && c != 'o') {
            break;
        }

        newSand = sand + dr;
        c = map[pair<int, int>(newSand.x, newSand.y)];

        if (c == '.') {
            sand = newSand;
            continue;
        } if (c != '#' && c != 'o') {
            break;
        }

        map[pair<int, int>(sand.x, sand.y)] = 'o';
        sum++;
        sand = {500, 0};
    }

    for (int y = 0; y < 10; y++) {
        for (int x = 494; x < 504; x++) {
            char c = ' ';
            if (map.find(pair<int, int>(x, y)) != map.end()) {
                c = map[pair<int, int>(x, y)];
            }
            cout << c;
        }
        cout << endl;
    }

    cout << sum << endl;
}

void task2() {
    ifstream input("input14.txt");
    string line;
    unordered_map<pair<int, int>, char, pair_hash> map;

    while (getline(input, line)) {
        vec2 current = {};
        char c;
        int steps;
        vec2 move = {};
        string arrow;
        stringstream ss(line);

        ss >> current.x;
        ss >> c;
        ss >> current.y;

        while (ss >> arrow) {
            vec2 coord;
            ss >> coord.x;
            ss >> c;
            ss >> coord.y;

            vec2 delta = coord - current;
            if (delta.x != 0) {
                delta.x = delta.x / abs(delta.x);
            }
            if (delta.y != 0) {
                delta.y = delta.y / abs(delta.y);
            }

            map[pair<int, int>(current.x, current.y)] = '#';

            while (current != coord) {
                current = current + delta;
                map[pair<int, int>(current.x, current.y)] = '#';
            }
        }
    }

    int xmax = 500;
    int xmin = 500;
    int ymax = 0;
    int ymin = 0;

    for (auto& p : map) {
        if (p.first.first > xmax) {
            xmax = p.first.first;
        } else if (p.first.first < xmin) {
            xmin = p.first.first;
        }

        if (p.first.second > ymax) {
            ymax = p.first.second;
        } else if (p.first.second < ymin) {
            ymin = p.first.second;
        }
    }

    xmin -= 200;
    xmax += 200;
    ymax += 2;

    for (int y = ymin; y < ymax; y++) {
        for (int x = xmin; x <= xmax; x++) {
            if (map.find(pair<int, int>(x, y)) == map.end()) {
                map[pair<int, int>(x, y)] = '.';
            }
            map[pair<int, int>(x, y)];
        }
    }

    for (int x = xmin; x <= xmax; x++) {
        map[pair<int, int>(x, ymax)] = '#';
    }

    int sum = 0;
    vec2 dd = {0, 1};
    vec2 dl = {-1, 1};
    vec2 dr = {1, 1};
    vec2 sand = {500, 0};
    while (true) {
        vec2 newSand = sand + dd;
        char c = map[pair<int, int>(newSand.x, newSand.y)];

        if (c == '.') {
            sand = newSand;
            continue;
        } if (/*c != '#' && c != 'o'*/ newSand.y == ymax) {
            //break;
            goto found_floor;
        }

        newSand = sand + dl;
        c = map[pair<int, int>(newSand.x, newSand.y)];

        if (c == '.') {
            sand = newSand;
            continue;
        } if (/*c != '#' && c != 'o'*/ newSand.y == ymax) {
            //break;
            goto found_floor;
        }

        newSand = sand + dr;
        c = map[pair<int, int>(newSand.x, newSand.y)];

        if (c == '.') {
            sand = newSand;
            continue;
        } /*if (c != '#' && c != 'o') {
            break;
        }*/

found_floor:
        map[pair<int, int>(sand.x, sand.y)] = 'o';
        sum++;
        if (sand.x == 500 && sand.y == 0) {
            cout << "exit" << endl;
            break;
        }
        sand = {500, 0};
    }

    /*for (int y = ymin; y <= ymax; y++) {
        for (int x = xmin; x <= xmax; x++) {
            char c = ' ';
            if (map.find(pair<int, int>(x, y)) != map.end()) {
                c = map[pair<int, int>(x, y)];
            }
            cout << c;
        }
        cout << endl;
    }*/

    cout << sum << endl;
}

int main() {
    task1();
    task2();
}