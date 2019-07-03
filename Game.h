#ifndef GameH
#define GameH

#include <SFML/Graphics.hpp>
#include "GameBoard.h"
#include "TModels.h"

class Game : public sf::Drawable, public sf::Transformable{
	protected:	
        sf::Vector2i	MouseMove_pos   ;
		sf::Vector2i	MousePress_pos  ;

		GameBoard		board_player    ;		// игровое поле игрока
		GameBoard		board_computer  ;	    // игровое поле	компьютера

	public:
        sf::Font	    font;
		bool            isInitialize    = false;

				        Game	        ();
				        ~Game	        ();
		void	        Init	        ();
        void            set_init_ships  (bool isInitialize);

	public:
        TModels         mini_models;

        void            control_ships       (int count);
        std::wstring    get_string_winner   ();
		void			MouseMove		    (sf::Vector2i mouse_pos);
		void			MousePress		    (sf::Vector2i mouse_pos);
        void            correct_position_ship();
		virtual void	draw			    (sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif