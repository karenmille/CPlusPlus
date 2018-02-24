/*
 
	Karen Miller

	cactpot.cpp

	Cactus pot is a lottery game where the player wins points rewards by the pay out table.
	
	Input: Position of square to be uncovered (coordinates stored into 2 parallel arrays)
		line selection, name (if high score achieved)

	Processing: 
		1. Prompt user to enter coordinates of table to uncover
			Input validated to prevent user from entering invalid coordinates
			or the already-uncovered number.
		2. Display table with uncovered cells and prompt user to choose a line.
		3. Based on the line chosen and sum of the line, user wins points according to payout table.
		4. If score is greater than previous score, user is prompted to enter name.

	Output: Revealed contents of table and amount of points won
*/

//Header files
#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

//Function prototypes
void showChoices();			
void Payout();				
void InitialMatrix(int[][3], int);
int	 GetNumber();
void UserChoice(int[], int[], int[][3], int);	
void UpdateMatrix(int[][3], int[], int[], int);	
void FinalChoiceDisplay();	
void GetFinalInput(char&);	
int	 LineSum(int[][3]);		
void DisplayTicket(int[][3]);	
int  PointsWon(int);		
void HighScore(int);

int main()
{
	// Blue background with green text
	system("Color 1A");

	// Declare variables
	int choice;
		
	do
	{
		showChoices();	// Display menu choices
		cin >> choice;

		switch (choice)
		{
			case 1:		// See Rules
				cout << "   RULES  " <<endl;
				cout << "-------------" << endl;
				cout << "How to Play" << endl;
				cout << "\n1. Select Three Numbers" << endl;
				cout << "\n2. Select a Line (one of eight lines vertical, horizontal, or diagonal)" <<endl;
				cout << "\n3. Receive a Reward (the sum of the line will be equivalent to the points in the pay out table)" << endl << endl << endl;
				Payout();
				cout << endl;
				break;

			case 2:		// Play Game
			{
				// Declare Variables
				int start, ticket[3][3], rowchoice[3], colchoice[3], sum, points;
				
				srand(time(NULL));

				cout << "\nCactus Pot Lottery Game ..." << endl << endl;

				// Display payout chart
				Payout();

				// Randomly generate a random starting number
				start = rand() % 9 + 1;

				// Show initial 3x3 ticket with all but 1 numbers hidden
				InitialMatrix(ticket, start);

				// Prompt user to choose 3 cells to reveal
				UserChoice(rowchoice, colchoice, ticket, start);

				// Redisplay the table with 3 more numbers revealed
				UpdateMatrix(ticket, rowchoice, colchoice, start);

				cout << endl;

				// Visual guide for user to select which line they want to reveal
				FinalChoiceDisplay();

				// Get sum of the line that the user selected
				sum = LineSum(ticket);

				// Get points based on the selected line sum and payout chart
				points = PointsWon(sum);

				// Display the ticket entirely revealed
				DisplayTicket(ticket);

				// Winning message
				cout << "\n\tThe sum of the line you chose is " << sum << endl
					<< "\tYou won " << points << " points!" << endl << endl;

				// Determine if winning score beats the high score
				HighScore(points);

				break;
			}
			case 3:		// See Highest Score
			{
				ifstream inFile;
				string name;
				int hiscore;

				inFile.open("highscore.txt");

				if (inFile)
				{
					getline(inFile, name);
					inFile >> hiscore;

					cout << "\nHigh Score: \n" << name << " " << hiscore << endl;
				}
				else
					cout << "No high scores yet!" << endl;

				inFile.close();

				break;
			}
			case 4:		// Exit
				cout << "Thanks for playing!" << endl;
				break;
			default:	// Invalid number selected
				cout << "Invalid input" << endl;
		}

		cout << endl;

	} while (choice != 4);

	return 0;
}

/*
	void showChoices()
	Displays menu options
	Return value: none
*/
void showChoices()
{
	cout << "-------------------------" << endl;
	cout << "   CACTPOT LOTTERY GAME "<< endl;
	cout << "-------------------------" << endl;
	cout << "          MENU "<< endl << endl;
	cout << "1:  See Rules " << endl;
	cout << "2:  Play Game " << endl;
	cout << "3:  See Highest Score " << endl;
	cout << "4:  Exit  " << endl;
	cout << "-------------------------" << endl;
	cout << "Enter your choice: ";

	return;
}

