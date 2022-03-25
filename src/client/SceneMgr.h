#pragma once
#include "Object.h"

namespace Client
{
class Scene;

class SceneMgr final : public Object
{
public:
	using ID = SceneID;

	SceneMgr();
	~SceneMgr() override;

	void OnHotpatch() override;
	void Tick() override;
	void Render(sf::RenderTarget & tgt, sf::RenderStates states) override;
	bool HandleEvent(const sf::Event & ev) override;

	unique_ptr<Scene> Create(ID id);

	Scene * _ptr = nullptr;
};
}