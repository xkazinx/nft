#include "pch.h"
#include "Sprite.h"
#include "NFT.h"

namespace Client
{
unordered_map<string, unique_ptr<Sprite>> Sprite::List;
unordered_map<string, Texture>            Sprite::Textures;

unique_ptr<Sprite> & Sprite::Add(const Path & file)
{
	List.insert({ file.string(), make_unique<Sprite>(file) });

	return List[file.string()];
}

Texture & Sprite::GetTexture(const string & texture_name)
{
	if(!Textures.contains(texture_name))
	{
		Textures.insert({ texture_name, Texture{} });
		Textures[texture_name].loadFromFile((path::DataDir / texture_name).string());
	}

	return Textures[texture_name];
}

void Sprite::Initialize()
{
	vector<string> exclude;

	{
		ifstream f("configs.json");
		json     j;
		f >> j;

		path::DataDir = j.value<string>("data_dir", path::DataDir.string());

		for(auto & path : j["exclude"])
		{
			exclude.push_back(path.get<string>());
		}
	}

	const Path data_path = "data";
	const Path src       = std::filesystem::current_path() / data_path;
	auto       src_str   = src.string();
	const auto src_sz    = src_str.size();

	vector<Path> paths;
	kazin::file::Fetch(src, paths);

	for(auto & path : paths)
	{
		if(ranges::find(exclude, path.string()) != exclude.end())
		{
			kazin::Print("Excluded Path: {}", path.string());
			continue;
		}

		if(path.extension() != ".png")
			continue;

		auto category_name = path.parent_path();
		auto nft_name      = category_name.parent_path().filename();
		category_name      = category_name.filename();
		
		auto & sprite = Sprite::Add(nft_name / category_name / path.filename());

		if(!NFT::List.contains(nft_name.string()))
		{
			NFT::List[nft_name.string()] = make_unique<NFT>(nft_name.string(), NFT_Type::Main);
		}

		auto & nft = NFT::List[nft_name.string()];
		if(auto category = nft->Find(category_name.string(), NFT_Type::Category))
		{
			auto asset = category->AddObject(make_unique<NFT>(path.filename().string(), NFT_Type::Asset));

			auto spr = asset->AddObject(make_unique<Sprite>(*sprite.get()));
		}
		else
		{
			nft->AddObject(make_unique<NFT>(category_name.string(), NFT_Type::Category));
		}

		kazin::Log::Debug("Fetched Path: path({}) nft_name({}) category_name({})",
			path.string(), nft_name.string(), category_name.string());
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

void Sprite::SetScale(Vector2f value)
{
	_sprite.setScale(value);

	Object::SetScale(value);
}
}
