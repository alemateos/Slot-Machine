//Author: Alejandro Mateos
//Slot Machine Game
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

enum Options { TOMATO, ORANGE, APPLE, PINEAPPLE, STRAWBERRY, GRAPES };

const int MILIDELAY = 100; //defines the delay in miliseconds as a constant
const int NUMSPINS = 50; //defines the number of time to spin the slot machine as a constant

void mainMenu();
void slotMachine();
string outputOptions(Options x); //Returns the string equivalent of the enum type Options value
void getPos(Options& x); //This function cycles through the Options values
void delay(); //delays the output by the number of miliseconds as defined by the constant MILIDELAY
void spinMachine(Options& one, Options& two, Options& three); //Simulates the spinning of the slot machine for a specifed number of spins as defined by NUMSPINS
void getStopOrder(int& first, int& second, int& last);
void score(Options& posOne, Options& posTwo, Options& posThree);
void outputScore(string userName[], int score[]);

const int SIZE = 20;
int points;

void statMenu();
void initData(string list[], string value);  //initData function to initialize a string array
void initData(int list[], int value);  //override of initData function to initialize an int array
//what reason could I have to override the initData function?
void readData(string userName[], int score[]);  //function to read data into memory
void displayData(string userName[], int score[]);  //function to display arrays
void sortUsers(string userName[], int score[]);  //function to sort our arrays
//deleteUser displays list of users and an index; ask the user for the index to delete;
//then mark that index for deletion
void deleteUser(string userName[], int score[]);
void saveData(string userName[], int score[]);

int main()
{
	mainMenu();

	return 0;
}


void mainMenu()
{
	char choice = 'z', pauseChar;
	string userName[SIZE];
	string name;
	int currentScore = 0;
	int score[SIZE];



	while (choice != 'q')
	{
		system("cls");
		cout << "\tWelcome to the Slot Machine Game Menu";
		cout << "\n\n\ta) Play the Slot Machine Game.";
		cout << "\n\n\tb) Game Stats. ";
		cout << "\n\n\tq) Exit.";
		cout << "\n\n\tPlease enter a selection: ";
		cin >> choice;

		switch (choice)
		{
		case 'a':

			initData(userName, "noname");
			initData(score, -1);
			readData(userName, score);
			outputScore(userName, score);
			cin >> pauseChar;
			break;

		case 'b':

			statMenu();

			break;

		case 'q':
			choice = 'q';
			cout << "\n\n";
			break;
		default:
			cout << "\nSorry, wrong selection please try again.\n";
		}
	}

}

void statMenu()
{
	char choice = 'z', pauseChar;
	string userName[SIZE];
	string name;
	int currentScore = 0;
	int score[SIZE];

	initData(userName, "noname");
	initData(score, -1);
	readData(userName, score);

	while (choice != 'q')
	{
		system("cls");
		cout << "\tWelcome to the Stats Menu";
		cout << "\n\n\ta) Game Stats.";
		cout << "\n\n\tb) Delete user. ";
		cout << "\n\n\tc) Go back to main menu. ";
		cout << "\n\n\tq) Exit.";
		cout << "\n\n\tPlease enter a selection: ";
		cin >> choice;

		switch (choice)
		{
		case 'a':

			sortUsers(userName, score);
			displayData(userName, score);
			cin >> pauseChar;

			break;

		case 'b':

			deleteUser(userName, score);  //marks one or more user for deletion
			cout << "\n\n";
			cin >> pauseChar;

			break;

		case 'c':

			system("cls");
			mainMenu();

			break;
		case 'q':

			choice = 'q';
			cout << "\n\n\tProgram will exit\n";
			exit(1); 
			cout << "\n\n";
			break;
		default:
			cout << "\nSorry, wrong selection please try again.\n";

		}

	}
}
//GAME
void slotMachine()
{
	//defines three spinning position each starting with a different value
	Options posOne = TOMATO;
	Options posTwo = TOMATO;
	Options posThree = TOMATO;

	char userChoice = 'z';

	spinMachine(posOne, posTwo, posThree); //spins the slotmachines positions
	score(posOne, posTwo, posThree);

}

//Do not change anything below this line
string outputOptions(Options x)
{
	//Returns the string equivalent of the enum type Options value
	switch (x)
	{
	case TOMATO:
		return "TOMATO";
		break;
	case ORANGE:
		return "ORANGE";
		break;
	case APPLE:
		return "APPLE";
		break;
	case PINEAPPLE:
		return "PINEAPPLE";
		break;
	case STRAWBERRY:
		return "STRAWBERRY";
		break;
	case GRAPES:
		return "GRAPES";
		break;

	}
}

