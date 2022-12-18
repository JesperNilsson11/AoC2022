#include "common.h"

struct Vec3 {
    int x;
    int y;
    int z;

    Vec3 operator-(Vec3 other) {
        Vec3 res = {};

        res.x = x - other.x;
        res.y = y - other.y;
        res.z = z - other.z;

        return res;
    }

    Vec3 operator+(Vec3 other) const {
        Vec3 res = {};

        res.x = x + other.x;
        res.y = y + other.y;
        res.z = z + other.z;

        return res;
    }

    Vec3 operator*(int f) {
        Vec3 res = {};

        res.x = x * f;
        res.y = y * f;
        res.z = z * f;

        return res;
    }

    bool operator==(Vec3 other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

struct Vec3_hash {
    std::size_t operator () (const Vec3 &p) const {
        return p.x + p.y * 256 + p.z * 16234;  
    }
};

void task1() {
    ifstream input("input18.txt");
    int sum = 0;
    string line;
    unordered_map<Vec3, int, Vec3_hash> faces;

    while (getline(input, line)) {
        stringstream ss(line);
        char c;
        Vec3 p;
        ss >> p.x;
        ss >> c;
        ss >> p.y;
        ss >> c;
        ss >> p.z;

        vector<Vec3> deltas = {{-1, 0, 0}, {1, 0, 0},
                                {0, -1, 0}, {0, 1, 0},
                                {0, 0, -1}, {0, 0, 1},};

        p = p * 2;
        for (auto d : deltas) {
            Vec3 temp = p + d;
            faces[temp]++;
        }
    }

    for (auto& p : faces) {
        if (p.second == 1)
            sum++;
    }

    cout << sum << endl;
}

enum Side {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    FORWARD,
    BACKWARD
};

struct Element {
    Vec3 pos;
    Side s;
};

Side getSide(Vec3 v) {
    if (v.x < 0)
        return RIGHT;
    else if (v.x > 0)
        return LEFT;
    else if (v.y < 0)
        return UP;
    else if (v.y > 0)
        return DOWN;
    else if (v.z > 0)
        return FORWARD;
    else if (v.z < 0)
        return BACKWARD;

    cout << "Error getSide" << endl;
    return RIGHT;
}

Side opposite(Side s) {
    if (s == UP)
        return DOWN;
    if (s == DOWN)
        return UP;
    if (s == LEFT)
        return RIGHT;
    if (s == RIGHT)
        return LEFT;
    if (s == FORWARD)
        return BACKWARD;
    if (s == BACKWARD)
        return FORWARD;

    cout << "Error opposite" << endl;
    return RIGHT;
}

void task2() {
    ifstream input("input18.txt");
    int sum = 0;
    string line;
    unordered_map<Vec3, int, Vec3_hash> faces;
    vector<Vec3> centers;
    Vec3 faceYmax = {};
    unordered_map<Vec3, bool, Vec3_hash> visited;

    while (getline(input, line)) {
        stringstream ss(line);
        char c;
        Vec3 p;
        ss >> p.x;
        ss >> c;
        ss >> p.y;
        ss >> c;
        ss >> p.z;

        vector<Vec3> deltas = {{-1, 0, 0}, {1, 0, 0},
                                {0, -1, 0}, {0, 1, 0},
                                {0, 0, -1}, {0, 0, 1},};

        p = p * 2;
        for (auto d : deltas) {
            Vec3 temp = p + d;
            faces[temp]++;
        }

        if (faceYmax.y < p.y + 1) {
            faceYmax = p;
            faceYmax.y += 1;
        }
    }

    list<Element> queue;
    queue.push_back({faceYmax, UP});

    while (!queue.empty()) {
        auto e = queue.front();
        queue.pop_front();

        if (visited[e.pos]) {
            continue;
        }
        visited[e.pos] = true;

        if (e.s == UP) {
            vector<Vec3> deltas = {{-1, 0, 0}, {1, 0, 0},
                                {0, 0, -1}, {0, 0, 1},};

            for (auto d : deltas) {
                Vec3 temp = e.pos + d;

                temp.y += 1;
                if (faces[temp] == 1) {
                    Side s = getSide(d);
                    queue.push_back({temp, s});
                    continue;
                }

                temp.y -= 1;
                temp = temp + d;
                if (faces[temp] == 1) {
                    queue.push_back({temp, e.s});
                    continue;
                }

                temp = temp - d;
                temp.y -= 1;
                if (faces[temp] == 1) {
                    Side s = getSide(d);
                    queue.push_back({temp, opposite(s)});
                    continue;
                }

                cout << "Did not find face wrong" << endl;
            }
        }

        if (e.s == DOWN) {
            vector<Vec3> deltas = {{-1, 0, 0}, {1, 0, 0},
                                {0, 0, -1}, {0, 0, 1},};

            for (auto d : deltas) {
                Vec3 temp = e.pos + d;

                temp.y -= 1;
                if (faces[temp] == 1) {
                    Side s = getSide(d);
                    queue.push_back({temp, s});
                    continue;
                }

                temp.y += 1;
                temp = temp + d;
                if (faces[temp] == 1) {
                    queue.push_back({temp, e.s});
                    continue;
                }

                temp = temp - d;
                temp.y += 1;
                if (faces[temp] == 1) {
                    Side s = getSide(d);
                    queue.push_back({temp, opposite(s)});
                    continue;
                }

                cout << "Did not find face wrong" << endl;
            }
        }

        if (e.s == LEFT) {
            vector<Vec3> deltas = {{0, -1, 0}, {0, 1, 0},
                                {0, 0, -1}, {0, 0, 1},};

            for (auto d : deltas) {
                Vec3 temp = e.pos + d;

                temp.x -= 1;
                if (faces[temp] == 1) {
                    Side s = getSide(d);
                    queue.push_back({temp, s});
                    continue;
                }

                temp.x += 1;
                temp = temp + d;
                if (faces[temp] == 1) {
                    queue.push_back({temp, e.s});
                    continue;
                }

                temp = temp - d;
                temp.x += 1;
                if (faces[temp] == 1) {
                    Side s = getSide(d);
                    queue.push_back({temp, opposite(s)});
                    continue;
                }

                cout << "Did not find face wrong" << endl;
            }
        }

        if (e.s == RIGHT) {
            vector<Vec3> deltas = {{0, -1, 0}, {0, 1, 0},
                                {0, 0, -1}, {0, 0, 1},};

            for (auto d : deltas) {
                Vec3 temp = e.pos + d;

                temp.x += 1;
                if (faces[temp] == 1) {
                    Side s = getSide(d);
                    queue.push_back({temp, s});
                    continue;
                }

                temp.x -= 1;
                temp = temp + d;
                if (faces[temp] == 1) {
                    queue.push_back({temp, e.s});
                    continue;
                }

                temp = temp - d;
                temp.x -= 1;
                if (faces[temp] == 1) {
                    Side s = getSide(d);
                    queue.push_back({temp, opposite(s)});
                    continue;
                }

                cout << "Did not find face wrong" << endl;
            }
        }

        if (e.s == BACKWARD) {
            vector<Vec3> deltas = {{0, -1, 0}, {0, 1, 0},
                                {-1, 0, 0}, {1, 0, 0},};

            for (auto d : deltas) {
                Vec3 temp = e.pos + d;

                temp.z += 1;
                if (faces[temp] == 1) {
                    Side s = getSide(d);
                    queue.push_back({temp, s});
                    continue;
                }

                temp.z -= 1;
                temp = temp + d;
                if (faces[temp] == 1) {
                    queue.push_back({temp, e.s});
                    continue;
                }

                temp = temp - d;
                temp.z -= 1;
                if (faces[temp] == 1) {
                    Side s = getSide(d);
                    queue.push_back({temp, opposite(s)});
                    continue;
                }

                cout << "Did not find face wrong" << endl;
            }
        }

        if (e.s == FORWARD) {
            vector<Vec3> deltas = {{0, -1, 0}, {0, 1, 0},
                                {-1, 0, 0}, {1, 0, 0},};

            for (auto d : deltas) {
                Vec3 temp = e.pos + d;

                temp.z -= 1;
                if (faces[temp] == 1) {
                    Side s = getSide(d);
                    queue.push_back({temp, s});
                    continue;
                }

                temp.z += 1;
                temp = temp + d;
                if (faces[temp] == 1) {
                    queue.push_back({temp, e.s});
                    continue;
                }

                temp = temp - d;
                temp.z += 1;
                if (faces[temp] == 1) {
                    Side s = getSide(d);
                    queue.push_back({temp, opposite(s)});
                    continue;
                }

                cout << "Did not find face wrong" << endl;
            }
        }
    }

    for (auto& p : visited) {
        if (p.second == true)
            sum++;
    }
    cout << sum << endl;
}

int main() {
    task1();
    task2();
}