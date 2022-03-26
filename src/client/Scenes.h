#pragma once
#include "Object.h"

namespace Client
{
class Scene;

class Scenes final : public Object
{
public:
	using ID = SceneID;

	Scenes();
	~Scenes() override;

	void OnHotpatch() override;
	void Tick() override;
	void Render(sf::RenderTarget & tgt, sf::RenderStates states) override;
	bool HandleEvent(const sf::Event & ev) override;

public:
	unique_ptr<Scene> Create(ID id);
};
}
