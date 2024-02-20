#include <SFML/Graphics.hpp>
#include <iostream>
#include <locale.h>
#include "Map.h"
#include <vector>
#pragma once
void menu(RenderWindow& window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("Sprites/igrat.png");
	menuTexture2.loadFromFile("Sprites/exit.png");
	menuBackground.loadFromFile("Sprites/korobka.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menuBg.setPosition(0, 0);
	//////////////////////////////Μενώ///////////////////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(45, 186, 108));
		if (IntRect(100, 30, 134, 64).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Green); menuNum = 1; };
		if (IntRect(100, 90, 142, 64).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Red); menuNum = 2; };
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 2) { window.close(); isMenu = false; }
		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.display();
	}
};