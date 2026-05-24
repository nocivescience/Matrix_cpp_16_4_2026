#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <iostream>

const int FONT_SIZE = 18;
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

struct MatrixDrop {
    float x;
    float y;
    float speed;
    int charIndex;
};

int main() {
    std::vector<MatrixDrop> drops;
    drops.push_back({1.0,2.0,3.0,4});
    for (const auto & drop : drops){
        std::cout << drop.x << "---" << drop.y << std::endl;
    }
    return 0;
}