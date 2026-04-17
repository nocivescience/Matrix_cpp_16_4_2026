#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

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
    // SFML 3 usa sf::VideoMode(sf::Vector2u)
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Matrix Effect - SFML 3");
    window.setFramerateLimit(60);

    // Cargar fuente (asegúrate de tener una fuente .ttf en la carpeta)
    sf::Font font;
    if (!font.openFromFile("arial.ttf")) return -1;

    // Caracteres disponibles
    std::string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ@#$%&*+-=";
    
    // Configurar columnas
    int numColumns = WINDOW_WIDTH / FONT_SIZE;
    std::vector<MatrixDrop> drops;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posDist(-WINDOW_HEIGHT, 0);
    std::uniform_real_distribution<float> speedDist(2.0f, 7.0f);
    std::uniform_int_distribution<int> charDist(0, charset.length() - 1);

    for (int i = 0; i < numColumns; ++i) {
        drops.push_back({ (float)i * FONT_SIZE, posDist(gen), speedDist(gen), charDist(gen) });
    }

    sf::Text text(font);
    text.setCharacterSize(FONT_SIZE);
    text.setFillColor(sf::Color(0, 255, 70)); // Verde Matrix

    // Rectángulo para el efecto de estela (Fade)
    sf::RectangleShape fadeRect(sf::Vector2f({(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT}));
    fadeRect.setFillColor(sf::Color(0, 0, 0, 40)); // El 40 es la opacidad (trail)

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // 1. Dibujamos el fondo semitransparente para desvanecer lo anterior
        window.draw(fadeRect);

        // 2. Actualizar y dibujar cada gota
        for (auto& drop : drops) {
            text.setString(charset[drop.charIndex]);
            text.setPosition({drop.x, drop.y});
            
            // Dibujar el caracter
            window.draw(text);

            // Mover la gota
            drop.y += drop.speed;

            // Cambiar el caracter aleatoriamente para dinamismo
            if (charDist(gen) > 40) drop.charIndex = charDist(gen);

            // Reiniciar si sale de la pantalla
            if (drop.y > WINDOW_HEIGHT) {
                drop.y = -FONT_SIZE;
                drop.speed = speedDist(gen);
            }
        }

        window.display();
    }

    return 0;
}