// Container for storing genre wise movies sorted by their ratings. Uses STL multimap and map.
class GenreRatingMap
{
private:
    std::map<std::string, std::multimap<double, Movie *>> table;

public:
    /*
    Description: Takes as input a pointer to the master array containing genre as keys
                 and a multi map as values whose keys are ratings and movie nodes as
                 values

    Time Complexity:
        -Best Case: O(n)
        -Worst Case: O(n * m) where m are the number of genres a movie has.
    */
    void createIndex(MovieCollection *obj)
    {
        std::multimap<std::string, Movie>::iterator itr;
        for (itr = obj->map.begin(); itr != obj->map.end(); itr++)
        {
            std::vector<std::string> genres = (*itr).second.genre;
            double rating = (*itr).second.imdb_score;
            Movie *movie = &(*itr).second;

            for (std::string genre : genres)
            {
                if (table.count(genre) == 0)
                {
                    std::multimap<double, Movie *> rating_map;
                    rating_map.insert({rating, movie});
                    table.insert({genre, rating_map});
                }
                else
                    table.find(genre)->second.insert({rating, movie});
            }
        }
    }

    /*
    Description: Prints the movies rating-wise (highest to lowest) from the genre selected by the user.

    Time Complexity:
        Finding genre is constant time operation not log(n) search usually associated with maps.
        Reason: Genres of a movie never scale. A movie has fixed amount of genres. Total number of
                genres in the dataset are 26 and it is intuitive that genres won't ever get large.
                So, finding genres is actually a constant time operation.
        
        -Best Case: O(1) * O(n) = O(n)
        -Worst Case: O(1) * O(n) = O(n)
    */
    void printByRating(std::string genre)
    {
        auto its = table.find(genre);
        int count = 0;
        bool flag = false;

        for (auto itr = its->second.begin(); itr != its->second.end(); itr++)
        {
            flag = true;
            std::string genre = its->first;
            double rating = (*itr).second->imdb_score;
            std::string title = (*itr).second->movie_title;
            std::cout << title << "|" << genre << "|" << rating << '\n';
            count++;
        }
        if (flag)
            std::cout << "Count: " << count << '\n';
        else
            std::cout << "Genre does not exist." << '\n';
        return;
    }
};
