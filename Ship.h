#ifndef ShipH
#define ShipH

class GameBoard;
class GameBoardCell;

/******************************************************************************************************
*	класс - корабль
******************************************************************************************************/
class Ship {
    public:
        std::vector < GameBoardCell > v_desc;

        Ship    ();
        ~Ship   ();

        // В БУФЕР КОРАБЛЯ ЗАНОСИМ ПОЛЯ, В КОТОРЫХ ОН РАСПОЛАГАЕТСЯ
        void    Create(GameBoard& gameBoard, int size, int ind_x, int ind_y, bool horizontal);

        // функция выстрела по корабрю, ЕСЛИ КОРАБЛЬ УБИТ, ТО ОКРУЖАЕМ ЕГО ПОЛЕМ ИЗ ПУСТЫХ ПОЛЕЙ
        bool    Shoot(GameBoard& gameBoard, int ind_x, int ind_y, bool &isDestroy);
};
#endif
