#include "pch.h"
#include "GenScene.h"
#include "NFT.h"
#include "Sprite.h"

namespace Client
{
GenScene::GenScene() :
	Scene(SceneID::Gen)
{
	_keys = "C: a new random cogollo   "s + kNextSceneKeys;

	OnHotpatch();
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
#if NFT_IMGUI
	{
		ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
		ImGui::SetWindowPos({0.f, 0.f});
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open..", "Ctrl+O")) { 

				}

				if (ImGui::MenuItem("Save", "Ctrl+S"))
				{
					
				}

				if (ImGui::MenuItem("Save as...", "Ctrl+S"))
				{
					
				}

				if (ImGui::MenuItem("Close", "Ctrl+W"))
				{
					my_tool_active = false;
				}

				ImGui::EndMenu();
			}
			
			ImGui::EndMenuBar();
		}
		
		ImGui::End();
	}
#endif

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
	if(ev.is<sf::Event::KeyPressed>())
	{
		switch(KeyPressed(ev))
		{
			using enum sf::Keyboard::Key;

		case C:
			_objects.clear();

			if(NFT::List.contains("cogollo"))
			{
				auto obj = AddObject(NFT::List["cogollo"]->GenerateRandom());

				/*auto obj = AddObject(unique_ptr<NFT>(
					{ NFT::List["cogollo"].get() }
				));*/
				
				Sprite* first_spr = nullptr;

				for(auto & object : obj->_objects)
				{
					if (object->_type != ObjectType::NFT)
						continue;
					
					auto * nft = ((NFT*)object.get());

					if (nft->_type != NFT_Type::Category)
						continue;

					for(auto & asset : nft->_objects)
					{
						if(asset->_type != ObjectType::NFT)
							continue;

						for(auto & sprite : asset->_objects)
						{
							if(sprite->_type != ObjectType::Sprite)
								continue;

							auto * spr = ((Sprite*)sprite.get());
							auto & sf_spr = spr->_sprite;

							sf_spr.setColor(color::GetRandom());
							
							if (!first_spr)
								first_spr = ((Sprite*)sprite.get());
						}
					}
				}

				Vector2f scale = { .20f, .20f };
				obj->SetScale(scale);
				
				obj->SetPosition({ 0.f, 0.f }, true);

				if(!first_spr)
					break;

				auto grect = first_spr->_sprite.getGlobalBounds();

				sf::Vector2f gsize = grect.size;

				float pos_x = (g_res_x / 2) - (gsize.x / 2);				float pos_y = (g_res_y / 2) - (gsize.y / 2);

				obj->SetPosition({ pos_x, pos_y }, true);
				
			}
			break;
		}
	}

	return Scene::HandleEvent(ev);
}
}
