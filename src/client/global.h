#pragma once

namespace Client
{
class App;
class Scenes;

namespace Global
{
	constexpr char kAppName[] = "NFTGEN";

	extern App *              g_app;
	extern unique_ptr<Scenes> g_scenes;
	extern u16                g_res_x, g_res_y;
	extern vector<sf::Font>   g_fonts;

	extern void Initialize();
	extern void Deinitialize();

	extern sf::RenderWindow & GetWindow();

	static constexpr float kTileSize = 64.f;

	class Guard
	{
	public:
		template<typename T>
		Guard(T func) :
			_reset(func)
		{
		}

		~Guard()
		{
			_reset();
		}

		std::function<void()> _reset;
	};

	namespace time
	{
		using Value = u32;
		inline thread_local Value Now;

		inline void Tick()
		{
			Now = timeGetTime();
		}

		class Timer
		{
		public:
			Timer(u32 ms)
			{
				Reset(ms);
			}

			bool Fire(bool reset)
			{
				if(Now > _trigger_tm)
				{
					if(reset)
						Reset();

					return true;
				}

				return false;
			}

			u8 GetPercentLeft()
			{
				if(Fire(false))
					return 0u;

				return u8((_trigger_tm - Now) * 100 / _ms);
			}

			void Reset()
			{
				_trigger_tm = Now + _ms;
			}

			void Reset(Value ms)
			{
				_ms = ms;
				Reset();
			}

			Value _trigger_tm;
			Value _ms;
		};
	}

	namespace scene
	{
		enum ID : u8
		{
			Dummy,
			PacMan,
			Gen,

			None = u8(-1),
		};
	}

	enum class FormatType : u8
	{
		None,
		// On, Off
		bool_Switch,
		// true, false
		bool_State,
		// Enabled, Disabled
		bool_Status,
		// Success, Failure
		bool_Result,
		// Yes, No
		bool_Affirmation,
	};

	template<typename T>
	inline string Format(T v, FormatType type = FormatType::None)
	{
		if constexpr(is_enum_v<T>)
		{
			return format("({}:{})", to_underlying(v), enum_name(v));
		}
		else if constexpr(is_same_v<bool, T>)
		{
			using enum FormatType;
			switch(type)
			{
			case bool_Switch:
				return format("{}", v ? "On" : "Off");
			case bool_State:
				return format("{}", v ? "True" : "False");
			case bool_Status:
				return format("{}", v ? "Enabled" : "Disabled");
			case bool_Result:
				return format("{}", v ? "Success" : "Failure");
			case bool_Affirmation:
				return format("{}", v ? "Yes" : "No");
			default:
				return format("{}", v);
			}
		}
		else
		{
			return to_string(v);
		}
	}

	namespace font
	{
		enum class ID
		{
			arial,
			arialbd,
			arialbi,
			ariali,
			ariblk,

			None = u8(-1)
		};

		extern vector<sf::Font> List;

		extern void Initialize();

		extern sf::Font Create(const string & file_name);
		extern void     Add(const string & file_name);
	}

	namespace text
	{
		template<typename Fnc> requires std::is_function_v<Fnc>
		void Render(Fnc fnc)
		{
			sf::Text text;
			fnc(text);
			Global::GetWindow().draw(text);
		}

		extern void Render(const string & text, u32 size = 30, sf::Color color = sf::Color::White);
	}

	namespace color
	{
		inline sf::Color GetRandom()
		{
			return
			{
				(u8)kazin::Random::Generate<int>(0, 255),
				(u8)kazin::Random::Generate<int>(0, 255),
				(u8)kazin::Random::Generate<int>(0, 255),
				255
			};
		}
	}

	namespace tile
	{
		enum Type
		{
			Land,
			Water,
			Sand,
		};

		enum Flag : u8
		{
			BorderLeft = 1 << 0,
			BorderTop = 1 << 1,
			BorderRight = 1 << 2,
			BorderBottom = 1 << 3,
		};
	}

	enum class ObjectType
	{
		Sprite,
		Scene,
		Scenes,
		Map,
		Tile,
		Unit,
		Object,
		Cogollo,
		NFT,
	};

	enum class DirectionID
	{
		North,
		East,
		South,
		West,

		None = u8(-1)
	};

	namespace direction
	{
		template<typename T>
		T Delta(DirectionID id)
		{
			switch(id)
			{
			case DirectionID::North:
				return { 0, -1 };
			case DirectionID::East:
				return { 1, 0 };
			case DirectionID::South:
				return { 0, 1 };
			case DirectionID::West:
				return { -1, 0 };

			default: ;
			}

			return { 0, 0 };
		}

		template<typename T>
		void Move(DirectionID id, T & value)
		{
			value += Delta<T>(id);
		}
	}

	using SceneID = Global::scene::ID;
}}
