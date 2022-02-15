#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <stdexcept>
using namespace std;
static int QCount = 0;
static int MCount = 0;

//insertion sort, takes in an array of size n
vector<int> insertionSort(vector<int> &power)
{
	int count = 0;
	for (size_t j = 1; j < power.size(); j++)
	{
		count++;
		int key = power[j];
		int i = j - 1;
		//move elements [0...i-1], that are greater than key, to one position ahead of its current position
		while (i >= 0 && power[i] > key)
		{
			count++;
			power[i + 1] = power[i];
			i--;
			
		}
		power[i + 1] = key;
	}
	//return the array
	cout << count << endl;
	return power;
	
}


//partition for quick sort, takes vector, start=p, end=r
int partition(vector<int>& power, int p, int r)
{
	//pivot is at the end
	int x = power[r];
	//this is the start
	int i = (p-1);
	//small array: A[p...i]
	//large array: A[i...j]
	for (int j = p; j <= r-1; j++)
	{
		if (power[j] <= x)
		{
			QCount++;
			i++;
			swap(power[i], power[j]);
			

		}
	}
	//put pivot at the end of small array
	swap(power[i + 1], power[r]);
	return i + 1;
}

//quicksort function takes vector, start and end
void quickSort(vector<int>& power, int p, int r)
{
	int count = 0;
	//base case
	if (p < r)
	{
		//create partition
		int q = partition(power, p, r);
		//recursive calls
		quickSort(power, p, q - 1);
		quickSort(power, q + 1 , r);
		
	}
}
//merges two subarrays of A.
//first sub array is beginning to middle
//second sub array is middle+1 to end
vector<int> merge(vector<int> left, vector<int> right) {
	size_t ileft = 0, iright = 0;
	vector<int> results;
	while (ileft < left.size() && iright < right.size())
	{
		if (left[ileft] < right[iright])
			results.push_back(left[ileft++]);
		else
			results.push_back(right[iright++]);
	}
	while (ileft < left.size())
		results.push_back(left[ileft++]);
	while (iright < right.size())
		results.push_back(right[iright++]);
	return results;
}

vector<int> mergeSort(vector<int>& power)
{
	MCount++;
	if (power.size() <= 1)
		return power;
	int len = power.size() / 2;
	vector<int> left(power.begin(), power.begin() + len);
	vector<int> right(power.begin() + len, power.end());
	return merge(mergeSort(left), mergeSort(right));
}

//reads file
vector<int> readFile(string fileName)
{
	//initialize vector 
	vector<int> power;
	//this will take the file name given to the program and then it will use that, to allow variability;
	ifstream file(fileName);
	string line;
	//check if file is open
	if (!file.is_open()) throw runtime_error("could not open file");
	//create count
	int count = 0;
	//while the file hasnt been read through
	while (getline(file, line))
	{
		//count must be greater than 0
		if (count > 0)
		{
			//for some reason this one needed the std::?
			//put the line into vector of strings
			std::stringstream s_stream(line);
			vector<string> result;
			//while still in s_stream
			while (s_stream.good())
			{
				//create substring and push back the second column
				string substr;
				getline(s_stream, substr, ',');
				result.push_back(substr);
			}
			//push the result vector of strings into the power vector of ints using stoi
			power.push_back(stoi(result[1]));
		}
		//count>0;
		count++;
	}
	//return vector of ints
	return power;
}

//prints main query to ask which sorting algorithm to use
void printMain() {
	cout << "you can call me doctor sort, the sorter supreme\n";
	cout << "I will sort for you whatever you may need!\n";
	cout << "choose from the list below to use whichever sorting algorithm you want!\n";
	cout << "if you would like to quit at any time, when prompted press 'E'\n";
	cout << "\n";
	cout << "+---------------------------------------------------+\n";
	cout << "|  I: Insertion sort  Q: quick sort  M: merge sort  |\n";
	cout << "+---------------------------------------------------+\n";
}

//retrieves user Input
char getOption(string validOptions) 
{
	//create variables
	string userChoice;
	char choice;
	int indexer;
	do {
		cout << "Enter option: ";
		if (cin.peek() == '\n')cin.ignore();
		getline(cin, userChoice);

		choice = toupper(userChoice[0]);

		indexer = validOptions.find(choice);
		if (indexer == -1) {
			cout << "Invalid Option, choose one of the valid responses Please" << endl;
		}

	} while (indexer == -1);

	return choice;

}


