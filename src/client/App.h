#pragma once

namespace Client
{
struct App final
{
	App();
	~App();

	RenderWindow _window{};

	int  Tick();
	// One pass of the loop: false when the window closed
	bool Frame();

	bool HandleEvents();

	sf::Clock _delta_clock;

	void InitializeWindow(u16 res_x, u16 res_y);
};
}
