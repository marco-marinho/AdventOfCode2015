#include <iostream>

using std::cout;

uint64_t first_of_col(uint64_t col){
    return (col*(1 + col))/2;
}

uint64_t row_offset(uint64_t row, uint64_t col){
    return ((row - 1) * (col + (col + row - 2))) / 2;
}

uint64_t code_idx(uint64_t row, uint64_t col){
    return first_of_col(col) + row_offset(row, col);
}

int main(){
    uint64_t next = 20151125;
    uint64_t count = 1;
    uint64_t target_count = code_idx(3010, 3019);
    while(count < target_count){
        next *= 252533;
        next = (next % 33554393);
        count++;
    }
    cout << "Task 01: " << next << std::endl;
}
