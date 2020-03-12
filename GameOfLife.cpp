#include <iostream>
#include "GameOfLife.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <sstream>

using namespace std;

//constructor declares the variables needed throughout the program
Game::Game() {
	string outputType = "";
	int countGen;
	string outString2 = "";
	string outFileName = "";
}

//destructor
Game::~Game() {

}

//Prints the board in the way that the user selected at the beginning of the program
void Game::printOptions(string outputType, int countGen, char**& board, int boardLength, int boardWidth){
	bool enter = false;
    //If statement to pause the print to the terminal
	if((outputType == "pause")||(outputType == "Pause")){

		sleep(1); //Briefly pauses printing
		cout << "Generation: " << countGen << "\n";

		for(int i = 0; i < boardLength; ++i) {
			for (int j = 0; j < boardWidth; ++j) {
				cout << board[i][j];
			}
			cout << "\n";
		}
    //Prints upon enter key
	}else if((outputType == "enter")||(outputType == "Enter")){

		cout << "Press enter key to continue \n" << endl;
		cin.get();

		if (cin.get()){
			enter = true;
		}

		if (enter = true){
			cout << "Generation: " << countGen << "\n";

			for(int i = 0; i < boardLength; ++i) {
				for (int j = 0; j < boardWidth; ++j) {
					cout << board[i][j];
				}
				cout << "\n";
			}
		}
	}
}

