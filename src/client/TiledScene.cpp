#include "pch.h"
#include "TiledScene.h"
#include "App.h"
#include "TiledMap.h"
#include "TiledTile.h"
#include "Sprite.h"
#include "TiledUnit.h"

namespace Client
{
TiledScene::TiledScene() :
	Scene(SceneID::PacMan),
	_map(make_unique<TiledMap>("default.txt"))
{

}

TiledScene::~TiledScene()
= default;

void TiledScene::OnHotpatch()
{
	_map->OnHotpatch();
	
	Scene::OnHotpatch();
}

void TiledScene::Tick()
{
	Scene::Tick();

	_map->Tick();

	[[maybe_unused]] const auto pos = sf::Mouse::getPosition();
}

void TiledScene::RenderUI()
{
	Scene::RenderUI();
}

void TiledScene::Render(sf::RenderTarget & tgt, sf::RenderStates states)
{
	Scene::Render(tgt, states);

	_map->Render(tgt, states);
}

bool TiledScene::HandleEvent(const sf::Event & ev)
{
	if(ev.type == sf::Event::KeyPressed)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		{
			switch(ev.key.code)
			{
				using enum sf::Keyboard::Key;
			case Left:
				_map->Move({ -kTileSize, 0 });
				return true;

			case Up:
				_map->Move({ 0, -kTileSize });
				return true;

			case Right:
				_map->Move({ kTileSize, 0 });
				return true;

			case Down:
				_map->Move({ 0, kTileSize });
				return true;

			default: ;
			}
		}
	}

	if(_map->HandleEvent(ev))
		return true;

	return Scene::HandleEvent(ev);
}
}