void getPos(Options& x)
{
	//This function cycles through the Options values
	//each time it is called it increments to the next Options value and
	//starts from the beginning of the list when it reaches the end of the list
	if (x == GRAPES)
		x = TOMATO;
	else
		x = static_cast<Options>(x + 1);

}
void delay()
{
	//delays the output by the number of miliseconds passed
	clock_t endWait = clock() + MILIDELAY;
	while (clock() < endWait)
	{

	} //do nothing

}
void spinMachine(Options& posOne, Options& posTwo, Options& posThree)
{
	int first, second, last;
	int count = 0;

	//determines how many spins to stop the first and second position to stop before the last.
	//numStopFirst must be greater than numStopSecond 
	int numStopFirst = 20, numStopSecond = 10;

	while (count <= NUMSPINS)
	{
		//randomly determine which position to stop first, second, and last
		getStopOrder(first, second, last);
		//determines how long to spin each position based on their stop order
		if (first == 1)
		{
			if (count <= NUMSPINS - numStopFirst)
			{
				getPos(posOne);
			}
			if (second == 2)
			{
				if (count <= NUMSPINS - numStopSecond)
					getPos(posTwo);
				getPos(posThree);
			}
			else
			{
				if (count <= NUMSPINS - numStopSecond)
					getPos(posThree);
				getPos(posTwo);
			}
		}
		else if (first == 2)
		{
			if (count <= NUMSPINS - numStopFirst)
			{
				getPos(posTwo);
			}
			if (second == 3)
			{
				if (count <= NUMSPINS - numStopSecond)
					getPos(posThree);
				getPos(posOne);
			}
			else
			{
				if (count <= NUMSPINS - numStopSecond)
					getPos(posOne);
				getPos(posThree);
			}
		}
		else
		{
			if (count <= NUMSPINS - numStopFirst)
			{
				getPos(posThree);
			}
			if (second == 2)
			{
				if (count <= NUMSPINS - numStopSecond)
					getPos(posTwo);
				getPos(posOne);
			}
			else
			{
				if (count <= NUMSPINS - numStopSecond)
					getPos(posOne);
				getPos(posTwo);
			}
		}

		//increments the value of Options each time the loop is execute
		//getPos(posOne);
		//getPos(posTwo);
		//getPos(posThree);
		delay(); //delay the execution of the cout statement by the number of miliseconds as defined by the constant MILIDELAY 
		//displays the value of each position on the same line in the conole
		cout << "Spinning:  " << setw(15) << outputOptions(posOne) << setw(15) << outputOptions(posTwo) << setw(15) << outputOptions(posThree) << "\r";
		count++; //increments count so that the loop can terminate
	}
}

void getStopOrder(int& first, int& second, int& last)
{
	//randomly determines the order in which to stop spinning each position

	srand(time(0));
	first = rand() % 3 + 1;
	last = rand() % 3 + 1;
	if (first == last)
	{
		if (last == 3)
		{
			last = 1;
			second = 2;
		}
		else
		{
			last = last + 1;
			if (last == 3)
				second = 1;
			else
				second = last + 1;
		}
	}
	else if (first == 1)
	{
		if (last == 2)
			second = 3;
		else
			second = 2;
	}
	else if (first == 2)
	{
		if (last == 3)
			second = 1;
		else
			second = 2;
	}
	else
	{
		if (last == 1)
			second = 2;
		else
			second = 1;
	}
}

//create your functions here
void score(Options& posOne, Options& posTwo, Options& posThree)
{

	if (posOne == posTwo&&posTwo == posThree)
	{
		cout << "\n\tYou have won 10 points" << endl;
		points = 10;

	}
	else if ((posOne == posTwo && posOne != posThree&& posTwo != posThree) || (posTwo == posThree&& posTwo != posOne&& posThree != posOne) || (posOne == posThree &&  posOne != posTwo&& posThree != posTwo))
	{
		cout << "\n\tYou have won 3 points" << endl;
		points = 3;

	}
	else if (posOne != posTwo&&posTwo != posThree)
	{
		cout << "\n\tYou have won 0 points" << endl;
		points = 0;

	}

}