//If the user selected mirror mode they will be brought here and the board will update to use the mirror mode setting
int Game::mirrorMode(int boardLength, int boardWidth, char**& board){

	int count = 0;
	countGen = 1;
	bool stable = false;
    //Creates Secondary Board based off of the First Board Dimensions

    char** nextGen = new char*[boardLength];

    for (int i = 0; i < boardLength; ++i) {
    	nextGen[i] = new char[boardWidth];
    }

    while(stable == false){
    	for(int i = 0; i < boardLength; ++i){
			for(int j = 0; j < boardWidth; ++j){
            	count = 0;

           		/* If count is ++ there is a singular neighbor with no reflection
            	 * If count is += 2 this accounts for the neighbor and the reflection of neighbor
            	 * If count is += 3 this accounts for own reflection in the corner
            	 */

				if (i == 0 && j == 0) {
					if(board[i+1][j] == 'X') count+=2;
					if(board[i][j+1] == 'X') count+=2;
					if(board[i+1][j+1] == 'X') count++;
					if(board[i][j] == 'X') count+=3;
				}
				else if (i == 0 && j == (boardWidth - 1)) {
					if(board[i+1][j] == 'X') count+=2;
					if(board[i][j-1] == 'X') count+=2;
					if(board[i+1][j-1] == 'X') count++;
					if(board[i][j] == 'X') count+=3;
				}
				else if (i == (boardLength - 1 ) && j == (boardWidth - 1)) {
					if(board[i-1][j] == 'X') count+=2;
					if(board[i][j-1] == 'X') count+=2;
					if(board[i-1][j-1] == 'X') count++;
					if(board[i][j] == 'X') count+=3;
				}
				else if (i == (boardLength - 1) && j == 0) {
					if(board[i-1][j] == 'X') count+=2;
					if(board[i][j+1] == 'X') count+=2;
					if(board[i-1][j+1] == 'X') count++;
					if(board[i][j] == 'X') count+=3;
            	}
	            else if (i == 0) {
					if(board[i+1][j] == 'X') count++;
					if(board[i][j+1] == 'X') count+=2;
					if(board[i+1][j+1] == 'X') count++;
					if(board[i][j-1] =='X') count+=2;
					if(board[i+1][j-1] == 'X') count++;
					if(board[i][j] == 'X') count++;
    	        }
				else if (j == 0) {
					if(board[i-1][j] == 'X') count+=2;
					if(board[i+1][j] == 'X') count+=2;
					if(board[i][j+1] == 'X') count++;
					if(board[i+1][j+1] == 'X') count++;
					if(board[i-1][j+1] == 'X') count++;
					if(board[i][j] == 'X') count++;
				}
	            else if (i == (boardLength - 1)) {
					if(board[i-1][j] == 'X') count++;
					if(board[i][j+1] == 'X') count+=2;
					if(board[i-1][j+1] == 'X') count++;
					if(board[i][j-1] =='X') count+=2;
					if(board[i-1][j-1] == 'X') count++;
					if(board[i][j] == 'X') count++;
				}
				else if (j == (boardWidth - 1)) {
					if(board[i-1][j] == 'X') count+=2;
					if(board[i+1][j] == 'X') count+=2;
					if(board[i][j-1] == 'X') count++;
					if(board[i+1][j-1] == 'X') count++;
					if(board[i-1][j-1] == 'X') count++;
					if(board[i][j] == 'X') count++;
				}
				else {
					if(board[i+1][j] == 'X') count++;
					if(board[i][j+1] == 'X') count++;
					if(board[i+1][j+1] == 'X') count++;
					if(board[i][j-1] =='X') count++;
					if(board[i-1][j] == 'X') count++;
					if(board[i-1][j-1] == 'X') count++;
					if(board[i+1][j-1] =='X') count++;
					if(board[i-1][j+1] == 'X') count++;
            	}
	            if (count < 2) {
    	        	//If there are One of Fewer Neighbors --> Death
        	   		nextGen[i][j] = '-';
        		}
        		else if (count == 2) {
	            	//If there are exactly Two Neighbors --> No Change (Stablized)
    	        	nextGen[i][j] = board[i][j];
        		}
        		else if (count == 3) {
            		//If there are Three Neighbors + Empty Cell --> Birth of Cell
            		nextGen[i][j] = 'X';
        		}
	        	else if (count > 3) {
    	        	//If there are Four or More Neighbors --> Death
        	    	nextGen[i][j] = '-';
        		}
	        }
    	}

        int checker = 0;

        for (int i = 0; i <boardLength; ++i){
       		for (int j = 0; j < boardWidth; ++j) {
	       		if (nextGen[i][j] == board[i][j]) {
	       			checker++;
	           	}
           		else {
           			stable = false;
         		}
       		}
    	}

    	if (checker == (boardLength*boardWidth)){
    		stable = true;
    		cout << "\nThe World is Stable" << endl;
    	}
        //Print out to a File
    	if (stable == false){

    		std::stringstream sstm;
    		sstm << "Generation: " << countGen << "\n";
            outString2 += sstm.str();


            if (countGen == 1){

            	for(int i = 0; i < boardLength; ++i){
      				for(int j = 0; j < boardWidth; ++j){
      					std::stringstream sstm;
   						sstm << board[i][j];
   						outString2 += sstm.str();
   					}
   					std::stringstream sstm;
   					sstm << "\n";
   					outString2 += sstm.str();
  				}

            	printOptions(outputType, countGen, board, boardLength, boardWidth);

            	for(int i = 0; i < boardLength; ++i){
      				for(int j = 0; j < boardWidth; ++j){
      					board[i][j] = nextGen[i][j];
      				}
      			}

            }else{

            	for(int i = 0; i < boardLength; ++i){
      				for(int j = 0; j < boardWidth; ++j){
      					board[i][j] = nextGen[i][j];
      					std::stringstream sstm;
      					sstm << board[i][j];
      					outString2 += sstm.str();
      				}
      				std::stringstream sstm;
   					sstm << "\n";
   					outString2 += sstm.str();
      			}
      			printOptions(outputType, countGen, board, boardLength, boardWidth);
      		}
    	}

    	countGen++;
    }

    if(outFileName != ""){
    	ofstream outputFile;
    	outputFile.open(outFileName.c_str());
    	outputFile << outString2 << "\n";
    	outputFile.close();
	}
    return 0;

}

