/*
	I used vectors instead of dataays because I wanted it to be dead simple to implement any length you'd like, or hell, even let the user pick it. I could have done this without the vectors fairly easily, so I wanted to explain my rationale for using them. 
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

void quickSort(std::vector<int>&,int,int);

int partition(std::vector<int>&, int,int);


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
	// just wastes resources to sort the vector again, so let's not
	if (!SORTED) {
		quickSort(data, 0, data.size());
	}
	SORTED = true;
	return data.front();
}

// passed by reference as an optimization
int highestValue(std::vector<int> &data) {
	// just wastes resources to sort the vector again, so let's not
	if (!SORTED) {
		quickSort(data, 0, data.size());
	}
	SORTED = true;
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

std::vector<int> getDuplicateValues(std::vector<int> data) {
	// just wastes resources to sort the vector again, so let's not
	if (!SORTED) {
		quickSort(data, 0, data.size());
	}
	SORTED = true;
	
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

void quickSort(std::vector<int>& A, int p,int q)
{
	int r;
	if(p < q) {
		r=partition(A, p,q);
		quickSort(A,p,r);  
		quickSort(A,r+1,q);
	}
}


int partition(std::vector<int>& A, int p,int q)
{
	int x= A[p];
	int i=p;
	int j;

	for (j=p+1; j<q; j++) {
		if(A[j]<=x){
			i=i+1;
			std::swap(A[i],A[j]);
		}
	}

	std::swap(A[i],A[p]);
	return i;
}