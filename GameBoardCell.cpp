#include "GameBoardCell.h"

//конструктр с параметрами
GameBoardCell::GameBoardCell(int ind_x = 0, int ind_y = 0, int x = 0, int y = 0, int w = 30, int h = 30, CellState state = Miss) {
	this->ind_x = ind_x;
	this->ind_y = ind_y;
	this->x = x;
	this->y = y;
	this->state = state;
	width = w;
	height = h;
	isSelectCell = false;
}

// функция устанавливает x-кординату клетки
void GameBoardCell::set_ind_x(int ind_x) { this->ind_x = ind_x; }
// функция устанавливает у-кординату клетки
void GameBoardCell::set_ind_y(int ind_y) { this->ind_y = ind_y; }
// функция возвращает x-кординату клетки
int  GameBoardCell::get_ind_x() { return ind_x; }
// функция возвращает у-кординату клетки
int  GameBoardCell::get_ind_y() { return ind_y; }

// функция устанавливает x-кординату клетки
void GameBoardCell::SetHeight(int height) { this->height = height; }
// функция устанавливает y-кординату клетки
void GameBoardCell::SetWidth(int width) { this->width = width; }
// функция устанавливает y-кординату клетки
void GameBoardCell::SetIsVisible(int isVisible) { this->isVisible = isVisible; }
// функция устанавливает x-кординату клетки
void GameBoardCell::SetX(int x) { this->x = x; }
// функция устанавливает y-кординату клетки
void GameBoardCell::SetY(int y) { this->y = y; }
// функция устанавливает флаг "ячейка выделена"
void GameBoardCell::setIsSelectCell(bool isSelectCell) { this->isSelectCell = isSelectCell; }
// функция устанавливает состояние клети
void GameBoardCell::SetState(CellState state) { this->state = state; }
// функция возвращает состояние текуйщей клетки
CellState GameBoardCell::GetState() { return this->state; }
// функция возвращает x текущей клетки
int GameBoardCell::GetX() { return this->x; }
// функция возвращает y текущей клетки
int GameBoardCell::GetY() { return this->y; }
// функция - проверка попадания в клетку
bool GameBoardCell::TryHit(int x, int y) { return x == this->x && y == this->y && this->state != HitDeck; }

bool GameBoardCell::MouseMove(sf::Vector2i mouse_pos) {
	bool isResult = false;
	if (mouse_pos.x >= this->x
		&& mouse_pos.x < this->x + width
		&& mouse_pos.y >= this->y
		&& mouse_pos.y < this->y + height
		) {
		isResult = true;
	}
	return isResult;
}

// функция печати одной клетки, в зависимости от ее состояния
void GameBoardCell::draw(sf::RenderTarget &target, sf::RenderStates states)const {

	//	РИСОВАНИЕ ПРЯМОУГОЛЬНИКА - РАМКА ПОЛЯ
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(sf::Vector2f(x, y));
	shape.setOutlineThickness(1.f);

	shape.setOutlineColor(sf::Color(100, 100, 100));
	if (!isSelectCell) {
		shape.setFillColor(sf::Color::Transparent);
	}
	else {
		shape.setFillColor(sf::Color(50, 50, 50));
	}
	target.draw(shape, states);


	//	РИСОВАНИЕ ПАЛУБЫ: В ВИДЕ ЗАКРАШЕННОГО ПРЯМОУГОЛЬНИКА
	if ((isVisible && state == Deck) || state == HitDeck) {
		sf::RectangleShape shape;
		shape.setSize(sf::Vector2f(width, height));
		shape.setPosition(sf::Vector2f(x, y));
		shape.setOutlineThickness(2.f);
		shape.setOutlineColor(sf::Color(100, 200, 100));
		if (!isSelectCell) {
			shape.setFillColor(sf::Color(50, 150, 50));
		}
		else {
			shape.setFillColor(sf::Color(50, 250, 50));
		}
		target.draw(shape, states);
	}

	//	РИСОВАНИЕ РАНЕННОГО КАРАБЛЯ: В ВИДЕ КРЕСТИКА
	if (state == HitDeck) {
		sf::VertexArray lines_hor(sf::Lines, 4 /*количество точек*/);
		int shift_x = width / 5;
		int shift_y = height / 5;
		lines_hor[0].position = sf::Vector2f(x + shift_x, y + shift_y);
		lines_hor[1].position = sf::Vector2f(x + width - shift_x, y + height - shift_y);
		lines_hor[2].position = sf::Vector2f(x + shift_x, y + height - shift_y);
		lines_hor[3].position = sf::Vector2f(x + width - shift_x, y + shift_y);
		target.draw(lines_hor);

		//	РИСОВАНИЕ ПОЛЯ, ПО КОТОРОМУ ПРОИЗВЕДЕН ВЫСТРЕЛ И В НЕМ ПУСТО: В ВИДЕ ТОЧКИ В ЦЕНТРЕ
	}
	else if (state == Miss) {
		sf::CircleShape shape;
		int radius = 2;
		shape.setPosition(sf::Vector2f(x + width / 2 - radius, y + height / 2 - radius));
		shape.setRadius(radius);
		shape.setOutlineColor(sf::Color(100, 100, 100));
		target.draw(shape);

	}
}
