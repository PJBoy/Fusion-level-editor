#pragma once

#include "global.h"

#include <exception>
#include <filesystem>
#include <fstream>
#include <string>

#define LOG_INFO __FILE__ ":" APPLY(STRINGIFY, __LINE__) " - "s
#define LOG_RETHROW \
    catch (const std::exception& e) \
    { \
        DebugFile(DebugFile::error) << LOG_INFO << "Exception thrown: "s << e.what() << '\n'; \
        throw; \
    }

class DebugFile : public std::ofstream
{
    static std::experimental::filesystem::path dataDirectory;

public:
    const inline static std::string
        error{"debug_error.txt"s},
        warning{"debug_warning.txt"s},
        info{"debug_info.txt"s};

    DebugFile(std::experimental::filesystem::path filename);

    static void init(std::experimental::filesystem::path dataDirectory_in);
    void writeImage(const halfword* data, word width, word height);
};