// //If the user selected donut mode they will be brought here and the board will update to use the donut mode setting
int Game::donutMode(int boardLength, int boardWidth, char**& board){


	int count = 0;
	countGen = 1;
	bool stable = false;
    //Creates Secondary Board based off of the First Board Dimensions
    char** nextGen = new char*[boardLength];

    for (int i = 0; i < boardLength; ++i) {
        	nextGen[i] = new char[boardWidth];
    }

    while(stable == false){
   		for(int i = 0; i < boardLength; ++i){
			for(int j = 0; j < boardWidth; ++j){
				count = 0;
				if (i == 0 && j == 0) {
					if(board[i+1][j] == 'X') count++;
					if(board[i][j+1] == 'X') count++;
					if(board[i+1][j+1] == 'X') count++;
					if(board[boardLength-1][j] == 'X') count++; //Bottom of Row (boardLength), same Column (boardWidth)
					if(board[boardLength-1][j+1] == 'X') count++; //Bottom Row (boardLength) Bottom Column+1 (boardWidth+1)
					if(board[boardLength-1][boardWidth-1] == 'X') count++; //Opposite Corner
					if(board[i][boardWidth-1] == 'X') count++; //Opposite Side
					if(board[i+1][boardWidth-1] == 'X') count++; //Opposite Side and Down One
				}
				else if (i == 0 && j == (boardWidth - 1)) {
					if(board[i+1][j] == 'X') count++;
					if(board[i][j-1] == 'X') count++;
					if(board[i+1][j-1] == 'X') count++;
					if(board[boardLength-1][j] == 'X') count++;
					if(board[boardLength-1][j-1] == 'X') count++;
					if(board[boardLength-1][0] == 'X') count++;
					if(board[i][0] == 'X') count++; //Opposite Corner
					if(board[i+1][0] == 'X') count++;
				}
				else if (i == (boardLength - 1 ) && j == (boardWidth - 1)) {
					if(board[i-1][j] == 'X') count++;
					if(board[i][j-1] == 'X') count++;
					if(board[i-1][j-1] == 'X') count++;
					if(board[0][j-1] == 'X') count++;
					if(board[0][j] == 'X') count++;
					if(board[0][0] == 'X') count++;
					if(board[i][0] == 'X') count++;
					if(board[i-1][0] == 'X') count++;
				}
				else if (i == (boardLength - 1) && j == 0) {
					if(board[i-1][j] == 'X') count++;
					if(board[i][j+1] == 'X') count++;
					if(board[i-1][j+1] == 'X') count++;
					if(board[0][j] == 'X') count++;
					if(board[0][j+1] == 'X') count++;
					if(board[0][boardWidth-1] == 'X') count++;
					if(board[i-1][boardWidth-1] == 'X') count++;
					if(board[i][boardWidth-1] == 'X') count++;
				}
				else if (j == 0) {
					if(board[i-1][j] == 'X') count++;
					if(board[i+1][j] == 'X') count++;
					if(board[i][j+1] == 'X') count++;
					if(board[i+1][j+1] == 'X') count++;
					if(board[i-1][j+1] == 'X') count++;
					if(board[i-1][boardWidth-1] == 'X') count++;
					if(board[i][boardWidth-1] == 'X') count++;
					if(board[i+1][boardWidth-1] == 'X') count++;
				}
				else if (i == 0) {
					if(board[i+1][j] == 'X') count++;
					if(board[i][j+1] == 'X') count++;
					if(board[i+1][j+1] == 'X') count++;
					if(board[i][j-1] =='X') count++;
					if(board[i+1][j-1] == 'X') count++;
					if(board[boardLength-1][j-1] == 'X') count++;
					if(board[boardLength-1][j] == 'X') count++;
					if(board[boardLength-1][j+1] == 'X') count++;
        	    }
            	else if (i == (boardLength - 1)) {
					if(board[i-1][j] == 'X') count++;
					if(board[i][j+1] == 'X') count++;
					if(board[i-1][j+1] == 'X') count++;
					if(board[i][j-1] =='X') count++;
					if(board[i-1][j-1] == 'X') count++;
					if(board[0][j-1] == 'X') count++;
					if(board[0][j] == 'X') count++;
					if(board[0][j+1] == 'X') count++;
				}
				else if (j == (boardWidth - 1)) {
					if(board[i-1][j] == 'X') count++;
					if(board[i+1][j] == 'X') count++;
					if(board[i][j-1] == 'X') count++;
					if(board[i+1][j-1] == 'X') count++;
					if(board[i-1][j-1] == 'X') count++;
					if(board[i-1][0] == 'X') count++;
					if(board[i][0] == 'X') count++;
					if(board[i+1][0] == 'X') count++;
				}
				else {
					if(board[i+1][j] == 'X') count++;
					if(board[i][j+1] == 'X') count++;
					if(board[i+1][j+1] == 'X') count++;
					if(board[i][j-1] =='X') count++;
					if(board[i-1][j] == 'X') count++;
					if(board[i-1][j-1] == 'X') count++;
					if(board[i+1][j-1] =='X') count++;
					if(board[i-1][j+1] == 'X') count++;
				}
        		if (count < 2) {
            		//If there are One of Fewer Neighbors --> Death
           			nextGen[i][j] = '-';
        		}
	        	else if (count == 2) {
    	        	//If there are exactly Two Neighbors --> No Change (Stablized)
        	    	nextGen[i][j] = board[i][j];
        		}
	        	else if (count == 3) {
    	        	//If there are Three Neighbors + Empty Cell --> Birth of Cell
        	    	nextGen[i][j] = 'X';
        		}
        		else if (count > 3) {
            		//If there are Four or More Neighbors --> Death
            		nextGen[i][j] = '-';
        		}
        	}
    	}

        int checker = 0;

        for (int i = 0; i <boardLength; ++i){
       		for (int j = 0; j < boardWidth; ++j) {
	       		if (nextGen[i][j] == board[i][j]) {
	       			checker++;
	           	}
           		else {
           			stable = false;
         		}
       		}
    	}

    	if (checker == (boardLength*boardWidth)){
    		stable = true;
    		cout << "\nThe World is Stable" << endl;
    	}

     	if (stable == false){

    		std::stringstream sstm;
    		sstm << "Generation: " << countGen << "\n";
            outString2 += sstm.str();


            if (countGen == 1){

            	for(int i = 0; i < boardLength; ++i){
      				for(int j = 0; j < boardWidth; ++j){
      					std::stringstream sstm;
   						sstm << board[i][j];
   						outString2 += sstm.str();
   					}
   					std::stringstream sstm;
   					sstm << "\n";
   					outString2 += sstm.str();
  				}

            	printOptions(outputType, countGen, board, boardLength, boardWidth);

            	for(int i = 0; i < boardLength; ++i){
      				for(int j = 0; j < boardWidth; ++j){
      					board[i][j] = nextGen[i][j];
      				}
      			}

            }else{

            	for(int i = 0; i < boardLength; ++i){
      				for(int j = 0; j < boardWidth; ++j){
      					board[i][j] = nextGen[i][j];
      					std::stringstream sstm;
      					sstm << board[i][j];
      					outString2 += sstm.str();
      				}
      				std::stringstream sstm;
   					sstm << "\n";
   					outString2 += sstm.str();
      			}
      			printOptions(outputType, countGen, board, boardLength, boardWidth);
      		}
    	}

    	countGen++;
    }

    if(outFileName != ""){
    	ofstream outputFile;
    	outputFile.open(outFileName.c_str());
    	outputFile << outString2 << "\n";
    	outputFile.close();
	}
    return 0;
}

