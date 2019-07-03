#include "TModel.h"


sf::Vector2i TModel::get_pos(int ind) {
	sf::Vector2i mouse_pos;
	mouse_pos.x = 0;
	mouse_pos.y = 0;

	if (buf.size() > 0) {
		mouse_pos.x = point_start.first - (buf[0].first)  * (width + 3) + (buf[ind].first)*(width + 3) + width / 2;
		mouse_pos.y = point_start.second - (buf[0].second) * (width + 3) + (buf[ind].second)*(height + 3) + height / 2;
	}

	return mouse_pos;
}

//установить координаты начала и конца
void TModel::set(int x0, int y0, int width, int height) {
	this->width = width;
	this->height = height;

	if (buf.size()>0) {
		int x1 = x0 + (coord0.first) *(width + 3) + (buf[0].first) * (width + 3);
		int y1 = y0 + (coord0.second)*(height + 3) + (buf[0].second)* (height + 3);
		point_start = std::pair<int, int>(x1, y1);

		int x2 = x0 + (coord0.first) *(width + 3) + (buf[buf.size() - 1].first + 1)*(width + 3);
		int y2 = y0 + (coord0.second)*(height + 3) + (buf[buf.size() - 1].second + 1)*(height + 3);
		point_end = std::pair<int, int>(x2 - x1 + 1, y2 - y1 + 1);
	}
}

bool TModel::select(sf::Vector2i mouse_pos) {
	if (isSelectable) {
		if (mouse_pos.x >= point_start.first
			&& mouse_pos.x < point_start.first + point_end.first
			&& mouse_pos.y >= point_start.second
			&& mouse_pos.y < point_start.second + point_end.second
			) {
			isSelect = true;
		}
		else {
			isSelect = false;
		}
	}
	else {
		isSelect = false;
	}
	return isSelect;
}

void TModel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (int j = 0; j<buf.size(); ++j) {

		int x = point_start.first - (buf[0].first) * (width + 3) + (buf[j].first)*(width + 3);
		int y = point_start.second - (buf[0].second) * (width + 3) + (buf[j].second)*(height + 3);

		sf::RectangleShape shape;
		shape.setPosition(sf::Vector2f(x, y));
		shape.setSize(sf::Vector2f(width, height));
		shape.setOutlineThickness(1.f);
		shape.setOutlineColor(sf::Color(100, 200, 100));
		shape.setFillColor(sf::Color(50, 150, 50));
		target.draw(shape, states);
	}
	if (isSelect && isSelectable) {
		if (buf.size() > 0) {
			sf::RectangleShape shape;
			shape.setPosition(sf::Vector2f(point_start.first - 2, point_start.second - 2));
			shape.setSize(sf::Vector2f(point_end.first, point_end.second));
			shape.setOutlineThickness(2.f);
			shape.setOutlineColor(sf::Color(100, 200, 100));
			shape.setFillColor(sf::Color::Transparent);
			target.draw(shape, states);
		}
	}
}