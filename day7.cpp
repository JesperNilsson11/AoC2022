#include "common.h"

class Dir {
public:
    Dir(string n, Dir* p) : name(n), parent(p) {}

    string name;
    Dir* parent = nullptr;
    vector<Dir> subdirs;
    int sum = 0;
};

int global_sum = 0;
int s = 0;

int search(Dir* c) {
    for (int i = 0; i < c->subdirs.size(); i++) {
        int temp = search(&c->subdirs[i]);

        c->sum += temp;

        if (temp <= 100000) {
            global_sum += temp;
        }
    }

    return c->sum;
}

int search_min(Dir* c, int min, int above) {
    if (c->sum < min && c->sum >= above) {
        min = c->sum;
    }

    for (int i = 0; i < c->subdirs.size(); i++) {
        int temp = search_min(&c->subdirs[i], min, above);

        if (temp < min)
            min = temp;
    }

    return min;
}

int main() {
    ifstream input("input7.txt");
    string line;
    int sum = 0;
    Dir* current = nullptr;
    Dir root("/", nullptr);

    while (getline(input, line)) {
        if (line[2] == 'c' && line[3] == 'd') {
            stringstream ss(line);
            string dir;
            ss >> dir;
            ss >> dir;
            ss >> dir;

            if ("/" == dir) {
                current = &root;
            } else if (".." == dir) {
                current = current->parent;
            } else {
                bool found = false;

                for (int i = 0; i < current->subdirs.size() && !found; i++) {
                    if (current->subdirs[i].name == dir) {
                        current = &current->subdirs[i];
                        found = true;
                    }
                }

                if (!found)
                    cout << "Error finding " << dir << endl;
            }
        } else if (line[2] == 'l' && line[3] == 's') {
            continue;
        } else if (line[0] == 'd' && line[1] == 'i' && line[2] == 'r') {
            stringstream ss(line);
            string dir;
            ss >> dir;
            ss >> dir;

            current->subdirs.push_back(Dir(dir, current));
        } else {
            stringstream ss(line);
            int size;
            ss >> size;
            current->sum += size;
            s += size;
        }
    }

    search(&root);

    long long needed_deletion = (long long)30000000 - ((long long)70000000 - root.sum);
    
    cout << global_sum << endl;
    cout << search_min(&root, 70000000, needed_deletion) << endl;
}