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

struct Moves {
    int dist;
    char dir;
};

enum Direction {
    RIGHT,
    DOWN,
    LEFT,
    UP
};

unordered_map<vec2, char, vec2_hash> board;

void wrap_around(vec2& pos, int dir) {
    vec2 delta = {};
    vec2 newpos = pos;
    switch (dir) {
        case RIGHT:
            delta.x = -1;
            break;
        case DOWN:
            delta.y = -1;
            break;
        case LEFT:
            delta.x = 1;
            break;
        case UP:
            delta.y = 1;
            break;
        default:
            cout << "Error facing dir" << endl;
    }

    newpos = pos + delta;
    while (board.find(newpos) != board.end()) {
        pos = newpos;
        newpos = pos + delta;
    }
}

void wrap_cube(vec2& pos, int& dir, const vec2 topleft[6]) {
    int s = 50;
    int a = s - 1;
    int index = -1;
    for (int i = 0; i < 6; i++) {
        if (pos.x >= topleft[i].x && pos.x <= topleft[i].x + a &&
            pos.y >= topleft[i].y && pos.y <= topleft[i].y + a) {
                index = i;
                break;
            }
    }

    pos.x = (pos.x - 1) % s;
    pos.y = (pos.y - 1) % s;

#if 1
    if (index == 0) {
        if (dir == UP) {
            dir = RIGHT;
            pos.y = topleft[5].y + pos.x;
            pos.x = topleft[5].x;
        } else if (dir == LEFT) {
            dir = RIGHT;
            pos.y = topleft[3].y + (a - pos.y);
            pos.x = topleft[3].x;
        }
    } else if (index == 1) {
        if (dir == UP) {
            dir = UP;
            pos.x = topleft[5].x + pos.x; // ???????????????
            pos.y = topleft[5].y + a;
        } else if (dir == RIGHT) {
            dir = LEFT;
            pos.y = topleft[4].y + (a - pos.y);
            pos.x = topleft[4].x + a;
        } else if (dir == DOWN) {
            dir = LEFT;
            pos.y = topleft[2].y + pos.x;
            pos.x = topleft[2].x + a;
        }
    } else if (index == 2) {
        if (dir == LEFT) {
            dir = DOWN;
            pos.x = topleft[3].x + pos.y;
            pos.y = topleft[3].y;
        } else if (dir == RIGHT) {
            dir = UP;
            pos.x = topleft[1].x + pos.y;
            pos.y = topleft[1].y + a;
        }
    } else if (index == 3) {
        if (dir == UP) {
            dir = RIGHT;
            pos.y = topleft[2].y + pos.x;
            pos.x = topleft[2].x;
        } else if (dir == LEFT) {
            dir = RIGHT;
            pos.y = topleft[0].y + (a - pos.y);
            pos.x = topleft[0].x;
        }
    } else if (index == 4) {
        if (dir == RIGHT) {
            dir = LEFT;
            pos.y = topleft[1].y + (a - pos.y);
            pos.x = topleft[1].x + a;
        } else if (dir == DOWN) {
            dir = LEFT;
            pos.y = topleft[5].y + pos.x;
            pos.x = topleft[5].x + a;
        }
    } else if (index == 5) {
        if (dir == LEFT) {
            dir = DOWN;
            pos.x = topleft[0].x + pos.y;
            pos.y = topleft[0].y;
        } else if (dir == DOWN) {
            dir = DOWN;
            pos.x = topleft[1].x + pos.x;
            pos.y = topleft[1].y;
        } else if (dir == RIGHT) {
            dir = UP;
            pos.x = topleft[4].x + pos.y;
            pos.y = topleft[4].y + a;
        }
    }
#else
    if (index == 0) {
        if (dir == UP) {
            dir = DOWN;
            pos.x = topleft[1].x + (3 - pos.x);
            pos.y = topleft[1].y;
        } else if (dir == LEFT) {
            dir = DOWN;
            pos.x = topleft[2].x + pos.y;
            pos.y = topleft[2].y;
        } else if (dir == RIGHT) {
            dir = LEFT;
            pos.y = topleft[5].y + (3 - pos.y); 
            pos.x = topleft[5].x + 3;
        }
    } else if (index == 1) {
        if (dir == UP) {
            dir = DOWN;
            pos.x = topleft[0].x + (3 - pos.x);
            pos.y = topleft[0].y;
        } else if (dir == LEFT) {
            dir == UP;
            pos.x = topleft[5].x + pos.y;
            pos.y = topleft[5].y + 3;
        } else if (dir == DOWN) {
            dir = UP;
            pos.x = topleft[4].x + (3 - pos.x);
            pos.y = topleft[4].y + 3;
        }
    } else if (index == 2) {
        if (dir == UP) {
            dir = RIGHT;
            pos.y = topleft[0].y + pos.x;
            pos.x = topleft[0].x;
        } else if (dir == DOWN) {
            dir = RIGHT;
            pos.y = topleft[4].y + (3 - pos.x);
            pos.x = topleft[4].x;
        }
    } else if (index == 3) {
        if (dir == RIGHT) {
            dir = DOWN;
            pos.x = topleft[5].x + (3 - pos.y);
            pos.y = topleft[5].y;
        }
    } else if (index == 4) {
        if (dir == LEFT) {
            dir = UP;
            pos.x = topleft[2].x + (3 - pos.y);
            pos.y = topleft[2].y + 3;
        } else if (dir == DOWN) {
            dir = UP;
            pos.x = topleft[1].x + (3 - pos.x);
            pos.y = topleft[1].y + 3;
        }
    } else if (index == 5) {
        if (dir == UP) {
            dir = LEFT;
            pos.y = topleft[3].y + (3 - pos.x);
            pos.x = topleft[3].x + 3;
        } else if (dir == RIGHT) {
            dir = LEFT;
            pos.y = topleft[0].y + (3 - pos.y);
            pos.x = topleft[0].x + 3;
        } else if (dir == DOWN) {
            dir = RIGHT;
            pos.y = topleft[1].y + (3 - pos.x);
            pos.x = topleft[1].x;
        }
    }
#endif
}

