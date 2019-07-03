#ifndef ShipH
#define ShipH

class GameBoard;
class GameBoardCell;

/******************************************************************************************************
*	ЙКЮЯЯ - ЙНПЮАКЭ
******************************************************************************************************/
class Ship {
    public:
        std::vector < GameBoardCell > v_desc;

        Ship    ();
        ~Ship   ();

        // б астеп йнпюакъ гюмняхл онкъ, б йнрнпшу нм пюяонкюцюеряъ
        void    Create(GameBoard& gameBoard, int size, int ind_x, int ind_y, bool horizontal);

        // ТСМЙЖХЪ БШЯРПЕКЮ ОН ЙНПЮАПЧ, еякх йнпюакэ сахр, рн нйпсфюел ецн онкел хг осяршу онкеи
        bool    Shoot(GameBoard& gameBoard, int ind_x, int ind_y, bool &isDestroy);
};
#endif