// //If the user selected classic mode they will be brought here and the board will update to use the classic mode setting
int Game::classicMode(int boardLength, int boardWidth, char**& board){

	int count = 0;
	countGen = 1;
	bool stable = false;

    //Creates Secondary Board based off of the First Board Dimensions
    char** nextGen = new char*[boardLength];

    for (int i = 0; i < boardLength; ++i) {
    	nextGen[i] = new char[boardWidth];
    }

    while(stable == false){

	    for (int i = 0; i < boardLength; ++i) {
    	    for (int j = 0; j < boardWidth; ++j) {
        	    count = 0;
            	if (i == 0 && j == 0) {
               		if (board[i+1][j] == 'X') count++;
	                if (board[i][j+1] == 'X') count++;
    	            if (board[i+1][j+1] == 'X') count++;
        	    }
            	else if (i == 0 && j == (boardWidth - 1)) {
                	if (board[i+1][j] == 'X') count++;
            	    if (board[i][j-1] == 'X') count++;
                	if (board[i+1][j-1] == 'X') count++;
	            }
    	        else if (i == (boardLength - 1) && j == 0) {
        	        if (board[i-1][j] == 'X') count++;
            	    if (board[i][j+1] == 'X') count++;
                	if (board[i-1][j+1] == 'X') count++;
	            }
    	        else if (i == (boardLength - 1) && j == (boardWidth - 1)) {
        	        if (board[i-1][j] == 'X') count++;
            	    if (board[i][j-1] == 'X') count++;
                	if (board[i-1][j-1] == 'X') count++;
	            }
    	        //Checks the Sides of the Board
        	    else if (i == 0) {
            	    if (board[i+1][j] == 'X') count++;
	                if (board[i][j+1] == 'X') count++;
    	            if (board[i+1][j+1] == 'X') count++;
        	        if (board[i][j-1] == 'X') count++;
	                if (board[i+1][j-1] == 'X') count++;
    	        }
        	    else if (j == 0) {
            	    if (board[i-1][j] == 'X') count++;
                	if (board[i+1][j] == 'X') count++;
	                if (board[i][j+1] == 'X') count++;
    	            if (board[i+1][j+1] == 'X') count++;
        	        if (board[i-1][j+1] == 'X') count++;
            	}
	            else if (i == (boardLength - 1)) {
    	            if (board[i-1][j] == 'X') count++;
        	        if (board[i][j+1] == 'X') count++;
            	    if (board[i-1][j+1] == 'X') count++;
	                if (board[i][j-1] == 'X') count++;
    	            if (board[i-1][j-1] == 'X') count++;
        	    }
            	else if(j == (boardWidth - 1)) {
                	if (board[i-1][j] == 'X') count++;
	                if (board[i+1][j] == 'X') count++;
    	            if (board[i][j-1] == 'X') count++;
        	        if (board[i+1][j-1] == 'X') count++;
            	    if (board[i-1][j-1] == 'X') count++;
	            }
    	        else {
					if(board[i+1][j] == 'X') count++;
					if(board[i][j+1] == 'X') count++;
					if(board[i+1][j+1] == 'X') count++;
					if(board[i][j-1] =='X') count++;
					if(board[i-1][j] == 'X') count++;
					if(board[i-1][j-1] == 'X') count++;
					if(board[i+1][j-1] =='X') count++;
					if(board[i-1][j+1] == 'X') count++;
				}
        		if (count < 2) {
            		//If there are One of Fewer Neighbors --> Death
	           		nextGen[i][j] = '-';
    	    	}
        		else if (count == 2) {
            		//If there are exactly Two Neighbors --> No Change (Stablized)
            		nextGen[i][j] = board[i][j];
	        	}
    	    	else if (count == 3) {
        	    	//If there are Three Neighbors + Empty Cell --> Birth of Cell
            		nextGen[i][j] = 'X';
        		}
        		else if (count > 3) {
            		//If there are Four or More Neighbors --> Death
            		nextGen[i][j] = '-';
        		}

        	}
        }


        int checker = 0;

        for (int i = 0; i <boardLength; ++i){
       		for (int j = 0; j < boardWidth; ++j) {
	       		if (nextGen[i][j] == board[i][j]) {
	       			checker++;
	           	}
           		else {
           			stable = false;
         		}
       		}
    	}


    	if (checker == (boardLength*boardWidth)){
    		stable = true;
    		cout << "\nThe World is Stable" << endl;
    	}


    	if (stable == false){

    		std::stringstream sstm;
    		sstm << "Generation: " << countGen << "\n";
            outString2 += sstm.str();

            if (countGen == 1){

            	for(int i = 0; i < boardLength; ++i){
      				for(int j = 0; j < boardWidth; ++j){
      					std::stringstream sstm;
   						sstm << board[i][j];
   						outString2 += sstm.str();
   					}
   					std::stringstream sstm;
   					sstm << "\n";
   					outString2 += sstm.str();
  				}

            	printOptions(outputType, countGen, board, boardLength, boardWidth);

            	for(int i = 0; i < boardLength; ++i){
      				for(int j = 0; j < boardWidth; ++j){
      					board[i][j] = nextGen[i][j];
      				}
      			}

            }else{

            	for(int i = 0; i < boardLength; ++i){
      				for(int j = 0; j < boardWidth; ++j){
      					board[i][j] = nextGen[i][j];
      					std::stringstream sstm;
      					sstm << board[i][j];
      					outString2 += sstm.str();
      				}
      				std::stringstream sstm;
   					sstm << "\n";
   					outString2 += sstm.str();
      			}
      			printOptions(outputType, countGen, board, boardLength, boardWidth);
      		}
    	}

    	countGen++;
    }

    if(outFileName != ""){
    	ofstream outputFile;
    	outputFile.open(outFileName.c_str());
    	outputFile << outString2 << "\n";
    	outputFile.close();
	}

    return 0;
}

