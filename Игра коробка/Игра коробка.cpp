#include <SFML/Graphics.hpp>
#include <iostream>
#include <locale.h>
#include "Map.h"
#include <vector>
#include "Classes.h"
#include "menu.h"
int changecamerax;
int changecameray;
using namespace sf;
int main()
{
	Box korobka(128,320);
	Box korobka1(768, 128);
	Box korobka2(1088, 576);
	Box korobka3(832, 640);
	Box korobka4(960, 704);
	Player eblo("GG.png", 128, 384, 100, 129);
	RenderWindow window(VideoMode(640, 480), "Igra");
	View view = window.getDefaultView();
	Doorper door1(576, 64);
	Doorper door2(1088, 448);
	Doorexit arbuz(576, 832);
	door2.sprite.setRotation(90);
	door2.sprite.move(64, 0);
	eblo.sprite.setScale(0.45, 0.45);
	eblo.w *= 0.45;
	eblo.h *= 0.45;
	Image map_image;
	map_image.loadFromFile("Sprites/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	s_map.setScale(2, 2);
	Clock clock;
	float CurrentFrame = 0;
	setlocale(LC_ALL, "RUS");
	menu(window);
	while (window.isOpen())
	{
		changecamerax = 0;
		changecameray = 0;
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 500;
		Event event;
		eblo.x = korobka.interactionWithPlayerx(eblo.dx, eblo.dy, eblo.x, eblo.y, eblo.w, eblo.h); 
		eblo.y= korobka.interactionWithPlayery(eblo.dx, eblo.dy, eblo.x, eblo.y, eblo.w, eblo.h);
		eblo.x = korobka1.interactionWithPlayerx(eblo.dx, eblo.dy, eblo.x, eblo.y, eblo.w, eblo.h);
		eblo.y = korobka1.interactionWithPlayery(eblo.dx, eblo.dy, eblo.x, eblo.y, eblo.w, eblo.h);
		eblo.x = korobka2.interactionWithPlayerx(eblo.dx, eblo.dy, eblo.x, eblo.y, eblo.w, eblo.h);
		eblo.y = korobka2.interactionWithPlayery(eblo.dx, eblo.dy, eblo.x, eblo.y, eblo.w, eblo.h);
		eblo.x = korobka3.interactionWithPlayerx(eblo.dx, eblo.dy, eblo.x, eblo.y, eblo.w, eblo.h);
		eblo.y = korobka3.interactionWithPlayery(eblo.dx, eblo.dy, eblo.x, eblo.y, eblo.w, eblo.h);
		eblo.x = korobka4.interactionWithPlayerx(eblo.dx, eblo.dy, eblo.x, eblo.y, eblo.w, eblo.h);
		eblo.y = korobka4.interactionWithPlayery(eblo.dx, eblo.dy, eblo.x, eblo.y, eblo.w, eblo.h);
		while (window.pollEvent(event))
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
				
			}; 
		}
		/////////////////////////////управление персонажем///////////////////////////////////////
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			eblo.dir = 1; eblo.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			eblo.sprite.setTextureRect(IntRect(100 * (int(CurrentFrame)), 265, 100, 129));
		}
		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			eblo.dir = 0; eblo.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			eblo.sprite.setTextureRect(IntRect(100 * (int(CurrentFrame)), 129, 100, 129));
		}
		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			eblo.dir = 3; eblo.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			eblo.sprite.setTextureRect(IntRect(100 * (int(CurrentFrame)), 401, 100, 129));
		}
		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
			eblo.dir = 2; eblo.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			eblo.sprite.setTextureRect(IntRect(100 * (int(CurrentFrame)), 0, 100, 129));
		}
		/////////////////////////////////////////////////////////////////////////////////////////
		changecamerax = door1.changecamerax(eblo.x, eblo.y, eblo.w, eblo.h);
		changecameray = door2.changecameray(eblo.x, eblo.y, eblo.w, eblo.h);
		if (door1.changeplayerx(eblo.x, eblo.y, eblo.w, eblo.h) != 0) { eblo.x = door1.changeplayerx(eblo.x, eblo.y, eblo.w, eblo.h); }
		if (door2.changeplayery(eblo.x, eblo.y, eblo.w, eblo.h) != 0) { eblo.y = door2.changeplayery(eblo.x, eblo.y, eblo.w, eblo.h); }
		view.move(changecamerax, changecameray);
		arbuz.pobeda(window ,eblo.x, eblo.y, eblo.w, eblo.h);
		
		eblo.update(time);
		window.clear();
		/////////////////////////////////////////////////////////////////////////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++) 
			for (int j = 0; j < WIDTH_MAP; j++) {
				if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect(64, 0, 32, 32));

				s_map.setPosition(j * 64, i * 64);

				window.draw(s_map);
			}
		//////////////////////////////////////////////////////////////////////////////////////////
		window.draw(door1.sprite);
		window.draw(door2.sprite);
		window.draw(eblo.sprite);
		window.draw(korobka.sprite);
		window.draw(korobka1.sprite);
		window.draw(korobka2.sprite);
		window.draw(korobka3.sprite);
		window.draw(korobka4.sprite);
		window.draw(arbuz.sprite);
		window.setView(view);
		window.display();
	}
	return 0;
}