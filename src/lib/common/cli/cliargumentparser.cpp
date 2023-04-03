#include "cliargumentparser.h"

#include <common/log/log.h>

#include <cstring>

using namespace common;
using namespace common::cli;

CommandLineArgumentParser::CommandLineArgumentParser(int argc, char** argv)
{
    int lastArgNameTokenIndex = -1;
    for (int i = 1; i < argc; ++i)
    {
        char* pCurrentToken = argv[i];
        // Check for argument name beginning with "--"
        if (strlen(pCurrentToken) > 2 && pCurrentToken[0] == '-' && pCurrentToken[1] == '-')
        {
            if (lastArgNameTokenIndex == (i - 1))
            {
                // The previous argument was a flag, emplace right here
                // +2 to skip the "--" characters
                m_parsedArguments.emplace_back(argv[i - 1] + 2);
            }
            else if (i == (argc - 1))
            {
                // This argument is a flag
                // +2 to skip the "--" characters
                m_parsedArguments.emplace_back(argv[i] + 2);
            }

            // This is an argument name. Track it.
            lastArgNameTokenIndex = i;
        }
        else if (lastArgNameTokenIndex == (i - 1))
        {
            // Found an argument value
            char* pPreviousToken = argv[i - 1]; 
            
            // +2 to skip the "--" characters
            m_parsedArguments.emplace_back(pPreviousToken + 2, pCurrentToken);
        }
    }
}

std::string CommandLineArgumentParser::GetArgument(const std::string& argumentName, const std::string& defaultValue) const
{
    const CommandLineArgument* pArgument = FindArgument(argumentName);
    if (pArgument)
    {
        return pArgument->AsString();
    }

    return defaultValue;
}

const CommandLineArgument* CommandLineArgumentParser::FindArgument(const std::string& argumentName) const
{
    for (const CommandLineArgument& argument : m_parsedArguments)
    {
        // Case-insensitive for now
        if (argument.GetName() == argumentName)
        {
            return &argument;
        }
    }

    return nullptr;
}