//asks the user which game mode they want and then continues to whichever mode they selected
void Game::selectMode(int& boardLength, int& boardWidth, char**& board){

	string mode = "";
	bool continueOn = true;

	while(continueOn == true){

		cout << "Select game mode: Classic, Mirror, or Donut \n" << endl;
		cin >> mode;

		if((mode == "Classic") || (mode == "classic")) {
			classicMode(boardLength, boardWidth, board);
			continueOn = false;
		}else if((mode == "Mirror") || (mode == "mirror")){
			mirrorMode(boardLength, boardWidth, board);
			continueOn = false;
		}else if ((mode == "Donut") || (mode == "donut")){
			donutMode(boardLength, boardWidth, board);
			continueOn = false;
		}else{
			continueOn = true;
		}
	}
}

//creates a board that will be used when the user wants a random board
void Game::createRandomBoard(int& boardLength, int& boardWidth){

	double densityNumber = 0.0;
	bool correctInput = false;
	int numOfCells = 0;
	int randLength = 0;
    int randWidth = 0;

    //Import boardLength
	cout << "What is the length of the board? \n" << endl;
	cin >> boardLength;

    //Import boardWidth
	cout << "What is the width of the board? \n" << endl;
	cin >> boardWidth;

    //Import Density
	while (correctInput == false){
		cout << "Give me a number between 0 and 1 \n" << endl;
		cin >> densityNumber;

		if((densityNumber >= 0.0) && (densityNumber <= 1.0)){
			correctInput = true;
		}else{
			correctInput = false;
		}
	}

	char** transferBoard = new char*[boardLength];

    for (int i = 0; i < boardLength; ++i) {
      	transferBoard[i] = new char[boardWidth];
    }

	numOfCells = round((boardLength*boardWidth)*densityNumber);

	for (int i = 0; i < boardLength; i++){
		for (int j = 0; j < boardWidth; j++){
			transferBoard[i][j] = '-';
		}
	}
    //Calls time to create a truly random set of values
	srand(time(NULL));

	for (int k = 0; k < numOfCells; k++){

		randLength = rand() % (boardLength);
		randWidth = rand() % (boardWidth);

		int numCells = 1;

		while(numCells > 0){
			if(transferBoard[randLength][randWidth] == '-'){
				transferBoard[randLength][randWidth] = 'X';
				numCells--;
			}else{
				randLength = rand() % (boardLength);
				randWidth = rand() % (boardWidth);
			}
		}
	}

	selectMode(boardLength, boardWidth, transferBoard);
}