void outputScore(string userName[], int score[])
{
	char selection = 'z';
	string name;
	int currentScore = 0;
	bool recordSave = false;
	char decision;

	cout << "\n\tPlease enter your username: \n\t";
	cin >> name;

	while (selection != 'n')
	{
		slotMachine();
		currentScore = currentScore + points;
		cout << "\n\nWould you like to spin again? (y/n): \n";
		cin >> selection;
		//store into array
	}
	if (selection == 'n')
	{
		cout << "\n\nDo you want to save your score? (y/n): \n";
		cin >> decision;
	}
	if (decision == 'y')
	{
		while (recordSave == false)
		{
			for (int i = 0; i < SIZE; i++)
			{
				if (score[i] == -1)
				{
					userName[i] = name;
					score[i] = currentScore;
					saveData(userName, score);

					recordSave = true;
				}
			}
		}
		cout << "\n\tYour score has been saved.\n";
	}
	else if (decision == 'n')
	{
		cout << "\n\tYour score has not been saved.\n";
	}

	cout << "\n\tYour score average is:  " << name << " " << currentScore << endl;
	cout << "\n\tPress 'n' to go back to menu." << endl;

}
//STATS


void initData(string list[], string value)
{
	for (int i = 0; i<SIZE; i++)
		list[i] = value;
}

void initData(int list[], int value)
{
	for (int i = 0; i<SIZE; i++)
		list[i] = value;
}

void readData(string userName[], int score[])
{
	ifstream inData;
	inData.open("mydata.txt");
	int thisindex = 0;

	while (!inData.eof())  //reads file until end of file reached
	{
		if (thisindex<SIZE)
		{
			inData >> userName[thisindex]; //reads a name and store it in the array
			inData >> score[thisindex];  //reads the score and store it with corresponding name
			thisindex++;
		}
		else {
			cout << "more records in data file than can be handled!";
			break;
		}
	}  
	inData.close();
}

void displayData(string userName[], int score[])
{
	for (int i = SIZE - 1; i >= 0; i--)
	{
		if (score[i] != -1)
		{
			cout << "\n" << setw(10) << userName[i] << "  " << setw(4) << score[i] << endl;
		}
		else
			break;
	}

}

void sortUsers(string userName[], int score[])
{
	int index;
	int smallestIndex;
	int location;
	int temp;
	string tempName;

	for (index = 0; index < SIZE - 1; index++)
	{
		//step a
		smallestIndex = index;

		for (location = index + 1; location<SIZE; location++)
			if (score[location] < score[smallestIndex])
				smallestIndex = location;

		//step b
		// swaps scores
		temp = score[smallestIndex];
		score[smallestIndex] = score[index];
		score[index] = temp;
		//swaps names
		tempName = userName[smallestIndex];
		userName[smallestIndex] = userName[index];
		userName[index] = tempName;
	}
}


void deleteUser(string userName[], int score[])
{
	//The way this function is written, because the arrays have been sorted the
	//user is asked to choose a record number starting with a number other than
	//0 if there are less records than the actual size of the array.
	//how could this be fixed? 

	int record;
	char choice = 'z';
	bool goodInput = false;

	while (choice != 'n')
	{
		//display users for deletion
		for (int i = 0; i<SIZE; i++)
			if (score[i] != -1)
				cout << endl << i << ") " << userName[i] << " " << score[i];

		cout << "\nPlease enter the number for the record you wish to delete: ";  //prompts user for record to delete
		cin >> record;  //get the record from the user to delete
		userName[record] = "nouser";  //marks the user record for deletion
		score[record] = -1;  //marks the corresponding score for deletion
		cout << "\nuser marked for deletion.";
		while (!goodInput)  //validates user input is correct
		{
			cout << "\nenter \"y\" to delete another user or \"n\" to continue: ";
			cin >> choice;
			switch (choice)
			{
			case 'Y':
			case 'y':
				choice = 'z';  //choice set to z because we do not want to terminate the outer loop
				goodInput = true;  //terminates the inner loop if user inputs Y||y
				break;
			case 'N':
			case 'n':
				choice = 'n'; //choice set to n to terminate the outer loop
				goodInput = true; //terminates the inner loop if user inputs N||n
				break;
			default:
				cout << "\nInvalid choice, please try again";
			}
		}
		goodInput = false;  //resets goodInput for the next iteration
	}
}

void saveData(string userName[], int score[])
{
	ofstream outfile;
	outfile.open("mydata.txt");

	for (int i = 0; i < SIZE; i++)
	{
		if (score[i] != -1)
		{
			outfile << userName[i] << " " << score[i] << endl;
			if (userName[i] == userName[i + 1])
				break;
		}
		else
			break;
	}
	outfile.close();

}