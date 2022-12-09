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
};

void task1() {
    ifstream input("input9.txt");
    string line;
    unordered_map<pair<int, int>, int, pair_hash> map;
    vec2 h = {};
    vec2 t = {};

    while (getline(input, line)) {
        char dir;
        int steps;
        vec2 move = {};
        stringstream ss(line);

        ss >> dir;
        ss >> steps;

        switch (dir) {
            case 'U':
                move.y = 1;
                break;
            case 'D':
                move.y = -1;
                break;
            case 'R':
                move.x = 1;
                break;
            case 'L':
                move.x = -1;
                break;
            default:
                cout << "Error in switch" << endl;
        }

        for (int i = 0; i < steps; i++) {
            h = h + move;
            vec2 delta = h - t;

            int d = abs(delta.x) | abs(delta.y);
            if (d > 1) {
                if (delta.x) {
                    t.x = t.x + delta.x / abs(delta.x);
                }
                if (delta.y) {
                    t.y = t.y + delta.y / abs(delta.y);
                }
            }

            map[pair<int, int>(t.x, t.y)];
        }
    }
    

    cout << map.size() << endl;
}

void task2() {
    ifstream input("input9.txt");
    string line;
    unordered_map<pair<int, int>, int, pair_hash> map;
    vec2 knots[10] = {};

    while (getline(input, line)) {
        char dir;
        int steps;
        vec2 move = {};
        stringstream ss(line);

        ss >> dir;
        ss >> steps;

        switch (dir) {
            case 'U':
                move.y = 1;
                break;
            case 'D':
                move.y = -1;
                break;
            case 'R':
                move.x = 1;
                break;
            case 'L':
                move.x = -1;
                break;
            default:
                cout << "Error in switch" << endl;
        }

        for (int i = 0; i < steps; i++) {
            knots[0] = knots[0] + move;

            for (int j = 0; j < 9; j++) {

            vec2 delta = knots[j] - knots[j+1];

            int d = abs(delta.x) | abs(delta.y);
            if (d > 1) {
                if (delta.x) {
                    knots[j+1].x = knots[j+1].x + delta.x / abs(delta.x);
                }
                if (delta.y) {
                    knots[j+1].y = knots[j+1].y + delta.y / abs(delta.y);
                }
            }
            }

            map[pair<int, int>(knots[9].x, knots[9].y)];
        }
    }
    

    cout << map.size() << endl;
}

int main() {
    task1();
    task2();
}