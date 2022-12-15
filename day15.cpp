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

    struct vec2 operator+(struct vec2 other) const {
        struct vec2 res = {};

        res.x = x + other.x;
        res.y = y + other.y;

        return res;
    }

    bool operator!=(struct vec2 other) {
        return x != other.x || y != other.y;
    }

    bool operator==(struct vec2 other) const {
        return x == other.x && y == other.y;
    }
};

struct vec2_hash {
    std::size_t operator () (const vec2 &v) const {
        return v.x << 32 | v.y;  
    }
};

struct sensor {
    vec2 s;
    vec2 b;
};

void task1() {
    ifstream input("input15.txt");
    string line;
    unordered_map<int, char> map;
    vector<sensor> sensors;

    while (getline(input, line)) {
        sensor s;
        string temp;
        char c;

        stringstream ss(line);
        ss >> temp;
        ss >> temp;
        ss >> c;
        ss >> c;

        ss >> s.s.x;
        ss >> c;
        ss >> c;
        ss >> c;
        ss >> s.s.y;

        ss >> temp;
        ss >> temp;
        ss >> temp;
        ss >> temp;
        ss >> temp;

        ss >> c;
        ss >> c;

        ss >> s.b.x;
        ss >> c;
        ss >> c;
        ss >> c;
        ss >> s.b.y;

        sensors.push_back(s);
    }

    int row = 2000000;
    //row = 10;
    sort(sensors.begin(), sensors.end(), [](sensor s1, sensor s2) -> bool {
        return s1.s.x < s2.s.x;
        });

    int sum = 0;
    for (auto& s : sensors) {
        vec2 delta = s.b - s.s;
        int distance = abs(delta.x) + abs(delta.y);

        if (distance + s.s.y < row || s.s.y - distance > row) {
            continue;
        }

        int dy = row - s.s.y;
        for (int x = 0; x <= (distance - abs(dy)); x++) {
            map[s.s.x + x] = '#';
            map[s.s.x + -x] = '#';
        }
    }

    for (auto& s : sensors) {
        if (s.b.y == row)
            map[s.b.x] = 'B';
    }

    for (auto& p : map) {
        if (p.second == '#') {
            sum++;
        }
    }

    cout << sum << endl;
}

void task2() {
    ifstream input("input15.txt");
    string line;
    vector<sensor> sensors;

    while (getline(input, line)) {
        sensor s;
        string temp;
        char c;

        stringstream ss(line);
        ss >> temp;
        ss >> temp;
        ss >> c;
        ss >> c;

        ss >> s.s.x;
        ss >> c;
        ss >> c;
        ss >> c;
        ss >> s.s.y;

        ss >> temp;
        ss >> temp;
        ss >> temp;
        ss >> temp;
        ss >> temp;

        ss >> c;
        ss >> c;

        ss >> s.b.x;
        ss >> c;
        ss >> c;
        ss >> c;
        ss >> s.b.y;

        sensors.push_back(s);
    }


    int larger = 4000000 + 1;
    int ss = 0;

    sort(sensors.begin(), sensors.end(), [](sensor s1, sensor s2) -> bool {
        return s1.s.x < s2.s.x;
        });

    for (int row = 0; row < larger; row++) {
        int minx = 0;

        for (auto& s : sensors) {
            vec2 delta = s.b - s.s;
            int distance = abs(delta.x) + abs(delta.y);

            if (distance + s.s.y <= row || s.s.y - distance >= row) {
                continue;
            }

            int dy = row - s.s.y;
            int x = -(distance - abs(dy));
            int bx = s.s.x + x;
            if (bx <= minx) {
                x = distance - abs(dy);
                if (x >= larger) {
                    x = larger - 1;
                }
                bx = s.s.x + x;

                if (bx > minx)
                    minx = bx;
            }
        }

        if (minx < larger - 1) {
            for (int x = 0; x < larger; x++) {
                bool found = false;
                for (auto& s : sensors) {
                    vec2 delta = s.b - s.s;
                    vec2 d = vec2{x, row} - s.s;
                    int distance = abs(delta.x) + abs(delta.y);
                    int dist = abs(d.x) + abs(d.y);

                    if (dist < distance) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << (long long)x * 4000000 + row << endl;
                    return;
                }
            }
        }
    }
}

int main() {
    cout << "task2: ";
    task2();
    cout << "task1: ";
    task1();
}