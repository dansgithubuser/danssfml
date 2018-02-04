#include <SFML/Graphics.hpp>

#include <string>

struct Boss{
	sf::RenderWindow window;
	sf::Font font;
	sf::VertexArray va;
	std::string result;
};

extern Boss* gBoss;

extern "C" {
	void text(int x, int y, int h, const char* s, int r, int g, int b, int a);
}
