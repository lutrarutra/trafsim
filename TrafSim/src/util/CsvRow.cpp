#include "CsvRow.hpp"
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


namespace ts
{

std::string const& CsvRow::operator[](std::size_t index) const
{
    return m_data[index];
}

std::size_t CsvRow::size() const
{
    return m_data.size();
}
void CsvRow::readNextRow(std::istream& str)
{
    std::string         line;
    std::getline(str, line);

    std::stringstream   lineStream(line);
    std::string         cell;

    m_data.clear();
    while(std::getline(lineStream, cell, ','))
    {
        m_data.push_back(cell);
    }
    // This checks for a trailing comma with no data after it.
    if (!lineStream && cell.empty())
    {
        // If there was a trailing comma then add an empty element.
        m_data.push_back("");
    }
}



std::istream& operator>>(std::istream& str, CsvRow& data)
{
    data.readNextRow(str);
    return str;
} 
}
