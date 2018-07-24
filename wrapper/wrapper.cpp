#include "wrapper.hpp"

#include <courierCode.hpp>
#include <keys.hpp>

#include <map>
#include <sstream>
#include <stdexcept>

int dansSfmlWrapperBossInit(int width, int height, const char* title){
	gDansSfmlWrapperBoss=new DansSfmlWrapperBoss;
	if(!gDansSfmlWrapperBoss->font.loadFromMemory(courierCode, courierCodeSize)) return 1;
	gDansSfmlWrapperBoss->window.create(sf::VideoMode(width, height), title);
	gDansSfmlWrapperBoss->window.setKeyRepeatEnabled(false);
	gDansSfmlWrapperBoss->va.setPrimitiveType(sf::PrimitiveType::Triangles);
	return 0;
}

const char* dansSfmlWrapperBossPollEvent(){
	std::stringstream ss;
	sf::Event event;
	if(gDansSfmlWrapperBoss->window.pollEvent(event)){
		switch(event.type){
			case sf::Event::KeyPressed:
			case sf::Event::KeyReleased:
				if(event.key.code==sf::Keyboard::Key::Unknown) break;
				ss<<(event.type==sf::Event::KeyPressed?"<":">")
					<<keys[event.key.code];
				break;
			case sf::Event::MouseMoved:
				ss<<"x"<<event.mouseMove.x<<"y"<<event.mouseMove.y;
				break;
			case sf::Event::MouseButtonPressed:
			case sf::Event::MouseButtonReleased:
				ss<<"b"<<(event.type==sf::Event::MouseButtonPressed?"<":">")
					<<event.mouseButton.button
					<<"x"<<event.mouseButton.x<<"y"<<event.mouseButton.y;
				break;
			case sf::Event::MouseWheelMoved:
				ss<<"w"<<event.mouseWheel.delta;
				break;
			case sf::Event::Closed:
				ss<<"q";
				break;
			case sf::Event::Resized:
				if(gDansSfmlWrapperBoss->customResize)
					ss<<"rw"<<event.size.width<<"h"<<event.size.height;
				else
					gDansSfmlWrapperBoss->window.setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
				break;
			default: break;
		}
	}
	gDansSfmlWrapperBoss->result=ss.str();
	return gDansSfmlWrapperBoss->result.c_str();
}

DansSfmlWrapperBoss* gDansSfmlWrapperBoss=nullptr;

extern "C" {
	int dans_sfml_wrapper_init(int width, int height, const char* title){
		if(gDansSfmlWrapperBoss) delete gDansSfmlWrapperBoss;
		return dansSfmlWrapperBossInit(width, height, title);
	}

	const char* dans_sfml_wrapper_poll_event(){ return dansSfmlWrapperBossPollEvent(); }

	void dans_sfml_wrapper_set_vertices_type(const char* s){
		std::map<std::string, sf::PrimitiveType> m={
			{"triangles", sf::PrimitiveType::Triangles},
			{"lines"    , sf::PrimitiveType::Lines},
		};
		if(m.count(s)) gDansSfmlWrapperBoss->va.setPrimitiveType(m.at(s));
	}

	void dans_sfml_wrapper_vertex(float x, float y, int r, int g, int b, int a){
		gDansSfmlWrapperBoss->va.append(sf::Vertex(
			sf::Vector2f(x, y),
			sf::Color(r, g, b, a)
		));
	}

	void dans_sfml_wrapper_draw_vertices(){
		gDansSfmlWrapperBoss->window.draw(gDansSfmlWrapperBoss->va);
		gDansSfmlWrapperBoss->va.clear();
	}

	void* dans_sfml_wrapper_vertex_buffer_construct(int size){
		auto result=new sf::VertexBuffer(sf::Points, sf::VertexBuffer::Static);
		if(!result->create(size)) throw std::runtime_error("couldn't create vertex buffer");
		return result;
	}

	void dans_sfml_wrapper_vertex_buffer_destruct(sf::VertexBuffer* buffer){
		delete buffer;
	}

	void dans_sfml_wrapper_vertex_buffer_update(sf::VertexBuffer* buffer, int i, float x, float y, int r, int g, int b, int a){
		sf::Vertex v(sf::Vector2f(x, y), sf::Color(r, g, b, a));
		buffer->update(&v, 1, i);
	}

	void dans_sfml_wrapper_vertex_buffer_draw(sf::VertexBuffer* buffer){
		gDansSfmlWrapperBoss->window.draw(*buffer);
	}

	void dans_sfml_wrapper_text_draw(float x, float y, int h, const char* s, int r, int g, int b, int a){
		sf::Text t(s, gDansSfmlWrapperBoss->font, h);
		t.setFillColor(sf::Color(r, g, b, a));
		t.setPosition(x, y);
		gDansSfmlWrapperBoss->window.draw(t);
	}

	float dans_sfml_wrapper_text_width(int h, const char* s){
		return sf::Text(s, gDansSfmlWrapperBoss->font, h).getLocalBounds().width;
	}

	int dans_sfml_wrapper_width(){ return gDansSfmlWrapperBoss->window.getSize().x; }

	int dans_sfml_wrapper_height(){ return gDansSfmlWrapperBoss->window.getSize().y; }

	void dans_sfml_wrapper_display(){
		gDansSfmlWrapperBoss->window.display();
	}

	float dans_sfml_wrapper_get_view_x(){
		const auto& view=gDansSfmlWrapperBoss->window.getView();
		return view.getCenter().x-view.getSize().x/2;
	}

	float dans_sfml_wrapper_get_view_y(){
		const auto& view=gDansSfmlWrapperBoss->window.getView();
		return view.getCenter().y-view.getSize().y/2;
	}

	float dans_sfml_wrapper_get_view_width(){
		return gDansSfmlWrapperBoss->window.getView().getSize().x;
	}

	float dans_sfml_wrapper_get_view_height(){
		return gDansSfmlWrapperBoss->window.getView().getSize().y;
	}

	void dans_sfml_wrapper_set_view(float x, float y, float w, float h){
		gDansSfmlWrapperBoss->window.setView(sf::View(sf::FloatRect(x, y, w, h)));
	}

	void dans_sfml_wrapper_custom_resize(int enable){
		gDansSfmlWrapperBoss->customResize=enable;
	}
}
