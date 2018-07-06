#pragma once

#include "PaintObject.h"

class HermiteCurve : public PaintObjectInterface {
public:
	struct Vector2 {
		int x, y;
	};
	struct Point {
		Vector2 pos; // �_
		Vector2 tan; // �ڐ��x�N�g��
	};

	HermiteCurve(const Point& _start, const Point& _end, const COLORREF& _penColor);
	HermiteCurve(const Point& _start, const Point& _end);
	~HermiteCurve();
	void update();
	void input(DWORD);
	void draw(HDC);
private:
	static constexpr auto ttp = 0.02f;
	float timer;
	float tt;
	Point start, end;
	COLORREF penColor;
};