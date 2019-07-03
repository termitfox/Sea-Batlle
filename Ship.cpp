#include "GameBoardCell.h"
#include "GameBoard.h"
#include "Ship.h"

//йнмярпсйрнп 
Ship::Ship() {
    v_desc.clear();
}
 //деярпсйрнп
Ship::~Ship() {

}

//б астеп йнпюакъ гюмняхл онкъ б йнрнпшу нм пюяонкюцюеряъ
void Ship::Create(GameBoard& gameBoard, int size, int ind_x, int ind_y, bool horizontal) {
    v_desc.clear();
    for (int i = 0; i < size; ++i) {
        if (horizontal) {
            //  нрлевюч б астепе йнпюакъ, врн б дюммни ъвеийе оюксаю 
            gameBoard.SetState(ind_x + i, ind_y, Deck);

            //  нрлевюч б астепе йнпюакъ, врн б дюммни ъвеийе оюксаю 
            v_desc.push_back(gameBoard.cells[ind_x + i][ind_y]);
        } else {
            //  нрлевюч б хцпнбнл онке, врн б дюммни ъвеийе оюксаю 
            gameBoard.SetState(ind_x, ind_y + i, Deck);

            //  нрлевюч б хцпнбнл онке, врн йнпюакэ ондахр
            v_desc.push_back(gameBoard.cells[ind_x][ind_y + i]);
        }
    }
}
//ТСМЙЖХЪ БШЯРПЕКЮ ОН ЙНПЮАПЧ, еякх йнпюакэ сахр, рн нйпсфюел ецн онкел хг осяршу онкеи
bool Ship::Shoot(GameBoard& gameBoard, int ind_x, int ind_y, bool &isDestroy) {
    bool isResult = false;
    for (auto i=0;i<v_desc.size();++i) {
        if (v_desc[i].get_ind_x() == ind_x && v_desc[i].get_ind_y() == ind_y) {

            //  нрлевюч б хцпнбнл онке, врн йнпюакэ ондахр
            gameBoard.SetState(ind_x, ind_y, HitDeck);

            //  нрлевюч б астепе йнпюакъ, врн йнпюакэ ондахр
            v_desc[i].SetState(HitDeck);

            //  бнгбпюыюч янашрхе "йнпюакэ ашк пюмем"
            isResult = true;
        }
    }

    //  онксвюч янярнъмхе йнпюакъ "пюгпсьем хкх мер"
    if (isResult){
        isDestroy = true;
        
        for (auto i=0; i<v_desc.size(); ++i) {
            if (v_desc[i].GetState() == Deck) {
                isDestroy = false;
                break;
            }
        }

        //  еякх йнпюакэ ашк онкмнярэч пюгпсьем, рн нйпсфюч нпенкнл хг осяршу онкеи
        if (isDestroy) {

            //  жхйк он бяел онкъл йнпюакъ
            for (auto i = 0; i < v_desc.size(); ++i) {

                //  жхйк он бяелс нйпсфемхч дюммнцн онкъ
                for (auto x = -1; x <= 1; ++x) {
                    for (auto y = -1; y <= 1; ++y) {
                        int ind_x = v_desc[i].get_ind_x() + x;
                        int ind_y = v_desc[i].get_ind_y() + y;
                        if (ind_x >= 0 && ind_x < 10 && ind_y >= 0 && ind_y < 10) {
							bool isHitDeck = gameBoard.get_state(ind_x, ind_y) != HitDeck;
							bool isDeck    = gameBoard.get_state(ind_x, ind_y) != Deck;
							if (isHitDeck && isDeck) {
                                gameBoard.SetState(ind_x, ind_y, Miss);
                            }
                        }
                    }
                }
            }
        }
    }

    return isResult;
}