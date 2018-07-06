#include "HermiteCurve.h"

HermiteCurve::HermiteCurve(const Point & _start, const Point & _end, const COLORREF & _penColor)
	: start(_start), end(_end), timer(0.0f), tt(0.0f), penColor(_penColor)
{
	state = PaintObjectInterface::State::Ready;
}

HermiteCurve::HermiteCurve(const Point& _start, const Point& _end)
	: HermiteCurve(_start, _end, RGB(0, 0, 0))
{
}

HermiteCurve::~HermiteCurve()
{
}

void HermiteCurve::update()
{
}

void HermiteCurve::input(DWORD)
{
}

void HermiteCurve::draw(HDC hdc)
{
	auto pen = CreatePen(PS_SOLID, 1, penColor);
	auto oldPen = (HPEN)SelectObject(hdc, pen);

	MoveToEx(hdc, start.pos.x, start.pos.y, NULL);

	for (float t = 0.0f; t < timer; t += 0.01f) {
		LineTo(
			hdc,
			(t - 1) * (t - 1)*(2 * t + 1) * start.pos.x+ t * t * (3 - 2 * t) * end.pos.x + (1 - t) * (1 - t) * t * start.tan.x + (t - 1) * t * t * end.tan.x,
			(t - 1) * (t - 1)*(2 * t + 1) * start.pos.y + t * t * (3 - 2 * t) * end.pos.y + (1 - t) * (1 - t) * t * start.tan.y + (t - 1) * t * t * end.tan.y
		);
	}

	if (tt < 1.0) tt += ttp;
	if (timer < 1.0) timer += tt;
	else {
		tt = timer = 0.0f;
		state = PaintObjectInterface::State::Exit;
	}

	SelectObject(hdc, oldPen);
	DeleteObject(pen);
}
