#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Box.h"

const float screen_size = 700;
using namespace sf;

struct Choice {
	int a;
	int b;
};
struct PropOfAnB {
	int sum;
	int product;
};

class Board {
private:
public: //Variable
	Edge edge;
	int a{}, b{}, totalLines, moveCount{};
	float breadth{};
	int size{};
	std::vector<RectangleShape>rects;				//Save those Rectangle for drawing purpose
	std::vector<CircleShape>circle;					//Save Dots
	std::vector<Choice>choice;						//Save Choices
	std::vector<PropOfAnB>selectedLines;			//Save sum and product to validate
	VertexArray vertex;								//Hold vertex
	int score1{}, score2{}, scoreCount{};
	std::vector<int>boxStore;
	std::pair<int, int> score;

	bool on_streak;

public: //Func

	Board(int size, RenderWindow& win, sf::Color c);
	void LineSelect();	
	void LineSelect2();										
	//input Choice
	bool notValid(int a, int b, int size) const;					//Validation
	bool isTaken(int a, int b, std::vector<PropOfAnB>Sum_Product);	//Validation
	void Draw(RenderWindow&);										//Draw lines and boxes
	void setVertex();												//Set up the Vertex
	void getBot();	
	void Score_Bot(int);											//Save score for bot
	void Score_player1(int);											//Save score for player
	void Score_player2(int);											//Save score for bot
	void printScore();												//Print Score
	void detect_box(int);



};
