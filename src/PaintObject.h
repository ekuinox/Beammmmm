#pragma once
#include <windows.h>
#include <chrono>
#include <vector>

/*
    X ->
   +----+
 Y |    |
 | |    |
 v |    |
   +----+

*/

static constexpr auto SCREEN_WIDTH = 800;
static constexpr auto SCREEN_HEIGHT = 600;

using time_point = std::chrono::system_clock::time_point;

using VECTOR = struct _VECTOR {
	float x;
	float y;
	_VECTOR(float _x, float _y) : x(_x), y(_y) {};
	_VECTOR() : _VECTOR(0, 0) {};
};

VECTOR operator+=(VECTOR &a, VECTOR &b);

using SCALE = struct _SCALE{
	float w;
	float h;
	_SCALE(float _w, float _h) : w(_w), h(_h) {};
	_SCALE() : _SCALE(0, 0) {};
};

using CircleCore = struct _CircleCore {
	float x, y, r;
	_CircleCore(float _x, float _y, float _r) : x(_x), y(_y), r(_r) {};
};

/*
* PaintObject
*/

class PaintObjectInterface {
public:
	enum class State {
		Ready,
		Exit,
	};
	virtual void update() = 0;
	virtual void input(DWORD) = 0;
	virtual void draw(HDC) = 0;
	virtual void show() { drawing = true; };
	virtual void hide() { drawing = false; };
	virtual void enable() { status = true; };
	virtual void disable() { status = false; };
	virtual State getState() { return state; };
protected:
	bool drawing;
	bool status;
	State state;
};

class PaintObject : public PaintObjectInterface {
protected:
	HPEN pen;
	HBRUSH brush;
public:
	PaintObject() {};
	PaintObject(float _x, float _y, float _w, float _h, float _speed_x = 0, float _speed_y = 0, float _acceleration_x = 0, float _acceleration_y = 0, HPEN _pen = HPEN(), HBRUSH _brush = HBRUSH())
		: center(_x, _y), center_init(center), size(_w, _h), speed(_speed_x, _speed_y), speed_init(speed),
		acceleration(_acceleration_x, _acceleration_y), acceleration_init(acceleration),last_update(std::chrono::system_clock::now()), pen(_pen), brush(_brush) {};
	virtual void update() = 0;
	void input(DWORD) {}
	virtual void draw(HDC) = 0;
	void init() { center = center_init; speed = speed_init; acceleration = acceleration_init; };
	void show() { drawing = true; };
	void hide() { drawing = false; };
	void enable() { status = true; };
	void disable() { status = false; };

	VECTOR speed, acceleration;
protected:
	VECTOR center, center_init;
	VECTOR speed_init, acceleration_init;
	SCALE size;
	bool gravity;
	time_point last_update;
};

class Circle : public PaintObject {
public:
	Circle(float _x, float _y, float _w, float _h, float _speed_x = 0, float _speed_y = 0, float _acceleration_x = 0, float _acceleration_y = 0, bool _gravity = true, HPEN _pen = HPEN(), HBRUSH _brush = HBRUSH());
	void update();
	void draw(HDC hdc);
	CircleCore getCircle();
	bool isCollision(Circle*);
};

class Line : public PaintObjectInterface {
public:
	Line(std::vector<VECTOR> _line, COLORREF _color = RGB(0, 0, 0), bool _center = false);
	void show() { drawing = true; };
	void hide() { drawing = false; };
	void enable() { status = true; };
	void disable() { status = false; };
	void draw(HDC hdc);
	void update();
private:
	std::vector<VECTOR> line;
	bool status;
	bool drawing;
	COLORREF color;
	bool center; // íÜêSãNì_
};