
class GenreTable
{
private:
    std::multimap<std::string, Movie *> table;

public:
    /*
    Description: Takes as input a pointer to the master array containing movie title as keys
                 and movie nodes as values and creates a multi map with year as keys and pointer
                 movie nodes

    Time Complexity:
        -Best Case: O(n)
        -Worst Case: O(n)
    */
    void createIndex(MovieCollection *obj)
    {
        std::multimap<std::string, Movie>::iterator itr;
        for (itr = obj->map.begin(); itr != obj->map.end(); itr++)
        {
            std::vector<std::string> genres = (*itr).second.genre;
            Movie *movie = &(*itr).second;

            // Map each movie pointer to its respective genres.
            for (std::string genre : genres)
                table.insert({genre, movie});
        }
    }

    /*
    Description: Prints the directors given a movie genre.

    Time Complexity: Searching genres takes constant time instead of logn which is usually associated with maps.
        
        Reason: Genres of a movie never scale. A movie has fixed amount of genres. Total number of
                genres in the dataset are 26 and it is intuitive that genres won't ever get large.
                So, finding genres is actually a constant time operation.

        -Best Case: O(1) * O(n) = O(n)
        -Worst Case: O(1) * O(n) = O(n)
    */

    void printDirectorsOfGenre(std::string genre)
    {
        auto its = table.equal_range(genre);
        int count = 0;
        bool flag = false;
        for (auto itr = its.first; itr != its.second; itr++)
        {
            flag = true;
            std::cout << (*itr).second->movie_title << "|" << (*itr).first
                      << "|" << (*itr).second->director_name << '\n';
            count++;
        }
        if (flag)
            std::cout << "Count: " << count << '\n';
        else
            std::cout << "Genre does not exist." << '\n';
        return;
    }

    /*
    Description: Prints the movies genre-wise. Search from multi-map in this case is done in constant steps not log(n)
                 time as genres of a movie never scale. They remain a fixed number.

    Time Complexity:
        -Best Case: O(1) * O(n) = O(n)
        -Worst Case: O(1) * O(n) = O(n)
    */
    void printByGenre(std::string genre)
    {
        auto its = table.equal_range(genre);
        int count = 0;
        bool flag = false;
        for (auto itr = its.first; itr != its.second; itr++)
        {
            flag = true;
            std::cout << (*itr).second->movie_title << "|" << (*itr).first << '\n';
            count++;
        }
        if (flag)
            std::cout << "Count: " << count << '\n';
        else
            std::cout << "Genre does not exist." << '\n';
        return;
    }
};

