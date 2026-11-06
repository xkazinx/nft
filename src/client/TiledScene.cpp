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
	_keys = "Arrows + B: one cogollo   WASD + Right Shift: the other   Ctrl+Arrows: the map   "s + kNextSceneKeys;
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
	if(CtrlHeld(ev))
	{
		switch(KeyPressed(ev))
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

	if(_map->HandleEvent(ev))
		return true;

	return Scene::HandleEvent(ev);
}
}
