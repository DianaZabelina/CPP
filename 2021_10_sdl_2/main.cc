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
#include <cerrno>
#include <memory>

#include <SDL2/SDL.h>

#include <SDL2/SDL_main.h>

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

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;

class Window {
public:
	std::shared_ptr<SDL_Window>		_window;
	std::shared_ptr<SDL_Renderer>	_renderer;

	Window();
	//����������
	virtual ~Window() {}

	virtual void handle_keys(const Uint8 *keys) {}
	virtual void update() {}
	virtual void render() {}
	void main_loop();
};

class WindowWithRectangles: public Window {
public:
	SDL_Rect rect1 { 50, 50, 15, 15 };
	int rect1_dx = 1, rect1_dy = 1;

	SDL_Rect rect2 { 685, 485, 15, 15 };
	SDL_Rect border1 { 10, 10, 780, 580 };
	SDL_Rect border2 { 12, 12, 776, 576 };

	WindowWithRectangles();
	//����������
	virtual ~WindowWithRectangles() {}

	virtual void handle_keys(const Uint8 *keys) override;
	virtual void update() override;
	virtual void render() override;
};

WindowWithRectangles::WindowWithRectangles() :
	Window() {
}

Window::Window() {
	_window = std::shared_ptr<SDL_Window>(
					SDL_CreateWindow("SDL Window", /*��������*/
							SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED, /*������������ �������� ������ ����*/
							WINDOW_WIDTH,
							WINDOW_HEIGHT,
							SDL_WINDOW_SHOWN),
					SDL_DestroyWindow);
	if (_window == nullptr) { //���� �� ���������
		std::cerr <<
				"�� ���� ������� ����: " <<
				SDL_GetError() << std::endl;
		exit(1);
	}

	//���� ������� ���������
	_renderer = std::shared_ptr<SDL_Renderer>(
				SDL_CreateRenderer(
						_window.get(), -1,
						SDL_RENDERER_ACCELERATED |
						SDL_RENDERER_PRESENTVSYNC),
				SDL_DestroyRenderer);
	if (_renderer == nullptr) { //�������� �� ��������
		std::cerr <<
				"�� ���� ������� ��������: " <<
				SDL_GetError() << std::endl;
		exit(1);
	}
}

void WindowWithRectangles::render() {
	//���������
	SDL_SetRenderDrawColor(_renderer.get(), 31, 63, 95, 255);
	SDL_RenderClear(_renderer.get());
	//�����
	SDL_SetRenderDrawColor(_renderer.get(), 255, 255, 255, 255);
	SDL_RenderFillRect(_renderer.get(), &border1);
	//���������
	SDL_SetRenderDrawColor(_renderer.get(), 31, 63, 95, 255);
	SDL_RenderFillRect(_renderer.get(), &border2);
	//������
	for (int i = 0; i <= 50; i++) {
		SDL_SetRenderDrawColor(_renderer.get(), 255 - 5 * i, 5 * i, 255, 255);
		SDL_RenderDrawLine(_renderer.get(),
				100 + i * 8, 100,
				100, 500 - i * 8);
		SDL_RenderDrawLine(_renderer.get(),
				500 - i * 8, 500,
				500, 100 + i * 8);
	}
	//�������
	SDL_SetRenderDrawColor(_renderer.get(), 255, 63, 63, 255);
	SDL_RenderFillRect(_renderer.get(), &rect1);
	//������
	SDL_SetRenderDrawColor(_renderer.get(), 63, 255, 63, 255);
	//����� ��� ����������� ���������������
	SDL_Rect r;
	if (SDL_IntersectRect(&rect1, &rect2, &r))
		SDL_SetRenderDrawColor(_renderer.get(), 255, 255, 63, 255);
	SDL_RenderFillRect(_renderer.get(), &rect2);
}

void Window::main_loop() {
	auto keys = SDL_GetKeyboardState(nullptr);

	SDL_Event event;
	for (;;) {
		//	1) ��������� �������, ��������� ����� � �.�.
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				return;
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					return;
				default:
					;
				}
			}
		}
		handle_keys(keys);

		//	2) ��������� ��������� ���������
		update();

		//	3) ����������� �������� ���������
		render();
		SDL_RenderPresent(_renderer.get());
	}
}

void WindowWithRectangles::handle_keys(const Uint8 *keys) {
	if (rect2.x < border2.w and keys[SDL_SCANCODE_RIGHT]) rect2.x += 2;
	if (rect2.x > border2.x and keys[SDL_SCANCODE_LEFT])  rect2.x -= 2;
	if (rect2.y < border2.h and keys[SDL_SCANCODE_DOWN])  rect2.y += 2;
	if (rect2.y > border2.y and keys[SDL_SCANCODE_UP])    rect2.y -= 2;
}

void WindowWithRectangles::update(){
	rect1.x += rect1_dx;
	rect1.y += rect1_dy;
	if (rect1.x <= 0)						rect1_dx =  1;
	if (rect1.x + rect1.w >= WINDOW_WIDTH)	rect1_dx = -1;
	if (rect1.y <= 0)						rect1_dy =  1;
	if (rect1.y + rect1.h >= WINDOW_HEIGHT)	rect1_dy = -1;
}

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
