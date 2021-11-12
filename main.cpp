#include <graphics.h>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <chrono>
#include <vector>

void draw_square(int x0, int y0, int side, int color)
{
	setcolor(color);
	setfillstyle(1, 15);
	int points[] = {x0 - (side / 2), y0 - (side / 2), x0 + (side / 2), y0 - (side / 2), x0 + (side / 2), y0 + (side / 2), x0 - (side / 2), y0 + (side / 2)};
	fillpoly(4, points);
}

struct point
{
	int x;
	int y;
};

class Player
{
private:
	int i, j, speed, size, c;

public:
	Player(int color)
	{
		i = 320;
		j = 240;
		speed = 1;
		size = 10;
		c = color;
	}

	void move_up()
	{
		if ((j - speed) > (0 + size))
		{
			j -= speed;
		}
	}
	void move_down()
	{
		if ((j + speed) < (480 - size))
		{
			j += speed;
		}
	}
	void move_right()
	{
		if ((i + speed) < (640 - size))
		{
			i += speed;
		}
	}
	void move_left()
	{
		if ((i - speed) > (0 + size))
		{
			i -= speed;
		}
	}

	void draw()
	{
		draw_square(i, j, size, c);
	}

	void increase_size()
	{
		size += 3;
	}

	bool hitbox_check(int x, int y)
	{
		if (x > (i - (size / 2)) && x < (i + (size / 2)) && y > (j - (size / 2)) && y < (j + (size / 2)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

int main()
{
	int duration = 0;
	int p1score = 0, p2score = 0;
	std::cout << "Duration of Game: ";
	std::cin >> duration;
	int gd = DETECT, gm;
	initgraph(&gd, &gm, NULL);
	setfillstyle(1, 11);
	bar(0, 0, 640, 10);
	bar(0, 0, 10, 480);
	bar(0, 480, 640, 470);
	bar(630, 10, 640, 480);
	Player p1(2);
	Player p2(14);
	clock_t start = clock();
	int count = 0, l = 0;
	struct point size_boost[200];
	while ((clock() - start) / CLOCKS_PER_SEC <= (duration-3))  // https://stackoverflow.com/a/45443047
	{
		count += 1;
		p1.draw();
		p2.draw();
		delay(1);

		for (int j = 0; j < l; j++)
		{
			if (p1.hitbox_check(size_boost[j].x, size_boost[j].y))
			{
				p1.increase_size();
				size_boost[j] = {-1, -1};
			}
			if (p2.hitbox_check(size_boost[j].x, size_boost[j].y))
			{
				p2.increase_size();
				size_boost[j] = {-1, -1};
			}
		}

		if (GetAsyncKeyState('D'))
		{
			p1.move_right();
		}
		if (GetAsyncKeyState('A'))
		{
			p1.move_left();
		}
		if (GetAsyncKeyState('W'))
		{
			p1.move_up();
		}
		if (GetAsyncKeyState('S'))
		{
			p1.move_down();
		}

		if (GetAsyncKeyState(VK_RIGHT))
		{
			p2.move_right();
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			p2.move_left();
		}
		if (GetAsyncKeyState(VK_UP))
		{
			p2.move_up();
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			p2.move_down();
		}

		if (GetAsyncKeyState('Q'))
		{
			break;
		}
		if (GetAsyncKeyState('C'))
		{
			cleardevice();
		}

		if (rand() % 200 == 0)
		{
			int rx = 40 + (rand() % 560);
			int ry = 40 + (rand() % 400);

			draw_square(rx, ry, 3, 12);
			size_boost[l] = {rx, ry};
			l++;
		}
	}

	for (int i = 0; i < 640; i++)
	{
		for (int j = 0; j < 480; j++)
		{
			int c = getpixel(i, j);
			if (c == 2)
			{
				p1score += 1;
			}
			else if (c == 14)
			{
				p2score += 1;
			}
		}
	}

	std::cout << "Player 1(Green) score: " << p1score << "\n"
			  << "Player 2(Yellow) score: " << p2score << "\n";
	if (p1score > p2score)
	{
		std::cout << "Player 1 wins.";
	}
	else
	{
		std::cout << "Player 2 wins.";
	}
	closegraph();

	return 0;
}
