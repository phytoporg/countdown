#pragma once

#include <string>

namespace countdown { namespace cli {
    class CommandLineArgument
    {
    public:
        CommandLineArgument(const std::string& argumentName, const std::string& argumentValue);

        const std::string& GetName() const;

        std::string AsString() const;

    private:
        const std::string m_name;
        const std::string m_value;
    };
}}