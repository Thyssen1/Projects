#include <iostream>
#include <string>
#include <fstream>
#include <set>

int** create_board() {
    int** board = new int*[9];

    for (int i = 0; i < 9; i++) {
        board[i] = new int[9];
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = 0;
        }
    }

    return board;
}

void populate_board(int** board) {
    int i = 0;
    int j = 0;

    std::string line;
    std::ifstream myfile("sudoku.txt");

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            for (auto &ch : line) {
                if (!isspace(ch) && (j < 9)) {
                    board[i][j] = atoi(&ch);
                    j++;
                }
            }
            j = 0;
            i++;
        }
        myfile.close();
    } else {
        std::cout << "Unable to open file." << std::endl;
    }
}

void print_board(int** board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void find_empty(int** board, int* row, int* col) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0) {
                *row = i;
                *col = j;
                return;
            }
        }
    }

    *row = -1;
    *col = -1;
}

bool is_valid(int** board, int* row, int* col) {
    std::set<int> nums;
    int counter = 0;

    // Check row
    for (int i = 0; i < 9; i++) {
        if (board[*row][i] != 0) {
            nums.insert(board[*row][i]);
            counter++;
        }
    }

    if (counter != nums.size()) { return false; }

    // Check row
    counter = 0;
    nums.clear();
    for (int j = 0; j < 9; j++) {
        if (board[j][*col] != 0) {
            nums.insert(board[j][*col]);
            counter++;
        }
    }

    if (counter != nums.size()) { return false; }

    counter = 0;
    nums.clear();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[3 * ( *row / 3) + i][3 * ( *col / 3) + j] != 0) {
                nums.insert(board[3 * ( *row / 3) + i][3 * ( *col / 3) + j]);
                counter++;
            }
        }
    }

    if (counter != nums.size()) { return false; }

    return true;    
}

bool is_valid(int** board) {
    std::set<int> nums;
    int counter = 0;

    // Check rows
    for (int i = 0; i < 9; i++) {
        counter = 0;
        nums.clear();

        for (int j = 0; j < 9; j++) {
            if (board[i][j] != 0) {
                nums.insert(board[i][j]);
                counter++;
            }
        }
    }

    if (counter != nums.size()) { return false; }

    // Check columns
    for (int i = 0; i < 9; i++) {
        counter = 0;
        nums.clear();

        for (int j = 0; j < 9; j++) {
            if (board[j][i] != 0) {
                nums.insert(board[j][i]);
                counter++;
            }
        }
    }

    if (counter != nums.size()) { return false; }

    // Subgrids
    for (int i = 0; i < 3; i += 3) {
        for (int j = 0; j < 3; j += 3) {
            counter = 0;
            nums.clear();
            
            for (int p = 0; p < 3; p++) {
                for (int q = 0; q < 3; q++) {
                    if (board[p + i][q + j] != 0) {
                        nums.insert(board[p + i][q + j]);
                        counter++;
                    }
                }
            }

            if (counter != nums.size()) { return false; }
        }
    }

    return true;    
}

bool solve_sudoku(int** board) {
    int row = 0;
    int col = 0;

    find_empty(board, &row, &col);

    if (row == -1) {
        // Board is solved
        std::cout << "solved?" << std::endl;
        return true;
    }

    for (int i = 1; i < 10; i++) {
        board[row][col] = i;
        if (is_valid(board, &row, &col)) {
            if (solve_sudoku(board)) {
                return true;
            }
        }

        board[row][col] = 0;
    }

    return false;
}

/*
allocate 2d array of stes
for i = 1..9
for j = 1..9
add possible numbers to set
end
end
*/

int main() {
    int** board = create_board();
    populate_board(board);
    solve_sudoku(board);
    print_board(board);

    std::cout << is_valid(board) << std::endl;

    return 0;
}




