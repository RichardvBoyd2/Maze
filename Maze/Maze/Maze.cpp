// Maze.cpp : Defines the entry point for the application.
//

#include "Maze.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

char start[3][3] = { {'.','.','.'},{'.','S','.'},{'.','.','.'} };
char goal[3][3] = { {'.','.','.'},{'.','F','.'},{'.','.','.'} };
char open[3][3] = { {'.','.','.'},{'.','.','.'},{'.','.','.'} };
char wall[3][3] = { {'X','X','X'},{'X','X','X'},{'X','X','X'} };
int boxX = 3, boxY = 3;
int mazeX, mazeY;
string mazeboxes[20][20]; //supports mazes up to 20 by 20 squares big


int main() {

	ifstream inFile("c:\\users\\rick\\source\\repos\\Maze\\Maze\\input_file.txt"); //can't get to work without full file path, adjust filepath to run properly
	
	if (inFile.fail()) {
		cerr << "Error opening File" << endl;
		system("pause");
	}

	//reads entire file into one string to ignore line breaks
	string inputline;
	string wholeinput;
	while (getline(inFile, inputline)) {
		wholeinput = wholeinput + inputline;
	}

	//removes "(" and ")" from string so it's easier to split by "." and ","
	char chars[] = "()";
	for (unsigned int i = 0; i < strlen(chars); ++i) {
		wholeinput.erase(remove(wholeinput.begin(), wholeinput.end(), chars[i]), wholeinput.end());
	}

	//splits string by "." to isolate important sections to use in different things.
	stringstream inputstream(wholeinput);
	string section;
	vector<string> splitinput;
	char delimeter = '.';
	while (getline(inputstream, section, delimeter)) {
		splitinput.push_back(section);
	}

	//splits the size section and stores values as maze size (times 3 to compensate for 3x3 boxes for each space)
	stringstream sizestream(splitinput[0]);
	delimeter = ',';
	vector<int> mazesize;
	while (getline(sizestream, section, delimeter)) {
		mazesize.push_back(stoi(section));
	}
	mazeX = mazesize[0] * 3;
	mazeY = mazesize[1] * 3;
	
	//splits the start position section and sets coordinates for start position
	stringstream startstream(splitinput[1]);
	vector<int> startpos;
	while (getline(startstream, section, delimeter)) {
		startpos.push_back(stoi(section));
	}
	mazeboxes[startpos[0]][startpos[1]] = "start";

	//splits the finishing location position section and set coordinates for finishing location
	stringstream finishstream(splitinput[2]);
	vector<int> finishpos;
	while (getline(finishstream, section, delimeter)) {
		finishpos.push_back(stoi(section));
	}
	mazeboxes[finishpos[0]][finishpos[1]] = "finish";

	//splits the wall coordinates and sets all positions of wall squares
	stringstream wallstream(splitinput[3]);
	vector<int> wallpos;
	while (getline(wallstream, section, delimeter)) {
		wallpos.push_back(stoi(section));
	}
	int wallcount = 0;
	while (wallcount < wallpos.size()) {
		mazeboxes[wallpos[wallcount]][wallpos[wallcount + 1]] = "wall";
		wallcount = wallcount + 2;
	}
	

	/* couts for testing
	cout << splitinput[0] << endl;
	cout << splitinput[1] << endl;
	cout << splitinput[2] << endl;
	cout << splitinput[3] << endl;
	cout << mazeX << endl;
	cout << mazeY << endl;
	cout << mazeboxes[0][0] << endl;
	cout << mazeboxes[9][9] << endl;
	cout << wallpos[0] << endl;
	cout << wallpos[1] << endl;
	cout << wallpos[2] << endl;
	cout << wallpos[3] << endl;
	cout << mazeboxes[0][5] << endl;
	cout << mazeboxes[6][5] << endl;
	cout << mazeboxes[4][3] << endl;
	cout << mazeboxes[6][6] << endl;
	cout << mazeboxes[8][4] << endl;
	
	int x = 0;
	for (int y = 0; y < mazeY; y++) {
		while (x < mazeX) {
			if (mazeboxes[x / 3][y / 3] == "start") {
				for (int j = 0; j < boxX; j++) {
					cout << start[y % 3][j];
					x++;
				}
			}
			else if (mazeboxes[x / 3][y / 3] == "finish") {
				for (int j = 0; j < boxX; j++) {
					cout << goal[y % 3][j];
					x++;
				}
			}
			else if (mazeboxes[x / 3][y / 3] == "wall") {
				for (int j = 0; j < boxX; j++) {
					cout << wall[y % 3][j];
					x++;
				}
			}
			else {
				for (int j = 0; j < boxX; j++) {
					cout << open[y % 3][j];
					x++;
				}
			}
			
			
		}
		x = 0;
		cout << endl;
	}
	*/

	//opens or creates output file to write maze in
	ofstream outFile("c:\\users\\rick\\source\\repos\\Maze\\Maze\\output_file.txt"); //can't get to work without full file path, adjust filepath to run properly

	//loops through coordinates, checking for the type of square and writing the correct characters to write the maze to the output file.
	int x = 0;
	for (int y = 0; y < mazeY; y++) {
		while (x < mazeX) {
			if (mazeboxes[x / 3][y / 3] == "start") {
				for (int j = 0; j < boxX; j++) {
					outFile << start[y % 3][j];
					x++;
				}
			}
			else if (mazeboxes[x / 3][y / 3] == "finish") {
				for (int j = 0; j < boxX; j++) {
					outFile << goal[y % 3][j];
					x++;
				}
			}
			else if (mazeboxes[x / 3][y / 3] == "wall") {
				for (int j = 0; j < boxX; j++) {
					outFile << wall[y % 3][j];
					x++;
				}
			}
			else {
				for (int j = 0; j < boxX; j++) {
					outFile << open[y % 3][j];
					x++;
				}
			}


		}
		x = 0;
		outFile << endl;
	}

	//displays message to console once finished and pauses
	cout << "Check output_file.txt to see the maze!" << endl;
	system("pause");
	return 0;
}
