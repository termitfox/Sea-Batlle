#ifndef GameBoardCellH
#define GameBoardCellH

#include <SFML/Graphics.hpp>

/******************************************************************************************************
*	множество состояний одной клетки
******************************************************************************************************/
enum CellState {
    Empty       //  НЕ БЫЛО УДАРА ПО ДАННОМУ ПОЛЮ:     ПУСТОЕ 
    , Deck      //  НЕ БЫЛО УДАРА ПО ДАННОМУ ПОЛЮ:     СОДЕРЖИТСЯ КОРАБЛЬ
    , Miss      //  БЫЛ УДАР ПО ДАННОМУ ПОЛЮ:          КОБАБЛЯ В ДАННОМ УЧАСТКЕ НЕТ ("ПРОМАЗАЛ")
    , HitDeck   //  БЫЛ УДАР ПО ДАННОМУ ПОЛЮ:          КОБАБЛЬ В ДАННОМ УЧАСТКЕ ЕСТЬ ("ПОПАЛ")
};
/******************************************************************************************************
* КЛАСС КЛЕТКА
******************************************************************************************************/
class GameBoardCell {
private:
    int         ind_x;      // координаты клетки в системе координат "Матрица ячеек"
    int         ind_y;      // координаты клетки в системе координат "Матрица ячеек"
    int         x;          // координаты клетки в системе координат "Экран"
    int         y;			// состояние клетки  в системе координат "Экран"
    int         width;		//ширина
    int         height;		//высота
    CellState	state;		//возможное состояние клетки

    bool		isVisible = true; //видно ли состояние клетки

public:
    bool		isSelectCell;						//выбрана ли клетка

	GameBoardCell(int ind_x = 0, int ind_y = 0, int x = 0, int y = 0, int w = 30, int h = 30, CellState state = Miss);
    
	int  get_ind_x();
	int  get_ind_y();
	CellState GetState();
	int GetX();
	int GetY();

	void set_ind_x(int ind_x);
	void set_ind_y(int ind_y);
	void SetHeight(int height);
	void SetWidth(int width);
	void SetIsVisible(int isVisible);
	void SetX(int x);
	void SetY(int y);
	void setIsSelectCell(bool isSelectCell);
	void SetState(CellState state);
	
	bool TryHit(int x, int y);
	bool MouseMove(sf::Vector2i mouse_pos);
	void draw(sf::RenderTarget &target, sf::RenderStates states)const;
};
#endif
