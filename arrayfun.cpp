/*
	I used vectors instead of dataays because I wanted it to be dead simple to implement any length you'd like, or hell, even let the user pick it. I could have done this without the vectors fairly easily (arguably would have been easier, as I already knew how to use arrays), so I wanted to explain my rationale for using them. 
*/


#include <iostream>
#include <vector>


void getData(std::vector<int> &data);

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
	std::vector<int> userInput(10);
	
	std::cout << "Enter 10 integers (separated by a space): ";
	getData(userInput);
	std::cout << std::endl << "You entered: ";
	printData(userInput);
	std::cout << std::endl << std::endl;
	std::cout << "Lowest value:\t" << lowestValue(userInput) << std::endl;
	std::cout << "Highest value:\t" << highestValue(userInput) << std::endl;
	std::cout << "# odd numbers:\t" << countOdds(userInput) << std::endl;
	std::cout << "Sum of all:\t" << sum(userInput) << std::endl;
	std::cout << "The following numbers appear multiple times: ";
	std::vector<int> duplicates = getDuplicateValues(userInput);
	for (int i = 0; i < duplicates.size(); i++) {
		std::cout << duplicates[i] << " ";
	}
	std::cout << std::endl;
}

void getData(std::vector<int> &data) {
	for (int i = 0; i < data.size(); i++) {
		std::cin >> data[i];
	}
}

void printData(std::vector<int> data) {
	for (int i = 0; i < data.size(); i++) {
		std::cout << data[i] << " ";
	}
}


// passed by reference as an optimization
int lowestValue(std::vector<int> &data) {
	sort(data);
	return data.front();
}

// passed by reference as an optimization
int highestValue(std::vector<int> &data) {
	sort(data);
	return data.back();
}

int countOdds(std::vector<int> data) {
	int odds = 0; 
	for (int i = 0; i < data.size(); i++) {
		if (data[i] % 2 != 0) {
			odds++;
		}
	}
	return odds;
}

int sum(std::vector<int> data) {
	int result = 0;
	for (int i = 0; i < data.size(); i++) {
		result += data[i];
	}
	return result;
}


/*
	Function: 					getDuplicateValues()
	Description: 				
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
		if (data[i] == previousValue && i > 0) {
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