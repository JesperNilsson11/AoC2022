#include "common.h"

typedef long long int_64;

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

enum Shape {
    ROW,
    PLUS,
    J,
    COLUMN,
    SQUARE
};

struct Rock {
    int_64 x;
    int_64 y;
    Shape s;
};

unordered_map<pair<int_64, int_64>, bool, pair_hash> game;

void move_sideways(Rock& r, bool right) {
    if (r.s == ROW) {
        Rock rnew = r;
        if (right) {
            rnew.x++;
            if (rnew.x + 3 < 7 && game[pair<int_64 , int_64 >(rnew.x + 3, rnew.y)] == false) {
                r = rnew;
            }
        } else {
            rnew.x--;
            if (rnew.x >= 0 && game[pair<int_64 , int_64 >(rnew.x, rnew.y)] == false) {
                r = rnew;
            }
        }

        return;
    }

    if (r.s == PLUS) {
        Rock rnew = r;
        if (right) {
            rnew.x++;
            if (rnew.x + 1 < 7 && game[pair<int_64 , int_64 >(rnew.x + 1, rnew.y)] == false
                    && game[pair<int_64 , int_64 >(rnew.x, rnew.y + 1)] == false
                    && game[pair<int_64 , int_64 >(rnew.x, rnew.y - 1)] == false) {
                r = rnew;
            }
        } else {
            rnew.x--;
            if (rnew.x - 1 >= 0 && game[pair<int_64 , int_64 >(rnew.x - 1, rnew.y)] == false
                    && game[pair<int_64 , int_64 >(rnew.x, rnew.y + 1)] == false
                    && game[pair<int_64 , int_64 >(rnew.x, rnew.y - 1)] == false) {
                r = rnew;
            }
        }

        return;
    }

    if (r.s == J) {
        Rock rnew = r;
        if (right) {
            rnew.x++;
            if (rnew.x < 7 && game[pair<int_64 , int_64 >(rnew.x, rnew.y)] == false
                    && game[pair<int_64 , int_64 >(rnew.x, rnew.y + 1)] == false
                    && game[pair<int_64 , int_64 >(rnew.x, rnew.y + 2)] == false) {
                r = rnew;
            }
        } else {
            rnew.x--;
            if (rnew.x - 2 >= 0 && game[pair<int_64 , int_64 >(rnew.x - 2, rnew.y)] == false
                    && game[pair<int_64 , int_64 >(rnew.x, rnew.y + 1)] == false
                    && game[pair<int_64 , int_64 >(rnew.x, rnew.y + 2)] == false) {
                r = rnew;
            }
        }

        return;
    }

    if (r.s == COLUMN) {
        Rock rnew = r;
        if (right) {
            rnew.x++;
            if (rnew.x < 7 && game[pair<int_64 , int_64 >(rnew.x, rnew.y)] == false
                    && game[pair<int_64 , int_64 >(rnew.x, rnew.y - 1)] == false
                    && game[pair<int_64 , int_64 >(rnew.x, rnew.y - 2)] == false
                    && game[pair<int_64 , int_64 >(rnew.x, rnew.y - 3)] == false) {
                r = rnew;
            }
        } else {
            rnew.x--;
            if (rnew.x >= 0 && game[pair<int_64 , int_64 >(rnew.x, rnew.y)] == false
                    && game[pair<int_64 , int_64 >(rnew.x, rnew.y - 1)] == false
                    && game[pair<int_64 , int_64 >(rnew.x, rnew.y - 2)] == false
                    && game[pair<int_64 , int_64 >(rnew.x, rnew.y - 3)] == false) {
                r = rnew;
            }
        }

        return;
    }

    if (r.s == SQUARE) {
        Rock rnew = r;
        if (right) {
            rnew.x++;
            if (rnew.x + 1 < 7 && game[pair<int_64 , int_64 >(rnew.x + 1, rnew.y)] == false
                    && game[pair<int_64 , int_64 >(rnew.x + 1, rnew.y - 1)] == false) {
                r = rnew;
            }
        } else {
            rnew.x--;
            if (rnew.x >= 0 && game[pair<int_64 , int_64 >(rnew.x, rnew.y)] == false
                    && game[pair<int_64 , int_64 >(rnew.x, rnew.y - 1)] == false) {
                r = rnew;
            }
        }

        return;
    }
}

