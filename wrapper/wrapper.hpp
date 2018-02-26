#include <SFML/Graphics.hpp>

#include <string>

struct DansSfmlWrapperBoss{
	sf::RenderWindow window;
	sf::Font font;
	sf::VertexArray va;
	std::string result;
};

extern DansSfmlWrapperBoss* gDansSfmlWrapperBoss;

extern "C" {
	void dans_sfml_wrapper_text_draw(int x, int y, int h, const char* s, int r, int g, int b, int a);
	float dans_sfml_wrapper_text_width(int h, const char* s);
}
