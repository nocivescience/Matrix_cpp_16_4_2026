#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

const int FONT_SIZE = 1;
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

struct MatrixDrop {
    float size;
    float x;
    float y;
    float speed;
    int charIndex;
};

int main() {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Que hermosa ventana");
    window.setFramerateLimit(60);
    sf::Font font;
    if(!font.openFromFile("arial.ttf")) return -1;
    std::string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijkmnlopqrstuvwxyz";
    int numColumns = WINDOW_WIDTH/(FONT_SIZE+10);
    std::vector<MatrixDrop> drops;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posDistY(-WINDOW_HEIGHT, 0);
    std::uniform_real_distribution<float> posDistX(0, WINDOW_WIDTH);
    std::uniform_real_distribution<float> speedDist(2.0f, 7.0f);
    std::uniform_int_distribution<int> charDist(0, charset.length()-1);
    std::uniform_int_distribution<int> sizeDist(7, 25);
    sf::Text text(font);
    text.setCharacterSize(sizeDist(gen));
    text.setFillColor(sf::Color(0, 255, 70));
    for (int i=0; i<numColumns;++i){
        drops.push_back({(float)i *sizeDist(gen), posDistX(gen), posDistY(gen),  speedDist(gen), charDist(gen)});
    }
    window.clear(sf::Color::Black);
    sf::RectangleShape fadeRectangle(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    fadeRectangle.setFillColor(sf::Color(0,0,0, 15));
    while(window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()){
                window.close();
            };
        };
        window.draw(fadeRectangle);
        // window.clear(sf::Color::Black);
        for (auto & drop: drops){
            text.setFillColor(sf::Color(50,255,100,255));
            text.setString(charset[drop.charIndex]);
            float sizeY = FONT_SIZE*sizeDist(gen);
            float gridY= std::floor(drop.y/sizeY)* (sizeY);
            text.setPosition({drop.x, gridY-6});
            window.draw(text);
            drop.y += drop.speed;
            if(gen()%5==0) {
                drop.charIndex= charDist(gen);
            };
            if(drop.y >WINDOW_HEIGHT) {
                drop.x = posDistX(gen);
                drop.y = 0;
                drop.speed = speedDist(gen);
                drop.size= sizeDist(gen);
            }
        }
        window.display();
    };
    return 0;
}