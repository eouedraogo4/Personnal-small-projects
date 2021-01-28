#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

#define PLAYER1 0
#define PLAYER2 1

typedef enum { win, moved, error } Status;
typedef enum { single, multi } Mode;


class Computer {
public:
	static pair<int,int> nextMove(vector<string> const& table) {
		return randomMove(table);
	}

	static pair<int,int> randomMove(vector<string> const& table) {
		srand(time(NULL));
		int x,y;
		while(true) {
			//get random x and y
			 x = (int)rand()%table.size();
			 y = (int)rand()%table[x].size();

			//check the move is avalaible
			if(table[x][y] == ' ') {
				return pair<int,int>(x,y);
			}
		}
		return pair<int,int>(x,y);
	}
};


class Game{
	int size;
	Mode mode;
	vector<string> gameTable;
	vector<vector<int>> HLines, VLines, OLines;

public:
	Game() : Game(3,single) {}

	Game(int size) : Game(size,single) {}

	Game(Mode mode) : Game(3,mode) {}

	Game(int size, Mode mode) : size(size), mode(mode) {}	
	
	void initGame() {
		//init lines
		HLines = vector<vector<int>>(2,vector<int>(size,0));	
		VLines = vector<vector<int>>(2,vector<int>(size,0));
		OLines = vector<vector<int>>(2,vector<int>(2,0));

		//init game table
		gameTable = vector<string>(size,string(size,' '));
	}

	void play() {
		//init maps, table and lines
		initGame();
		
		//when the game ends(win or draw(count == size means no more empty place to play)) flag = true
		bool flag = false;
		int count = 0;
		
		//game always start with player1
		int player = PLAYER1;
		
		while(!flag) {
			//display game current status
			displayTable();
	
			//status will tell current player move is correct(empty, in the game table range), incorrect or if the player wins
			//when the move is incorrect ask again the player the correct it
			Status status;
			do {
				//check if there still exist empty places to play(if not it is a Draw
				if(count >= size*size) {
					flag = true;
					cout << "Draw" << endl;
					break;
				}
				
				//get the current player next move
				pair<int,int> p = nextMove(player);
				
				//adding the move to maps, game table and updating the lines
				status = addMove(player,p.first,p.second);
				switch(status) {
					case win : 
						flag = true;
						displayTable();
						displayWins(player);
						break;
					case error :
						cout << "Move not avalaible" << endl;
						break;
					case moved:
						count++;
						break;
					default : break;
				}
			}while(status != moved && status != win);

			//change player
			player = player == PLAYER1 ? PLAYER2 : PLAYER1;
		}
	}

	void displayTable() {
		//s will be a horizontal line(i.e "  - - - -")
		string s(" ");
		for(int i = 0; i < size; i++)
			s += " -";

		//diplay X axis (i.e "  1 2 3")
		cout << " ";
		for(int i = 0; i < size; i++) 
			cout << " " << i;
		cout << endl;

		//display the game table
		for(int i = 0; i < size; i++) {
			//display the horizontal line s then display Y axis next element
			cout << s << endl << i;

			//display table values
			for(auto& c: gameTable[i])
				cout << "|" << c;
			cout << "|" << endl;
		}
		cout << s << endl;
	}
	
	
	pair<int,int> nextMove(int i) {
		//when single mode computer play for player2
		if(mode == single && i == PLAYER2) {
			cout << "Computer " << endl;
			return Computer::nextMove(gameTable);
		}

		//get the next move from inputs
		cout << "Player " << i+1 << endl;
		int x, y;
		while(true) {
			cout << "Enter your next move : ";
			cin >> x >> y;

			//check the move is in range
			if(x >= 0 &&  y >= 0 && x < size &&  y < size) {
				//check the move is avalaible
				if(gameTable[x][y] == ' ') {
					return pair<int,int>(x,y);
				}
				else {
					cout << "Not avalaible !!" << endl << "Try again : ";
				}
			}
			else {
				cout << "Input out of range !! " << endl << "Try again : ";
			}
		}
		return pair<int,int>(x,y);
	}

	//i represent the the player number : PLAYER1 or PLAYER2
	Status addMove(int i, int x, int y) {
		//if x already exist and y too it means the move had been already played
		if(gameTable[x][y] != ' ') {
			return error;
		}
		
		//update game table
		gameTable[x][y] = i == PLAYER1 ? 'O' : 'X';

		//update lines
		return updateLines(i,x,y);
	}
	
	
	Status updateLines(int k, int x, int y) {
		if(++HLines[k][x] >= size)
			return win;
		if(++VLines[k][y] >= size) 
			return win;
		if(x == y && ++OLines[k][0] >= size)
			return win;
		if(x + y == size-1 && ++OLines[k][1] >= size)
			return win;
		return moved;
	}
	
	
	void displayWins(int i) {
		if(mode == multi || i == PLAYER1) {
		cout << "Player " << i+1 << " Won" << endl;
		}
		else {
			cout << "Computuer Won" << endl;
		}
	}

};



int main() {
	while(true) {
		//set game mode
		int mode, size;
		cout << "1. Single" << endl << "2. Multi Player" << endl << "3. Exit" << endl;
		cin >> mode;

		//exit 
		if(mode == 3)
			break;
		
		//set game table size
		cout << "Set Table size : ";
		cin >> size;

		//init game and play
		Game* game = NULL;
		switch(mode) {
			case 1:
				game = new Game(size,single);
				game->play();
				break;
			case 2:
				game = new Game(size,multi);
				game->play();
				break;
		}
		delete game;
	}
	return 0;
}

