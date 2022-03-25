#include "pch.h"
#include "DummyScene.h"

namespace Client
{
DummyScene::DummyScene() :
	Scene(SceneID::Dummy)
{

}

DummyScene::~DummyScene()
= default;

void DummyScene::OnHotpatch()
{
	Scene::OnHotpatch();
}

void DummyScene::Tick()
{
	Scene::Tick();
}

void DummyScene::RenderUI()
{
	Scene::RenderUI();
}

void DummyScene::Render(sf::RenderTarget & tgt, sf::RenderStates states)
{
	Scene::Render(tgt, states);
}

bool DummyScene::HandleEvent([[maybe_unused]] const sf::Event & ev)
{
	return Scene::HandleEvent(ev);
}
}
