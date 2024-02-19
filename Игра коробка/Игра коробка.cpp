#include <SFML/Graphics.hpp>
#include <iostream>
#include <locale.h>
#include "Map.h"
#include <vector>
char a[8];
using namespace sf;
class Player {
public:
	float x, y, w, h, d, dx, dy, speed = 0;
	int dir = 0;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String F, int X, int Y, float W, float H) {
		File = F;
		w = W; h = H;
		image.loadFromFile("Sprites/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(100, 0, w, h));
	};
	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}
		
		x += dx * time;
		y += dy * time;
		speed = 0;
		sprite.setPosition(x, y);
		interactionWithMap();
	};
	float getplayercoordinateX(){
		return x;
	}
	float getplayercoordinateY() {
		return y;
	}
	void interactionWithMap()
	{
		for(int i=y/64;i<(y+h+64)/64-1; i++)
			for (int j = x / 64; j < (x + w) / 64; j++) {
				if (TileMap[i][j] == '0')
				{
					if (dy > 0) y = i * 64 - h;
					if (dy < 0) y = i * 64 + 64;
					if (dx > 0) x = j * 64 - w;
					if (dx < 0) x = j * 64 + 64;
				}
				

				
		}
	}
};
class Box {
public:
	int xb, yb;
	float wb=32,hb = 32;
	String File="map.png";
	Image image;
	Texture texture;
	Sprite sprite;
	Box(int X, int Y)
	{
		image.loadFromFile("Sprites/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, wb, hb));
		sprite.setScale(2, 2);
		xb = X; yb = Y;	
		sprite.setPosition(xb, yb);
	}
	float interactionWithPlayerx(float dx,float dy,float x,float y,int w,int h)
	{
		if (dx > 0 && IntRect(xb, yb, 64, 64).intersects(IntRect(x, y, w, h)))
		{
			if (TileMap[yb/64][(xb + 64) / 64] != '0') xb += 64;
			else x = xb - w;
		}
		if (dx < 0 && IntRect(xb, yb, 64, 64).intersects(IntRect(x, y, w, h)))
		{
			if (TileMap[yb/64][(xb - 64) / 64] != '0')xb -= 64;
			else x = xb + 64;
		}
		sprite.setPosition(xb, yb);
		return x;
	}
	float interactionWithPlayery(float dx, float dy, float x, float y, int w, int h)
	{
		if (dy > 0 && IntRect(xb, yb, 64, 64).intersects(IntRect(x, y, w, h)))
		{
			if (TileMap[(yb + 64) / 64][xb / 64] != '0')yb += 64;
			else y = yb - h;
		}
		if (dy < 0 && IntRect(xb, yb, 64, 64).intersects(IntRect(x, y, w, h)))
		{
			if (TileMap[(yb - 64) / 64][xb / 64] != '0')yb -= 64;
			else y = yb + 64;
		}
		sprite.setPosition(xb, yb);
		return y;
	}
};
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
	//////////////////////////////Меню///////////////////////////////
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
int main()
{
	Box korobka(192,320);
	Player eblo("GG.png", 64, 384, 100, 129);
	eblo.sprite.setScale(0.45, 0.45);
	eblo.w *= 0.45;
	eblo.h *= 0.45;
	RenderWindow window(VideoMode(640, 480), "Igra");
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
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 500;
		Event event;
		eblo.x = korobka.interactionWithPlayerx(eblo.dx, eblo.dy, eblo.x, eblo.y, eblo.w, eblo.h); 
		eblo.y= korobka.interactionWithPlayery(eblo.dx, eblo.dy, eblo.x, eblo.y, eblo.w, eblo.h);
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
		window.draw(eblo.sprite);
		window.draw(korobka.sprite);
		window.display();
	}
	return 0;
}