void task1() {
    ifstream input("input22.txt");
    string line;
    //unordered_map<vec2, char, vec2_hash> map;
    vector<Moves> moves;
    bool firstline = true;
    vec2 pos = {1, 1};
    vec2 topleft = {};
    int facing = 0;

    while (getline(input, line)) {
        if (line.size() == 0)
            break;

        for (int i = 0; i < line.size(); i++) {
            char c = line[i];
            if (firstline && c == '.') {
                topleft = pos;
                firstline = false;
            }

            if (c != ' ')
                board[pos] = c;
            pos.x++;
        }

        pos.y++;
        pos.x = 1;
    }

    getline(input, line);
    int d;
    stringstream ss(line);
    while (ss >> d) {
        Moves m = {};
        m.dist = d;
        ss >> m.dir;
        moves.push_back(m);
    }

    pos = topleft;

    for (auto& m : moves) {
        for (int i = 0; i < m.dist; i++) {
            vec2 newpos = pos;

            switch (facing) {
            case RIGHT:
                newpos.x++;
                break;
            case DOWN:
                newpos.y++;
                break;
            case LEFT:
                newpos.x--;
                break;
            case UP:
                newpos.y--;
                break;
            default:
                cout << "Error facing dir" << endl;
            }

            auto p = board.find(newpos);
            if (p == board.end()) {
                wrap_around(newpos, facing);
            }

            if (board[newpos] == '#') {
                break;
            }

            pos = newpos;
        }

        if (m.dir == 'R') {
            facing++;
            facing %= 4;
        } else if (m.dir == 'L') {
            facing += 3;
            facing %= 4;
        }
    }

    int sum = pos.y * 1000 + 4 * pos.x + facing;
    cout << sum << endl;
}

void task2() {
    ifstream input("input22.txt");
    string line;
    //unordered_map<vec2, char, vec2_hash> map;
    vector<Moves> moves;
    vec2 pos = {1, 1};
    vec2 topleft[6];
    int facing = 0;

    int size = 50;
    int index = 0;

    while (getline(input, line)) {
        if (line.size() == 0)
            break;

        for (int i = 0; i < line.size(); i++) {
            char c = line[i];
            if (pos.x % size == 1 && pos.y % size == 1 && (c == '.' || c == '#')) {
                topleft[index++] = pos;
            }

            if (c != ' ')
                board[pos] = c;
            pos.x++;
        }

        pos.y++;
        pos.x = 1;
    }

    getline(input, line);
    int d;
    stringstream ss(line);
    while (ss >> d) {
        Moves m = {};
        m.dist = d;
        ss >> m.dir;
        moves.push_back(m);
    }

    pos = topleft[0];

    for (auto& m : moves) {
        for (int i = 0; i < m.dist; i++) {
            vec2 newpos = pos;
            int newfacing = facing;

            switch (facing) {
            case RIGHT:
                newpos.x++;
                break;
            case DOWN:
                newpos.y++;
                break;
            case LEFT:
                newpos.x--;
                break;
            case UP:
                newpos.y--;
                break;
            default:
                cout << "Error facing dir" << endl;
            }

            auto p = board.find(newpos);
            if (p == board.end()) {
                newpos = pos;
                wrap_cube(newpos, newfacing, topleft);
            }

            if (board[newpos] == '#') {
                break;
            }

            pos = newpos;
            facing = newfacing;
        }

        if (m.dir == 'R') {
            facing++;
            facing %= 4;
        } else if (m.dir == 'L') {
            facing += 3;
            facing %= 4;
        }
    }

    int sum = pos.y * 1000 + 4 * pos.x + facing;
    cout << sum << endl;
}

int main() {
    task1();
    board.clear();
    task2();
}