//prints out query to get size of array to sort
void printPokeSize() {
	cout << "Now choose the amount of pokemon you want to sort!\n";
	cout << "+---------------------------------------------------+\n";
	cout << "|A. small             B. Medium            C. Large |\n";
	cout << "|D. RSmall            f. Rmed              g. Rlarge|\n";
	cout << "|h. SSmall            i. Smed              j. SLarge|\n";
	cout << "+---------------------------------------------------+\n";

}

//print vector
void printVector(vector<int> power)
{
	cout << "***********************************************************************************************************************" << endl;
	for (vector<int>::iterator i = power.begin(); i != power.end(); i++)
		cout<<setw(5) << *i << ' ';
	cout << endl;
	cout << "***********************************************************************************************************************" << endl;
}

int main() {
	//initialize variables
	char userInput=' ';
	char sizeInput=' ';
	//initialize vector power
	vector<int> power;
	//create strings with the paths to the files
	string small = "C:\\Users\\Thebl\\source\\repos\\cs315 project1\\Debug\\pokemonRandomSmall.csv";
	string medium = "C:\\Users\\Thebl\\source\\repos\\cs315 project1\\Debug\\pokemonRandomMedium.csv";
	string Large = "C:\\Users\\Thebl\\source\\repos\\cs315 project1\\Debug\\pokemonRandomLarge.csv";
	string rSmall = "C:\\Users\\Thebl\\source\\repos\\cs315 project1\\Debug\\pokemonReverseSortedSmall.csv";
	string rMed = "C:\\Users\\Thebl\\source\\repos\\cs315 project1\\Debug\\pokemonReverseSortedMedium.csv";
	string rlarge = "C:\\Users\\Thebl\\source\\repos\\cs315 project1\\Debug\\pokemonReverseSortedLarge.csv";
	string SSmall = "C:\\Users\\Thebl\\source\\repos\\cs315 project1\\Debug\\pokemonSortedSmall.csv";
	string SMed = "C:\\Users\\Thebl\\source\\repos\\cs315 project1\\Debug\\pokemonSortedMedium.csv";
	string SLarge = "C:\\Users\\Thebl\\source\\repos\\cs315 project1\\Debug\\pokemonSortedLarge.csv";
	//validation strings for getOption
	string sortingOptions = "IiQqMmEe";
	string sizeOptions = "AaBbCcEeDdFfGgHhIiJj";
	//while loop to check for exit
	do {
		printMain();
		userInput = getOption(sortingOptions);

		//if the user wants to insertion sort, will use this, it pretty much repeats for 9 times depending on the file, same code for the different sorts too, just a template. 
		if (userInput == 'I' || userInput == 'i')
		{
			//prints query for size of array
			printPokeSize();
			//retrieves user input
			sizeInput = getOption(sizeOptions);
			//compare them
			if (sizeInput == 'A' || sizeInput == 'a')
			{
				//sorts the set, prints vector before and after sorting. 
				cout << "I will now sort the small set of pokemon using Inserstion sort!\n";
				power = readFile(small);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				power = insertionSort(power);
				cout << "this is the array after sorting" << endl;
				printVector(power);
			
			}
			if (sizeInput == 'B' || sizeInput == 'b')
			{
				cout << "I will now sort the medium set of pokemon using insertion sort!\n";
				power = readFile(medium);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				power = insertionSort(power);
				cout << "this is the array after sorting" << endl;
				printVector(power);
			
			}
			if (sizeInput == 'C' || sizeInput == 'c')
			{
				cout << "I will now sort the large set of pokemon using inserstion sort!\n";
				power = readFile(Large);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				power = insertionSort(power);
				cout << "this is the array after sorting" << endl;
				printVector(power);
				
			}
			if (sizeInput == 'D' || sizeInput == 'd')
			{
				cout << "I will now sort the resverse sorted small set of pokemon using Inserstion sort!\n";
				power = readFile(rSmall);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				power = insertionSort(power);
				cout << "this is the array after sorting" << endl;
				printVector(power);

			}
			if (sizeInput == 'F' || sizeInput == 'f')
			{
				cout << "I will now sort the reverse sorted medium set of pokemon using Inserstion sort!\n";
				power = readFile(rMed);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				power = insertionSort(power);
				cout << "this is the array after sorting" << endl;
				printVector(power);

			}
			if (sizeInput == 'G' || sizeInput == 'g')
			{
				cout << "I will now sort the reverse sorted Large set of pokemon using Inserstion sort!\n";
				power = readFile(rlarge);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				power = insertionSort(power);
				cout << "this is the array after sorting" << endl;
				printVector(power);

			}
			if (sizeInput == 'H' || sizeInput == 'h')
			{
				cout << "I will now sort the sorted small set of pokemon using Inserstion sort!\n";
				power = readFile(SSmall);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				power = insertionSort(power);
				cout << "this is the array after sorting" << endl;
				printVector(power);

			}
			if (sizeInput == 'I' || sizeInput == 'i')
			{
				cout << "I will now sort the sorted medium set of pokemon using Inserstion sort!\n";
				power = readFile(SMed);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				power = insertionSort(power);
				cout << "this is the array after sorting" << endl;
				printVector(power);

			}
			if (sizeInput == 'J' || sizeInput == 'j')
			{
				cout << "I will now sort the small set of pokemon using Inserstion sort!\n";
				power = readFile(SLarge);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				power = insertionSort(power);
				cout << "this is the array after sorting" << endl;
				printVector(power);

			}
		}
		//wants to quick sort will use this
		else if (userInput == 'Q' || userInput == 'q')
		{
			printPokeSize();
			sizeInput = getOption(sizeOptions);
			if (sizeInput == 'A' || sizeInput == 'a')
			{
				cout << "I will now sort the small set of pokemon using quick sort!\n";
				power = readFile(small);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				quickSort(power, 0, power.size()-1);
				cout << "this is the array after sorting" << endl;
				printVector(power);
				cout << QCount << endl;
				QCount = 0;
		
			}
			if (sizeInput == 'B' || sizeInput == 'b')
			{
				cout << "I will now sort the medium set of pokemon using quick sort!\n";
				power = readFile(medium);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				quickSort(power, 0, power.size()-1);
				cout << "this is the array after sorting" << endl;
				printVector(power);
				cout << QCount << endl;
				QCount = 0;
			}
			if (sizeInput == 'C' || sizeInput == 'c')
			{
				cout << "I will now sort the large set of pokemon using quick sort!\n";
				power = readFile(Large);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				quickSort(power, 0, power.size()-1);
				cout << "this is the array after sorting" << endl;
				printVector(power);
				cout << QCount << endl;
				QCount = 0;
				
			}
			if (sizeInput == 'D' || sizeInput == 'd')
			{
				cout << "I will now sort the resverse sorted small set of pokemon using quick sort!\n";
				power = readFile(rSmall);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				quickSort(power, 0, power.size() - 1);
				cout << "this is the array after sorting" << endl;
				printVector(power);
				cout << QCount << endl;
				QCount = 0;

			}
			if (sizeInput == 'F' || sizeInput == 'f')
			{
				cout << "I will now sort the reverse sorted medium set of pokemon using quick sort!\n";
				power = readFile(rMed);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				quickSort(power, 0, power.size() - 1);
				cout << "this is the array after sorting" << endl;
				printVector(power);
				cout << QCount << endl;
				QCount = 0;

			}
			if (sizeInput == 'G' || sizeInput == 'g')
			{
				cout << "I will now sort the reverse sorted Large set of pokemon using quick sort!\n";
				power = readFile(rlarge);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				quickSort(power, 0, power.size() - 1);
				cout << "this is the array after sorting" << endl;
				printVector(power);
				cout << QCount << endl;
				QCount = 0;

			}
			if (sizeInput == 'H' || sizeInput == 'h')
			{
				cout << "I will now sort the sorted small set of pokemon using quick sort!\n";
				power = readFile(SSmall);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				quickSort(power, 0, power.size() - 1);
				cout << "this is the array after sorting" << endl;
				printVector(power);
				cout << QCount << endl;
				QCount = 0;
			}
			if (sizeInput == 'I' || sizeInput == 'i')
			{
				cout << "I will now sort the sorted medium set of pokemon using quick sort!\n";
				power = readFile(SMed);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				quickSort(power, 0, power.size() - 1);
				cout << "this is the array after sorting" << endl;
				printVector(power);
				cout << QCount << endl;
				QCount = 0;
			}
			if (sizeInput == 'J' || sizeInput == 'j')
			{
				cout << "I will now sort the small set of pokemon using quick sort!\n";
				power = readFile(SLarge);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				quickSort(power, 0, power.size() - 1);
				cout << "this is the array after sorting" << endl;
				printVector(power);
				cout << QCount << endl;
				QCount = 0;
			}
		
		}
		//wants to merge sort will do this
		else if (userInput == 'M' || userInput == 'm')
		{
			printPokeSize();
			sizeInput = getOption(sizeOptions);
			if (sizeInput == 'A' || sizeInput == 'a')
			{
				cout << "I will now sort the small set of pokemon using Merge sort!\n";
				power = readFile(small);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				power=mergeSort(power);
				cout << "this is the array after sorting" << endl;
				printVector(power);
				cout << MCount << endl;
				MCount = 0;
			
			}
			if (sizeInput == 'B' || sizeInput == 'b')
			{
				cout << "I will now sort the medium set of pokemon using Merge sort!\n";
				power = readFile(medium);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				power=mergeSort(power);
				cout << "this is the array after sorting" << endl;
				printVector(power);
				cout << MCount << endl;
				MCount = 0;
			}
			if (sizeInput == 'C' || sizeInput == 'c')
			{
				cout << "I will now sort the large set of pokemon using Merge sort!\n";
				power = readFile(Large);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				power=mergeSort(power);
				cout << "this is the array after sorting" << endl;
				printVector(power);
				cout << MCount << endl;
				MCount = 0;
			}
			if (sizeInput == 'D' || sizeInput == 'd')
			{
				cout << "I will now sort the resverse sorted small set of pokemon using Merge sort!\n";
				power = readFile(rSmall);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				power = mergeSort(power);
				cout << "this is the array after sorting" << endl;
				printVector(power);
				cout << MCount << endl;
				MCount = 0;
			}
			if (sizeInput == 'F' || sizeInput == 'f')
			{
				cout << "I will now sort the resverse sorted medium set of pokemon using Merge sort!\n";
				power = readFile(rMed);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				power = mergeSort(power);
				cout << "this is the array after sorting" << endl;
				printVector(power);
				cout << MCount << endl;
				MCount = 0;
			}
			if (sizeInput == 'G' || sizeInput == 'g')
			{
				cout << "I will now sort the reverse sorted Large set of pokemon using merge sort!\n";
				power = readFile(rlarge);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				power = mergeSort(power);
				cout << "this is the array after sorting" << endl;
				printVector(power);
				cout << MCount << endl;
				MCount = 0;
			}
			if (sizeInput == 'H' || sizeInput == 'h')
			{
				cout << "I will now sort the sorted small set of pokemon using merge sort!\n";
				power = readFile(SSmall);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				power = mergeSort(power);
				cout << "this is the array after sorting" << endl;
				printVector(power);
				cout << MCount << endl;
				MCount = 0;
			}
			if (sizeInput == 'I' || sizeInput == 'i')
			{
				cout << "I will now sort the sorted medium set of pokemon using merge sort!\n";
				power = readFile(SMed);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				power = mergeSort(power);
				cout << "this is the array after sorting" << endl;
				printVector(power);
				cout << MCount << endl;
				MCount = 0;
			}
			if (sizeInput == 'J' || sizeInput == 'j')
			{
				cout << "I will now sort the small set of pokemon using merge sort!\n";
				power = readFile(SLarge);
				cout << "this is the array before sorting" << endl;
				printVector(power);
				power = mergeSort(power);
				cout << "this is the array after sorting" << endl;
				printVector(power);
				cout << MCount << endl;
				MCount = 0;
			}
			

		}
		cout << "***********************************************************************************************************************" << endl;
	} while ((userInput != 'e' && userInput != 'E') && (sizeInput != 'e' && sizeInput != 'E'));
	//print the last array sorted
	cout << "thank you for using pokeSorter!\n";
	cout << "this is the last array you sorted!\n";
	printVector(power);
	
	
	
	system("pause");
	return 0;
	
}