int_64 peak = 0;
vector<int_64> peaks(7);
bool move_down(Rock& r) {
    if (r.s == ROW) {
        Rock rnew = r;

        rnew.y--;
        if (rnew.y <= 0 ||
            game[pair<int_64 , int_64 >(rnew.x, rnew.y)] ||
            game[pair<int_64 , int_64 >(rnew.x + 1, rnew.y)] ||
            game[pair<int_64 , int_64 >(rnew.x + 2, rnew.y)] ||
            game[pair<int_64 , int_64 >(rnew.x + 3, rnew.y)]) {
            
            game[pair<int_64 , int_64 >(r.x, r.y)] = true;
            game[pair<int_64 , int_64 >(r.x + 1, r.y)] = true;
            game[pair<int_64 , int_64 >(r.x + 2, r.y)] = true;
            game[pair<int_64 , int_64 >(r.x + 3, r.y)] = true;

            if (r.y > peak)
                peak = r.y;

            peaks[r.x] = r.y;
            peaks[r.x+1] = r.y;
            peaks[r.x+2] = r.y;
            peaks[r.x+3] = r.y;

            return false;
        }
        r = rnew;
        return true;
    }

    if (r.s == PLUS) {
        Rock rnew = r;

        rnew.y--;
        if (rnew.y - 1 <= 0 ||
            game[pair<int_64 , int_64 >(rnew.x - 1, rnew.y)] ||
            game[pair<int_64 , int_64 >(rnew.x, rnew.y - 1)] ||
            game[pair<int_64 , int_64 >(rnew.x + 1, rnew.y)]) {
            
            game[pair<int_64 , int_64 >(r.x, r.y)] = true;
            game[pair<int_64 , int_64 >(r.x - 1, r.y)] = true;
            game[pair<int_64 , int_64 >(r.x, r.y - 1)] = true;
            game[pair<int_64 , int_64 >(r.x + 1, r.y)] = true;
            game[pair<int_64 , int_64 >(r.x, r.y + 1)] = true;

            if (r.y + 1 > peak)
                peak = r.y + 1;

            peaks[r.x] = r.y + 1;
            peaks[r.x-1] = r.y;
            peaks[r.x+1] = r.y;

            return false;
        }
        r = rnew;
        return true;
    }

    if (r.s == J) {
        Rock rnew = r;

        rnew.y--;
        if (rnew.y <= 0 ||
            game[pair<int_64 , int_64 >(rnew.x - 2, rnew.y)] ||
            game[pair<int_64 , int_64 >(rnew.x - 1, rnew.y)] ||
            game[pair<int_64 , int_64 >(rnew.x, rnew.y)]) {
            
            game[pair<int_64 , int_64 >(r.x, r.y)] = true;
            game[pair<int_64 , int_64 >(r.x - 1, r.y)] = true;
            game[pair<int_64 , int_64 >(r.x - 2, r.y)] = true;
            game[pair<int_64 , int_64 >(r.x, r.y + 1)] = true;
            game[pair<int_64 , int_64 >(r.x, r.y + 2)] = true;

            if (r.y + 2 > peak)
                peak = r.y + 2;
            peaks[r.x] = r.y + 2;
            peaks[r.x-1] = r.y;
            peaks[r.x-2] = r.y;

            return false;
        }
        r = rnew;
        return true;
    }

    if (r.s == COLUMN) {
        Rock rnew = r;

        rnew.y--;
        if (rnew.y - 3 <= 0 || game[pair<int_64 , int_64 >(rnew.x, rnew.y - 3)]) {
            
            game[pair<int_64 , int_64 >(r.x, r.y)] = true;
            game[pair<int_64 , int_64 >(r.x, r.y - 1)] = true;
            game[pair<int_64 , int_64 >(r.x, r.y - 2)] = true;
            game[pair<int_64 , int_64 >(r.x, r.y - 3)] = true;

            if (r.y > peak)
                peak = r.y;

            peaks[r.x] = r.y;

            return false;
        }
        r = rnew;
        return true;
    }

    Rock rnew = r;

    rnew.y--;
    if (rnew.y - 1 <= 0 || game[pair<int_64 , int_64 >(rnew.x, rnew.y - 1)] || game[pair<int_64 , int_64 >(rnew.x + 1, rnew.y - 1)]) {      
        game[pair<int_64 , int_64 >(r.x, r.y)] = true;
        game[pair<int_64 , int_64 >(r.x, r.y - 1)] = true;
        game[pair<int_64 , int_64 >(r.x + 1, r.y - 1)] = true;
        game[pair<int_64 , int_64 >(r.x + 1, r.y)] = true;

        if (r.y > peak)
            peak = r.y;

        peaks[r.x] = r.y;
        peaks[r.x+1] = r.y;

        return false;
    }
    r = rnew;
    return true;
}

