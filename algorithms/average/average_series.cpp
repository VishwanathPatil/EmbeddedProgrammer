#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

int main() {
	std::ifstream file("input/series.txt");
	if (!file.is_open()) {
		std::cerr << "Error: Unable to open file!" << std::endl;
		return 1;
	}

	double sum = 0.0;
	int count = 0;
	double number;
	double running_average = 0;
	double running_average_simplest_form = 0;
	/* average is of current window not added */
	double simpleWindowMovingAverage = 0;
	double exponential_average = 0;
	// Alpha value for exponential average choosen based on importance of latest
	// value influence (more influence from new value more is alpha value)
	double exponential_average_alpha = 0.5;
	int n = 0;
	double summinor = 0;
	// Skip header line
	std::string header;
	std::getline(file, header);

	while (file >> number) { // Read each float number from the fil
		++count;
		sum += number;
		// How much influence each new value makes
		running_average -= running_average/count;
		// Influence current number is making on average
		running_average += number/count;
		if(count > 1) {
			running_average_simplest_form = (running_average_simplest_form * (count-1) + number) / count;
			exponential_average = number * exponential_average_alpha + exponential_average * (1-exponential_average_alpha);
		}
		else {
			exponential_average = running_average_simplest_form = number;
		}
		summinor += running_average_simplest_form - running_average;
	}

	file.close();

	if (count == 0) {
		std::cout << "No numbers found in the file." << std::endl;
	} else {
		double average = sum / count;
		std::cout << std::fixed << std::setprecision(20);
		std::cout << "Average: " << average << ", running average: " << running_average << ", running avg simplest:" << running_average_simplest_form << ", exponential average:" << exponential_average << std::endl;
		std::cout << "SumMinor: " << summinor << ", element count:" << count;
	}

	return 0;
}
