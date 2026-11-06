#include "pch.h"
#include "Sprite.h"
#include "NFT.h"

namespace Client
{
unordered_map<string, unique_ptr<Sprite>> Sprite::List;
unordered_map<string, Texture>            Sprite::Textures;

unique_ptr<Sprite> & Sprite::Add(const Path & file)
{
	List.insert({ file.generic_string(), make_unique<Sprite>(file) });

	return List[file.generic_string()];
}

Texture & Sprite::GetTexture(const string & texture_name)
{
	if(!Textures.contains(texture_name))
	{
		Textures.insert({ texture_name, Texture{} });
		if(!Textures[texture_name].loadFromFile((path::DataDir / texture_name).string()))
			Warn("texture {} not loaded", texture_name);
	}

	return Textures[texture_name];
}

void Sprite::Initialize()
{
	vector<string> exclude;

	if(ifstream f("configs.json"); f)
	{
		json j;
		f >> j;

		path::DataDir = j.value<string>("data_dir", path::DataDir.string());

		for(auto & path : j["exclude"])
		{
			exclude.push_back(path.get<string>());
		}
	}

	const Path data_path = "data";
	const Path src       = std::filesystem::current_path() / data_path;

	// Every file under data\ (was kazin::file::Fetch), sorted: the categories and
	// their files in the same order on every system (a browser's file system lists
	// them in another order than NTFS)
	vector<Path> paths;
	{
		std::error_code ec;
		for(std::filesystem::recursive_directory_iterator it(src, ec), end; !ec && it != end; it.increment(ec))
			if(it->is_regular_file())
				paths += it->path();
	}
	ranges::sort(paths);

	for(auto & path : paths)
	{
		if(ranges::find(exclude, path.string()) != exclude.end())
		{
			Info("Excluded Path: {}", path.string());
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

			asset->AddObject(make_unique<Sprite>(*sprite.get()));
		}
		else
		{
			// (as in 2022: a category's first file only makes the category; it is
			// no asset of it. to-resolve.md)
			nft->AddObject(make_unique<NFT>(category_name.string(), NFT_Type::Category));
		}
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
