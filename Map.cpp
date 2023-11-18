#include <iostream>
#include <fstream>
#include <vector>

#include "Map.h"

using namespace std;

/*
---------------------------------------------------------------------------------
|						 Here is the constructor								|
---------------------------------------------------------------------------------
*/

Map::Map() {
	m_ballconfig = new string;
	m_ball = 0;
	m_sizeX = 0;
	m_sizeY = 0;
	m_num = 0;
	m_vstr = new vector<string>;
	m_config = new string;
	m_error = \
		"Map is not correctly formated. Expected format would be :\n\n\
\
BallNum\n\
0000\n\
0000\n\
0000\n\
0000\n\
WidthxHeight\n\n \
\
You can change 0 by bricks health capped at 9\n \
Width max is 13\n \
Height max is 7\n \
BallNum max is 999\n";
}

/*
---------------------------------------------------------------------------------
|						 Here are the Get Methods								|
---------------------------------------------------------------------------------
*/

int		Map::GetWidth() {
	return m_sizeX;
}

int		Map::GetHeight() {
	return m_sizeY;
}

// Get the Supposed size of the map based on the map txt file

void		Map::GetSize() {
	char*	x;
	char*	y;
	int		sizex = 0;
	int		sizey = 0;
	int		lenLine = m_config->size();

	for (int i = 0; (m_config->at(i) and m_config->at(i) >= 48 and m_config->at(i) <= 57); i++)
		sizex++;
	for (int j = sizex + 1; j < m_config->length(); j++)
		sizey++;
	x = new char[sizex + 1];
	y = new char[sizey + 1];
	for (int i = 0; i < sizex; i++)
		x[i] = m_config->at(i);
	x[sizex] = '\0';
	for (int j = 0; j < sizey; j++)
		y[j] = m_config->at(sizex + j + 1);
	y[sizey] = '\0';
	m_sizeX = stoi(x);
	m_sizeY = stoi(y);
	delete[] x;
	delete[] y;
	m_num = m_sizeX * m_sizeY;
}

int    Map::GetBall() {
	return m_ball;
}

/*
---------------------------------------------------------------------------------
|						 Here are the Check Methods								|
---------------------------------------------------------------------------------
*/

bool		Map::IsBallNumValid() {
	if (m_ball <= 0 or m_ball > 999)
		return false;
	return true;
}

bool		Map::IsBallNumFormated() {
	if (m_ballconfig->size() == 0 || m_ballconfig->size() > 3)
	{
		std::cout << m_error << std::endl;
		exit(1);
	}
	for (int i = 0; i < m_ballconfig->size(); ++i)
	{
		if (m_ballconfig->at(i) < 48 and m_ballconfig->at(i) > 57)
		{
			std::cout << m_error << std::endl;
			exit(1);
		}
	}
	return true;
}

// Check the format of the config line of the txt file

bool		Map::IsConfigFormated(){
	int		lenLine = m_config->size();
	bool	first = false;
	bool	second = false;

	if (lenLine == 0 || lenLine > 4)
		return false;
	for (int i = 0; i < lenLine; ++i) {
		if (second and (m_config->at(i) < 48 || m_config->at(i) > 57))
			return false;
		else if (first and m_config->at(i) != 120 and second)
			return false;
		else if (first and m_config->at(i) != 120)
			second = true;
		if (m_config->at(i) == 120)
			first = true;
		if (m_config->at(i) == 120 and !m_config->at(i + 1))
			return false;
	}
	return true;
}

bool		Map::IsLineFormated(string *line) {
	if (line->size() != m_sizeX) 
		return false;
		
	for (int i = 0; i < m_sizeX; ++i) {
		if (line->at(i) < 48 || line->at(i) > 57)
			return false;
	}
	return true;
}

bool		Map::IsHeightFormated() {
	if (m_vstr->size() != m_sizeY)
		return false;
	return true;
}

// Check map height then every line of the map file

bool		Map::IsMapFormated() {
	if (!IsHeightFormated())
		return false;
	for (int i = 0; i < m_sizeY; ++i) {
		if (!IsLineFormated(&m_vstr->at(i))) {
			return false;
		}
	}
	return true;
}

void		Map::CheckMap() {
	if (!IsConfigFormated() && !IsBallNumValid()) {
		cout << m_error << endl;
		exit(1);
	}
	GetSize();
	if (!IsMapFormated())
	{
		cout << m_error << endl;
		exit(1);
	}
}

/*
---------------------------------------------------------------------------------
|						 Here is the Main Method								|
---------------------------------------------------------------------------------
*/

void Map::ParseMap(string *filePath) {

	ifstream input(*filePath);

	if (!input.is_open()) {
		
		cout << "Error loading map" << endl;
		exit(1);
	}
	string line;

	getline(input, line);
	if (line.empty()) {
		cout << m_error << endl;
		exit(1);
	}
	*m_ballconfig = line;
	IsBallNumFormated();
	m_ball = stoi(*m_ballconfig);

	// Pushback line after line the txt file in the mvstr vector

	while (getline(input, line)) {
		if (!line.empty()) {
			m_vstr->push_back(line);
		}
	}

	input.close();

	*m_config = m_vstr->at(m_vstr->size() - 1);
	m_vstr->pop_back();
}

Map::~Map() {
	delete m_config;
	delete m_ballconfig;
	m_vstr->clear();
}