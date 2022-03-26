#include "pch.h"
#include "GenScene.h"
#include "NFT.h"
namespace Client
{
GenScene::GenScene() :
	Scene(SceneID::Dummy)
{
	AddObject(unique_ptr<NFT>(NFT::List["cogollo"].get()));
}

GenScene::~GenScene()
= default;

void GenScene::SetPosition(Vector2f pos, bool update)
{
	Scene::SetPosition(pos, update);
}

void GenScene::UpdatePosition()
{
	Scene::UpdatePosition();
}

void GenScene::Move(Vector2f pos)
{
	Scene::Move(pos);
}

void GenScene::RenderUI()
{
	Scene::RenderUI();
}

void GenScene::OnHotpatch()
{
	Scene::OnHotpatch();
}

void GenScene::Tick()
{
	Scene::Tick();
}

void GenScene::Render(sf::RenderTarget & tgt, sf::RenderStates states)
{
	Scene::Render(tgt, states);
}

bool GenScene::HandleEvent(const sf::Event & ev)
{
	return Scene::HandleEvent(ev);
}
}
