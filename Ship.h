#ifndef ShipH
#define ShipH

class GameBoard;
class GameBoardCell;

/******************************************************************************************************
*	����� - �������
******************************************************************************************************/
class Ship {
    public:
        std::vector < GameBoardCell > v_desc;

        Ship    ();
        ~Ship   ();

        // � ����� ������� ������� ����, � ������� �� �������������
        void    Create(GameBoard& gameBoard, int size, int ind_x, int ind_y, bool horizontal);

        // ������� �������� �� �������, ���� ������� ����, �� �������� ��� ����� �� ������ �����
        bool    Shoot(GameBoard& gameBoard, int ind_x, int ind_y, bool &isDestroy);
};
#endif