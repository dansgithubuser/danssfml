#include "wrapper.hpp"

#include <courierCode.hpp>
#include <keys.hpp>

#include <map>
#include <sstream>

int bossInit(int width, int height, const char* title){
	gBoss=new Boss;
	if(!gBoss->font.loadFromMemory(courierCode, courierCodeSize)) return 1;
	gBoss->window.create(sf::VideoMode(width, height), title);
	gBoss->window.setKeyRepeatEnabled(false);
	gBoss->va.setPrimitiveType(sf::PrimitiveType::Triangles);
	return 0;
}

const char* bossPollEvent(){
	std::stringstream ss;
	sf::Event event;
	if(gBoss->window.pollEvent(event)){
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
				gBoss->window.setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
				break;
			default: break;
		}
	}
	gBoss->result=ss.str();
	return gBoss->result.c_str();
}

Boss* gBoss=nullptr;

extern "C" {
	int init(int width, int height, const char* title){
		if(gBoss) delete gBoss;
		return bossInit(width, height, title);
	}

	const char* poll_event(){ return bossPollEvent(); }

	void set_vertices_type(const char* s){
		std::map<std::string, sf::PrimitiveType> m={
			{"triangles", sf::PrimitiveType::Triangles},
			{"lines"    , sf::PrimitiveType::Lines},
		};
		if(m.count(s)) gBoss->va.setPrimitiveType(m.at(s));
	}

	void vertex(int x, int y, int r, int g, int b, int a){
		gBoss->va.append(sf::Vertex(
			sf::Vector2f((float)x, (float)y),
			sf::Color(r, g, b, a)
		));
	}

	void draw_vertices(){
		gBoss->window.draw(gBoss->va);
		gBoss->va.clear();
	}

	void text(int x, int y, int h, const char* s, int r, int g, int b, int a){
		sf::Text t(s, gBoss->font, h);
		t.setFillColor(sf::Color(r, g, b, a));
		t.setPosition((float)x, (float)y);
		gBoss->window.draw(t);
	}

	int width(){ return gBoss->window.getSize().x; }

	int height(){ return gBoss->window.getSize().y; }

	void display(){
		gBoss->window.display();
	}
}
