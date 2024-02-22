#include "menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <locale.h>
#include "Map.h"
#include <vector>
#pragma once
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
	float getplayercoordinateX() {
		return x;
	}
	float getplayercoordinateY() {
		return y;
	}
	void interactionWithMap()
	{
		for (int i = y / 64; i < (y + h) / 64; i++)
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
	float wb = 32, hb = 32;
	String File = "map.png";
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
	float interactionWithPlayerx(float dx, float dy, float x, float y, int w, int h)
	{
		if (dx > 0 && IntRect(xb, yb, 64, 64).intersects(IntRect(x, y, w, h)))
		{
			if (nextblock(dx,dy)==false) xb += 64;
			else x = xb - w;
		}
		if (dx < 0 && IntRect(xb, yb, 64, 64).intersects(IntRect(x, y, w, h)))
		{
			if (nextblock(dx,dy) == false)xb -= 64;
			else x = xb + 64;
		}
		sprite.setPosition(xb, yb);
		return x;
	}
	float interactionWithPlayery(float dx, float dy, float x, float y, int w, int h)
	{
		if (dy > 0 && IntRect(xb, yb, 64, 64).intersects(IntRect(x, y, w, h)))
		{
			if (nextblock(dx,dy) == false)yb += 64;
			else y = yb - h;
		}
		if (dy < 0 && IntRect(xb, yb, 64, 64).intersects(IntRect(x, y, w, h)))
		{
			if (nextblock(dx,dy) == false)yb -= 64;
			else y = yb + 64;
		}
		sprite.setPosition(xb, yb);
		return y;
	}
	bool nextblock(float dx,float dy) {
		if (dx > 0) return ((TileMap[yb / 64][(xb + 64) / 64] == '0'));
		if (dx < 0) return ((TileMap[yb / 64][(xb - 64) / 64] == '0'));
		if (dy > 0) return ((TileMap[(yb + 64) / 64][xb / 64] == '0'));
		if (dy < 0) return ((TileMap[(yb - 64) / 64][xb / 64] == '0'));
	}
};
class Doorper {
public:
	int xd, yd;
	float wd=32, hd=32;
	String File = "door.png";
	Image image;
	Texture texture;
	Sprite sprite;
	Doorper(int X, int Y) {
		image.loadFromFile("Sprites/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, wd, hd));
		sprite.setScale(2, 2);
		xd = X; yd = Y;
		sprite.setPosition(xd, yd);
	}
	int changecamerax(int x,int y,int w,int h) {
		if (IntRect(xd-10, yd, 10, 64).intersects(IntRect(x, y, w, h)))
		{
			return 576;
		}
		if (IntRect(xd+64, yd, 10, 64).intersects(IntRect(x, y, w, h)))
		{
			return -576;
		}
		return 0;
	}
	int changecameray(int x, int y, int w, int h) {
		if (IntRect(xd+2, yd-10, 60, 10).intersects(IntRect(x, y, w, h)))
		{
			return 480;
		}
		if (IntRect(xd+2, yd+64, 60, 10).intersects(IntRect(x, y, w, h)))
		{
			return -480;
		}
		return 0;
	}
	int changeplayerx(int x, int y, int w, int h) {
		if (IntRect(xd - 10, yd, 10, 64).intersects(IntRect(x, y, w, h)))
		{
			return x + 128;
			
		}
		if (IntRect(xd + 64, yd, 10, 64).intersects(IntRect(x, y, w, h)))
		{
			return x - 128;
		}
		else return 0;
		
	}
	int changeplayery(int x, int y, int w, int h) {
		if (IntRect(xd+2, yd - 10, 60, 10).intersects(IntRect(x, y, w, h)))
		{
			return y + 148;
		}
		if (IntRect(xd+2, yd + 64, 60, 10).intersects(IntRect(x, y, w, h)))
		{
			return y - 148;
		}
		else return 0;
	}
};
class Doorexit {
public:
	int xa, ya;
	float wa = 32, ha = 32;
	String File = "Arbuz.png";
	Image image;
	Texture texture;
	Sprite sprite;
	Doorexit(int X, int Y) {
		image.loadFromFile("Sprites/" + File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, wa, ha));
		sprite.setScale(2, 2);
		xa = X; ya = Y;
		sprite.setPosition(xa, ya);
	}
	void pobeda(RenderWindow& window ,int x, int y, int w, int h) {
		if (IntRect(xa, ya, 64, 64).intersects(IntRect(x, y, w, h)))
		{
			pobedaekran(window);
		}
	}
};