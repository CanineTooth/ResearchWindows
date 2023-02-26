#pragma once
#include <map>
#include <string>
#include "xorstr.hpp"

#define CALL_HASH(name, hash) call::export_routine::get_instance().get<hash,decltype(&name)>()
#define CALL_NAME(name) call::export_routine::get_instance().get<decltype(&name)>(std::hash<std::string>{}(xorstr_(#name)))
#define DATA_NAME(name, type) call::export_routine::get_instance().get<type>(std::hash<std::string>{}(xorstr_(#name)))

namespace call
{
	class export_routine
	{
	private:
		export_routine() {};
		~export_routine();
	public:
		export_routine(const export_routine&) = delete;
		export_routine& operator =(const export_routine&) = delete;
		static export_routine& get_instance()
		{
			static export_routine instance;
			return instance;
		}

		template<class... Args>
		decltype(auto) operator()(Args&&... args) const
		{
			return get()(std::forward<Args>(args)...);
		}

		template<std::uint64_t hash, class T>
		__forceinline T get() noexcept
		{
			if (m_routine_map.empty())
			{
				init_map();
			}
			return (T)m_routine_map.find(hash)->second;
		}

		template<class T>
		__forceinline T get(std::uint64_t hash) noexcept
		{
			if (m_routine_map.empty())
			{
				init_map();
			}
			return (T)m_routine_map.find(hash)->second;
		}

	private:
		void init_map();
	private:
		std::map<std::size_t, std::uint64_t> m_routine_map;
	};
}


