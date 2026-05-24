#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

const int FONT_SIZE = 18;
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

struct MatrixDrop {
    float size;
    float x;
    float y;
    float speed;
    int charIndex;
    int alpha;
};

int main() {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Que hermosa ventana");
    window.setFramerateLimit(60);
    sf::Font font;
    if(!font.openFromFile("arial.ttf")) return -1;
    std::string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ@#$%&*+-=";
    int numColumns = WINDOW_WIDTH/FONT_SIZE;
    std::vector<MatrixDrop> drops;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posDistY(-WINDOW_HEIGHT, 0);
    std::uniform_real_distribution<float> posDistX(0, WINDOW_WIDTH);
    std::uniform_real_distribution<float> speedDist(2.0f, 7.0f);
    std::uniform_int_distribution<int> charDist(0, charset.length()-1);
    std::uniform_int_distribution<int> alphaDist(100, 255);
    sf::Text text(font);
    text.setCharacterSize(FONT_SIZE);
    text.setFillColor(sf::Color(0, 255, 70));
    for (int i=0; i<numColumns;++i){
        drops.push_back({(float)i *FONT_SIZE, posDistX(gen), posDistY(gen),  speedDist(gen), charDist(gen), alphaDist(gen)});
    }
    while(window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()){
                window.close();
            };
        };
        window.clear(sf::Color::Black);
        for (auto & drop: drops){
            text.setFillColor(sf::Color(0,255,70, drop.alpha));
            text.setString(charset[drop.charIndex]);
            text.setPosition({drop.x, drop.y});
            window.draw(text);
            drop.y += drop.speed;
            if(drop.alpha>10) {
                drop.alpha-=1;
            }
            if (charDist(gen)>1) drop.charIndex= charDist(gen);
            if(drop.y >WINDOW_HEIGHT) {
                drop.x = posDistX(gen);
                drop.y = 0;
                drop.speed = speedDist(gen);
                drop.alpha = alphaDist(gen);
            }
        }
        window.display();
    };
    return 0;
}