/*
	void Payout()
	Displays a table with payout for each sum of numbers
	Return value: none
*/
void Payout()
{
	cout << "-----------------------------------------------" << endl
		<< "               P  A  Y  O  U  T                " << endl
		<< "-----------------------------------------------" << endl
		<< left << setw(4) << "Sum" << setw(20) << "Gold Point Rewards"
		<< left << setw(4) << "Sum" << setw(20) << "Gold Point Rewards" << endl
		<< left << setw(4) << "6 " << setw(20) << "     10,000       "
		<< left << setw(4) << "16" << setw(20) << "        72        " << endl
		<< left << setw(4) << "7 " << setw(20) << "        36        "
		<< left << setw(4) << "17" << setw(20) << "       180        " << endl
		<< left << setw(4) << "8 " << setw(20) << "       720        "
		<< left << setw(4) << "18" << setw(20) << "       119        " << endl
		<< left << setw(4) << "9 " << setw(20) << "       360        "
		<< left << setw(4) << "19" << setw(20) << "        36        " << endl
		<< left << setw(4) << "10" << setw(20) << "        80        "
		<< left << setw(4) << "20" << setw(20) << "       306        " << endl
		<< left << setw(4) << "11" << setw(20) << "       252        "
		<< left << setw(4) << "21" << setw(20) << "      1,080       " << endl
		<< left << setw(4) << "12" << setw(20) << "       108        "
		<< left << setw(4) << "22" << setw(20) << "       144        " << endl
		<< left << setw(4) << "13" << setw(20) << "        72        "
		<< left << setw(4) << "23" << setw(20) << "      1,800       " << endl
		<< left << setw(4) << "14" << setw(20) << "        54        "
		<< left << setw(4) << "24" << setw(20) << "      3,600       " << endl
		<< left << setw(4) << "15" << setw(20) << "       180        " << endl
		<< "-----------------------------------------------" << endl << endl;
	
	return;
}

/*
	void InitialMatrix(int ticket[][3], int start)
	Sets up and displays a matrix of 3x3 with random numbers
	Return value: none
*/
void InitialMatrix(int ticket[][3], int start)
{
	//bool reset = false;
	
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
		{
			// Generate random non-repeating number for each element of the array
			ticket[row][col] = GetNumber();

			// 
			if (ticket[row][col] == start)
				cout << ticket[row][col] << " ";
			else
				cout << "X ";

			if (col == 2)
				cout << endl;
		}

	return;
}

/*
	int GetNumber()
	Generate a random number
	Return value: number + 1
*/
int GetNumber()
{
	static bool assigned[] = { false, false, false, false, false, false, false, false, false };
	int number;

	if (assigned[0] == true && assigned[1] == true && assigned[2] == true &&
		assigned[3] == true && assigned[4] == true && assigned[5] == true &&
		assigned[6] == true && assigned[7] == true && assigned[8] == true)
	{
		for (int i = 0; i < 9; i++)
			assigned[i] = false;
	}
	
	do
	{
		number = rand() % 9;
	} while (assigned[number]);

	assigned[number] = true;

	

	return number + 1;
}

/*
	void UserChoice(int row[], int col[], int ticket[][3], int start)
	Prompt user for matrix positions to uncover and return
	values through parallel arrays.
	Return value: none
*/
void UserChoice(int row[], int col[], int ticket[][3], int start)
{
	int a, b;

	for (int i = 0; i < 3; i++)
	{
		do
		{
			cout << "\tSelect a position to reveal number (row, col): ";
			cin >> a >> b;

			a--;
			b--;

			if (a < 0 || a > 2 || b < 0 || b > 2)
				cout << "\tError ... Try numbers between 1 and 3." << endl;
			else if (ticket[a][b] == start)
				cout << "\tThis cell has already been uncovered, don't waste a turn!" << endl;

		} while (a < 0 || a > 2 || b < 0 || b > 2 || ticket[a][b] == start);

		// Match visual equivalent of user's input to corresponding array subscripts
		
		row[i] = a;
		col[i] = b;
	}

	return;
}

/*
	void UpdateMatrix(int ticket[][3], int row[], int col[], int start)
	Displays ticket with the starting number and three positions uncovered by user.
	Return value: none
*/

void UpdateMatrix(int ticket[][3], int row[], int col[], int start)
{
	int assigned[3][3] = { 0 };

	for (int i = 0; i < 3; i++)
		assigned[row[i]][col[i]] = 1;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
		{
			if (ticket[i][j] == start)
				assigned[i][j] = 1;

		}
	}


	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			if (assigned[i][j] == 1)
				cout << ticket[i][j] << " ";
			else
				cout << "X ";

			if (j == 2)
				cout << endl;
		}

	return;
}

