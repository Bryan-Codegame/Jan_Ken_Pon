#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <locale.h>

using namespace std;

const int ROUNDS_TO_WIN = 2;
const string EMPTY = " ";
const string PI = "Piedra";
const string PA = "Papel";
const string TI = "Tijera";
const int TIE = 3;

void menu();
int askNumber(string question, int high, int low = 1);
void winnerAnnouncement(int countPlayer, int countComputer, int countTie);
int humanMove();
int computerMove();
void displayScore(vector<string>& board, int countPlayer, int countComputer, int moveP, int moveC);
int winner(vector<string>& board);

int main() {
	const int NUM_SPACES = 3;
	int movePlayer; //Move Player
	int moveComputer; //Move Computer
	int countPlayer = 0;
	int countComputer = 0;
	int countTie = 0;
	
	vector<string> jankenpon = { PI, PA, TI };
	
	cout << "\nBIENVENIDO A PIEDRA-PAPEL-TIJERA\n";

	while (countPlayer < ROUNDS_TO_WIN && countComputer < ROUNDS_TO_WIN && countTie != TIE) {
		
		vector<string> board(NUM_SPACES, EMPTY);
		
		menu();

		movePlayer = humanMove();
		board[movePlayer] = jankenpon[movePlayer];

		moveComputer = computerMove();
		board[moveComputer] = jankenpon[moveComputer];

		
		if (winner(board) == TIE) {
			countTie++;
		} 
		else if (moveComputer == winner(board)) {
			countComputer++;
		}
		else {
			countPlayer++;
		}

		displayScore(board, countPlayer, countComputer, movePlayer, moveComputer);
		
	}
	
	winnerAnnouncement(countPlayer, countComputer, countTie);
}

void menu() {

	cout << "\n1. Piedra\n";
	cout << "2. Papel\n";
	cout << "3. Tijera\n";
}


void displayScore(vector<string>& board, int countPlayer, int countComputer, int moveP, int moveC) {
	
	cout << "\n--------------------------------------------";
	cout << "\n" << countPlayer << " \t " << countComputer;
	cout << "\nPlayer \t Computer";
	cout << "\n" << board[moveP] << " \t " << board[moveC];
	cout << "\n--------------------------------------------\n";

	//TODO: Está imprimiendo el orden es decir si yo elijo tijera y le compu papel entonces imprime en este orden {"", papel, tijera} dandole al player papel en lugar de lo que eligió.
	//Esta función tiene que saber que escogió el jugador y que escogió la computadora
	/*for (int i = 0; i < board.size(); i++) {
		if (board[i] != EMPTY) {
			cout << board[i] << " \t";
		}

		if (count(board.begin(), board.end(), EMPTY) == 2) {
			cout << board[i];
		}
	}*/
}	

void winnerAnnouncement(int countPlayer, int countComputer, int countTie) {
	
	if (countTie == TIE) {
		cout << "EMPATE";
	}
	else if (countPlayer == ROUNDS_TO_WIN) {
		cout << "¡¡GANASTE!!";
	}
	else {
		cout << "PERDISTE :(";
	}
}

int askNumber(string question, int high, int low) {
	int number;
	do {
		cout << question << "(" << low << " - " << high << ")";
		cin >> number;
	} while (number > high || number < low);

	return number;
}

int humanMove() {
	int move = askNumber("Elige el número de la opción del ", 3);
	move = move - 1;
	return move;
}

int computerMove() {
	int numRand = rand();
	int move = ((numRand % 3));
	return move;
}

int winner(vector<string>& board) {

	/*
		board [0, 1, 2]
		board {PI, " ", TI} = Tiene valores en la pos {0, 2} = Gana PI => retorna row = 0
		board {PI, PA, " "} = Tiene valores en la pos {0, 1} = Gana PA => retorna row = 1
		board {" ", PA, TI} = Tiene valores en la pos {1, 2} = Gana TI => retorna row = 2
		En la posición 

	*/

	const int TOTAL_ROWS = 3;

	const int COMPARE_POS[3][2] = {
		{0, 2},
		{0, 1},
		{1, 2}
	};

	for (int row = 0; row < TOTAL_ROWS; row++) {
		if (board[COMPARE_POS[row][0]] != EMPTY && board[COMPARE_POS[row][1]] != EMPTY) {
			return row;
		}
	}

	return TIE;
	
}