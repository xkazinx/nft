#include "pch.h"
#include "Sprite.h"
#include "NFT.h"

namespace Client
{
unordered_map<string, Sprite>  Sprite::List;
unordered_map<string, Texture> Sprite::Textures;

Texture & Sprite::GetTexture(const string & texture_name)
{
	if(!Textures.contains(texture_name))
	{
		Textures.insert(std::make_pair(texture_name, Texture{}));
		Textures[texture_name].loadFromFile(texture_name);
	}

	return Textures[texture_name];
}

void Sprite::Initialize()
{
	List =
	{
		{
			"cogollo",
			Sprite{ "gfx/nug_full.png" }
		}
	};

	vector<string> exclude;

	{
		ifstream f("data/configs.json");
		json     j;
		f >> j;

		for(auto & path : j["exclude"])
		{
			exclude.push_back(path.get<string>());
		}
	}

	vector<Path> paths;
	const Path   src     = std::filesystem::current_path() / "data";
	auto         src_str = src.string();
	const auto   src_sz  = src_str.size();
	kazin::file::Fetch(src, paths);

	for(auto & path : paths)
	{
		if(std::ranges::find(exclude, path.string()) != exclude.end())
		{
			kazin::Print("Excluded {}", path.string());
			continue;
		}

		if(path.extension() != ".png")
			continue;
		
		//#todo here, Object() and ~Object() is being called at every insert. Maybe, this is solved using unique_ptr, but is there a way to solve this holding instances and not pointers?

		auto str = path.string();
		
		List.insert(std::make_pair(str.substr(src_sz + 1, str.size()), Sprite{ str }));

		auto category_name = path.parent_path();
		auto nft_name = category_name.parent_path().filename();
		category_name = category_name.filename();

		if(!NFT::List.contains(nft_name.string()))
		{
			NFT::List[nft_name.string()] = make_unique<NFT>(nft_name.string(), NFT_Type::Main);	
		}

		auto & nft = NFT::List[nft_name.string()];
		if(auto category = nft->Find(category_name.string(), NFT_Type::Category))
		{
			category->AddObject(make_unique<NFT>(path.filename().string(), NFT_Type::Asset));
		}
		else
		{
			nft->AddObject(make_unique<NFT>(category_name.string(), NFT_Type::Category));

		}

		kazin::Log::Debug("Fetched Path: path({}) nft_name({}) category_name({})", path.string(), nft_name.string(), category_name.string());

	}

	for(auto & pair : List)
	{
		kazin::Log::Debug("Pair primary: {}, second {}", pair.first, pair.second._sprite.getTexture()->getSize().x);
	}
}

void Sprite::Deinitialize()
{
}

Sprite::~Sprite()
= default;

void Sprite::Render(sf::RenderTarget & tgt, sf::RenderStates states)
{
	Object::Render(tgt, states);

	tgt.draw(_sprite, states);
}

void Sprite::Tick()
{
	Object::Tick();
}

bool Sprite::HandleEvent(const sf::Event & ev)
{
	return Object::HandleEvent(ev);
}

void Sprite::OnHotpatch()
{
	Object::OnHotpatch();
}

void Sprite::SetPosition(Vector2f pos, bool update)
{
	_sprite.setPosition(pos);

	Object::SetPosition(pos, update);
}

void Sprite::Move(Vector2f pos)
{
	_sprite.move(pos);

	Object::Move(pos);
}
}
