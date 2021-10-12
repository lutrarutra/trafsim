#pragma once
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
namespace ts
{
class CsvRow
{
    public:
        std::string const& operator[](std::size_t index) const;
        std::size_t size() const;
        void readNextRow(std::istream& str);
    private:
        std::vector<std::string>    m_data;
};

std::istream& operator>>(std::istream& str, CsvRow& data);
}
