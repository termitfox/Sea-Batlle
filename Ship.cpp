#include "GameBoardCell.h"
#include "GameBoard.h"
#include "Ship.h"

//КОНСТРУКТОР 
Ship::Ship() {
    v_desc.clear();
}
 //ДЕСТРУКТОР
Ship::~Ship() {

}

//В БУФЕР КОРАБЛЯ ЗАНОСИМ ПОЛЯ В КОТОРЫХ ОН РАСПОЛАГАЕТСЯ
void Ship::Create(GameBoard& gameBoard, int size, int ind_x, int ind_y, bool horizontal) {
    v_desc.clear();
    for (int i = 0; i < size; ++i) {
        if (horizontal) {
            //  ОТМЕЧАЮ В БУФЕРЕ КОРАБЛЯ, ЧТО В ДАННОЙ ЯЧЕЙКЕ ПАЛУБА 
            gameBoard.SetState(ind_x + i, ind_y, Deck);

            //  ОТМЕЧАЮ В БУФЕРЕ КОРАБЛЯ, ЧТО В ДАННОЙ ЯЧЕЙКЕ ПАЛУБА 
            v_desc.push_back(gameBoard.cells[ind_x + i][ind_y]);
        } else {
            //  ОТМЕЧАЮ В ИГРОВОМ ПОЛЕ, ЧТО В ДАННОЙ ЯЧЕЙКЕ ПАЛУБА 
            gameBoard.SetState(ind_x, ind_y + i, Deck);

            //  ОТМЕЧАЮ В ИГРОВОМ ПОЛЕ, ЧТО КОРАБЛЬ ПОДБИТ
            v_desc.push_back(gameBoard.cells[ind_x][ind_y + i]);
        }
    }
}
//функция выстрела по корабрю, ЕСЛИ КОРАБЛЬ УБИТ, ТО ОКРУЖАЕМ ЕГО ПОЛЕМ ИЗ ПУСТЫХ ПОЛЕЙ
bool Ship::Shoot(GameBoard& gameBoard, int ind_x, int ind_y, bool &isDestroy) {
    bool isResult = false;
    for (auto i=0;i<v_desc.size();++i) {
        if (v_desc[i].get_ind_x() == ind_x && v_desc[i].get_ind_y() == ind_y) {

            //  ОТМЕЧАЮ В ИГРОВОМ ПОЛЕ, ЧТО КОРАБЛЬ ПОДБИТ
            gameBoard.SetState(ind_x, ind_y, HitDeck);

            //  ОТМЕЧАЮ В БУФЕРЕ КОРАБЛЯ, ЧТО КОРАБЛЬ ПОДБИТ
            v_desc[i].SetState(HitDeck);

            //  ВОЗВРАЩАЮ СОБЫТИЕ "КОРАБЛЬ БЫЛ РАНЕН"
            isResult = true;
        }
    }

    //  ПОЛУЧАЮ СОСТОЯНИЕ КОРАБЛЯ "РАЗРУШЕН ИЛИ НЕТ"
    if (isResult){
        isDestroy = true;
        
        for (auto i=0; i<v_desc.size(); ++i) {
            if (v_desc[i].GetState() == Deck) {
                isDestroy = false;
                break;
            }
        }

        //  ЕСЛИ КОРАБЛЬ БЫЛ ПОЛНОСТЬЮ РАЗРУШЕН, ТО ОКРУЖАЮ ОРЕОЛОМ ИЗ ПУСТЫХ ПОЛЕЙ
        if (isDestroy) {

            //  ЦИКЛ ПО ВСЕМ ПОЛЯМ КОРАБЛЯ
            for (auto i = 0; i < v_desc.size(); ++i) {

                //  ЦИКЛ ПО ВСЕМУ ОКРУЖЕНИЮ ДАННОГО ПОЛЯ
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
