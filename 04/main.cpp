#include <iostream>
#include "md5.h"

using std::cout; using std::endl;

int main() {
    std::string source = "iwrupvqb";
    std::string current = source;
    std::string desired = "00000";
    std::string hash;
    int add = 1;
    bool found = false;
    while(!found){
        hash = md5(current);
        if (hash.rfind(desired, 0) == 0) {
            found = true;
        }
        else{
            current = source + std::to_string(add);
            add++;
        }
    }

    cout << "Found at: " << current << endl;
    return 0;
}


