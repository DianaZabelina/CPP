#include <iostream>
#include <limits>
#include <iomanip>
#include <fstream>
#include <vector>

/*
 * --- �������
 * >>> ���������
 * --- �����������
 */

/*
 * ������
 *
 * ���� ������ �����������.
 * � ���������� ���� ���, ���������, ��.
 * ������� ������ ����������� � ���� �������.
 */

struct Employee {
	char name[21];
	char job[16];
	int salary;
};

void print_table_header() {
	std::cout <<
			"       Employee      |       Job       | Salary \n"
			"---------------------+-----------------+--------\n";
}

void print_table_row(const Employee &empl) {
	std::cout <<
			std::setw(20) << std::left << empl.name << " | " <<
			std::setw(15) << std::left << empl.job << " | " <<
			std::setw(7) << std::right << empl.salary <<
			std::endl;
}

void read_file(const char *filename, std::vector<Employee> &list) {
	list.clear();

	std::ifstream data_file { filename, std::ios::binary };
	if (not data_file)
		return;

	/*
	 * | char[]     | char[]     |i|
	 * | Employee                  |
	 * -------------------------------
	 * | char[]                    |
	 * ^
	 * empl
	 *
	 * &empl - Employee *
	 *         char *
	 * */

	Employee empl;
	while (data_file.read(
				/*������ char-��*/reinterpret_cast<char*>(&empl),
				/*������*/sizeof(empl)))
		list.push_back(empl);

	data_file.close();
}

void write_file(
		const char *filename,
		std::vector<Employee> &list) {
	std::ofstream data_file{filename, std::ios::binary };
		for(auto &&e : list)
			data_file.write(reinterpret_cast<char*>(&e), sizeof(e));

		data_file.close();
}

void input_employee(
		std::vector<Employee> &list){

}

constexpr int EMPL_COUNT = 3;
Employee empl_list[] {
		{ "Ivanov I.I.", "SysAdmin", 3'000 },
		{ "Petrov P.P.", "Manager", 9'000 },
		{ "Sidorov S.S", "Janitor", 12'000 },
};

int main() {
	std::vector<Employee> empl_roster;

	read_file("empl_roster.db", empl_roster);

	int choice;
	do {
		menu:
			std::cout <<
					" �������� ��� �������:\n"
					" ---------------------\n"
					" 1. ������� ������\n"
					" 2. �������� ����������\n"
					"\n"
					" 0. �����\n"
					"---> ";
			if(not(std::cin >> choice)){
				if(std::cin.eof()){
					std::cerr << "������ �����-������" << std::endl;
					return 1;
				}
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				goto menu;
			}
			switch(choice){
			case 0:
				std::cout << "�� ��������!" << std::endl;
				break;
			case 1:
				print_table_header();
				for (auto &&e : empl_roster)
					print_table_row(e);
				break;
			case 2:
				input_employee(empl_roster);
				break;
			default:
				std::cout << "��� ������ ��������." << std::endl;
			}
	} while (choice!=0);

	write_file("empl_roster.db", empl_roster);

	return 0;
}

