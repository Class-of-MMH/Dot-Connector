#include "Board.h"
#include "Box.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <utility>



Board::Board(int size, RenderWindow& win, sf::Color c) { //Create the game

	on_streak = false;
	this->size = size;
	totalLines = 2 * (size * size - size);	//Calculate the total valid lines
	edge.setSize(size, totalLines);			//Pass size and totalLines to box class
	std::cout << " The size of the game is " << size << std::endl;
	CircleShape aCircle; //Create a visual Dot
	vertex.setPrimitiveType(Lines); //Set primitive type for vertex
	vertex.resize(2 * totalLines);	//Set its size
	circle.resize(totalLines);
	float breadth = static_cast<float>(0.8f * screen_size) / static_cast<float>(size) - 1.f;
	//Print those dots----------------------------------------------
	for (int i = 0; i < size * size; i++) {
		float circle_x = 0.1 * screen_size + float{ (i % size) * breadth };
		//Set the position for
		float circle_y = 0.1 * screen_size + float{ (i / size) * breadth };	//	those circles
		circle.push_back(aCircle);
		circle[i].setRadius(8);
		circle[i].setPosition(circle_x, circle_y);
		circle[i].setFillColor(Color(0, 0, 0));
		circle[i].setOrigin(4, 4);
	}
	// win.clear(Color255,185,33);
	win.clear(c);
	for (auto i : circle)
		win.draw(i);
	win.display();

}

//Select the line-------------------------------------------------
void Board::LineSelect()
{
	Choice aChoice;                  //To save this single choice into vector::choice
	PropOfAnB aProp;					//to save a prop of a and b into vector::selectedLines to use for Board::isTaken
	std::cout << " \n player1 move (2 integers): ";
	std::cin >> a >> b;
	while ((notValid(a, b, size)) || (isTaken(a, b, selectedLines))) { //Validation
		std::cout << " Wrong input, please input again: " << std::endl;
		std::cin.clear();
		std::cin >> a >> b;
	}
	if (a < b) { aChoice.a = a; aChoice.b = b; }			//This is for sorting a and b
	else { aChoice.a = b; aChoice.b = a; }					// so that a always smaller than b
	choice.push_back(aChoice);									//the Board::choice
	aProp.product = a * b;						//Input product into
	aProp.sum = a + b;							//vector::selectedLines to
	selectedLines.push_back(aProp);				//use for Board::isTaken
	edge.inputEdges(aChoice.a, aChoice.b);
	setVertex();
}

void Board::LineSelect2()
{
	Choice aChoice;                  //To save this single choice into vector::choice
	PropOfAnB aProp;					//to save a prop of a and b into vector::selectedLines to use for Board::isTaken
	std::cout << " \n player2 move (2 integers): ";
	std::cin >> a >> b;
	while ((notValid(a, b, size)) || (isTaken(a, b, selectedLines))) { //Validation
		std::cout << " Wrong input, please input again: " << std::endl;
		std::cin.clear();
		std::cin >> a >> b;
	}
	if (a < b) { aChoice.a = a; aChoice.b = b; }			//This is for sorting a and b
	else { aChoice.a = b; aChoice.b = a; }					// so that a always smaller than b
	choice.push_back(aChoice);									//the Board::choice
	aProp.product = a * b;						//Input product into
	aProp.sum = a + b;							//vector::selectedLines to
	selectedLines.push_back(aProp);				//use for Board::isTaken
	edge.inputEdges(aChoice.a, aChoice.b);
	setVertex();
}


//Validation------------------------------------------
bool Board::notValid(int a, int b, int size)  const {
	if ((abs(b - a) == size
		|| (abs(b - a) == 1 && std::max(a, b) % size != 0))
		&& (a < size * size && b < size * size))
		return false;
	return true;
}

//See if it's taken or not----------------------------------------
bool Board::isTaken(int a, int b, std::vector<PropOfAnB>Sum_Product) {
	for (auto i : Sum_Product) {
		if ((a * b) == i.product && (a + b) == i.sum) {
			return true;
		}
	}
	return false;
}

//Draw those stuff
void Board::Draw(RenderWindow& win)
{
	for (auto i : circle) win.draw(i);			//Redraw the circle
	win.draw(vertex);							//Draw those Vertex
	for (auto t : rects) win.draw(t);			//Draw those boxes
}

void Board::setVertex()
{
	vertex[2 * moveCount].position.x = circle[choice[moveCount].a].getPosition().x + 5;				//Draws Vertex
	vertex[2 * moveCount].position.y = circle[choice[moveCount].a].getPosition().y + 5;				//  by using
	vertex[2 * moveCount + 1].position.x = circle[choice[moveCount].b].getPosition().x + 5;			//  coord of circle
	vertex[2 * moveCount + 1].position.y = circle[choice[moveCount].b].getPosition().y + 5;			//  +5 because the radius is 10
	vertex[2 * moveCount].color = Color::Black;
	vertex[2 * moveCount + 1].color = Color::Blue;
	moveCount++;
}

