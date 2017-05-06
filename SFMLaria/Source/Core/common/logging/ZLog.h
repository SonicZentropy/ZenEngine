#pragma once
#include <spdlog/spdlog.h>

namespace Zen {

	class ZLog
	{
	public:
		static shared_ptr<spdlog::logger> Logger;
	};

	shared_ptr<spdlog::logger> ZLog::Logger = spdlog::stdout_color_mt("console");
}