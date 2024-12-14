#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib> 
#include <ctime>   
#include <cmath>   
#include <string>  

using namespace std;

void generateInputFile(const string& filename) {
	ofstream outFile(filename);
	if (!outFile.is_open()) {
		cerr << "Не удалось открыть файл для записи: " << filename.c_str() << endl;
		return;
	}

	srand(static_cast<unsigned int>(time(nullptr))); 

	for (int i = 0; i < 100; ++i) {
		int randomNum = rand() % 101 - 50; 
		outFile << randomNum << endl;
	}

	outFile.close();
}

void processNumbers(const string& inputFilename, const string& outputFilename, bool previewResults) {
	ifstream inputFile(inputFilename);
	ofstream outputFile(outputFilename);

	if (!inputFile.is_open() || !outputFile.is_open()) {
		cerr << "Не удалось открыть файл." << endl;
		return;
	}

	vector<int> numbers;
	int number;
	double sum = 0;
	int count = 0;

	while (inputFile >> number) {
		numbers.push_back(number);
		sum += number;
		count++;
	}

	inputFile.close();

	if (count == 0) {
		cerr << "Файл пуст или не содержит чисел." << endl;
		return;
	}

	double average = sum / count;

	for (int num : numbers) {
		if (abs(num) % 2 != 0) { 
			double result = static_cast<double>(num) / average;
			if (previewResults) {
				cout << result << endl; 
			}
			outputFile << result << endl;
		}
		else {
			if (previewResults) {
				cout << num << endl; 
			}
			outputFile << num << endl;
		}
	}

	outputFile.close();

	if (!previewResults) {
		cout << "Обработка завершена. Результаты записаны в output.txt." << endl;
	}
}

int main() {
	setlocale(LC_ALL, "RUS");

	generateInputFile("input.txt");

	int choice;
	cout << "Желаете ли вы посмотреть значения, которые будут занесены в файл?\n";
	cout << "1. Посмотреть\n";
	cout << "2. Не смотреть\n";
	cout << "Ваш выбор: ";
	cin >> choice;

	bool previewResults = (choice == 1);

	processNumbers("input.txt", "output.txt", previewResults);

	cout << "Нажмите Enter, чтобы закрыть программу." << endl;
	cin.ignore(); 
	cin.get(); 

	return 0;
}
