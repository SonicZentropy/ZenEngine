#include "stdafx.h"

namespace Zen {
	shared_ptr<spdlog::logger> ZLog::Logger = spdlog::stdout_color_mt("console");
}
