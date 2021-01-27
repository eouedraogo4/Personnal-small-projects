#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

typedef enum { human1, human2, computer } Player; 
typedef enum { win, moved, error } Status;

int size;
unordered_map<int, unordered_map<int,int>> movesMap;
vector<string> gameTable;
vector<vector<int>> HLines;
vector<vector<int>> VLines;
vector<vector<int>> OLines;

void initLines() {
	HLines = vector<vector<int>>(2,vector<int>(size,0));	
	VLines = vector<vector<int>>(2,vector<int>(size,0));
	OLines = vector<vector<int>>(2,vector<int>(2,0));
}

Status updateLines(int k, int x, int y) {
	if(++HLines[k][x] >= size)
		return win;
	if(++VLines[k][y] >= size) 
		return win;
	if(x == y) {
		if(++OLines[k][0] >= size)
			return win;
	}
	else if(x + y == size-1) {
		if(++OLines[k][1] >= size)
			return win;
	}
	return moved;
}

Status addMove(Player player, int x, int y) {
	unordered_map<int, unordered_map<int,int>>::iterator it1 = movesMap.find(x);
	if(it1 == movesMap.end()) {
		unordered_map<int,int> map({{y,0}});
		movesMap.insert(pair<int,unordered_map<int,int>>(x,map));
	}
	else {
		unordered_map<int,int>::iterator it2 = it1->second.find(y);
		if(it2 == it1->second.end()) {
			it1->second.insert(pair<int,int>(y,0));
		}
		else {
			return error;
		}
	}
	
	int k;
	if(player == human1) {
		 k = 0;
		 gameTable[x][y] = 'O';
	}
	else {
		k = 1;
		gameTable[x][y] = 'X';
	}
	
	return updateLines(k,x,y);
}

pair<int,int> computerMove() {
	return pair<int,int>(0,0);
}


pair<int,int> nextMove(Player player) {
	if(player == human1 || player == human2) {
		if(player == human1)
			cout << "Player 1 " << endl;
		else
			cout << "Player 2 " << endl;
		while(true) {
			int x, y;
			cout << "Enter your next move : ";
			cin >> x >> y;
			if(x >= 0 &&  y >= 0 && x < size &&  y < size)
				return pair<int,int>(x,y);
			cout << "Input out of range !! " << endl;
		}
	}
	else {
		cout << "Computer " << endl;
		return computerMove();
	}
}


void displayWinner(Player player) {
	if(player == human1) {
		cout << "Player 1 Won" << endl;
	}
	else if(player == human2) {
		cout << "Player 2 Won" << endl;
	}
	else {
		cout << "Computuer Won" << endl;
	}
}

void printH() {
	cout << " ";
	for(int  i = 0; i < size; i++)
		cout << " -";
	cout << endl;
}

void displayTable() {
	cout << " ";
	for(int i = 0; i < size; i++) 
		cout << " " << i;
	cout << endl;
	for(int i = 0; i < size; i++) {
		printH();
		cout << i;
		for(auto& c: gameTable[i])
			cout << "|" << c;
		cout << "|" << endl;
	}
	printH();
}

void play(Player player1, Player player2) {
	initLines();
	movesMap.clear();
	gameTable = vector<string>(size);
	for(int i = 0; i < size; i++)
		gameTable[i] = string(size,' ');

	bool flag = false;
	int count = 0;
	Player player = player1;
	while(!flag) {
		displayTable();
		pair<int,int> p = nextMove(player);
		Status status;
		do {
			status = addMove(player,p.first,p.second);
			switch(status) {
				case win : 
					flag = true;
					displayTable();
					displayWinner(player);
					break;
				case error :
					cout << "Move not avalaible" << endl;
					p = nextMove(player);
					break;
				case moved:
					count++;
					break;
				default : break;
			}
			if(count >= size*size) {
				flag = true;
				cout << "Draw" << endl;
				break;
			}
		}while(status != moved && status != win);
		player = player == player1 ? player2 : player1;
	}	
}


int main() {
	int mode;
	do{
		cout << "1. Two players" << endl << "2. Computer" << endl << "3. Exit" << endl;
		cin >> mode;
		if(mode == 1 || mode == 2) {
			cout << "Select Level : ";
			cin >> size;
			if(mode == 1)
			       	play(human1, human2);
			else
				play(human1, computer);
		}
	}while(mode != 3);

	return 0;
}

