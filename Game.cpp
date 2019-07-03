#include "Game.h"
#include <string>

using namespace std;


Game::Game(){
	bool isFontLoad = font.loadFromFile("mr_MangaMasterBBG.ttf");//	гюцпсгйю ьпхтрю
    Init();
}

Game::~Game()
{
}

void Game::Init() {
	board_player.initialize(60, 140, 300, 300, wstring(L"хЦПНЙ"), font, true);
	board_computer.initialize(460, 140, 300, 300, wstring(L"йНЛОЭЧРЕП"), font, false);
	isInitialize = false;
    mini_models.m_ships.clear();
    mini_models.unlock();
    mini_models.next_select();
    control_ships(0);
}

void Game::set_init_ships(bool isInitialize){
    this->isInitialize = isInitialize;
    board_player.hide_select_cell();
    board_computer.hide_select_cell();
    board_player.use_ships();						
}

//оепелеыемхе лшьх
void Game::MouseMove(sf::Vector2i mouse_pos) {
    if (get_string_winner().empty()) {
        if (this->MouseMove_pos != mouse_pos) {
            this->MouseMove_pos = mouse_pos;
		    
            if (!isInitialize) {
	            board_player.MouseMove(mouse_pos);

                //  пюяонкнфемхе лндекх бмсрпх накюярх хцпнбнцн онкъ
                correct_position_ship();
     
            }else{
		        board_computer.MouseMove(mouse_pos);
            }
	    }
    }
}

