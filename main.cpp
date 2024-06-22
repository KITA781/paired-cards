#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>

class Maps {
public:
    sf::Sprite sprite;
    int number;
    bool open, draw;

    void set(sf::Texture& image) {
        sprite.setTexture(image);
        open = false;
        draw = true;
        rect(); // Вызываем rect() сразу после установки текстуры
    }

    void rect() {
        if (open)
            sprite.setTextureRect(sf::IntRect(120 * (number - 1), 0, 120, 220));
        else
            sprite.setTextureRect(sf::IntRect(120 * 6, 0, 120, 220));
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));
    sf::RenderWindow window(sf::VideoMode(950, 700), "Maps!");

    sf::Texture t;
    if (!t.loadFromFile("D:\\KITA\\Maps\\Maps.png")) {
        return -1; // Помилка завантаження файлу текстури
    }

    Maps m[6], n[6];
    for (int i = 0; i < 6; i++) {
        m[i].number = 0;
        n[i].number = 0;
    }

    // Присвоїти випадкові числа m
    for (int i = 0; i < 6; i++) {
        int tmp = rand() % 6;
        while (m[tmp].number != 0)
            tmp = rand() % 6;
        m[tmp].number = i + 1;
    }
    for (int i = 0; i < 6; i++) {
        m[i].set(t);
        m[i].sprite.setPosition(50 + 150 * i, 0);
    }

    // Присвоїти випадкові числа n
    for (int i = 0; i < 6; i++) {
        int tmp = rand() % 6;
        while (n[tmp].number != 0)
            tmp = rand() % 6;
        n[tmp].number = i + 1;
    }
    for (int i = 0; i < 6; i++) {
        n[i].set(t);
        n[i].sprite.setPosition(50 + 150 * i, 250);
    }

    int clickCount = 0, timer = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.key.code == sf::Mouse::Left && timer == 0) {
                    sf::Vector2i pos = sf::Mouse::getPosition(window);

                    for (int i = 0; i < 6; i++) {
                        if (m[i].sprite.getGlobalBounds().contains(static_cast<float>(pos.x), static_cast<float>(pos.y))) {
                            m[i].open = true;
                            clickCount++;
                        }
                        if (n[i].sprite.getGlobalBounds().contains(static_cast<float>(pos.x), static_cast<float>(pos.y))) {
                            n[i].open = true;
                            clickCount++;
                        }
                    }
                }
            }
        }

        if (clickCount == 2) {
            clickCount = 0;
            timer = 1000;
        }

        if (timer > 0) {
            timer--;

            if (timer == 0) {
                for (int i = 0; i < 6; i++) {
                    for (int j = 0; j < 6; j++) {
                        if (m[i].number == n[j].number && m[i].open && n[j].open) {
                            m[i].draw = false;
                            n[j].draw = false;
                        }
                    }
                }

                for (int i = 0; i < 6; i++) {
                    m[i].open = false;
                    n[i].open = false;
                }
            }
        }

        for (int i = 0; i < 6; i++) {
            m[i].rect();
            n[i].rect();
        }
        window.clear(sf::Color::White);

        for (int i = 0; i < 6; i++) {
            if (m[i].draw)
                window.draw(m[i].sprite);
            if (n[i].draw)
                window.draw(n[i].sprite);
        }
        window.display();
    }

    return 0;
}
