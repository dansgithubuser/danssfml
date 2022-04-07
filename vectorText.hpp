#include <SFML/Graphics.hpp>

#include <cstdint>
#include <stdexcept>
#include <string>

//numpad
#define N7I 0.0f, 2.0f
#define N8I 1.0f, 2.0f
#define N9I 2.0f, 2.0f
#define N4I 0.0f, 1.0f
#define N5I 1.0f, 1.0f
#define N6I 2.0f, 1.0f
#define N1I 0.0f, 0.0f
#define N2I 1.0f, 0.0f
#define N3I 2.0f, 0.0f

#define N7 N7I, N7I
#define N8 N8I, N8I
#define N9 N9I, N9I
#define N4 N4I, N4I
#define N5 N5I, N5I
#define N6 N6I, N6I
#define N1 N1I, N1I
#define N2 N2I, N2I
#define N3 N3I, N3I

//under
#define U1I 0.0f, -1.0f
#define U2I 1.0f, -1.0f
#define U3I 2.0f, -1.0f

#define U1 U1I, U1I
#define U2 U2I, U2I
#define U3 U3I, U3I

//lowercase mid
#define L1I 0.0f, 0.5f
#define L2I 1.0f, 0.5f
#define L3I 2.0f, 0.5f

#define L1 L1I, L1I
#define L2 L2I, L2I
#define L3 L3I, L3I

//horizontal lines
#define L79 N7I, N9I
#define L46 N4I, N6I
#define L13 N1I, N3I

//vertical lines
#define L71 N7I, N1I
#define L82 N8I, N2I
#define L93 N9I, N3I

//25-point grid
#define T15I 0.0f, 2.0f
#define T25I 0.5f, 2.0f
#define T35I 1.0f, 2.0f
#define T45I 1.5f, 2.0f
#define T55I 2.0f, 2.0f

#define T14I 0.0f, 1.5f
#define T24I 0.5f, 1.5f
#define T34I 1.0f, 1.5f
#define T44I 1.5f, 1.5f
#define T54I 2.0f, 1.5f

#define T13I 0.0f, 1.0f
#define T23I 0.5f, 1.0f
#define T33I 1.0f, 1.0f
#define T43I 1.5f, 1.0f
#define T53I 2.0f, 1.0f

#define T12I 0.0f, 0.5f
#define T22I 0.5f, 0.5f
#define T32I 1.0f, 0.5f
#define T42I 1.5f, 0.5f
#define T52I 2.0f, 0.5f

#define T11I 0.0f, 0.0f
#define T21I 0.5f, 0.0f
#define T31I 1.0f, 0.0f
#define T41I 1.5f, 0.0f
#define T51I 2.0f, 0.0f

#define T15 T15I, T15I
#define T25 T25I, T25I
#define T35 T35I, T35I
#define T45 T45I, T45I
#define T55 T55I, T55I

#define T14 T14I, T14I
#define T24 T24I, T24I
#define T34 T34I, T34I
#define T44 T44I, T44I
#define T54 T54I, T54I

#define T13 T13I, T13I
#define T23 T23I, T23I
#define T33 T33I, T33I
#define T43 T43I, T43I
#define T53 T53I, T53I

#define T12 T12I, T12I
#define T22 T22I, T22I
#define T32 T32I, T32I
#define T42 T42I, T42I
#define T52 T52I, T52I

#define T11 T11I, T11I
#define T21 T21I, T21I
#define T31 T31I, T31I
#define T41 T41I, T41I
#define T51 T51I, T51I

//subglyphs
#define O N7I, N9, N3, N1, N7I
#define DOT 1.0f, 0.1f, 1.0f, -0.1f