//Creates board based off of File Import
void Game::createFileBoard(string inputfile){

    ifstream inputStream;
    //Open up file user is reading
	inputStream.open(inputfile.c_str());

	int boardLength = 0;
	int boardWidth = 0;
	int counter = 0;
	string line = "";

	while(!inputStream.eof()){
		getline(inputStream, line);

		if (counter == 0){
			boardLength = atoi(line.c_str());
		} else if (counter == 1){
			boardWidth = atoi(line.c_str());
		} else {
			break;
		}
		counter++;
	}

	counter = 0;

	char** transferBoard = new char*[boardLength];


    for (int i = 0; i < boardLength; ++i) {
      	transferBoard[i] = new char[boardWidth];
    }

    for (int i = 0; i < boardLength; i++){
		for (int j = 0; j < boardWidth; j++){
			transferBoard[i][j] = '-';
		}
	}

	inputStream.seekg(0, inputStream.beg);

	int row = 0;

	while(!inputStream.eof()){

		getline(inputStream, line);

		if (counter == 0){

		} else if (counter == 1){

		} else {
			for(int i = 0; i < boardWidth; i++){
				char element = line[i];
				transferBoard[row][i] = element;
			}
			row++;
		}
		counter++;
	}

	selectMode(boardLength, boardWidth, transferBoard);

}

//asks the user if they want a random board or to submit a map
//choose how you want the game to be printed (in a file, with a pause, or by enter key)
void Game::selectSettings(){

	string setting = "";
	bool correctAnswer = false;
	bool wrongChoice = true;

	while(wrongChoice == true){
        //How user wants board printed
		cout << "How would you like your data printed? (type 'pause', 'enter', or 'file')\n" << endl;
		cin >> outputType;

		if((outputType == "pause")||(outputType == "Pause")){

			wrongChoice = false;

		}else if((outputType == "enter")||(outputType == "Enter")){

			wrongChoice = false;

		}else if((outputType == "file")||(outputType == "File")){

			cout << "What file would you like print out to? (include '.txt') \n" <<endl;
			cin >> outFileName;

			wrongChoice = false;

		}else{
			cout << "That's not an option. Try again.\n" << endl;
			wrongChoice = true;
		}

	}

	while(correctAnswer == false){

		string outFileName = "";
        //If User wants Random or File
		cout << "Would you like to have a random board or submit your own file? (type 'random' or 'file') \n" << endl;
		cin >> setting;

		if((setting == "random") || (setting == "Random")) {

			int boardLength = 0;
			int boardWidth = 0;

			createRandomBoard(boardLength, boardWidth);
			correctAnswer = true;

		}else if((setting == "file")||(setting == "File")){

			string fileName;

			cout << "What is the name of the .txt file you want to use? (include \".txt\") \n" << endl;
			cin >> fileName;

			createFileBoard(fileName);

			correctAnswer = true;

		}else{

			cout << "That selection is not applicable. Try one of the given selections \n" << endl;
			correctAnswer = false;

		}
	}
}
