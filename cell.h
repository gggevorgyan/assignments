#pragma once

#include<unordered_set>
#include <string>
#include <vector>

class spreadsheet;
/*
 * split 's' into tokens delimited by a single space
 */
std::size_t split(const std::string & s, std::vector<std::string> & tokens)
{
    tokens.clear();
    std::size_t pos_start = 0;
    std::size_t pos = s.find(' ', pos_start);

    while (pos != std::string::npos)
    {
        tokens.push_back(s.substr(pos_start, pos - pos_start));
        pos_start = pos + 1;
        pos = s.find(' ', pos_start);
    }
    tokens.push_back(s.substr(pos_start, std::min(pos, s.size()) - pos_start + 1));

    return tokens.size();
}

struct cell
{
    enum def_type
    {
        single = 1,
        binary_expr = 3
    };

    cell(const std::string &def, spreadsheet *sp);

    void set(const std::string &def);

    float getValue(std::unordered_set<std::string>& vars) const;
    float extractSingleValue() const;
    float extractFromExpr(std::unordered_set<std::string>& vars) const;
    float extractArgument(std::unordered_set<std::string>& vars, const std::string &def) const;

    void checkAgainstCyclicDependency();
    void addToDependencyChain(cell *cell_ptr);

private:
    std::vector<std::string> def_tokens;
    def_type def_t;

    mutable bool take_current;
    mutable float value;
    spreadsheet *sp_sheet_ptr;
};
