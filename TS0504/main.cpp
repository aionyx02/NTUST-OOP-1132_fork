////////////////////////////////////////////////////////////////////////////////
/// @brief Verification program that checks if a given 9x9 grid follows Sudoku rules
///
/// @file main.cpp
/// @author xinshoutw <me@xinshou.tw>
/// @date 2026/03/07
/// @version 0.0.2
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

bool verify_sudoku(const uint8_t smap[81]);

int main() {
    uint8_t sudoku_map[81]{};
    std::string input_str;

    int cur_index = 0;
    while (getline(std::cin, input_str)) {
        if (input_str.empty())
            continue;

        sscanf(
            input_str.c_str(), "%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu\n", sudoku_map + cur_index, &sudoku_map[cur_index + 1], &sudoku_map[cur_index + 2],
            &sudoku_map[cur_index + 3], &sudoku_map[cur_index + 4], &sudoku_map[cur_index + 5], &sudoku_map[cur_index + 6], &sudoku_map[cur_index + 7],
            &sudoku_map[cur_index + 8]);
        cur_index += 9;

        if (cur_index == 81) {
            if (verify_sudoku(sudoku_map)) {
                std::cout << "True\n";
            } else {
                std::cout << "False\n";
            }
            cur_index = 0;
        }
    }
}

bool verify_sudoku(const uint8_t smap[81]) {
    // check horizons
    for (int y = 0; y < 9; ++y) {
        int counter = 0;
        for (int x = 0; x < 9; ++x) {
            counter |= (1 << smap[9 * y + x]);
        }

        if (counter != 0b1111111110)
            return false;
    }

    // check verticals
    for (int x = 0; x < 9; ++x) {
        int counter = 0;
        for (int y = 0; y < 9; ++y) {
            counter |= (1 << smap[9 * y + x]);
        }

        if (counter != 0b1111111110)
            return false;
    }

    // check square box
    for (int y = 0; y < 9; y += 3) {
        for (int x = 0; x < 9; x += 3) {
            int counter = 0;
            counter |= (1 << smap[9 * (y + 0) + (x + 0)]) | (1 << smap[9 * (y + 0) + (x + 1)]) | (1 << smap[9 * (y + 0) + (x + 2)]) |
                       (1 << smap[9 * (y + 1) + (x + 0)]) | (1 << smap[9 * (y + 1) + (x + 1)]) | (1 << smap[9 * (y + 1) + (x + 2)]) |
                       (1 << smap[9 * (y + 2) + (x + 0)]) | (1 << smap[9 * (y + 2) + (x + 1)]) | (1 << smap[9 * (y + 2) + (x + 2)]);

            if (counter != 0b1111111110)
                return false;
        }
    }

    return true;
}
