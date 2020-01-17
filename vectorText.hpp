#include <SFML/Graphics.hpp>

#include <cstdint>
#include <stdexcept>
#include <string>

void vectorText(
	std::string s,
	float x, float y, float h,
	uint8_t r, uint8_t g, uint8_t b, uint8_t a,
	sf::VertexArray& va, const sf::RenderWindow& window
){
	const auto viewSize=window.getView().getSize();
	const auto aspect=viewSize.x/viewSize.y;
	auto numpad_sketch_x=[&](char c, bool relative=true, int offset=0){
		std::map<char, int> m={
			{'1', 0},
			{'2', 1},
			{'3', 2},
			{'4', 0},
			{'5', 1},
			{'6', 2},
			{'7', 0},
			{'8', 1},
			{'9', 2},
		};
		if(!m.count(c)) throw std::logic_error("invalid");
		return (relative?x:0)+h*(m.at(c)+offset)/4*aspect;
	};
	auto numpad_sketch_y=[&](char c, bool relative=true, int offset=0){
		std::map<char, int> m={
			{'1', 0},
			{'2', 0},
			{'3', 0},
			{'4', 1},
			{'5', 1},
			{'6', 1},
			{'7', 2},
			{'8', 2},
			{'9', 2},
		};
		if(!m.count(c)) throw std::logic_error("invalid");
		return (relative?y:0)-h*(m.at(c)+offset)/2;
	};
	auto numpad_sketch=[&](std::string code){
		sf::Vertex v_curr, v_prev(
			sf::Vector2f(numpad_sketch_x(code.at(0)), numpad_sketch_y(code.at(0))),
			sf::Color(r, g, b, a)
		);
		for(size_t i=1; i<code.size(); ++i){
			switch(code.at(i)){
				case 'p':
					++i;
					v_curr=sf::Vertex(
						sf::Vector2f(
							v_prev.position.x+(numpad_sketch_x(code.at(i), false, -1))/3,
							v_prev.position.y-(numpad_sketch_y(code.at(i), false, -1))/3
						),
						sf::Color(r, g, b, a)
					);
					break;
				default:
					v_curr=sf::Vertex(
						sf::Vector2f(numpad_sketch_x(code.at(i)), numpad_sketch_y(code.at(i))),
						sf::Color(r, g, b, a)
					);
			}
			va.append(v_prev);
			va.append(v_curr);
			v_prev=v_curr;
		}
	};
	va.setPrimitiveType(sf::PrimitiveType::Lines);
	std::map<char, std::string> m={
		{'0', "179319"},
		{'1', "78213"},
		{'2', "796413"},
		{'3', "7964631"},
		{'4', "6493"},
		{'5', "974631"},
		{'6', "971364"},
		{'7', "791"},
		{'8', "4793146"},
		{'9', "647931"},
		{'.', "2p2p6p8p4"},
		{'-', "46"},
	};
	for(char c: s){
		if(m.count(c)){
			numpad_sketch(m.at(c));
			x+=h*3/4*aspect;
		}
		else throw std::logic_error(std::string("unimplemented character ")+c);
	}
}
