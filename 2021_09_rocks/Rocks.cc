#include <iostream>
#include <random>

/*
 * ���� "�����"
 *
 * 2 ������ (������������ � ���������) �� ������� ����� 1, 2 ��� 3 ����� �� ����.
 * � ���� N ������ (���������� ���������� ��������).
 * ����������� ���, ��� ���� ������ ���������.
 *
 * 1. ���� �����������, �����  ����������� ���� �� �������.
 * 2. �� ��������� ���� ����������, ����� �� ������ �����. ���� �� - ��������� ����.
 * 3. �������� ����� ��������.
 * 4. ����� ���������� ������ ����� ������ �����.
 * 5. �� ���� ���������� �������, ������� ������ �� ����.
 *
 */

int main()
{
	//������� ����
	std::cout <<
				"���� \"�����\"\n\n"
				"�������:\n"
				"1. ������� ���� �� N ������.\n"
				"2. 2 ������ (������������ � ���������) �� ������� ����� 1, 2 ��� 3 ����� �� ���� ����.\n"
				"3. ����������� ���, ��� ���� ������ ���������.\n" << std::endl;

	//���������� ���������� ������ N
	std::default_random_engine rnd;
	std::random_device rdev;
	rnd.seed(rdev());
	std::uniform_int_distribution<>N{1,5};
	int numOfRocks=N(rnd);





	//����� ���������� ������
	std::cout << "���������� ������ � ����: " << numOfRocks << std::endl;

	//��� ������������
	int userTurn;
userTurn_retry:
	std::cout << "��� ���: " << std::endl;
	//�������� ���� ������
	if(not(std::cin >> userTurn))
	{
		std::cout << "������������ ����. ������� ����� �� 1 �� 3." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		goto userTurn_retry;
	}
	//�������� ������� ������
	if(userTurn<1 || userTurn>3 || userTurn>numOfRocks)
	{
		std::cout << "������������ ����. ������� ����� �� 1 �� 3. ����� �� ������ ��������� ���������� ������ � ����." << std::endl;
		std::cin.clear();
		goto userTurn_retry;
	}
	numOfRocks-=userTurn;





	//����� ���������� ������
	std::cout << "���������� ������ � ����: " << numOfRocks << std::endl;

	//���������� ���������� ������ ��� ���� ����������
	int n;
	if(numOfRocks<3)n=numOfRocks;
	else n=3;
	std::uniform_int_distribution<>turn{1,n};
	//��� ����������
	int computerTurn=turn(rnd);
	std::cout << "��� ����������: " << computerTurn << std::endl;
	numOfRocks-=computerTurn;

	return 0;
}
