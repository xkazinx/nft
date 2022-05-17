#include "pch.h"
#include "GenScene.h"
#include "NFT.h"
#include "Sprite.h"

namespace Client
{
GenScene::GenScene() :
	Scene(SceneID::Gen)
{
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
	if(ev.type == sf::Event::KeyPressed)
	{
		switch(ev.key.code)
		{
			using enum sf::Keyboard::Key;

		case C:
			_objects.clear();

			{
				auto obj = AddObject(NFT::List["cogollo"]->GenerateRandom());

				/*auto obj = AddObject(unique_ptr<NFT>(
					{ NFT::List["cogollo"].get() }
				));*/
				
				Sprite* test_spr = nullptr;

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

							((Sprite*)sprite.get())->_sprite.setColor(Random::Color());

							if (!test_spr)
								test_spr = ((Sprite*)sprite.get());

							/*auto size = ((Sprite*)sprite.get())->_sprite.getTexture()->getSize();*/
							
						}
					}
				}
				
				obj->SetScale({ .33f, .33f });

				// TODO: Center on screen regardless of scale and size
				auto size = test_spr->_sprite.getTexture()->getSize();
				
				Print("size: {} {}", size.x, size.y);
				size.x = size.x / 3.3f;
				size.y = size.y / 3.3f;

				Print("size: {} {}", size.x, size.y);

				float pos_x = (g_res_x / 2) - (size.x / 2);
				float pos_y = (g_res_y / 2) - (size.y / 2);

				//obj->SetPosition({ 0.f, 0.f }, true);
				obj->SetPosition({ pos_x, pos_y }, true);
			}
			break;
		}
	}

	return Scene::HandleEvent(ev);
}
}
