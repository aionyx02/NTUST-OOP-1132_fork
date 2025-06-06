#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int64_t mem_size, cmd_count;

    string inp_method;
    int64_t inp_pos;
    string inp_type;

    string inp_value_string;
    uint64_t inp_value;

    cin >> mem_size >> cmd_count;
    auto* mem = new uint8_t[mem_size + 1]; // store '\0'
    memset(mem, '\0', mem_size + 1);

    for (int cmd = 0; cmd < cmd_count; ++cmd) {
        cin >> inp_method >> inp_pos >> inp_type;

        if (inp_method == "Set") {
            if (inp_type == "String") {
                cin >> ws;
                getline(cin, inp_value_string);

                for (size_t i = 0; i < inp_value_string.size(); ++i) {
                    if (inp_pos + i >= mem_size) {
                        cout << "Violation Access.\n";
                        break;
                    }
                    mem[inp_pos + i] = inp_value_string[i];
                }

            } else if (inp_type == "int") {
                cin >> inp_value;

                for (int i = 0; i < 4; ++i, inp_value >>= 8) {
                    if (inp_pos + i >= mem_size) {
                        cout << "Violation Access.\n";
                        break;
                    }
                    mem[inp_pos + i] = inp_value & 0xFF;
                }

            } else if (inp_type == "short") {
                cin >> inp_value;

                for (int i = 0; i < 2; ++i, inp_value >>= 8) {
                    if (inp_pos + i >= mem_size) {
                        cout << "Violation Access.\n";
                        break;
                    }
                    mem[inp_pos + i] = inp_value & 0xFF;
                }

            } else if (inp_type == "char") {
                cin >> inp_value;
                if (inp_pos >= mem_size) {
                    cout << "Violation Access.\n";
                    continue;
                }
                mem[inp_pos] = inp_value;
            }
        }

        if (inp_method == "Get") {
            if (inp_pos >= mem_size) {
                cout << "Violation Access.\n";
                continue;
            }

            if (inp_type == "String") {
                cout << mem + inp_pos << '\n';
            } else if (inp_type == "int") {
                if (inp_pos + 3 >= mem_size) {
                    cout << "Violation Access.\n";
                    continue;
                }

                cout << *reinterpret_cast<uint32_t*>(mem + inp_pos) << '\n';
            } else if (inp_type == "short") {
                if (inp_pos + 1 >= mem_size) {
                    cout << "Violation Access.\n";
                    continue;
                }
                cout << *reinterpret_cast<uint16_t*>(mem + inp_pos) << '\n';
            } else if (inp_type == "char") {
                cout << static_cast<unsigned int>(mem[inp_pos]) << '\n';
            }
        }
    }

    delete[] mem;
}
