/*
 * Simple DirectMedia Layer 2 (SDL2)
 *
 * mingw32
 * SDL2main
 * SDL2
 *
 * raw pointer - ����� ���������
 * int a;
 * int *p=&a;
 *
 * "smart" pointer - "�����" ���������
 * std::shared_ptr
 * std::unique_ptr
 * std::weak_ptr
 *
 * �������� ���� ���������:
 *		1) ��������� �������, ��������� ����� � �.�.
 *		2) ��������� ��������� ���������
 *		3) ����������� �������� ���������
 */

#include <iostream>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>

#include "WindowWithRectangles.h"

/*
 * 1) ������������
 * 		- ���������
 *      - ���������
 * 1.5) ���������
 *      - ������ ����� �������� � ���� ������ �������
 * 2) ������������
 * 3) �����������
 *
 * ������� ���������:
 * 						��� ������		�������		���������
 *      public				+				+			+
 *      protected			+				+
 *      private				+
 *
 */

int main(int, char**) {
	WindowWithRectangles window1;
	//std::shared_ptr<Window> w;
	// = std::make_shared<Window>();

	std::cout << "Program started!" << std::endl;
	SDL_Init(SDL_INIT_EVERYTHING);

	window1.main_loop();
	//w->main_loop();

	std::cout << "Program ended!" << std::endl;
	return 0;
}
