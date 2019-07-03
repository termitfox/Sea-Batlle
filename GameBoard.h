#ifndef GameBoardH
#define GameBoardH

#include "GameBoardCell.h"
#include "Ship.h"

#include <set>
#include <vector>
#include <list>
#include <algorithm>

/******************************************************************************************************
*   ИГРОВОЕ ПОЛЕ ДЛЯ ОДНОГО ИГРОКА
******************************************************************************************************/
class GameBoard {
    public:
        int					            x0;
        int					            y0;
        int					            width;
        int					            height;
        std::wstring			        name;
        GameBoardCell		            cells[10][10];	// клетки игрового поля
        sf::Font			            *font;
        bool                            isAllShipsDestroyed;

    private:
        bool                            isVisible = false;
        std::vector < Ship >            ships;
        std::vector < GameBoardCell >   v_hip_deck;						//вектор клеток, где есть подбитый корабль
        bool                            is_destroy_hip_deck = false; // если корабль добит

    public:
                        GameBoard           ();
                        ~GameBoard          ();
        void            initialize          (   int             x0
                                                , int           y0
                                                , int           width
                                                , int           height
                                                , std::wstring  name
                                                , sf::Font      &font
                                                , bool          isVisible
                                            );
        void            generate_new_state  ();
        void            SetIsVisible        (bool isVisible);
        void            MouseMove           (sf::Vector2i mouse_pos);
        bool            MousePress          (sf::Vector2i mouse_pos);
        void            hide_select_cell    ();
        void            set_ships           (sf::Vector2i mouse_pos);
        bool            shoot_rand          ();
        bool            Shoot               (int ind_x, int ind_y, bool &isDestroy);
        void            SetState            (int ind_x, int ind_y, CellState state);
        CellState       get_state           (int ind_x, int ind_y);
        sf::Vector2i    getCoord            (int x, int y);
        void            use_ships           ();
        sf::Vector2i    get_pos_select_cell ();
        void            draw                (sf::RenderTarget &target, sf::RenderStates states) const;
};
#endif