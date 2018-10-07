// Maze.cpp : Defines the entry point for the application.
//

#include "Maze.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

char start[3][3] = { {'.','.','.'},{'.','S','.'},{'.','.','.'} };
char goal[3][3] = { {'.','.','.'},{'.','F','.'},{'.','.','.'} };
char open[3][3] = { {'.','.','.'},{'.','.','.'},{'.','.','.'} };
char wall[3][3] = { {'X','X','X'},{'X','X','X'},{'X','X','X'} };
char path[3][3] = { {',',',',','},{',',',',','},{',',',',','} };
int boxX = 3, boxY = 3;
int mazeX, mazeY;
int finishX, finishY;
string mazeboxes[20][20]; //supports mazes up to 20 by 20 squares big

//opens or creates output file to write maze in
ofstream outFile("c:\\users\\rick\\source\\repos\\Maze\\Maze\\output_file.txt"); //can't get to work without full file path, adjust filepath to run properly


void printMaze() {
	
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
			else if (mazeboxes[x / 3][y / 3] == "open") {
				for (int j = 0; j < boxX; j++) {
					outFile << open[y % 3][j];
					x++;
				}
			}
			else if (mazeboxes[x / 3][y / 3] == "path") {
				for (int j = 0; j < boxX; j++) {
					outFile << path[y % 3][j];
					x++;
				}
			}

		}
		x = 0;
		outFile << endl;
	}
	for (int i = 0; i < mazeX; i++) {
		outFile << "-";
	}
	outFile << " " << endl;
}

struct qBox {
public:
	int x, y, manDist;

	qBox() {};
	qBox(int i, int j) {
		x = i;
		y = j;
		manDist = abs(finishX - x) + abs(finishY - y);
	}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}
	
};

struct Compare {
	bool operator()(const qBox &lhs, const qBox &rhs) const {
		return lhs.manDist < rhs.manDist;
	}
};

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

	for (int i = 0; i < mazesize[0]; i++) {
		for (int j = 0; j < mazesize[1]; j++) {
			mazeboxes[i][j] = "open";
		}
	}

	//splits the start position section and sets coordinates for start position
	stringstream startstream(splitinput[1]);
	vector<int> startpos;
	while (getline(startstream, section, delimeter)) {
		startpos.push_back(stoi(section));
	}
	mazeboxes[startpos[0]][startpos[1]] = "start";
	int ratX = startpos[0];
	int ratY = startpos[1];
	
	//splits the finishing location position section and set coordinates for finishing location
	stringstream finishstream(splitinput[2]);
	vector<int> finishpos;
	while (getline(finishstream, section, delimeter)) {
		finishpos.push_back(stoi(section));
	}
	mazeboxes[finishpos[0]][finishpos[1]] = "finish";
	finishX = finishpos[0];
	finishY = finishpos[1];
	qBox start = qBox(startpos[0], startpos[1]);

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

	printMaze();

	//puzzle solving loop using stack
	/*stack <string> route; 
	while (mazeboxes[ratX][ratY] != "finish") { 
		mazeboxes[ratX][ratY] = "path";

		if (mazeboxes[ratX + 1][ratY] == "open" | mazeboxes[ratX + 1][ratY] == "finish") {
			ratX++;
			route.push("west");
			cout << route.top() << endl;
			continue;
		}
		else if (mazeboxes[ratX][ratY + 1] == "open" | mazeboxes[ratX][ratY + 1] == "finish") {
			ratY++;
			route.push("south");
			cout << route.top() << endl;
			continue;
		}
		else if (mazeboxes[ratX - 1][ratY] == "open" | mazeboxes[ratX - 1][ratY] == "finish") {
			ratX--;
			route.push("east");
			cout << route.top() << endl;
			continue;
		}
		else if (mazeboxes[ratX][ratY - 1] == "open" | mazeboxes[ratX][ratY - 1] == "finish") {
			ratY--;
			route.push("north");
			cout << route.top() << endl;
			
			continue;
		}
		else {
			string last = route.top();
			route.pop();
			if (last == "west") {
				ratX--;
			}
			else if (last == "south") {
				ratY--;
			}
			else if (last == "east") {
				ratX++;
			}
			else if (last == "north") {
				ratY++;
			}
		}
		
	}*/


	//puzzle solving loop using queue
	/*queue<qBox> paths;
	paths.push(start);
	int testX, testY;
	testX = paths.front().getX();
	testY = paths.front().getY();
	while (mazeboxes[testX][testY] != "finish") {
	
		mazeboxes[testX][testY] = "path";

		if (mazeboxes[testX + 1][testY] == "open" | mazeboxes[testX + 1][testY] == "finish") {
			paths.push(qBox(testX + 1, testY));
		}
		if (mazeboxes[testX][testY + 1] == "open" | mazeboxes[testX][testY + 1] == "finish") {
			paths.push(qBox(testX, testY + 1));
		}
		if (mazeboxes[testX - 1][testY] == "open" | mazeboxes[testX - 1][testY] == "finish") {
			paths.push(qBox(testX - 1, testY));
		}
		if (mazeboxes[testX][testY - 1] == "open" | mazeboxes[testX][testY - 1] == "finish") {
			paths.push(qBox(testX, testY - 1));
		}
				
		paths.pop();
		testX = paths.front().getX();
		testY = paths.front().getY();
	}*/

	priority_queue<qBox, vector<qBox>, Compare> paths;
	paths.push(start);
	int testX, testY;
	testX = paths.top().x;
	testY = paths.top().y;
	while (mazeboxes[testX][testY] != "finish") {

		mazeboxes[testX][testY] = "path";
		/*cout << "size "; cout << paths.size() << endl;
		cout << "top x "; cout << paths.top().x << endl;
		cout << "top y "; cout << paths.top().y << endl;
		system("pause");*/
		paths.pop();
		//printMaze();
		

		if (mazeboxes[testX + 1][testY] == "open" | mazeboxes[testX + 1][testY] == "finish") {
			paths.push(qBox(testX + 1, testY));
			//cout << "right" << endl;
		}
		if (mazeboxes[testX][testY + 1] == "open" | mazeboxes[testX][testY + 1] == "finish") {
			paths.push(qBox(testX, testY + 1));
			//cout << "down" << endl;
		}
		if (mazeboxes[testX - 1][testY] == "open" | mazeboxes[testX - 1][testY] == "finish") {
			paths.push(qBox(testX - 1, testY));
			//cout << "left" << endl;
		}
		if (mazeboxes[testX][testY - 1] == "open" | mazeboxes[testX][testY - 1] == "finish") {
			paths.push(qBox(testX, testY - 1));
			//cout << "up" << endl;
		}
		
		testX = paths.top().x;
		testY = paths.top().y;

	}



	printMaze();

	//displays message to console once finished and pauses
	cout << "Check output_file.txt to see the maze!" << endl;
	system("pause");
	return 0;
}