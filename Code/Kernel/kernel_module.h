#pragma once
#include <tuple>
#include "xorstr.hpp"

#define GET_MODULE(name) system_info::kernel_module::get_instance().get_module_info(xorstr_(L#name))

namespace system_info
{
	class kernel_module
	{
	private:
		kernel_module() {};
		~kernel_module() {};
	public:
		kernel_module(const kernel_module&) = delete;
		kernel_module& operator =(const kernel_module&) = delete;
		static kernel_module& get_instance()
		{
			static kernel_module instance;
			return instance;
		}

		// <DllBase, SizeOfImage>
		std::pair<void*, unsigned long> get_module_info(const wchar_t* ModuleName);
	};
} // system_info