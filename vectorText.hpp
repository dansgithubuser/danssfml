#include <SFML/Graphics.hpp>

#include <cstdint>
#include <stdexcept>
#include <string>

void vectorText(
	std::string s,
	float x, float y, float h,
	uint8_t r, uint8_t g, uint8_t b, uint8_t a,
	sf::VertexArray& va
){
	auto generate_cx=[&](char c, int a=1, int o=0){
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
		return a*x+h*(m.at(c)+o)/4;
	};
	auto generate_cy=[&](char c, int a=1, int o=0){
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
		return a*y-h*(m.at(c)+o)/2;
	};
	auto generate=[&](std::string code){
		sf::Vertex v, u(
			sf::Vector2f(generate_cx(code.at(0)), generate_cy(code.at(0))),
			sf::Color(r, g, b, a)
		);
		for(size_t i=1; i<code.size(); ++i){
			switch(code.at(i)){
				case 'p':
					++i;
					v=sf::Vertex(
						sf::Vector2f(
							u.position.x+(generate_cx(code.at(i), 0, -1))/3,
							u.position.y-(generate_cy(code.at(i), 0, -1))/3
						),
						sf::Color(r, g, b, a)
					);
					break;
				default:
					v=sf::Vertex(
						sf::Vector2f(generate_cx(code.at(i)), generate_cy(code.at(i))),
						sf::Color(r, g, b, a)
					);
			}
			va.append(u);
			va.append(v);
			u=v;
		}
		x+=h*3/4;
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
		if(m.count(c)) generate(m.at(c));
		else throw std::logic_error("unimplemented character");
	}
}
