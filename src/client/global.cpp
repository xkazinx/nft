#include "pch.h"
#include "Global.h"
#include "Scenes.h"
#include "App.h"
#include "Sprite.h"

namespace Client::Global
{
App *                  g_app;
unique_ptr<Scenes>   g_scenes;
u16                    g_res_x = 1024, g_res_y = 768;

void Initialize()
{
	font::Initialize();

	// ordered
	Sprite::Initialize();
	g_scenes = make_unique<Scenes>();
}

void Deinitialize()
{
}

sf::RenderWindow & GetWindow()
{
	return g_app->_window;
}

namespace font
{
	vector<sf::Font> List;

	void Initialize()
	{
		for(const auto & name : enum_names<ID>())
			Add(name.data() + ".ttf"s);
	}

	sf::Font Create(const string & file_name)
	{
		sf::Font font;
		font.loadFromFile(file_name);
		return font;
	}

	void Add(const string & file_name)
	{
		List.push_back(Create(file_name));
	}
}

namespace text
{
	void Render(const string & text, u32 size, sf::Color color)
	{
		static sf::Text shape(text, font::List[0], size);

		shape.setString(text);
		shape.setCharacterSize(size);
		shape.setFont(font::List[0]);

		shape.setFillColor(color);
		shape.setOutlineColor(sf::Color::Black);
		shape.setOutlineThickness(1.f);

		g_app->_window.draw(shape);
	}
}
}
