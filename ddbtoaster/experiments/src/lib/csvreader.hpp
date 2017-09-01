#ifndef DBTOASTER_CSVREADER_HPP
#define DBTOASTER_CSVREADER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace dbtoaster {
        
    class CSVAdaptor
    {
        public:
            CSVAdaptor(char del) : delimiter(del) { }

            std::string const& operator[](std::size_t index) const
            {
                return data[index];
            }

            std::size_t size() const
            {
                return data.size();
            }

            void readNextRow(std::istream& str)
            {
                data.clear();
        
                std::string line;
                std::getline(str, line);

                std::stringstream lineStream(line);
                std::string cell;

                while (std::getline(lineStream, cell, delimiter))
                {
                    data.push_back(cell);
                }
            }

            std::vector<std::string> data;

        private:
            char delimiter;
    };

    std::istream& operator>>(std::istream& str, CSVAdaptor& data)
    {
        data.readNextRow(str);
        return str;
    }   

    template <typename T>
    void readFromFile(std::vector<T>& data, const std::string& path, char delimiter)
    {            
        data.clear();
        
        std::ifstream file(path);

        CSVAdaptor row(delimiter);
        while (file >> row)
        {
            T tmp(row.data);
            data.push_back(tmp);
        }

        file.close();
    }

    template <typename T>
    void readFromBinaryFile(std::vector<T>& data, const std::string& path)
    {                        
        data.clear();

        std::ifstream file(path, std::ios::in | std::ios::binary);

        size_t length;
        file.read((char*) &length, sizeof(size_t));    
        data.reserve(length);

        T tmp;
        for (size_t i = 0; i < length; i++) 
        {
            tmp.readFrom(file);
            data.push_back(tmp);
        }

        file.close();
    }

    template <typename T>
    void writeToBinaryFile(std::vector<T>& data, const std::string& path)
    {
        std::ofstream file(path, std::ios::out | std::ios::binary);

        size_t length = data.size();
        file.write((char*) &length, sizeof(size_t));
        for (T t : data) t.writeTo(file);

        file.close();
    }
}

#endif /* DBTOASTER_CSVREADER_HPP */
