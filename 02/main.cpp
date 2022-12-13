#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <array>
#include <algorithm>
#include <numeric>

const std::regex sep{ "x" };

std::array<int, 2> getAreas(std::string measurements){

    std::array<int, 3> sides;
    std::array<int, 4> areas;
    std::array<int, 2> ribbon;
    std::array<int, 2> out;

    const std::vector<std::string> dims{
            std::sregex_token_iterator(measurements.begin(), measurements.end(), sep, -1),
            std::sregex_token_iterator()
    };

    for(int idx = 0; idx < 3; idx++){
        sides[idx] = std::stoi(dims[idx]);
    }

    areas[0] = 2*sides[0]*sides[1];
    areas[1] = 2*sides[0]*sides[2];
    areas[2] = 2*sides[1]*sides[2];
    areas[3] = *std::min_element(areas.begin(), areas.end()-1)/2;

    out[0] = std::accumulate(areas.begin(), areas.end(), 0);

    std::sort(sides.begin(), sides.end());

    ribbon[0] = 2*(sides[0] + sides[1]);
    ribbon[1] = sides[0] * sides[1] * sides[2];

    out[1] = std::accumulate(ribbon.begin(), ribbon.end(), 0);

    return out;

}

int main() {

    std::string line;
    std::ifstream data("../02/data.txt");
    int total_area = 0;
    int total_ribbon = 0;

    if (data.is_open())
    {
        while(getline(data, line))
        {
            auto areas = getAreas(line);
            total_area += areas[0];
            total_ribbon += areas[1];

        }
        data.close();
    }
    std::cout << "Total area: " << total_area << std::endl;
    std::cout << "Total ribbon: " << total_ribbon << std::endl;
    return 0;
}

