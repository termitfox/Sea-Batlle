#include "GameBoard.h"
#include <codecvt>

/******************************************************************************************************
*
******************************************************************************************************/
GameBoard::GameBoard() {
}
/******************************************************************************************************
*
******************************************************************************************************/
GameBoard::~GameBoard() {
}
/******************************************************************************************************
*	������������� ����� �������� ����
******************************************************************************************************/
void GameBoard::initialize(int             x0
                            , int           y0
                            , int           width
                            , int           height
                            , std::wstring  name
                            , sf::Font      &font
                            , bool          isVisible
                        ) {
    this->font = &font;
    this->x0 = x0;
    this->y0 = y0;
    this->name = name;
    this->height = height;
    this->width = width;

    // ��������� ������������� ��������������� ��������� ������
    for (int y = 0; y < 10; ++y) {
        for (int x = 0; x < 10; ++x) {
            cells[x][y].set_ind_x(x);
            cells[x][y].set_ind_y(y);
            cells[x][y].SetHeight(this->height / 10);
            cells[x][y].SetWidth(this->width / 10);
            cells[x][y].SetX(this->x0 + x * this->width / 10);
            cells[x][y].SetY(this->y0 + y * this->height / 10);
            
            // ��������� ������� ���� ������� ��������
            cells[x][y].SetState(Empty);
        }
    }

    //  ��������� ��������� ������ "�������� ��� ���������� ������� �� �����"
    SetIsVisible(isVisible);

    //  ��������� �������� ���� ���������� ���� "��������� �� ���������� �� ���� �������"
    if(!isVisible){
        generate_new_state();
    }

    //  ����� �����: "��� ������� ����������"
    isAllShipsDestroyed = false;
}
/******************************************************************************************************
*  ��������� ��������
******************************************************************************************************/
void GameBoard::generate_new_state() {
    int idx = 0;

    // ���������� 4-� ��������
    ships.resize(10);
    
    ships[idx++].Create(*this, 4, 0, 0, true);
    // ���������� 3-� ��������
    ships[idx++].Create(*this, 3, 0, 2, false);
    ships[idx++].Create(*this, 3, 8, 1, false);
    // ���������� 2-� ��������
    ships[idx++].Create(*this, 2, 3, 9, true);
    ships[idx++].Create(*this, 2, 2, 6, true);
    ships[idx++].Create(*this, 2, 6, 5, true);
    // ���������� 1-� ��������
    ships[idx++].Create(*this, 1, 4, 2, true);
    ships[idx++].Create(*this, 1, 8, 8, true);
    ships[idx++].Create(*this, 1, 0, 8, true);
    ships[idx++].Create(*this, 1, 6, 0, true);
};
/******************************************************************************************************
*������������� � ������� ������ ����� �� � ������
******************************************************************************************************/
void GameBoard::SetIsVisible(bool isVisible) {
    this->isVisible = isVisible;
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            cells[x][y].SetIsVisible(isVisible);
        }
    }
}
/******************************************************************************************************
*
******************************************************************************************************/
void GameBoard::hide_select_cell() {
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            cells[x][y].setIsSelectCell(false);
        }
    }
}

