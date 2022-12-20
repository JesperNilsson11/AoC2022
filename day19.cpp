#include "common.h"

struct Robot_Costs {
    int ore_cost;
    int clay_cost;

    int obsidian_ore;
    int obsidian_clay;

    int geode_ore;
    int geode_obsidian;
};

struct Robots {
    Robot_Costs rc;
    int ore_robots;
    int clay_robots;
    int obsidian_robots;
    int geode_robots;

    int ore;
    int clay;
    int obsidian;
    int geodes;

    int max_ore_robots;
};

int max_geodes(const Robots& robots, int minute, int turns) {
    int max = 0;

    for (int i = 0; i < 4; i++) {
        Robots r = robots;
        int min = minute;
        int neededore = 0;
        int neededclay = 0;
        int neededobsidian = 0;
        
        if (i == 3) {
            neededore = r.rc.ore_cost;
            if (r.ore_robots >= r.max_ore_robots)
                continue;
        } else if (i == 2) {
            neededore = r.rc.clay_cost;
            if (r.clay_robots >= r.rc.obsidian_clay)
                continue;
        } else if (i == 1) {
            neededore = r.rc.obsidian_ore;
            neededclay = r.rc.obsidian_clay;
            if (r.clay_robots == 0)
                continue;
        } else if (i == 0) {
            neededore = r.rc.geode_ore;
            neededobsidian = r.rc.geode_obsidian;
            if (r.obsidian_robots == 0)
                continue;
        }

        bool exited = false;
        while (neededore > r.ore || neededclay > r.clay || neededobsidian > r.obsidian) {
            min++;
            r.ore += r.ore_robots;
            r.clay += r.clay_robots;
            r.obsidian += r.obsidian_robots;
            r.geodes += r.geode_robots;

            if (min >= 23) {
                if (min == 23)
                    r.geodes += r.geode_robots;
                if (max < r.geodes) {
                    max = r.geodes;
                }
                exited = true;
                break;
            }
        }
        if (exited)
            continue;

        min++;
        r.ore += r.ore_robots;
        r.clay += r.clay_robots;
        r.obsidian += r.obsidian_robots;
        r.geodes += r.geode_robots;

        if (i == 3) {
            r.ore -= r.rc.ore_cost;
            r.ore_robots++;
        } else if (i == 2) {
            r.ore -= r.rc.clay_cost;
            r.clay_robots++;
        } else if (i == 1) {
            r.ore -= r.rc.obsidian_ore;
            r.clay -= r.rc.obsidian_clay;
            r.obsidian_robots++;
        } else {
            r.ore -= r.rc.geode_ore;
            r.obsidian -= r.rc.geode_obsidian;
            r.geode_robots++;
        }

        if (min >= turns - 1) {
            if (min == turns - 1)
                r.geodes += r.geode_robots;
            if (max < r.geodes) {
                max = r.geodes;
            }
            continue;
        }

        int g = max_geodes(r, min, turns);
        if (g > max)
            max = g;
    }

    return max;
}

void task1() {
    ifstream input("input19.txt");
    int sum = 0;
    string line;
    int id = 0;
    while (getline(input, line)) {
        id++;
        stringstream ss(line);
        string temp;
        Robot_Costs r;

        for (int i = 0; i < 6; i++)
            ss >> temp;

        ss >> r.ore_cost;

        for (int i = 0; i < 5; i++)
            ss >> temp;
        ss >> r.clay_cost;

        for (int i = 0; i < 5; i++)
            ss >> temp;
        ss >> r.obsidian_ore;
        for (int i = 0; i < 2; i++)
            ss >> temp;
        ss >> r.obsidian_clay;

        for (int i = 0; i < 5; i++)
            ss >> temp;
        ss >> r.geode_ore;
        for (int i = 0; i < 2; i++)
            ss >> temp;
        ss >> r.geode_obsidian;

        Robots robots = {};
        robots.rc = r;
        robots.ore_robots = 1;
        robots.max_ore_robots = max(robots.rc.ore_cost, max(robots.rc.clay_cost, max(robots.rc.obsidian_ore, robots.rc.geode_ore)));
        int max = max_geodes(robots, 0, 24);
        sum += id * max;
    }

    cout << sum << endl;
}

void task2() {
    ifstream input("input19.txt");
    int sum = 0;
    string line;
    int id = 0;
    int maxes[3];
    while (getline(input, line)) {
        id++;
        stringstream ss(line);
        string temp;
        Robot_Costs r;

        for (int i = 0; i < 6; i++)
            ss >> temp;

        ss >> r.ore_cost;

        for (int i = 0; i < 5; i++)
            ss >> temp;
        ss >> r.clay_cost;

        for (int i = 0; i < 5; i++)
            ss >> temp;
        ss >> r.obsidian_ore;
        for (int i = 0; i < 2; i++)
            ss >> temp;
        ss >> r.obsidian_clay;

        for (int i = 0; i < 5; i++)
            ss >> temp;
        ss >> r.geode_ore;
        for (int i = 0; i < 2; i++)
            ss >> temp;
        ss >> r.geode_obsidian;

        Robots robots = {};
        robots.rc = r;
        robots.ore_robots = 1;
        robots.max_ore_robots = max(robots.rc.ore_cost, max(robots.rc.clay_cost, max(robots.rc.obsidian_ore, robots.rc.geode_ore)));
        int m = max_geodes(robots, 0, 32);
        maxes[id-1] = m;
        if (id == 3)
            break;
    }

    cout << maxes[0] * maxes[1] * maxes[2] << endl;
}

int main() {
    task1();
    task2();
}