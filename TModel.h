#pragma once
#include <SFML/Graphics.hpp>

class TModel {
public:
	std::pair< int, int >                   coord0;						//��������� ����������
	std::vector< std::pair< int, int > >    buf;						//����� ��������� �������
	int                                     width;						//������
	int                                     height;						//������
	std::pair< int, int >                   point_start;				//����� ������ �������
	std::pair< int, int >                   point_end;					//����� ����� �������
	bool                                    isSelect = false;			//������� ��
	bool                                    isSelectable = true;		//����� �� �������

	sf::Vector2i TModel::get_pos(int ind);
	void set(int x0, int y0, int width, int height);
	bool select(sf::Vector2i mouse_pos);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};