/******************************************************************************************************
*������� ����������� ����
******************************************************************************************************/
void GameBoard::MouseMove(sf::Vector2i mouse_pos) {
    bool isX = mouse_pos.x >= this->x0 && mouse_pos.x < this->x0 + width;
    bool isY = mouse_pos.y >= this->y0 && mouse_pos.y < this->y0 + height;
    if (isX && isY) {
        for (int y = 0; y < 10; y++) {
            for (int x = 0; x < 10; x++) {
                if (cells[x][y].MouseMove(mouse_pos)) {
                    cells[x][y].setIsSelectCell(true);
                }else {
                    cells[x][y].setIsSelectCell(false);
                }
            }
        }
    }
}
/******************************************************************************************************
*������� Click ����
******************************************************************************************************/
bool GameBoard::MousePress(sf::Vector2i mouse_pos) {
	bool isResult = false;
    bool isX = mouse_pos.x >= this->x0 && mouse_pos.x < this->x0 + width;
    bool isY = mouse_pos.y >= this->y0 && mouse_pos.y < this->y0 + height;
    if (isX && isY) {
        for (int y = 0; y < 10; ++y) {
            for (int x = 0; x < 10; ++x) {
                if (cells[x][y].MouseMove(mouse_pos)) {
                    
                    //  ���� ��� ���� ����� �� ������� ����, �� ���� ������ ��� ���� �� ���������� ���
                    if(cells[x][y].GetState() == Miss || cells[x][y].GetState() == HitDeck){
                        isResult = true;
                    }else{
                        isResult = Shoot(x, y, is_destroy_hip_deck);
                    }
                    break;
                }
            }
        }

    //  ����� �� ���� ������, ���� ��� ���������� 
    }else {
        isResult = true;
    }
    return isResult;
}
/******************************************************************************************************
*������� ����������� ��������
******************************************************************************************************/
void GameBoard::set_ships(sf::Vector2i mouse_pos){
    bool isX = mouse_pos.x >= this->x0 && mouse_pos.x < this->x0 + width;
    bool isY = mouse_pos.y >= this->y0 && mouse_pos.y < this->y0 + height;
    if (isX && isY) {
        for (int y = 0; y < 10; ++y) {
            for (int x = 0; x < 10; ++x) {
                if (cells[x][y].MouseMove(mouse_pos) ) {
                    if(cells[x][y].GetState()== Deck){  
						cells[x][y].SetState(Empty);
                    }else{     
						cells[x][y].SetState(Deck);
					}
                    break;
                }
            }
        }
    }
}
/******************************************************************************************************
*   ������������ ������ �������� �� ���������, ������� ����������� PLAYER
******************************************************************************************************/
void GameBoard::use_ships(){
    std::list < std::set< int > >   v_l_ships;
    
	//	���� �� ���� ����� �������� ����
    for (int y=0; y < 10 ;++y){
        for (int x=0;x<10;++x){

			//	���� ������� ����� �������� ������� �������
            if (cells[x][y].GetState()==Deck) {
                
				std::vector< int > v_buf;
				
				//	������� ���� "������" ��������� � �����
				v_buf.push_back(y*10+x);

	            //  ���������� 4 ������ � ������ �������  (y*10+x) ��������� � �����
				bool is_x_left	 = (x-1)>= 0 ? (cells[x-1][y].GetState() == Deck) : false;
				bool is_x_right  = (x+1)< 10 ? (cells[x+1][y].GetState() == Deck) : false;
				bool is_y_top	 = (y-1)>= 0 ? (cells[x][y-1].GetState() == Deck) : false;
				bool is_y_bottom = (y+1)< 10 ? (cells[x][y+1].GetState() == Deck) : false;
				if (is_x_left)	{ v_buf.push_back(     y*10 + (x-1) ); }
				if (is_x_right) { v_buf.push_back(     y*10 + (x+1) ); }
				if (is_y_top)	{ v_buf.push_back( (y-1)*10 + x     ); }
				if (is_y_bottom){ v_buf.push_back( (y+1)*10 + x     ); }

				//	����� ���� �������, ������� ����� ��������� ���� �� ���� ������� �� ��������������� ������� v_buf 
				//	��� ������ ��������� ���������� � ����, � �������� � ���� ��� �������� 
				std::set< int > set_all;
				for (auto it=v_l_ships.begin(); it!= v_l_ships.end();) {
					bool find = false;
					for (int l=0;l<v_buf.size();++l){
						auto it_search = it->find(v_buf[l]);
						if (it_search != it->end()) {
							find = true;
							break;
						}
					}
					if (find) {
						set_all.insert(it->begin(), it->end());
						it = v_l_ships.erase(it);
					}else{ 
						++it;
					}
				}

				//	� �������� ������ ��������� ������� ��������
				set_all.insert(v_buf.begin(), v_buf.end());
				v_l_ships.push_back(set_all);
            }
        }
    }

	//	� ����� � ������ v_l_ships ������ �������� �������������� ������ - ������� 
	ships.clear();
	for (auto it=v_l_ships.begin();it!=v_l_ships.end();++it) {
		Ship ship;
		for(auto obj : (*it)) {
			int x = obj % 10;
			int y = obj / 10;
			ship.v_desc.push_back(cells[x][y]);
		}
		ships.push_back(ship);
	}
}
/******************************************************************************************************
*	��������� ��������� ���������� � ���������� ������
******************************************************************************************************/
sf::Vector2i GameBoard::get_pos_select_cell()
{
    sf::Vector2i result;
    result.x = 0;
    result.y = 0;

    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            if(cells[x][y].isSelectCell){
                result.x = cells[x][y].GetX();
                result.y = cells[x][y].GetY();
                
                break;
            }
        }
    }
    return result;
}
/******************************************************************************************************
*	������� ��������� ������� �� ����
******************************************************************************************************/
bool GameBoard::shoot_rand() {
    bool    isHip = false;
    int     ind_x = 10 * uint64_t(std::rand()) / uint64_t(RAND_MAX);
    int     ind_y = 10 * uint64_t(std::rand()) / uint64_t(RAND_MAX);
    bool    isOk = false;
    int     local_x = ind_x;
    int     local_y = ind_y;


    //  ���� ����� ��� ������ �������, ����� � ������ ������� ��������� ��������� �������� ������
    //  ���� �� ����� ������ �������
    if (v_hip_deck.size() > 0) {

        //  ���� �� ����� ��������� ������� ����
        for (int i = 0; i < v_hip_deck.size(); ++i) {
            ind_x = v_hip_deck[i].get_ind_x();
            ind_y = v_hip_deck[i].get_ind_y();

            if (!isOk) {
                local_x = ind_x;
                local_y = ind_y - 1;
                local_x = local_x < 0 ? 0 : local_x;
                local_x = local_x > 9 ? 9 : local_x;
                local_y = local_y < 0 ? 0 : local_y;
                local_y = local_y > 9 ? 9 : local_y;
                if (cells[local_x][local_y].GetState() != Miss && cells[local_x][local_y].GetState() != HitDeck) {
                    isOk = true;
                }
            }
            if (!isOk) {
                local_x = ind_x;
                local_y = ind_y + 1;
                local_x = local_x < 0 ? 0 : local_x;
                local_x = local_x > 9 ? 9 : local_x;
                local_y = local_y < 0 ? 0 : local_y;
                local_y = local_y > 9 ? 9 : local_y;
                if (cells[local_x][local_y].GetState() != Miss && cells[local_x][local_y].GetState() != HitDeck) {
                    isOk = true;
                }
            }
            if (!isOk) {
                local_x = ind_x - 1;
                local_y = ind_y;
                local_x = local_x < 0 ? 0 : local_x;
                local_x = local_x > 9 ? 9 : local_x;
                local_y = local_y < 0 ? 0 : local_y;
                local_y = local_y > 9 ? 9 : local_y;
                if (cells[local_x][local_y].GetState() != Miss && cells[local_x][local_y].GetState() != HitDeck) {
                    isOk = true;
                }
            }
            if (!isOk) {
                local_x = ind_x + 1;
                local_y = ind_y;
                local_x = local_x < 0 ? 0 : local_x;
                local_x = local_x > 9 ? 9 : local_x;
                local_y = local_y < 0 ? 0 : local_y;
                local_y = local_y > 9 ? 9 : local_y;
                if (cells[local_x][local_y].GetState() != Miss && cells[local_x][local_y].GetState() != HitDeck) {
                    isOk = true;
                }
            }

            if (isOk) {
                break;
            }
        }
    }
		else {

        //  ���� �� ����� ��������� ������� ����
        for (int radius = 0; radius < 10; ++radius) {

            if (!isOk) {
                local_y = ind_y - radius;
                local_y = local_y < 0 ? 0 : local_y;
                local_y = local_y > 9 ? 9 : local_y;
                for (int x = -radius; x <= radius; ++x) {
                    local_x = ind_x + x;
                    local_x = local_x < 0 ? 0 : local_x;
                    local_x = local_x > 9 ? 9 : local_x;
                    if (cells[local_x][local_y].GetState() == Empty || cells[local_x][local_y].GetState() == Deck) {
                        isOk = true;
                        break;
                    }
                }
            }

            if (!isOk) {
                local_y = ind_y + radius;
                local_y = local_y < 0 ? 0 : local_y;
                local_y = local_y > 9 ? 9 : local_y;
                for (int x = -radius; x <= radius; ++x) {
                    local_x = ind_x + x;
                    local_x = local_x < 0 ? 0 : local_x;
                    local_x = local_x > 9 ? 9 : local_x;
                    if (cells[local_x][local_y].GetState() == Empty || cells[local_x][local_y].GetState() == Deck) {
                        isOk = true;
                        break;
                    }
                }
            }

            if (!isOk) {
                local_x = ind_x - radius;
                local_x = local_x < 0 ? 0 : local_x;
                local_x = local_x > 9 ? 9 : local_x;
                for (int y = -radius; y <= radius; ++y) {
                    local_y = ind_y + y;
                    local_y = local_y < 0 ? 0 : local_y;
                    local_y = local_y > 9 ? 9 : local_y;
                    if (cells[local_x][local_y].GetState() == Empty || cells[local_x][local_y].GetState() == Deck) {
                        isOk = true;
                        break;
                    }
                }
            }

            if (!isOk) {
                local_x = ind_x + radius;
                local_x = local_x < 0 ? 0 : local_x;
                local_x = local_x > 9 ? 9 : local_x;
                for (int y = -radius; y <= radius; ++y) {
                    local_y = ind_y + y;
                    local_y = local_y < 0 ? 0 : local_y;
                    local_y = local_y > 9 ? 9 : local_y;
                    if (cells[local_x][local_y].GetState() == Empty || cells[local_x][local_y].GetState() == Deck) {
                        isOk = true;
                        break;
                    }
                }
            }

            if (isOk) {
                break;
            }
        }
    }

    //  ������� ����, � ������� ��� �� ��������: [local_x][local_y], ������� ��������� ����� � ������������� �����
    if (isOk) {
        isHip = Shoot(local_x, local_y, is_destroy_hip_deck);

        //  ���� ������� ����, �� ������� ����� ���������� ����� 
        if (is_destroy_hip_deck) {
            v_hip_deck.clear();
        }else {
            //  ����������� ��������� �������� ������ 
            //  �� ��������� ���� ����� ������ ������� ������ ������ (��� �������, ��� ������� �� ����)
            if (isHip) {
                v_hip_deck.push_back(cells[local_x][local_y]);
            }
        }
    }

    return isHip;
}
/******************************************************************************************************
*	������� ������� �� ����
******************************************************************************************************/
bool GameBoard::Shoot(int ind_x, int ind_y, bool &isDestroy) {
    bool isResult = false;
    if (cells[ind_x][ind_y].GetState() == Deck || cells[ind_x][ind_y].GetState() == HitDeck) {
        isResult = true;

        //  �������� ��������� �������: "������� ����", ���������� ������������ ������� "Miss" 
        for (auto i = 0; i < ships.size(); ++i) {
            if (ships[i].Shoot(*this, ind_x, ind_y, isDestroy)) {
                break;
            }
        }

        //  ���� ��� ������� �����, �� ������������� ���� "��� ������� �����"
        bool isDestroyAll = true;
        for (auto i=0;i<ships.size();++i) {
            for (auto j=0;j<ships[i].v_desc.size();++j) {
                if (ships[i].v_desc[j].GetState() != HitDeck) {
                    isDestroyAll = false;
                    break;
                }
            }
        }
        isAllShipsDestroyed = isDestroyAll;


    }else {
        cells[ind_x][ind_y].SetState(Miss);
    }
    return isResult;
}
/******************************************************************************************************
*	������� ��������� ������� ������ �������� ����
******************************************************************************************************/
void GameBoard::SetState(int ind_x, int ind_y, CellState state) {
    cells[ind_x][ind_y].SetState(state);
}
/******************************************************************************************************
*	������� ��������� ������� ������ �������� ����
******************************************************************************************************/
CellState GameBoard::get_state(int ind_x, int ind_y) {
    return cells[ind_x][ind_y].GetState();
}
/******************************************************************************************************
*	������� ��������� ��������� ������ �������� ����
******************************************************************************************************/
sf::Vector2i GameBoard::getCoord(int x, int y) {
    sf::Vector2i coord;
    coord.x = cells[y][x].GetX();
    coord.y = cells[y][x].GetY();
    return coord;
}
/******************************************************************************************************
*   ��������� �������� ����
******************************************************************************************************/
void GameBoard::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Color	color_line = sf::Color(150, 150, 150);
    sf::Color	color_text = sf::Color(150, 200, 150);

    //	������� ����� �������� ����
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(sf::Vector2f(x0, y0));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color(100, 100, 100));
    shape.setFillColor(sf::Color::Transparent);
    target.draw(shape, states);

    //	������� ��� �����
    sf::Text	text("temp", *font, 20);
    text.setFillColor(color_text);
    text.setString(name);
	int size = text.getCharacterSize() * text.getString().getSize();

    text.setPosition(x0 + width / 2 - text.getLocalBounds().width/2, y0 - 50);
    target.draw(text, states);

    //*	��������� ������������ �������� 
    for (unsigned int i = 0; i < 10; ++i) {

        //	��������� �������������� �������� "�����"
        text.setFillColor(color_text);
		text.setString(L'�' + i);
        text.setPosition(x0 + i * width / 10 + width / (2 * 10), y0 - 25);
        target.draw(text, states);

        //	��������� ������������ �������� "�����"
        text.setFillColor(color_text);
        text.setString(std::to_string(i + 1));
        text.setPosition(x0 - 25, y0 + i * height / 10);
        target.draw(text, states);
    }
    //*/

    //	��������� ���� ����� �������� ����
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            cells[x][y].draw(target, states);
        }
    }
}