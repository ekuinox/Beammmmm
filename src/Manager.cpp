#include "Manager.h"
#include "HermiteCurve.h"
#include <random>

void Manager::init()
{
	constexpr auto startPointsCount = 20;

	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());

	const auto endPoint = HermiteCurve::Point{
		{ engine() % SCREEN_WIDTH, engine() % SCREEN_HEIGHT },{ engine() % SCREEN_WIDTH - SCREEN_WIDTH, engine() % SCREEN_HEIGHT - SCREEN_HEIGHT }
	};

	for (auto i = 0; i < startPointsCount; ++i) {
		const auto startPoint = HermiteCurve::Point{
			{ engine() % SCREEN_WIDTH, engine() % SCREEN_HEIGHT },{ engine() % SCREEN_WIDTH - SCREEN_WIDTH, engine() % SCREEN_HEIGHT - SCREEN_HEIGHT }
		};

		polygons.emplace_back(new HermiteCurve(
			startPoint,
			endPoint,
			RGB(engine() % 255, engine() % 255, engine() % 255)
		));
	}
}

Manager::Manager()
{
	init();
}

Manager::~Manager()
{
	for (const auto& pol : polygons) delete pol;
}

void Manager::update()
{
	for (const auto& polygon : polygons) polygon->update();
	if (polygons.front()->getState() == PaintObjectInterface::State::Exit) {
		for (const auto& pol : polygons) delete pol;
		polygons.clear();
		polygons.shrink_to_fit();
		init();
	}
}

void Manager::input(DWORD key)
{
	for (const auto& polygon : polygons) polygon->input(key);
}

void Manager::draw(HWND wh)
{
	PAINTSTRUCT ps;
	auto hdc = BeginPaint(wh, &ps);
	for (const auto& polygon : polygons) polygon->draw(hdc);
	EndPaint(wh, &ps);
}
