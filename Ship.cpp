#include "GameBoardCell.h"
#include "GameBoard.h"
#include "Ship.h"

//����������� 
Ship::Ship() {
    v_desc.clear();
}
 //����������
Ship::~Ship() {

}

//� ����� ������� ������� ���� � ������� �� �������������
void Ship::Create(GameBoard& gameBoard, int size, int ind_x, int ind_y, bool horizontal) {
    v_desc.clear();
    for (int i = 0; i < size; ++i) {
        if (horizontal) {
            //  ������� � ������ �������, ��� � ������ ������ ������ 
            gameBoard.SetState(ind_x + i, ind_y, Deck);

            //  ������� � ������ �������, ��� � ������ ������ ������ 
            v_desc.push_back(gameBoard.cells[ind_x + i][ind_y]);
        } else {
            //  ������� � ������� ����, ��� � ������ ������ ������ 
            gameBoard.SetState(ind_x, ind_y + i, Deck);

            //  ������� � ������� ����, ��� ������� ������
            v_desc.push_back(gameBoard.cells[ind_x][ind_y + i]);
        }
    }
}
//������� �������� �� �������, ���� ������� ����, �� �������� ��� ����� �� ������ �����
bool Ship::Shoot(GameBoard& gameBoard, int ind_x, int ind_y, bool &isDestroy) {
    bool isResult = false;
    for (auto i=0;i<v_desc.size();++i) {
        if (v_desc[i].get_ind_x() == ind_x && v_desc[i].get_ind_y() == ind_y) {

            //  ������� � ������� ����, ��� ������� ������
            gameBoard.SetState(ind_x, ind_y, HitDeck);

            //  ������� � ������ �������, ��� ������� ������
            v_desc[i].SetState(HitDeck);

            //  ��������� ������� "������� ��� �����"
            isResult = true;
        }
    }

    //  ������� ��������� ������� "�������� ��� ���"
    if (isResult){
        isDestroy = true;
        
        for (auto i=0; i<v_desc.size(); ++i) {
            if (v_desc[i].GetState() == Deck) {
                isDestroy = false;
                break;
            }
        }

        //  ���� ������� ��� ��������� ��������, �� ������� ������� �� ������ �����
        if (isDestroy) {

            //  ���� �� ���� ����� �������
            for (auto i = 0; i < v_desc.size(); ++i) {

                //  ���� �� ����� ��������� ������� ����
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