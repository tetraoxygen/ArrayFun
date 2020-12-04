/*
	I used vectors instead of dataays because I wanted it to be dead simple to implement any length you'd like, or hell, even let the user pick it. I could have done this without the vectors fairly easily (arguably would have been easier, as I already knew how to use arrays), so I wanted to explain my rationale for using them. 
*/


#include <iostream>
#include <vector>


void getData(std::vector<int> &data, int length);

void printData(std::vector<int> data);

int lowestValue(std::vector<int> &data);

int highestValue(std::vector<int> &data);

int countOdds(std::vector<int> data);

int sum(std::vector<int> data);

std::vector<int> getDuplicateValues(std::vector<int> data);

void sort(std::vector<int> &data);

void quickSort(std::vector<int>&, int, int);

int partition(std::vector<int>&, int, int);


// slight optimization to not have to run quickSort() again if it's already been run
bool SORTED = false;
int main()
{
	std::vector<int> userInput;
	
	std::cout << "Enter 10 integers (separated by a space): ";
	getData(userInput, 10);
	std::cout << std::endl << "\tYou entered: ";
	printData(userInput);
	std::cout << std::endl << std::endl;
	std::cout << "\tLowest value:\t" << lowestValue(userInput) << std::endl;
	std::cout << "\tHighest value:\t" << highestValue(userInput) << std::endl;
	std::cout << "\t# odd numbers:\t" << countOdds(userInput) << std::endl;
	std::cout << "\tSum of all:\t" << sum(userInput) << std::endl;
	std::cout << "\tThe following numbers appear multiple times: ";
	std::vector<int> duplicates = getDuplicateValues(userInput);
	for (int i = 0; i < duplicates.size(); i++) {
		std::cout << duplicates[i] << " ";
	}
	std::cout << std::endl;
}


/*
	Function: 					getData()
	Description: 				Gets any number of user data from the user, and appends them to the end of an array.
	Arguments:
		data (vector<int>&): 	vector to insert user input into
		length (int):			number of ints to accept from the user
*/
void getData(std::vector<int> &data, int length) {
	int input = 0;
	for (int i = 0; i < length; i++) {
		std::cin >> input;
		data.push_back(input);
	}
}

/*
	Function: 					printData()
	Description: 				prints a vector's values with spaces between them
	Arguments:
		data (vector<int>&): 	vector to print, space delimited
*/
void printData(std::vector<int> data) {
	for (int i = 0; i < data.size(); i++) {
		std::cout << data[i] << " ";
	}
}

/*
	Function: 					lowestValue()
	Description: 				finds the lowest value in a vector
	Arguments:
		data (vector<int>&): 	vector to find lowest value of
	Return value:
		lowest value in data
*/
// passed by reference as an optimization
int lowestValue(std::vector<int> &data) {
	sort(data);
	return data.front();
}

/*
	Function: 					highestValue()
	Description: 				finds the highest value in a vector
	Arguments:
		data (vector<int>&): 	vector to find highest value of
	Return value:
		highest value in data
*/
// passed by reference as an optimization
int highestValue(std::vector<int> &data) {
	sort(data);
	return data.back();
}

/*
	Function: 					countOdds()
	Description: 				Counts the number of odd numbers in a vector
	Arguments:
		data (vector<int>&): 	vector to find number of odd values in
	Return value:
		number of odd numbers in data
*/
int countOdds(std::vector<int> data) {
	int odds = 0; 
	for (int i = 0; i < data.size(); i++) {
		if (data[i] % 2 != 0) {
			odds++;
		}
	}
	return odds;
}


/*
	Function: 					sum()
	Description: 				Counts the number of odd numbers in a vector
	Arguments:
		data (vector<int>&): 	vector to sum values of
	Return value:
		sum of all values in data
*/
int sum(std::vector<int> data) {
	int result = 0;
	for (int i = 0; i < data.size(); i++) {
		result += data[i];
	}
	return result;
}


/*
	Function: 					getDuplicateValues()
	Description: 				Finds all values that appear more than once
	Arguments:
		data (vector<int>&): 	vector to find duplicates in
	Return value:
		Vector of all ints that were duplicated in data
*/
std::vector<int> getDuplicateValues(std::vector<int> data) {
	sort(data);
	
	int previousValue = 0;
	std::vector<int> duplicates;
	
	for (int i = 0; i < data.size(); i++) {
		// if data is the previous value, i is not 0 (you can't have a duplicate on the first go around, and if the first value is zero, something would go wrong here) and duplicates either has nothing in it, or the most recent duplicate (having the list be sorted helps a lot here) is not the value I would be inserting
		if (data[i] == previousValue && i > 0 && (duplicates.size() == 0 || data[i] != duplicates.back())) {
			duplicates.push_back(data[i]);
		}
		previousValue = data[i];
	}
	
	return duplicates;
}

// MARK: Sorting 

/*
	Function: 					sort()
	Description: 				Helper function that checks if the vector has already been sorted, and if so, doesn't sort it again. Also automatically fills in the correct bounds for quickSort().
	Arguments:
		data (vector<int>&): 	vector to sort
*/
void sort(std::vector<int> &data) {
	// just wastes resources to sort the vector again, so let's not
	if (!SORTED) {
		quickSort(data, 0, data.size() - 1);
	}
	SORTED = true;
}


/*
	Function: 					quickSort()
	Description: 				Sorts a vector in place using QuickSort.
	Arguments:
		values (vector<int>&):	vector to sort
		left (int): 			left bounding of the vector
		right (int): 			right bounding of the vector
	*/
// Sorts a list
void quickSort(std::vector<int> &values, int left, int right) {
	if(left < right) {
		int pivotIndex = partition(values, left, right);
		quickSort(values, left, pivotIndex - 1);
		quickSort(values, pivotIndex, right);
	}
}

/*
	Function: 				partition()
	Description: 			Swaps all elements smaller than the pivot to the left of the pivot
	values (vector<int>&):	vector to sort
	left (int): 			left bounding of the partition
	right (int): 			right bounding of the partition
*/
int partition(std::vector<int> &values, int left, int right) {
	int pivotIndex = left + (right - left) / 2;
	int pivotValue = values[pivotIndex];
	int i = left, j = right;
	int temp;
	while(i <= j) {
		while(values[i] < pivotValue) {
			i++;
		}
		while(values[j] > pivotValue) {
			j--;
		}
		if(i <= j) {
			temp = values[i];
			values[i] = values[j];
			values[j] = temp;
			i++;
			j--;
		}
	}
	return i;
}