void vectorText(
	std::string s,
	float x, float y, float h,
	uint8_t r, uint8_t g, uint8_t b, uint8_t a,
	float aspect,
	sf::VertexArray& va
){
	const std::map<char, std::vector<float>> glyphs={
		{' ', {}},
		{'\n', {}},
		{'!', {N8I, L2I, DOT}},
		{'"', {T25I, T24I, T45I, T44I}},
		{'#', {T25I, T21I, T45I, T41I, T14I, T54I, T12I, T52I}},
		{'$', {T54I, T14, N4, N6, T52, T12I, L82}},
		{'%', {N1I, N9I,  0.0f, 2.0f, 0.0f, 1.8f,  2.0f, 0.0f, 2.0f, 0.2f}},
		{'&', {N3I, T14, T25, T34, T12, T21, N2, N6I}},
		{'\'', {N8I, T34I}},
		{'(', {T45I, T24, T22, T41I}},
		{')', {T25I, T44, T42, T21I}},
		{'*', {N8I, N5I,  0.5f, 1.7f, 1.5f, 1.3f,  0.5f, 1.3f, 1.5f, 1.7f}},
		{'+', {L1I, L3I, N5I, N2I}},
		{',', {N2I, 0.8f, -0.5f}},
		{'-', {L1I, L3I}},
		{'.', {DOT}},
		{'/', {N1I, N9I}},
		{'0', {O, N1I, N9I}},
		{'1', {N7I, N8, N2I, N1I, N3I}},
		{'2', {N7I, N9, N6, N4, N1, N3I}},
		{'3', {N7I, N9, N6, N4I, N6I, N3, N1I}},
		{'4', {N6I, N4, N9, N3I}},
		{'5', {N9I, N7, N4, N6, N3, N1I}},
		{'6', {N9I, N7, N1, N3, N6, N4I}},
		{'7', {N7I, N9, N3I}},
		{'8', {O, L46}},
		{'9', {N6I, N4, N7, N9, N3, N1I}},
		{':', {DOT, 1.0f, 1.1f, 1.0f, 0.9f}},
		{';', {N2I, 0.8f, -0.5f,  1.0f, 1.1f, 1.0f, 0.9f}},
		{'<', {N6I, L1, N3I}},
		{'=', {L46, L1I, L3I}},
		{'>', {N4I, L3, N1I}},
		{'?', {N7I, N9, N6, N5, T32I, DOT}},
		{'@', {N6I, N5, N2, N3, N9, N7, N1I}},
		{'A', {L71, L79, L93, L46}},
		{'B', {N7I, N1, N3, N6, N4I, N7I, N8, N5I}},
		{'C', {L79, L71, L13}},
		{'D', {N7I, N1, N2, N6, N8, N7I}},
		{'E', {L71, L13, L46, L79}},
		{'F', {L71, L46, L79}},
		{'G', {N5I, N6, N3, N1, N7, N9I}},
		{'H', {L71, L93, L46}},
		{'I', {L82, L79, L13}},
		{'J', {N8I, N2, N1I, L79}},
		{'K', {L71, N9I, N4, N3I}},
		{'L', {L71, L13}},
		{'M', {N1I, N7, N5, N9, N3I}},
		{'N', {N1I, N7, N3, N9I}},
		{'O', {O}},
		{'P', {N1I, N7, N9, N6, N4I}},
		{'Q', {O, N5I, N3I}},
		{'R', {N1I, N7, N9, N6, N4, N3I}},
		{'S', {N9I, N7, N4, N6, N3, N1I}},
		{'T', {L82, L79}},
		{'U', {N7I, N1, N3, N9I}},
		{'V', {N7I, N2, N9I}},
		{'W', {N7I, N1, N5, N3, N9I}},
		{'X', {N7I, N3I, N1I, N9I}},
		{'Y', {N9I, N1I, N7I, N5I}},
		{'Z', {N7I, N9, N1, N3I}},
		{'[', {T45I, T25, T21, T41I}},
		{'\\', {N7I, N3I}},
		{']', {T25I, T45, T41, T21I}},
		{'^', {T24I, N8, T44I}},
		{'_', {L13}},
		{'`', {T25I, T43I}},
		{'a', {N4I, N6, N3, N1, L1, L3I}},
		{'b', {N7I, N1, N3, N6, N4I}},
		{'c', {N6I, N4, N1, N3I}},
		{'d', {N6I, N4, N1, N3, N9I}},
		{'e', {L1I, L3, N6, N4, N1, N3I}},
		{'f', {N2I, N8, N9I, L46}},
		{'g', {N3I, N1, N4, N6, U3, U1I}},
		{'h', {L71, N4I, N6, N3I}},
		{'i', {N5I, N2I, 1.0f, 1.4f, 1.0f, 1.6f}},
		{'j', {N5I, U2, U1I, 1.0f, 1.4f, 1.0f, 1.6f}},
		{'k', {N7I, N1I, N6I, L1, N3I}},
		{'l', {L82}},
		{'m', {N1I, N4, N5, N2I, N5I, N6, N3I}},
		{'n', {N1I, N4, N6, N3I}},
		{'o', {N4I, N6, N3, N1, N4I}},
		{'p', {U1I, N4, N6, N3, N1I}},
		{'q', {U3I, N6, N4, N1, N3I}},
		{'r', {N4I, N1I, L1I, N6I}},
		{'s', {N6I, N4, L1, L3, N3, N1I}},
		{'t', {L82, L46}},
		{'u', {N4I, N1, N3, N6I}},
		{'v', {N4I, N2, N6I}},
		{'w', {N4I, N1, L2, N3, N6I}},
		{'x', {N4I, N3I, N1I, N6I}},
		{'y', {N6I, U1I, N4I, N2I}},
		{'z', {N4I, N6, N1, N3I}},
		{'{', {T45I, N8, T34, T23, T32, N2, T41I}},
		{'|', {L82}},
		{'}', {T25I, N8, T34, T43, T32, N2, T21I}},
		{'~', {T13I, T24, T33, T42, T53I}},
	};
	const std::vector<float> notAGlyph={O, N7I, N3I, N1I, N9I};
	va.setPrimitiveType(sf::PrimitiveType::Lines);
	float x_i = x;
	for(char c: s){
		const auto& glyph=glyphs.count(c)?glyphs.at(c):notAGlyph;
		for(size_t i=0; i<glyph.size(); i+=2) va.append(sf::Vertex(
			sf::Vector2f(
				x+glyph[i+0]/4*h*aspect,
				y-glyph[i+1]/2*h
			),
			sf::Color(r, g, b, a)
		));
		x+=h*3/4*aspect;
		if (c == '\n') {
			x=x_i;
			y+=h*2;
		}
	}
}
