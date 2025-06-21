#include "logging.h"

namespace rendell
{
    RendellLogger::RendellLogger() : logx::Logger()
    {

    }

    const char* RendellLogger::getLevelName_Unsafe(logx::Level level) const
    {
		static const std::unordered_map<logx::Level, const char* > levelNames
		{
			{logx::Level::critical, "RENDELL::CRITICAL"},
			{logx::Level::error, "RENDELL::ERROR"},
			{logx::Level::warning, "RENDELL::WARNING"},
			{logx::Level::info, "RENDELL::INFO"},
			{logx::Level::debug, "RENDELL::DEBUG"},
			{logx::Level::trace, "RENDELL::TRACE"},
		};

		auto it = levelNames.find(level);
		if (it != levelNames.end())
		{
			return it->second;
		}

		return nullptr;
	}

	static std::unique_ptr<logx::Logger> s_logger{ nullptr };

	logx::Logger* get_logger()
	{
		if (!s_logger)
		{
			s_logger = std::make_unique<RendellLogger>();
		}

		return s_logger.get();
	}

}