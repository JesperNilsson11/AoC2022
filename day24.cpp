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

struct Blizzard {
    vec2 pos;
    vec2 velocity;
};

void move_blizzards(vector<Blizzard>& blizzards, int width, int height) {
    for (auto& b : blizzards) {
        b.pos = b.pos + b.velocity;
        if (b.pos.x < 0) {
            b.pos.x += width;
        } else if (b.pos.x >= width) {
            b.pos.x -= width;
        }

        if (b.pos.y < 0) {
            b.pos.y += height;
        } else if (b.pos.y >= height) {
            b.pos.y -= height;
        }
    }
}

void task1() {
    ifstream input("input24.txt");
    string line;
    int minutes = 0;
    int y = -1;
    vector<Blizzard> blizzards;
    bool foundstart = false;
    vec2 start = {};
    vec2 end = {};
    int width = 0;
    int height = 0;

    while (getline(input, line)) {
        width = line.size() - 2;
        for (int x = 0; x < line.size(); x++) {
            Blizzard b;
            if (line[x] == '>') {
                b.velocity = {1, 0};
            } else if (line[x] == 'v') {
                b.velocity = {0, 1};
            } else if (line[x] == '<') {
                b.velocity = {-1, 0};
            } else if (line[x] == '^') {
                b.velocity = {0, -1};
            } else if (line[x] == '.') {
                if (!foundstart) {
                    start = {x-1, y};
                    foundstart = true;
                }
                end = {x-1, y};
                continue;
            } else if (line[x] == '#') {
                continue;
            }

            b.pos = {x-1, y};
            blizzards.push_back(b);
        }
        y++;
    }
    height = y - 1;

    unordered_map<vec2, bool, vec2_hash> next_minute;
    next_minute[start] = true;

    while (!next_minute.empty()) {
        vector<vec2> positions;
        for (auto& nm : next_minute) {
            if (nm.second) {
                positions.push_back(nm.first);
            }
        }
        next_minute.clear();
        move_blizzards(blizzards, width, height);
        unordered_map<vec2, bool, vec2_hash> blizmap;
        for (auto&b : blizzards) {
            blizmap[b.pos] = true;
        }

        for (auto& p : positions) {
            bool found = false;
            vector<vec2> deltas = {vec2{0, 0}, vec2{1, 0}, vec2{-1, 0}, vec2{0, 1}, vec2{0, -1}};
            for (auto d : deltas) {
                vec2 pos = p + d;
                if (pos == end) {
                    next_minute.clear();
                    found = true;
                    break;
                }

                if (blizmap[pos] == true) {
                    continue;
                }

                if ((pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height) || pos == start) {
                    next_minute[pos] = true;
                }
            }

            if (found)
                break;
        }

        minutes++;
    }

    cout << minutes << endl;
}

void task2() {
    ifstream input("input24.txt");
    string line;
    int minutes = 0;
    int y = -1;
    vector<Blizzard> blizzards;
    bool foundstart = false;
    vec2 start = {};
    vec2 end = {};
    int width = 0;
    int height = 0;

    while (getline(input, line)) {
        width = line.size() - 2;
        for (int x = 0; x < line.size(); x++) {
            Blizzard b;
            if (line[x] == '>') {
                b.velocity = {1, 0};
            } else if (line[x] == 'v') {
                b.velocity = {0, 1};
            } else if (line[x] == '<') {
                b.velocity = {-1, 0};
            } else if (line[x] == '^') {
                b.velocity = {0, -1};
            } else if (line[x] == '.') {
                if (!foundstart) {
                    start = {x-1, y};
                    foundstart = true;
                }
                end = {x-1, y};
                continue;
            } else if (line[x] == '#') {
                continue;
            }

            b.pos = {x-1, y};
            blizzards.push_back(b);
        }
        y++;
    }
    height = y - 1;

    unordered_map<vec2, bool, vec2_hash> next_minute;
    next_minute[start] = true;

    while (!next_minute.empty()) {
        vector<vec2> positions;
        for (auto& nm : next_minute) {
            if (nm.second) {
                positions.push_back(nm.first);
            }
        }
        next_minute.clear();
        move_blizzards(blizzards, width, height);
        unordered_map<vec2, bool, vec2_hash> blizmap;
        for (auto&b : blizzards) {
            blizmap[b.pos] = true;
        }

        for (auto& p : positions) {
            bool found = false;

            vector<vec2> deltas = {vec2{0, 0}, vec2{1, 0}, vec2{-1, 0}, vec2{0, 1}, vec2{0, -1}};
            for (auto d : deltas) {
                vec2 pos = p + d;
                if (pos == end) {
                    next_minute.clear();
                    found = true;
                    break;
                }

                if (blizmap[pos] == true) {
                    continue;
                }

                if ((pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height) || pos == start) {
                    next_minute[pos] = true;
                }
            }

            if (found)
                break;
        }

        minutes++;
    }

    next_minute.clear();
    next_minute[end] = true;

    while (!next_minute.empty()) {
        vector<vec2> positions;
        for (auto& nm : next_minute) {
            if (nm.second) {
                positions.push_back(nm.first);
            }
        }
        next_minute.clear();
        move_blizzards(blizzards, width, height);
        unordered_map<vec2, bool, vec2_hash> blizmap;
        for (auto&b : blizzards) {
            blizmap[b.pos] = true;
        }

        for (auto& p : positions) {
            bool found = false;

            vector<vec2> deltas = {vec2{0, 0}, vec2{1, 0}, vec2{-1, 0}, vec2{0, 1}, vec2{0, -1}};
            for (auto d : deltas) {
                vec2 pos = p + d;
                if (pos == start) {
                    next_minute.clear();
                    found = true;
                    break;
                }

                if (blizmap[pos] == true) {
                    continue;
                }

                if ((pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height) || pos == end) {
                    next_minute[pos] = true;
                }
            }

            if (found)
                break;
        }

        minutes++;
    }

    next_minute.clear();
    next_minute[start] = true;
    while (!next_minute.empty()) {
        vector<vec2> positions;
        for (auto& nm : next_minute) {
            if (nm.second) {
                positions.push_back(nm.first);
            }
        }
        next_minute.clear();
        move_blizzards(blizzards, width, height);
        unordered_map<vec2, bool, vec2_hash> blizmap;
        for (auto&b : blizzards) {
            blizmap[b.pos] = true;
        }

        for (auto& p : positions) {
            bool found = false;

            vector<vec2> deltas = {vec2{0, 0}, vec2{1, 0}, vec2{-1, 0}, vec2{0, 1}, vec2{0, -1}};
            for (auto d : deltas) {
                vec2 pos = p + d;
                if (pos == end) {
                    next_minute.clear();
                    found = true;
                    break;
                }

                if (blizmap[pos] == true) {
                    continue;
                }

                if ((pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height) || pos == start) {
                    next_minute[pos] = true;
                }
            }

            if (found)
                break;
        }

        minutes++;
    }

    cout << minutes << endl;
}

int main() {
    task1();
    task2();
}