#include "Display.h"
#include <array>

void main() {
    Display::testRoundUp();
}

void Display::testRoundUp() {

    std::array a4{3.0, 1.0, 4.0};
    std::array data{
        {12.302492394, 12.30}
    };

    for(int test = 0; test != data.length(); test++){
        double output = roundUp(data[test][0]);

        if(output != data[test][0]) {
            throw new exception("Not equal");
        }
    }
}