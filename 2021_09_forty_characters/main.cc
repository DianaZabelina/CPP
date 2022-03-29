#include <iostream>
#include <fstream>
#include <string>

/*
 * ����� ����������� ���������� ����� input.txt �� ������� ����� �������,
 * ����� ������ ���������� ������ �� ��������� 40 ��������, �� ����� ��������� ������.
 *
 * �������, ��� ���� ������� 40 �������� � ����� ���, � ����������� ����� ��������� � ���������� �����.
 */

int main() {
	//�������� �����
	std::ifstream file;
	file.open("input.txt");
	//������ �� ������
	std::string s;
	file >> s;
	std::string output = s;
	while (file >> s) {
		if ((output.length() + 1 + s.length()) <= 40) {
			output = output + " " + s;
		}
		else {
			std::cout << output << std::endl;
			output = s;
		}
	}
	//����� ��������� ������ �� ������, ���� ��� �� �������� � �����
	if ((output.length() + 1 + s.length()) <= 40) {
		std::cout << output << std::endl;
	}
	file.close();
	return 0;
}
