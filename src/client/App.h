#pragma once

namespace Client
{
class App final
{
public:
	App();
	~App();

	RenderWindow _window{};
	HMODULE      _livePP;

	int  Tick();
	bool HandleEvents();
	void ToggleConsole();

private:
	void InitializeWindow(u16 res_x, u16 res_y);

	static void AdjustViewport(const GLsizei & x, const GLsizei & y);
};
}