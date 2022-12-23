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
        return (long long)v.x << 31 | v.y;  
    }
};

struct Elves {
    vec2 pos;
    vec2 newpos;
};

void task1() {
    ifstream input("input23.txt");
    string line;
    int sum = 0;
    int y = 0;
    vector<Elves> elves;
    unordered_map<vec2, bool, vec2_hash> positions;

    while (getline(input, line)) {
        for (int x = 0; x < line.size(); x++) {
            if (line[x] == '.')
                continue;

            Elves e = {};
            e.pos = {x, y};
            elves.push_back(e);
            positions[e.pos] = true;
        }
        y++;
    }

    int firstdir = 0;
    for (int round = 0; round < 10; round++) {
        unordered_map<vec2, int, vec2_hash> newpositions;
        for (auto& e : elves) {
            bool wantstomove = false;
            for (int y = -1; y <= 1 && !wantstomove; y++) {
                for (int x = -1; x <= 1 && !wantstomove; x++) {
                    if (y == 0 && x == 0)
                        continue;

                    if (positions[vec2{e.pos.x+x, e.pos.y+y}]) {
                        wantstomove = true;
                        break;
                    }
                }
            }

            e.newpos = e.pos;
            if (wantstomove) {
                vector<vector<vec2>> deltas = {{{-1, -1}, {0, -1}, {1, -1}},
                                                {{-1, 1}, {0, 1}, {1, 1}},
                                                {{-1, -1}, {-1, 0}, {-1, 1}},
                                                {{1, -1}, {1, 0}, {1, 1}}};
                for (int i = 0; i < 4; i++) {
                    auto d = deltas[(firstdir + i) % 4];

                    if (!positions[e.pos + d[0]] && !positions[e.pos + d[1]] && !positions[e.pos+d[2]]) {
                        e.newpos = e.pos + d[1];
                        break;
                    }
                }
            }

            newpositions[e.newpos]++;
        }

        positions.clear();
        for (auto& e : elves) {
            if (newpositions[e.newpos] == 1) {
                e.pos = e.newpos;
            }

            positions[e.pos] = true;
        }

        firstdir = (firstdir + 1) % 4;
    }   

    vec2 min = elves[0].pos;
    vec2 max = elves[0].pos;
    for (auto& e : elves) {
        if (min.x > e.pos.x)
            min.x = e.pos.x;
        if (min.y > e.pos.y)
            min.y = e.pos.y;
        if (max.x < e.pos.x)
            max.x = e.pos.x;
        if (max.y < e.pos.y)
            max.y = e.pos.y;
    }

    int width = max.x - min.x + 1;
    int height = max.y - min.y + 1;
    int size = height * width;
    sum = size - elves.size();

    cout << sum << endl;
}

void task2() {
    ifstream input("input23.txt");
    string line;
    int sum = 0;
    int y = 0;
    vector<Elves> elves;
    unordered_map<vec2, bool, vec2_hash> positions;

    while (getline(input, line)) {
        for (int x = 0; x < line.size(); x++) {
            if (line[x] == '.')
                continue;

            Elves e = {};
            e.pos = {x, y};
            elves.push_back(e);
            positions[e.pos] = true;
        }
        y++;
    }

    int firstdir = 0;
    int round = 0;
    bool nobodymoved = false;
    while (!nobodymoved) {
        nobodymoved = true;
        unordered_map<vec2, int, vec2_hash> newpositions;
        for (auto& e : elves) {
            bool wantstomove = false;
            for (int y = -1; y <= 1 && !wantstomove; y++) {
                for (int x = -1; x <= 1 && !wantstomove; x++) {
                    if (y == 0 && x == 0)
                        continue;

                    if (positions[vec2{e.pos.x+x, e.pos.y+y}]) {
                        wantstomove = true;
                        break;
                    }
                }
            }

            e.newpos = e.pos;
            if (wantstomove) {
                vector<vector<vec2>> deltas = {{{-1, -1}, {0, -1}, {1, -1}},
                                                {{-1, 1}, {0, 1}, {1, 1}},
                                                {{-1, -1}, {-1, 0}, {-1, 1}},
                                                {{1, -1}, {1, 0}, {1, 1}}};
                for (int i = 0; i < 4; i++) {
                    auto d = deltas[(firstdir + i) % 4];

                    if (!positions[e.pos + d[0]] && !positions[e.pos + d[1]] && !positions[e.pos+d[2]]) {
                        e.newpos = e.pos + d[1];
                        break;
                    }
                }
            }

            newpositions[e.newpos]++;
        }

        positions.clear();
        for (auto& e : elves) {
            if (newpositions[e.newpos] == 1) {
                if (e.pos != e.newpos) {
                    nobodymoved = false;
                }
                
                e.pos = e.newpos;
            }

            positions[e.pos] = true;
        }

        firstdir = (firstdir + 1) % 4;
        round++;
    }   

    cout << round << endl;
}

int main() {
    task1();
    task2();
}