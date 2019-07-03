#pragma once

#include <SFML/Graphics.hpp>
#include "TModel.h"

class TModels {
public:
	std::vector < TModel >  v_model;						//����� ����� ��������
	TModel                  model;							//�������
	int                     x0 = 50;					//��������� �
	int                     y0 = 480;					//��������� �
	int                     width = 12;					//������
	int                     height = 12;					//������
	int                     last_index_select = -1;			//��������� ��������� ��� �������
	std::map  <int, int>    m_ships;						//����� ��������
	std::string			    name;							//��� �������

	TModels();

	void select(sf::Vector2i mouse_pos);
	void select_by_index(int ind);
	void next_select();
	void lock(int count);
	void unlock();
	bool AllLock();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};