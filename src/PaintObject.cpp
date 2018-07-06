#include "PaintObject.h"

// 重力加速度
#define GRAVITY (9.8f)

Circle::Circle(float _x, float _y, float _w, float _h, float _speed_x, float _speed_y, float _acceleration_x, float _acceleration_y, bool _gravity, HPEN _pen, HBRUSH _brush)
	: PaintObject(_x, _y, _w, _h, _speed_x, _speed_y, _acceleration_x, _acceleration_y, _pen, _brush)
{
	gravity = _gravity;
}

void Circle::update()
{
	if (!status) return;
	auto now = std::chrono::system_clock::now(); // 現在時刻
	auto s = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_update).count(); // 経過時間のカウント
	
	// 経過時間に応じて量を変化させたい
	speed.x += acceleration.x;
	speed.y += (acceleration.y - gravity ? GRAVITY : 0);

	center.x += speed.x * s / 1000;
	center.y += speed.y * s / 1000;

	// 画面外判定
	auto circle = getCircle();
	if (circle.x - circle.r < 0 || SCREEN_WIDTH < circle.x + circle.r) speed.x *= -1;
	if (circle.y - circle.r < 0 || SCREEN_HEIGHT < circle.y + circle.r) speed.y *= -1;

	last_update = now; // 最終更新に代入して終了
}

void Circle::draw(HDC hdc)
{
	if (!drawing) return;

	auto old_pen = (HPEN)SelectObject(hdc, pen);
	auto old_brush = (HBRUSH)SelectObject(hdc, brush);
	Ellipse(hdc, center.x - size.w / 2, center.y - size.h / 2, center.x + size.w / 2, center.y + size.h / 2);
	SelectObject(hdc, old_pen);
	SelectObject(hdc, old_brush);
}

CircleCore Circle::getCircle()
{
	return CircleCore(center.x, center.y, size.w / 2);
}

bool Circle::isCollision(Circle* another)
{
	auto core = getCircle();
	auto another_core = another->getCircle();
	return (sqrt(pow(another_core.x - core.x, 2) + (another_core.y - core.y, 2))) < (another_core.r + core.r);
}

Line::Line(std::vector<VECTOR> _line, COLORREF _color, bool _center)
	: line(_line), color(_color), center(_center)
{
}

void Line::draw(HDC hdc)
{
	auto pen = CreatePen(PS_SOLID, 5, color);
	auto old_pen = (HPEN)SelectObject(hdc, pen);
	POINT p;
	MoveToEx(hdc, line.front().x + (center ? SCREEN_WIDTH / 2 : 0), line.front().y + (center ? SCREEN_HEIGHT / 2 : 0), &p);
	for (auto i = 1; i < line.size(); ++i)
	{
		LineTo(hdc, line[i].x + (center ? SCREEN_WIDTH / 2 : 0), line[i].y + (center ? SCREEN_HEIGHT / 2 : 0));
	}
	MoveToEx(hdc, p.x, p.y, &p);
	SelectObject(hdc, old_pen);
	DeleteObject(pen);
}

void Line::update()
{
}

VECTOR operator+=(VECTOR & a, VECTOR & b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}

VECTOR operator/(VECTOR v, int n)
{
	return VECTOR(v.x / n, v.y / n);
}

VECTOR operator/(VECTOR & a, VECTOR & b)
{
	return VECTOR(a.x / b.x, a.y / b.y);
}
