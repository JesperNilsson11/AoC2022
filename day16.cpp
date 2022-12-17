#include "common.h"

unordered_map<string, int> map_cost;

struct Valve {
    string name;
    vector<string> paths;
    int flow;
};

struct Node {
    Valve* v = nullptr;
    bool visited = false;
};

struct Stats {
    int min = 0;
    int total = 0;
    int rate = 0;
};

struct Ele {
    int min = 0;
    int total = 0;
    int rate = 0;
    int steps = 0;
    int esteps = 0;
    Valve* current;
    Valve* ecurrent;
};

int gmax = 0;

int most_pressure(vector<Node>& nodes, Valve* current, Stats s) {
    int max = 0;
    bool all_visited = true;
    s.total += s.rate;
    s.min++;

    if (s.min >= 30) {
        return s.total;
    }

    for (auto& n : nodes) {
        int p = 0;
        if (n.visited) {
            continue;
        }
        all_visited = false;
        Stats ss = s;
        int cost = map_cost[current->name + n.v->name];
        for (int i = 0; i < cost; i++) {
            ss.total += ss.rate;
            ss.min++;
            if (ss.min >= 30) {
                if (ss.total > max) {
                    max = ss.total;
                }
                goto end;
            }
        }
        ss.rate += n.v->flow;
        n.visited = true;
        p = most_pressure(nodes, n.v, ss);
        n.visited = false;
end:
        if (p > max) {
            max = p;
        }
    }

    if (all_visited) {
        while (s.min < 30) {
            s.total += s.rate;
            s.min++;
        }

        if (s.total > max)
            max = s.total;
    }

    return max;
}

int ele_pressure(vector<Node>& nodes, Ele ele) {
    int max = 0;
    bool all_visited = true;
    for (auto& n : nodes) {
        if (!n.visited) {
            all_visited = false;
            break;
        }
    }

    if (all_visited && ele.steps < 0 && ele.esteps < 0) {
        while (true) {
            if (ele.min >= 26) {
                return ele.total;
             }

            ele.total += ele.rate;
            ele.min++;
            ele.steps--;
            ele.esteps--;
        }
    }

    while (ele.steps > 0 && ele.esteps > 0) {
        if (ele.min >= 26) {
            return ele.total;
        }

        ele.total += ele.rate;
        ele.min++;
        ele.steps--;
        ele.esteps--;
    }

    if (ele.min >= 26) {
        return ele.total;
    }

    if (ele.steps == 0 || ele.esteps == 0) {

    ele.total += ele.rate;
    ele.min++;
    if (ele.min >= 26) {
        return ele.total;
    }

    if (ele.steps == 0) {
        ele.rate += ele.current->flow;
    }
    if (ele.esteps == 0) {
        ele.rate += ele.ecurrent->flow;
    }

    ele.steps--;
    ele.esteps--;

    if (all_visited) {
        return ele_pressure(nodes, ele);
    }
    }


    for (auto& n : nodes) {
        if (n.visited)
            continue;
        int p = 0;
        Ele e = ele;

        if (e.steps < 0) {
            if (e.steps == 0)
                ele.rate += e.current->flow;
            int cost = map_cost[ele.current->name + n.v->name];
            e.steps = cost;
            e.current = n.v;
        } else if (e.esteps < 0) {
            if (e.esteps == 0)
                ele.rate += e.ecurrent->flow;
            int cost = map_cost[ele.ecurrent->name + n.v->name];
            e.esteps = cost;
            e.ecurrent = n.v;
        }

        n.visited = true;
        p = ele_pressure(nodes, e);
        n.visited = false;

        if (p > max) {
            max = p;
        }
    }

    if (gmax < max) {
        gmax = max;
        cout << max << " ";
    }

    return max;
}

int main() {
    ifstream input("input16.txt");
    string line;
    unordered_map<string, Valve> valves;
    vector<Valve*> vip_valves;

    while (getline(input, line)) {
        stringstream ss(line);
        string s;
        char c;
        Valve v;
        ss >> s;
        ss >> v.name;
        ss >> s;
        ss >> s;

        for (int i = 0; i < 5; i++) {
            ss >> c;
        }
        ss >> v.flow;
        for (int i = 0; i < 5; i++) {
            ss >> s;
        }

        while (ss >> s) {
            if (s.back() == ',') {
                s = s.substr(0, s.size() - 1);
            }
            v.paths.push_back(s);
        }

        valves[v.name] = v;
        if (v.flow > 0 || v.name == "AA") {
            vip_valves.push_back(&valves[v.name]);
        }
    }

    for (auto vv : vip_valves) {
        unordered_map<string, bool> nodes;
        list<pair<Valve*, int>> queue;
        
        queue.push_back({vv, 0});
        nodes[vv->name] = true;
        while (!queue.empty()) {
            auto p = queue.front();
            auto v = p.first;
            queue.pop_front();

            for (auto& e : v->paths) {
                if (nodes[e])
                    continue;

                string key = vv->name + e;
                map_cost[key] = p.second + 1;
                queue.push_back({&valves[e], p.second + 1});
                nodes[e] = true;
            }
        }
    }

    sort(vip_valves.begin(), vip_valves.end(), [](Valve* v1, Valve* v2) -> bool {
        return v1->flow > v2->flow;
    });

    vector<Node> vip;
    for (auto v : vip_valves) {
        vip.push_back({v, false});
    }
    int res = most_pressure(vip, vip.back().v, {});
    cout << "task1: " << res << endl;
    res = ele_pressure(vip, Ele{0, 0, 0, -1, -1, vip.back().v, vip.back().v});
    cout << "task2: " << res << endl;
}
