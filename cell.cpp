#include "cell.h"
#include "spreadsheet.h"


cell::cell(const std::string &def, spreadsheet *sp) : take_current(false), value(0), sp_sheet_ptr(sp)
{
    set(def);
}

void cell::set(const std::string &def)
{
    def_t = def_type(split(def, def_tokens));
    take_current = false;
}




float cell::extractArgument(std::unordered_set<std::string>& vars, const std::string &def) const
{
    char *ending = nullptr;
    float converted_value = strtof(def_tokens[0].c_str(), &ending);
    if (*ending != 0)
    {
        auto current_cell = sp_sheet_ptr->getCell(def);
        if(vars.find(def) != vars.end()) throw std::logic_error("Error cyclic dependency");
        vars.insert(def);
        auto res = current_cell.getValue(vars);
        vars.erase(def);
        return res; 
    }
    return converted_value;
    
}

float cell::extractFromExpr(std::unordered_set<std::string>& vars) const
{
    
    auto arg1 = extractArgument(vars, def_tokens[0]);
    auto arg2 = extractArgument(vars, def_tokens[2]);

    switch (def_tokens[1][0])
    {
    case '+':
        return arg1 + arg2;
        break;
    case '-':
        return arg1 - arg2;
        break;
    case '*':
        return arg1 * arg2;
        break;
    case '/':
        return arg1 / arg2;
        break;
    default:
        throw std::logic_error("ERROR: Invalid operator");
        break;
    }
}

float cell::extractSingleValue() const
{
    if (take_current)
        return value;
    char *ending;
    float converted_value = strtof(def_tokens[0].c_str(), &ending);
    if (*ending != 0)
    {
        throw std::logic_error("ERROR: Invalid floating-point literal >> " + def_tokens[0]);
    }
    else
    {
        value = converted_value;
        take_current = true;
        return value;
    }
}

float cell::getValue(std::unordered_set<std::string>& vars) const
{
    float res;
    switch (def_t)
    {
    case single:
        return extractSingleValue();
    case binary_expr:
        return extractFromExpr(vars);
    default:
        throw std::logic_error("ERROR: Non proper number of inputs in definition \n\
                                Accepted form are <number> OR <term> <operator> <term>\n\
                                Where <term> := <number> | <cell name> ");
        break;
    }
}