void task1() {
    ifstream input("input17.txt");
    int_64 sum = 0;
    vector<bool> pattern;
    int_64 index = 0;
    char c;
    int_64 stones = 0;

    while (input >> c) {
        if (c == '>') {
            pattern.push_back(true);
        } else {
            pattern.push_back(false);
        }
    }

    Rock r{2, 4, ROW};

    while (stones < 2022) {
        bool moving = true;

        while (moving) {
            move_sideways(r, pattern[index]);
            index++;
            index %= pattern.size();

            moving = move_down(r);
        }

        stones++;
        int sh = (r.s + 1) % 5;
        r.s = (Shape)sh;
        if (r.s == ROW) {
            r.x = 2;
            r.y = peak + 4;
        } else if (r.s == PLUS) {
            r.x = 3;
            r.y = peak + 5;
        } else if (r.s == J) {
            r.x = 4;
            r.y = peak + 4;
        } else if (r.s == COLUMN) {
            r.x = 2;
            r.y = peak + 7;
        } else if (r.s == SQUARE) {
            r.x = 2;
            r.y = peak + 5;
        }
    }

    cout << peak << endl;
}

struct Position {
    int deltas[7];
    int index = 0;

    bool operator==(const Position& p) const {
        for (int i = 0; i < 7; i++) {
            if (deltas[i] != p.deltas[i])
                return false;
        }

        return index == p.index;
    }
};

struct pos_hash {
    std::size_t operator () (const Position &p) const {
        size_t hash = 0;
        for (int i = 0; i < 7; i++) {
            hash += p.deltas[i] * (10 * i);
        }

        return hash;  
    }
};

struct Data {
    int_64 stones;
    int_64 peak;
};

void task2() {
    ifstream input("input17.txt");
    int_64 sum = 0;
    vector<bool> pattern;
    int_64 index = 0;
    char c;
    int_64 stones = 0;

    while (input >> c) {
        if (c == '>') {
            pattern.push_back(true);
        } else {
            pattern.push_back(false);
        }
    }

    Rock r{2, 4, ROW};
    unordered_map<Position, Data, pos_hash> deltas;
    int_64 offset = 0;
    bool found = false;

    while (stones < 1000000000000) {
        bool moving = true;

        while (moving) {
            move_sideways(r, pattern[index]);
            index++;
            index %= pattern.size();

            moving = move_down(r);
        }

        stones++;
        int sh = (r.s + 1) % 5;
        r.s = (Shape)sh;
        if (r.s == ROW) {
            r.x = 2;
            r.y = peak + 4;
            Position p;
            p.index = index;
            for (int i = 0; i < 7; i++) {
                p.deltas[i] = r.y - peaks[i];
            }

            auto d = deltas.find(p);
            if (d == deltas.end()) {
                deltas[p] = {stones, peak};
                continue;
            }

            if (found)
                continue;
            
            found = true;
            int_64 diffstones = stones - d->second.stones;
            int_64 diffpeaks = peak - d->second.peak;

            int_64 turnsleft = 1000000000000 - stones;
            int_64 div = turnsleft / diffstones;
            int_64 rest = turnsleft % diffstones;
            offset = div * diffpeaks;
            stones = 1000000000000 - rest;
        } else if (r.s == PLUS) {
            r.x = 3;
            r.y = peak + 5;
        } else if (r.s == J) {
            r.x = 4;
            r.y = peak + 4;
        } else if (r.s == COLUMN) {
            r.x = 2;
            r.y = peak + 7;
        } else if (r.s == SQUARE) {
            r.x = 2;
            r.y = peak + 5;
        }
    }

    cout << peak + offset << endl;
}

int main() {
    task1();
    game.clear();
    peak = 0;
    peaks.clear();
    peaks.resize(7);
    task2();
}