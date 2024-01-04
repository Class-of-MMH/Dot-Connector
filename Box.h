#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <utility>

using namespace sf;


class Edge
{
public:		//Var
	std::vector<std::pair<int, int>> Edges;   //First is column, Second is row
	int size{}, totalLines{};
public:		//Function
	void inputEdges(int a, int b);			//Save the edges
	void setSize(int size, int totalLines);	//set the size and total Lines
	bool in(int a, int b);					//Check if there is box
};
