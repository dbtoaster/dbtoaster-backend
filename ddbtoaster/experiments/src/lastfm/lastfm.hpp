#ifndef DBTOASTER_LASTFM_HPP
#define DBTOASTER_LASTFM_HPP

#include <vector>
#include "types.hpp"
#include "serialization.hpp"

namespace dbtoaster 
{

    struct UserArtists
    {
        DOUBLE_TYPE user;
        DOUBLE_TYPE weight;
        DOUBLE_TYPE artist;

        UserArtists() { }
        
        UserArtists(std::vector<std::string>& fields)
        {
            if (fields.size() < 3) return;
            user = std::stod(fields[0]);
            weight = std::stod(fields[1]);
            artist = std::stod(fields[2]);
        }

        void writeTo(std::ostream& o) 
        {
            write(o, user);
            write(o, weight);
            write(o, artist);
        }

        void readFrom(std::istream& i)
        {
            read(i, user);
            read(i, weight);
            read(i, artist);
        }
    };

    struct UserFriends
    {
        DOUBLE_TYPE user;
        DOUBLE_TYPE friend_;

        UserFriends() { }
        
        UserFriends(std::vector<std::string>& fields)
        {
            if (fields.size() < 2) return;
            user = std::stod(fields[0]);
            friend_ = std::stod(fields[1]);
        }

        void writeTo(std::ostream& o) 
        {
            write(o, user);
            write(o, friend_);
        }

        void readFrom(std::istream& i)
        {
            read(i, user);
            read(i, friend_);
        }        
    };

    struct Degree2
    {
        int deg1;
        int deg2;

        Degree2() { }
        
        Degree2(std::vector<std::string>& fields)
        {
            if (fields.size() < 2) return;
            deg1 = std::stoi(fields[0]);
            deg2 = std::stoi(fields[1]);
        }

        void writeTo(std::ostream& o) 
        {
            write(o, deg1);
            write(o, deg2);
        }

        void readFrom(std::istream& i)
        {
            read(i, deg1);
            read(i, deg2);
        }
    };

    struct Degree1
    {
        int deg1;

        Degree1() { }
        
        Degree1(std::vector<std::string>& fields)
        {
            if (fields.size() < 1) return;
            deg1 = std::stoi(fields[0]);
        }

        void writeTo(std::ostream& o) 
        {
            write(o, deg1);
        }

        void readFrom(std::istream& i)
        {
            read(i, deg1);
        }
    };
}

#endif /* DBTOASTER_LASTFM_HPP */
