#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>

using std::vector;
using std::string;
using std::cout;
using std::unordered_map;

vector<vector<int>> nb_coords = {{-1,1},{0,1},{1,1},{-1,0},
                                 {1,0},{-1,-1},{0,-1},{1,-1}};

vector<vector<int>> getData(const string &path){
    vector<vector<int>> output = vector<vector<int>>();
    std::ifstream data(path);
    string line;
    if (data.is_open())
    {
        while(getline(data, line))
        {
            vector<int> buffer = vector<int>();
            for (char const &c: line) {
                int input = c == '.' ? 0 : 1;
                buffer.push_back(input);
            }
            output.push_back(buffer);
        }
    }
    return output;
}

void printGrid(const vector<vector<int>>& grid){
    cout << std::endl;
    cout << std::endl;
    for (const auto& line: grid){
        for (auto element: line){
            char to_print = element ? '#' : '.';
            cout << to_print;
        }
        cout << std::endl;
    }
    cout << std::endl;
}

void updateGrid(vector<vector<int>>& grid, bool broken){
    unsigned long nrows = grid.size();
    unsigned long ncols = grid[0].size();
    vector<vector<int>> buffer(nrows, std::vector<int>(ncols, 0));

    if (broken){
        grid[0][0]=1;
        grid[0][ncols-1]=1;
        grid[nrows-1][0]=1;
        grid[nrows-1][ncols-1]=1;
    }

    for(int row = 0; row < nrows; row++){
        for(int col = 0; col < ncols; col++){
            for(auto coord: nb_coords){
                int nrow = row+coord[0];
                int ncol = col+coord[1];
                if(nrow>=0 && ncol>=0 && nrow < nrows && ncol < ncols){
                    if(grid[nrow][ncol] == 1){
                        buffer[row][col] += 1;
                    }
                }
            }
        }
    }

    for(int row = 0; row < nrows; row++){
        for(int col = 0; col < ncols; col++) {
            if (grid[row][col] == 1 && (buffer[row][col] == 3 || buffer[row][col] == 2)){
                grid[row][col] = 1;
            }
            else if (buffer[row][col] == 3 && grid[row][col] == 0){
                grid[row][col] = 1;
            }
            else {
                grid[row][col] = 0;
            }
        }
    }

    if (broken){
        grid[0][0]=1;
        grid[0][ncols-1]=1;
        grid[nrows-1][0]=1;
        grid[nrows-1][ncols-1]=1;
    }

}

int countLightsOn(const vector<vector<int>> &grid){
    unsigned long nrows = grid.size();
    unsigned long ncols = grid[0].size();
    int total_on = 0;
    for(int row = 0; row < nrows; row++) {
        for (int col = 0; col < ncols; col++) {
            if(grid[row][col] > 0){
                total_on++;
            }
        }
    }
    return total_on;
}

int main(){

    vector<vector<int>> data = getData("data.txt");
    for(int step = 0; step < 100; step ++){
        updateGrid(data, false);
    }
    cout << "Task 1: " << countLightsOn(data) << std::endl;
    data = getData("data.txt");
    for(int step = 0; step < 100; step ++){
        updateGrid(data, true);
    }
    cout << "Task 2: " << countLightsOn(data) << std::endl;
}