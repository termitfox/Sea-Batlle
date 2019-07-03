#pragma once
#include <SFML/Graphics.hpp>

class TModel {
public:
	std::pair< int, int >                   coord0;						//начальная координата
	std::vector< std::pair< int, int > >    buf;						//буфер координат корабля
	int                                     width;						//ширина
	int                                     height;						//высота
	std::pair< int, int >                   point_start;				//точка начала корабля
	std::pair< int, int >                   point_end;					//точка конца корабля
	bool                                    isSelect = false;			//выбрана ли
	bool                                    isSelectable = true;		//можно ли выбрать

	sf::Vector2i TModel::get_pos(int ind);
	void set(int x0, int y0, int width, int height);
	bool select(sf::Vector2i mouse_pos);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};