#include <SFML/Graphics.hpp>
#include "Game.h"
#include <string>
#include <iostream>
#include <locale.h>

using namespace std;

/************************************************************************************************************************************************
 *  ГЛАВНАЯ ФУНКЦИЯ
 ***********************************************************************************************************************************************/
int main(int argc, char** argv){
    setlocale(LC_ALL, "Russian");         //  ДЛЯ ВЫВОДА РУССКОГО ТЕКСТА

	Game game;

    //  СОЗДАНИЕ ОКНА
    sf::RenderWindow window(sf::VideoMode(800, 600), L"МОРСКОЙ БОЙ");

	//	ФОРМИРОВАНИЕ ТЕКСТА 
	sf::Text text(wstring(L"F2 - Новая игра  /  Esc - Выход"), game.font, 20);
	text.setFillColor(sf::Color::Cyan);
	text.setPosition(5.f, 5.f);

	sf::Text text1(wstring(L"Расположите свои карабли на поле."), game.font, 20);
	text1.setFillColor(sf::Color::Cyan);
	text1.setPosition(60 + 300 / 2 - text1.getLocalBounds().width / 2, 40.f);

	sf::Text text2(wstring(L"Игра начата"), game.font, 20);
	text2.setFillColor(sf::Color::Cyan);
	text2.setPosition(window.getSize().x/2 - text2.getLocalBounds().width / 2, 40.f);

	//	частота обновления 30 кадров в секунду
	window.setFramerateLimit(30);

    //	Включаем вертикальную синхронизацию (для плавной анимации)
    window.setVerticalSyncEnabled(true);

    //	ИГРОВОЙ ЦИКЛ
    while (window.isOpen()) {
        
        //  ОБРАБОТКА СОБЫТИЙ
        sf::Event event;
        while (window.pollEvent(event)) {
            //  ЗАКРЫТИЕ ФОРМЫ
            if (event.type == sf::Event::Closed) { window.close();}
			if (event.type == sf::Event::KeyPressed) {
				
				//	НАЖАТА "Esc": ЗАКРЫТЬ ПРИЛОЖЕНИЕ
				if (event.key.code == sf::Keyboard::Escape)     { window.close(); }
				
				//	НАЖАТА "F2": НАЧАТЬ НОВУЮ ИГРУ
				if (event.key.code == sf::Keyboard::F2)         { game.Init();}

			}
        }

		//  СОБЫТИЯ ПЕРЕМЕЩЕНИЕ МЫШИ
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
		game.MouseMove(mouse_pos);

        //  СОБЫТИЯ Click МЫШИ
        if (event.type == sf::Event::MouseButtonPressed) {
            event.type = event.Count;
            game.MousePress(mouse_pos);
        }

        //	ОЧИСТКА ЭКРАНА
        window.clear();

        //	РИСОВАНИЕ ИГРОВОГО ПОЛЯ
        window.draw(game);

		//	ВЫВОД ТЕКСТА
		window.draw(text);

		if(!game.isInitialize){
			window.draw(text1);
		}else if(game.get_string_winner().empty()){
			window.draw(text2);
		}else{
            sf::Text text5(game.get_string_winner(), game.font, 40);
            text5.setFillColor(sf::Color::Cyan);
            text5.setPosition(window.getSize().x / 2 - text5.getLocalBounds().width / 2, 40.f);
            window.draw(text5);

		}

        //	ОБНОВЛЕНИЕ ОКНА
        window.display();
    }
    return EXIT_SUCCESS;
 }