#include "common.h"

class CPU {
    public:
        CPU() = default;

        void instruction(string line) {
            stringstream ss(line);
            string instruction;

            ss >> instruction;
            signal += tick();

            if (instruction == "addx") {
                int num;
                ss >> num;
                signal += tick();
                x += num;
            }
        }

        void signalStrength() {
            cout << signal << endl;
        }

    private:
        int tick() {
            int row = clock / 40;
            int col = clock % 40;
            clock++;

            if (col > x + 1 || col < x - 1) {
                cout << ".";
            } else {
                cout << "#";
            }

            if (col == 39) {
                cout << endl;
            }

            if (clock == 20) {
                return 20 * x;
            } else if (clock == 60) {
                return 60 * x;
            } else if (clock == 100) {
                return 100 * x;
            } else if (clock == 140) {
                return 140 * x;
            } else if (clock == 180) {
                return 180 * x;
            } else if (clock == 220) {
                return 220 * x;
            }

            return 0;
        }
        
        int signal = 0;
        int clock = 0;
        int x = 1;
};

int main() {
    ifstream input("input10.txt");
    string line;
    CPU cpu;

    while (getline(input, line)) {
        cpu.instruction(line);
    }
    

    cpu.signalStrength();
}