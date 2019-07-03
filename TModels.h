#pragma once

#include <SFML/Graphics.hpp>
#include "TModel.h"

class TModels {
public:
	std::vector < TModel >  v_model;						//буфер типов кораблей
	TModel                  model;							//корабль
	int                     x0 = 50;					//начальный х
	int                     y0 = 480;					//начальный у
	int                     width = 12;					//ширина
	int                     height = 12;					//высота
	int                     last_index_select = -1;			//последний выбранный тип корабля
	std::map  <int, int>    m_ships;						//буфер кораблей
	std::string			    name;							//имя корабля

	TModels();

	void select(sf::Vector2i mouse_pos);
	void select_by_index(int ind);
	void next_select();
	void lock(int count);
	void unlock();
	bool AllLock();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};