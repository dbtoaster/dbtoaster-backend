#ifndef DBTOASTER_LASTFM_TEMPLATE_HPP
#define DBTOASTER_LASTFM_TEMPLATE_HPP

#include "stopwatch.hpp"
#include "csvreader.hpp"
#include "lastfm.hpp"

using namespace std;

const string dataPath = "datasets/lastfm-q1-normalised";
const string dataset = "";

namespace dbtoaster 
{
    class data_t;

    std::vector<UserArtists> userArtists;
    std::vector<UserFriends> userFriends;
    std::vector<Degree1> degree1;
    std::vector<Degree2> degree2;

    void load_relations()
    {
        Stopwatch sw;

        sw.restart();
        userArtists.clear();
        readFromFile(userArtists, dataPath + "/" + dataset + "/Userartists.tbl", '|');
        sw.stop();
        std::cout << "Loaded UserArtists (" << userArtists.size() << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;

        sw.restart();        
        userFriends.clear();
        readFromFile(userFriends, dataPath + "/" + dataset + "/Userfriends.tbl", '|');
        sw.stop();
        std::cout << "Loaded UserFriends (" << userFriends.size() << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;

        sw.restart();
        degree1.clear();
        readFromFile(degree1, dataPath + "/" + dataset + "/Degree1.tbl", '|');
        sw.stop();
        std::cout << "Loaded Degree1 (" << degree1.size() << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;

        sw.restart();
        degree2.clear();
        readFromFile(degree2, dataPath + "/" + dataset + "/Degree2.tbl", '|');
        sw.stop();
        std::cout << "Loaded Degree2 (" << degree2.size() << ")... " << sw.elapsedTimeInMilliSeconds() << " ms" << std::endl;
    }

    void destroy_relations()
    {
        userArtists.clear();
        userFriends.clear();
        degree1.clear();
        degree2.clear();
    }

    #define INSERT_USER_ARTISTS {           \
        data.on_insert_UserArtists(         \
            userArtists[i].user,            \
            userArtists[i].weight,          \
            userArtists[i].artist); }

    #define INSERT_USER_FRIENDS {           \
        data.on_insert_UserFriends(         \
            userFriends[i].user,            \
            userFriends[i].friend_); }

    #define INSERT_DEGREE1 { data.on_insert_Degree1(degree1[i].deg1); }
    #define INSERT_DEGREE2 { data.on_insert_Degree2(degree2[i].deg1, degree2[i].deg2); }

    void process_tables(dbtoaster::data_t& data) 
    {
        for (size_t i = 0; i < userFriends.size(); i++) 
        {   
            INSERT_USER_FRIENDS
        }

        for (size_t i = 0; i < userArtists.size(); i++) 
        {
            INSERT_USER_ARTISTS
        }

        for (size_t i = 0; i < degree1.size(); i++) 
        {
            INSERT_DEGREE1
        }

        for (size_t i = 0; i < degree2.size(); i++) 
        {
            INSERT_DEGREE2
        }
    }

    void process_streams(dbtoaster::data_t& data)
    { 
        // size_t i = 0, count = 0;

        // count = userFriends.size();
        // for (; i < count; i++) 
        // {   
        //     INSERT_USER_ARTISTS
        //     INSERT_USER_FRIENDS
        // }
        
        // count = userArtists.size();
        // for (; i < count; i++) 
        // {
        //     INSERT_USER_ARTISTS
        // }    
    }

    void print_result(dbtoaster::data_t& data)
    {
        data.serialize(std::cout, 0);
    }
}

#endif /* DBTOASTER_LASTFM_TEMPLATE_HPP */
