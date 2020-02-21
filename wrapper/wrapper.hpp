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
	void dans_sfml_wrapper_close();
	const char* dans_sfml_wrapper_poll_event();
	void dans_sfml_wrapper_vertices_set_type(const char* s);
	void dans_sfml_wrapper_vertices_add(float x, float y, int r, int g, int b, int a);
	void dans_sfml_wrapper_vertices_draw();
	sf::VertexBuffer* dans_sfml_wrapper_vertex_buffer_construct(int size);
	void dans_sfml_wrapper_vertex_buffer_destruct(sf::VertexBuffer* buffer);
	void dans_sfml_wrapper_vertex_buffer_set_type(sf::VertexBuffer* buffer, const char* type);
	void dans_sfml_wrapper_vertex_buffer_update(sf::VertexBuffer* buffer, int i, float x, float y, int r, int g, int b, int a);
	void dans_sfml_wrapper_vertex_buffer_draw(sf::VertexBuffer* buffer);
	void dans_sfml_wrapper_text_draw(float x, float y, int h, const char* s, int r, int g, int b, int a);
	float dans_sfml_wrapper_text_width(int h, const char* s);
	int dans_sfml_wrapper_width();
	int dans_sfml_wrapper_height();
	void dans_sfml_wrapper_display();
	float dans_sfml_wrapper_view_get_x();
	float dans_sfml_wrapper_view_get_y();
	float dans_sfml_wrapper_view_get_width();
	float dans_sfml_wrapper_view_get_height();
	void dans_sfml_wrapper_view_set(float x, float y, float w, float h);
	void dans_sfml_wrapper_custom_resize(int enable);
	void dans_sfml_wrapper_capture_start();
	void dans_sfml_wrapper_capture_finish(const char* fileName);
	void dans_sfml_wrapper_vector_text(float x, float y, float h, const char* s, int r, int g, int b, int a, float aspect);
	sf::RenderTexture* dans_sfml_wrapper_render_texture_construct(int w, int h);
	void dans_sfml_wrapper_render_texture_destruct(sf::RenderTexture* texture);
	void dans_sfml_wrapper_render_texture_draw(sf::RenderTexture* texture, float x, float y, float w, float h);
	sf::RenderTarget* dans_sfml_wrapper_render_texture_as_target(sf::RenderTexture* texture);
	void dans_sfml_wrapper_render_texture_display(sf::RenderTexture* texture);
	void dans_sfml_wrapper_target_set(sf::RenderTarget* target);
	void dans_sfml_wrapper_target_reset();
}

#endif
