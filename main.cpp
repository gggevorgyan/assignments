
#include "spreadsheet.h"

#include <iostream>
#include <string>
#include <vector>


int main()
{
    try
    {
        spreadsheet sheet { };

        std::vector<std::string> tokens { };
        for (std::string line; std::getline(std::cin, line) && ! line.empty(); )
        {
            split (line, tokens);

            if ("get" == tokens[0]) // get <name>
            {
                const std::string & name = tokens[1];
                const double v = sheet.get(name);

                std::cout << name << ' ' << v << std::endl;
            }
            else if ("set" == tokens[0]) // set <name> = ...
            {
                const std::string & name = tokens[1];
                const std::size_t eq_pos = line.find('=');
                const std::string definition = line.substr( eq_pos + 2, line.size () - eq_pos - 2);

                sheet.set(name, definition);
            }
            else
                throw std::invalid_argument("malformed input line [" + line + ']');
        }
    }
    catch (const std::logic_error & e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
