#ifndef WRAPPER_HPP_INCLUDED
#define WRAPPER_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include <string>

struct DansSfmlWrapperBoss{
	sf::RenderTarget* target;
	sf::RenderWindow window;
	sf::RenderTexture texture;
	sf::Font font;
	sf::VertexArray va;
	std::string result;
	bool customResize=false;
};

extern DansSfmlWrapperBoss* gDansSfmlWrapperBoss;

extern "C" {
	int dans_sfml_wrapper_init(int width, int height, const char* title);
	const char* dans_sfml_wrapper_poll_event();
	void dans_sfml_wrapper_set_vertices_type(const char* s);
	void dans_sfml_wrapper_vertex(float x, float y, int r, int g, int b, int a);
	void dans_sfml_wrapper_draw_vertices();
	void* dans_sfml_wrapper_vertex_buffer_construct(int size);
	void dans_sfml_wrapper_vertex_buffer_destruct(sf::VertexBuffer* buffer);
	void dans_sfml_wrapper_vertex_buffer_update(sf::VertexBuffer* buffer, int i, float x, float y, int r, int g, int b, int a);
	void dans_sfml_wrapper_vertex_buffer_draw(sf::VertexBuffer* buffer);
	void dans_sfml_wrapper_text_draw(float x, float y, int h, const char* s, int r, int g, int b, int a);
	float dans_sfml_wrapper_text_width(int h, const char* s);
	int dans_sfml_wrapper_width();
	int dans_sfml_wrapper_height();
	void dans_sfml_wrapper_display();
	float dans_sfml_wrapper_get_view_x();
	float dans_sfml_wrapper_get_view_y();
	float dans_sfml_wrapper_get_view_width();
	float dans_sfml_wrapper_get_view_height();
	void dans_sfml_wrapper_set_view(float x, float y, float w, float h);
	void dans_sfml_wrapper_custom_resize(int enable);
	void dans_sfml_wrapper_capture_start();
	void dans_sfml_wrapper_capture_finish(const char* fileName);
}

#endif
