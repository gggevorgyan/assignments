#pragma once

#include "cell.h"

#include <unordered_map>


class spreadsheet
{
    public:

        spreadsheet() 
        {
            /* TODO */
            
        }

        double get(const std::string & name) const
        {
            std::unordered_set<std::string> current_vars;

            return getCell(name).getValue(current_vars);
        }

        void set(const std::string & name, const std::string & definition)
        {
            auto r = data.emplace(name, definition, this);
            r.first->second.set(definition);
        }

    private:

        /* TODO */
        std::unordered_map<std::string, cell> data;
        const cell& getCell(const std::string & name)const {
            auto it  =data.find(name); 
            if(it == data.end()){
                throw std::logic_error("ERROR: Undefined reference >> "+name);   
            }
            return it->second;
        }
        
        friend class cell;

};