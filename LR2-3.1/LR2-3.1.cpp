#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;
vector<int> numbers;


void GenerateDataset(const string& filename, const int num)
{
	std::ofstream my_file(filename);
	std::cout << "File created at: \t " << filename<< std::endl;
	srand(time(NULL));
	for (auto i=0; i<num;i++)
	{
		for (auto j=0; j<3; j++)
		{
			my_file << rand() << "\t";
		}
		my_file<<std::endl;
	}
	my_file.close();
}

string rename_file_to_sort (string filename)
{
	const string sorted = ".sort";
	const string txt = ".txt";
	const auto pos = filename.rfind(txt);
	filename.insert(pos,sorted);
	return filename;
}

int SortDataset (string filename)
{
	auto temp = 0;
	std::ifstream my_file;
	my_file.open(filename);
	while (my_file>>temp){
		numbers.push_back(temp);
	}
	my_file.close();
	filename = rename_file_to_sort(filename);
	std::ofstream my_file_write(filename);
	
	auto pass = false;
	double temp_sort;
	auto compares = 0;

	while (!pass) {
		pass = true;
		for (auto i = 0; i < numbers.size() - 1; i++) {
			if (numbers[i] > numbers[i + 1]) {
				pass = false;
				temp_sort = numbers[i];
				numbers[i] = numbers[i + 1];
				numbers[i + 1] = temp_sort;
				compares++;
			}
		}
	}
	std::cout << "vector sorted" << std::endl;
	
	for(auto number: numbers)
	{
		my_file_write << number;
		my_file_write << std::endl;
	}
	my_file_write.close();
	
	return compares;
	
}


int main()
{
	auto number_of_compares=0;
	const string path_to_file = "C:/Users/mksh2/source/repos/LR2-3/1/";
	string file_name;
	auto number_of_lines = 0;

	std::cout << "Input file name" << std::endl;
	std::cin >> file_name;

	const auto full_file_name = path_to_file + file_name + ".txt";

	std::cout << "Input number of lines in a file" << std::endl;
	std::cin >> number_of_lines;

	if (number_of_lines<=0)
	{
		std::cout << "Number of lines cannot be below 0" << std::endl;
		return 0;
	}
	GenerateDataset(full_file_name, number_of_lines);
	number_of_compares=SortDataset(full_file_name);
	std::cout << "Number of compares: "<<number_of_compares << std::endl;
	
}