//йнппейрхпнбйю онкнфемхъ йнпюакъ (врнаш ме бшундхк гю хцпнбне онке)  
void Game::correct_position_ship(){
    for (int ind_y = 0; ind_y < 10; ind_y++) {
        bool isFind = false;
        for (int ind_x = 0; ind_x < 10; ind_x++) {
            if (board_player.cells[ind_x][ind_y].isSelectCell) {

                mini_models.model.set(board_player.cells[ind_x][ind_y].GetX() + 1, board_player.cells[ind_x][ind_y].GetY() + 1, 30 - 3, 30 - 3);
                int x = mini_models.model.point_start.first + mini_models.model.point_end.first - 15;
                while (x > board_player.x0 + board_player.width) {
                    --ind_x;
                    mini_models.model.set(board_player.cells[ind_x][ind_y].GetX() + 1, board_player.cells[ind_x][ind_y].GetY() + 1, 30 - 3, 30 - 3);
                    x = mini_models.model.point_start.first + mini_models.model.point_end.first - 15;
                }

                int y = mini_models.model.point_start.second + mini_models.model.point_end.second - 15;
                while (y > board_player.y0 + board_player.height) {
                    --ind_y;

                    mini_models.model.set(board_player.cells[ind_x][ind_y].GetX() + 1, board_player.cells[ind_x][ind_y].GetY() + 1, 30 - 3, 30 - 3);
                    y = mini_models.model.point_start.second + mini_models.model.point_end.second - 15;
                }

                isFind = true;
                break;
            }
        }

        if (isFind)
            break;
    }
}
//мюфюрхе ймнойх лшьх
void Game::MousePress(sf::Vector2i mouse_pos) {
    //  онкэгнбюрекэ сярюмюбкхбюер йнпюакх мю онке
    if(!isInitialize){

        //  бшанп лхмх лндекх
        mini_models.select      (mouse_pos);
        correct_position_ship   ();


        //  йкхй бшонкмем он хцпнбнлс онкч
        bool isX = mouse_pos.x >= board_player.x0 && mouse_pos.x < board_player.x0 + board_player.width;
        bool isY = mouse_pos.y >= board_player.y0 && mouse_pos.y < board_player.y0 + board_player.height;
        if (isX && isY) {

            //  сярюмнбйю мю хцпнбне онке бшапюммнцн йнпюакъ
            bool    isSetOk = true;
            int     count   = mini_models.model.buf.size();
            std::vector<std::pair <int, int>> buf;

			for (int i = 0; i < mini_models.model.buf.size(); ++i) {
                mouse_pos = mini_models.model.get_pos(i);
                for (int y = 0; y < 10; ++y){
                    bool isFind = false;                
					for (int x = 0; x < 10; ++x) {
                        if (board_player.cells[x][y].MouseMove(mouse_pos)) {
                            
                            //  опнбепйю: гюмърн кх дюммне онке сфе хкх мер, еякх гюмърн рн isSetOk = false;
                            if(board_player.cells[x][y].GetState() == Deck){
                                isSetOk = false;
                            }

                            //  жхйк он бяелс нйпсфемхч дюммнцн онкъ
                            for (auto x1 = -1; x1 <= 1; ++x1) {
                                for (auto y1 = -1; y1 <= 1; ++y1) {
                                    int ind_x = x + x1;
                                    int ind_y = y + y1;
                                    if (ind_x >= 0 && ind_x < 10 && ind_y >= 0 && ind_y < 10) {
                                        bool isDeck = board_player.get_state(ind_x, ind_y) == Deck;
                                        if (isDeck) {
                                            isSetOk = false;
                                            break;
                                        }
                                    }
                                }
                            }

                            if (isSetOk) {
                                buf.push_back(pair<int, int>(x, y));
                            }

                            isFind = true;
                            break;
                        }
                    }
                    if(isFind){
                        break;
                    }
                }
                if(!isSetOk){
                    break;
                }
            }
            
            //  опнжедспю ондяверю ббедеммшу йнпюакеи
            if(isSetOk){
                for(int i=0;i< buf.size();++i){
                    board_player.cells[buf[i].first][buf[i].second].SetState(Deck);
                }

                control_ships(count);
            }
        }

    //  йнпюакх ятнплхпнбюмш, напюанрйю опнжеяяю оепеярпекйх
    }else{
        if(get_string_winner().empty()){

	        //  унд хцпнйю: ярпекъер хцпнй опх щрнл лемъеряъ онке йнлоэчрепю
	        bool isPlayer = board_computer.MousePress(mouse_pos);

	        //  унд йнлоэчрепю: ярпекъер йнлоэчреп х лемъел янярнръмхе мю онке хцпнйю
            //  йнло. ундхр еякх хцпнй опнлюгюк, еякх йнло оноюк, рн йнло ундхр онйю ме опнлюфер
	        if(!isPlayer){
	            while( board_player.shoot_rand() );
            }
        }
    }
}
//тСМЙЖХЪ ЙНМРПНКЪ ЙНПНАКЕИ: БЯЕ КХ ЙНПЮАКХ ХЦПНЙ ПЮЯЯРЮБХК ХКХ МЕР
void Game::control_ships(int count){
    if(count>0){
        mini_models.m_ships[count]++;
    }

    bool isLock = false;    

    if(count==4){
        if(mini_models.m_ships[count]>=1)       { mini_models.lock(count); mini_models.model.buf.clear();isLock = true;}
    }
    if (count == 3){
        if (mini_models.m_ships[count] >= 2)    { mini_models.lock(count); mini_models.model.buf.clear();isLock = true;}
    }
    if (count == 2){
        if (mini_models.m_ships[count] >= 3)    { mini_models.lock(count); mini_models.model.buf.clear();isLock = true;}
    }
    if (count == 1){
        if (mini_models.m_ships[count] >= 4)    { mini_models.lock(count); mini_models.model.buf.clear();isLock = true;}
    }

    //  бшдекъел якедсчысч лндекэ - йнпюакэ
    if (isLock){
        mini_models.next_select();
        correct_position_ship();
    }

    //  еякх бяе йнпюакх ббедемш, рн мювюрэ хцпс
    if(isLock && mini_models.AllLock()){
        set_init_ships(true);
    }


    mini_models.name = "";
    mini_models.name = mini_models.name  + " "          + std::to_string( 1 - mini_models.m_ships[4]);
    mini_models.name = mini_models.name  + "         "  + std::to_string( 2 - mini_models.m_ships[3]);
    mini_models.name = mini_models.name  + "        "   + std::to_string( 3 - mini_models.m_ships[2]);
    mini_models.name = mini_models.name  + "     "      + std::to_string( 4 - mini_models.m_ships[1]);
}
//бшбнд: онаедю хкх онпюфемхе хцпнйю
std::wstring Game::get_string_winner(){
    std::wstring str;

    if(board_player.isAllShipsDestroyed){
        str = L" о Н П Ю Ф Е М Х Е ! ";
    }else if (board_computer.isAllShipsDestroyed) {
        str = L" о Н А Е Д Ю ! ";
    }
    return str;
}
//пхянбюмхе хцпнбшу онкеи
void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	states.transform *= getTransform();

    if(!isInitialize){
        board_player.draw	    (target, states);

        //  пхянбюмхе лхмх лндекеи
        mini_models.draw        (target, states);

        //   мюпхянбюрэ лндекэ йнрнпюъ ашкю бшапюмю  
        mini_models.model.draw  (target, states);

        sf::Text	text("temp", font, 20);
        text.setFillColor(sf::Color(150, 200, 150));
        text.setPosition( 60, 450.f );
        text.setString(mini_models.name);

        target.draw(text, states);

    }else{
        board_player.draw	(target, states);
        board_computer.draw	(target, states);
    }
}