/*
	void FinalChoiceDisplay()
	Displays line options to be selected based on the corresponding letters
	Return value: none
*/
void FinalChoiceDisplay()
{
	char rowcolDisplay[3][23] = { { 'A', 'A', 'A', ' ', '-', '-', '-', ' ' , '-', '-', '-', ' ', 'D', '-', '-', ' ', '-', 'E', '-', ' ' , '-', '-', 'F' },
								  { '-', '-', '-', ' ', 'B', 'B', 'B', ' ' , '-', '-', '-', ' ', 'D', '-', '-', ' ', '-', 'E', '-', ' ' , '-', '-', 'F' },
								  { '-', '-', '-', ' ', '-', '-', '-', ' ' , 'C', 'C', 'C', ' ', 'D', '-', '-', ' ', '-', 'E', '-', ' ' , '-', '-', 'F' }, };

	char diagDisplay[3][7] = { { 'G', '-', '-', ' ', '-', '-', 'H' },
							   { '-', 'G', '-', ' ', '-', 'H', '-' },
							   { '-', '-', 'G', ' ', 'H', '-', '-' } };

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 23; j++)
		{
			cout << rowcolDisplay[i][j] << " ";

			if (j == 22)
				cout << endl;
		}
	
	cout << endl;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 7; j++)
		{
			cout << diagDisplay[i][j] << " ";

			if (j == 6)
				cout << endl;
		}

	return;
}

/*
	void GetFinalInput(char& choice)
	Prompt user for a letter choice and return via reference variable
	Return value: none
*/
void GetFinalInput(char& choice)
{
	do
	{
		cout << "\nSelect a corresponding letter from above to reveal line: ";
		cin >> choice;

		if (choice < 'A' || choice > 'H')
			cout << "Invalid choice ... Letter must be capital between A and H." << endl;

	} while (choice < 'A' || choice > 'H');

	return;
}

/*
	int lineSum(int ticket[][3])
	Finds sum of line that user selected
	Return value: sum
*/
int LineSum(int ticket[][3])
{
	char c;			//User's choice
	int sum = 0;	//Sum initialized to 0

	GetFinalInput(c);

	switch (c)
	{
		case 'A':	// Sum of row 1
			for (int i = 0; i < 3; i++)
				sum += ticket[0][i];
			break;
		case 'B':	// Sum of row 2
			for (int i = 0; i < 3; i++)
				sum += ticket[1][i];
			break;
		case 'C':	// Sum of row 3
			for (int i = 0; i < 3; i++)
				sum += ticket[2][i];
			break;
		case 'D':	// Sum of column 1
			for (int i = 0; i < 3; i++)
				sum += ticket[i][0];
			break;
		case 'E':	// Sum of column 2
			for (int i = 0; i < 3; i++)
				sum += ticket[i][1];
			break;
		case 'F':	// Sum of column 3
			for (int i = 0; i < 3; i++)
				sum += ticket[i][2];
			break;
		case 'G':	// Sum of diagonal 1,1 + 2,2 + 3,3
			for (int i = 0; i < 3; i++)
				sum += ticket[i][i];
			break;
		case 'H':	// Sum of diagonal 3,1 + 2,2 + 1,3
			sum = ticket[2][0] + ticket[1][1] + ticket[0][2];
			break;
	}

	return sum;
}

/*
	int pointsWon(int sum)
	Determines and returns amount of points won based on the
	payout table displayed by payout()
	Return value: points
*/
int PointsWon(int sum)
{
	int points;

	switch (sum)
	{
		case 6:
			points = 10000;
			break;
		case 7:
			points = 36;
			break;
		case 8:
			points = 720;
			break;
		case 9:
			points = 360;
			break;
		case 10:
			points = 80;
			break;
		case 11:
			points = 252;
			break;
		case 12:
			points = 108;
			break;
		case 13:
			points = 72;
			break;
		case 14:
			points = 54;
			break;
		case 15:
			points = 180;
			break;
		case 16:
			points = 72;
			break;
		case 17:
			points = 180;
			break;
		case 18:
			points = 119;
			break;
		case 19:
			points = 36;
			break;
		case 20:
			points = 306;
			break;
		case 21:
			points = 1080;
			break;
		case 22:
			points = 144;
			break;
		case 23:
			points = 1800;
			break;
		case 24:
			points = 3600;
			break;
	}

	return points;
}

/*
	void DisplayTicket(int ticket[][3])
	Displays the entire matrix uncovered
	Return value: none
*/
void DisplayTicket(int ticket[][3])
{
	cout << endl;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			cout << ticket[i][j] << " ";

			if (j == 2)
				cout << endl;
		}

	return;
}

/*
	void HighScore(int score)
	Determine if points won is greater than previous score in "highscore.txt"
	and overwrite new score if so.
	Return value: none
*/
void HighScore(int score)
{
	int prevscore;
	ifstream inFile;
	ofstream outFile;
	string name;
	
	inFile.open("highscore.txt");

	if (inFile)
	{
		getline(inFile, name);
		inFile >> prevscore;
	}
	else
		prevscore = 0;
	
	inFile.close();

	outFile.open("highscore.txt");

	if (outFile)
	{
		if (score >= prevscore)
		{
			cout << "*******************************************" << endl;
			cout << "New high score!! Enter your name: ";
			cin.ignore();
			getline(cin, name);
			cout << "*******************************************" << endl;
			outFile << name << endl << score;
		}
		else
			outFile << name << endl << prevscore;
	}
	else
		cout << "Error ... could not open file." << endl;

	outFile.close();

	return;
}