void Board::getBot() {
	int a{}, b{};
	bool InvalidBox = false;
	PropOfAnB aProp;
	Choice aChoice;
	srand(time(NULL));
	a = rand() % (size * size);				//Randomize bot selection and validate it
	b = rand() % (size * size);				//Randomize bot selection and validate it
	while (isTaken(a, b, selectedLines) || notValid(a, b, size) || (a == b)) {	//This loop will stop whenever a,b is valid
		a = rand() % (size * size);
		b = rand() % (size * size);
	}
	if (a < b) { aChoice.a = a; aChoice.b = b; }			//This is for sorting a and b
	else { aChoice.a = b; aChoice.b = a; }					// so that a always smaller than b
	choice.push_back(aChoice);									//the Board::choice
	aProp.product = a * b;						//Input product into
	aProp.sum = a + b;							//vector::selectedLines to
	selectedLines.push_back(aProp);				//use for Board::std::n
	edge.inputEdges(aChoice.a, aChoice.b);
	std::cout << " Bot chooses " << a << "-----" << b << std::endl;
	setVertex();
}


//Save scores for player
void Board::Score_player1(int leftcorner)
{
	bool isValid = true;						//To validate if the boxes is saved or not
	for (auto i : boxStore) {
		if (leftcorner == i) isValid = false;
	}
	if (isValid) {
		on_streak = true;
		score.first++;
		boxStore.push_back(leftcorner);
		std::cout << " This is the new box " << std::endl;
		float Box_breadth = (static_cast<float>(0.8f * screen_size) / static_cast<float>(size) - 1.f) - 4; //Box breadth is 4 pixel smaller than board breadth
		RectangleShape new_rect(Vector2f(Box_breadth, Box_breadth));
		new_rect.setFillColor(Color(0, 0, 0, 200));
		new_rect.setPosition(Vector2f(circle[leftcorner].getPosition()) + Vector2f(5, 5));			//Use the position of Circle to draw those boxes left corner
		rects.push_back(new_rect);
	}
	else {
		on_streak = false;
	}

}

//Save scores for bot
void Board::Score_player2(int leftcorner)
{
	bool isValid = true;						//To validate if the boxes is saved or not
	for (auto i : boxStore) {
		if (leftcorner == i) isValid = false;
	}
	if (isValid) {
		on_streak = true;
		score.second++;
		boxStore.push_back(leftcorner);
		std::cout << " This is the new box " << std::endl;
		float Box_breadth = (static_cast<float>(0.8f * screen_size) / static_cast<float>(size) - 1.f) - 4; //Box breadth is 4 pixel smaller than board breadth
		RectangleShape new_rect(Vector2f(Box_breadth, Box_breadth));
		new_rect.setFillColor(Color(255,255,255));
		new_rect.setPosition(Vector2f(circle[leftcorner].getPosition()) + Vector2f(5, 5));			//Use the position of Circle to draw those boxes left corner
		rects.push_back(new_rect);
	}
	else {
		on_streak = false;
	}
}

void Board::Score_Bot(int leftcorner)
{
		bool isValid = true;							//To validate if the boxes is saved or not
		for (auto i : boxStore) {
			if (leftcorner == i) isValid = false;
		}
		if (isValid) {
			on_streak = true;
			score.second++;
			boxStore.push_back(leftcorner);
			float Box_breadth = (static_cast<float>(0.8f * screen_size) / static_cast<float>(size) - 1.f) - 4; //Box breadth is 4 pixel smaller than board breadth
			RectangleShape new_rect(Vector2f(Box_breadth, Box_breadth));
			new_rect.setFillColor(Color(150, 60, 80, 200));
			new_rect.setPosition(Vector2f(circle[leftcorner].getPosition()) + Vector2f(5, 5)); //Use the position of Circle to draw those boxes left corner
			rects.push_back(new_rect);
		}
		else {
			on_streak = false;
		}


}

//Show the Score on CONSOLE
void Board::printScore()
{
	std::cout << "   The Score Board " << std::endl;
	std::cout << " Player1 |" << score.first << " Boxes " << std::endl;
	std::cout << " Player2 | " << score.second << " Boxes " << std::endl;
}

//This is to detect if there are enough edges to
//	make a box .  "i" will be the index of the
//	circle that contains the upperleft corner

void Board::detect_box(int o) {
	for (int i = 0; i < size * size - 1; i++) {
		if (edge.in(i, i + 1) && edge.in(i, i + size)
			&& edge.in(i + 1, i + 1 + size)
			&& edge.in(i + size, i + 1 + size)) {
			if (o) {
				Score_player2(i);
				// std::cout << "player2" << std::endl;
			}
			else {
				Score_player1(i);
				// std::cout << "player1" << std::endl;
			}
		}
	}
}
