// Container for year related functions.
class YearTable
{
private:

    /*
        CHOOSING ORDERED VS UNORDERD MAP.
        Ordered Best and Worst Time Complexity = log n (For all operations)
        Unordered Best = O(1)
        Unordered Worst = O(n) 
    
        Unordered worst case depends purely on the implementation of its hash function and how it handles collisions.
        Ordered is most reliable as it always provides logarithmic complexity. However, encountering the worst case
        complexity of unordered is quite unlikely if the data type is of int which provides good hashing.
        Therefore, for string keys, the preferred choice would be to use ordered maps and for integer keys, 
        unordered map seems more reasonable.

        References: https://stackoverflow.com/questions/24154986/what-is-the-worst-case-scenario-for-an-unordered-map
                    https://www.geeksforgeeks.org/map-vs-unordered_map-c/
                    
    */

    // Print a movie given a release year. O(n) print time as finding a year is O(1) here.
    std::unordered_multimap<int, Movie *> u_table;

    // Print movies in order of release years. O(n) print time as years are already sorted in this container.
    std::multimap<int, Movie *> o_table;

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
            int year = (*itr).second.title_year;
            Movie *movieptr = &(*itr).second;

            o_table.insert({year, movieptr});
            u_table.insert({year, movieptr});
        }
    }

    /*
    Description: Prints the years in ascending order. The years already sorted in the ordered multi map.

    Time Complexity:
        -Best Case: O(n)
        -Worst Case: O(n)
    */
    void printByYearAscending()
    {
        int count = 0;
        for (auto itr = o_table.begin(); itr != o_table.end(); itr++)
        {
            std::cout << (*itr).second->movie_title << "|" << (*itr).second->title_year << '\n';
            count++;
        }
        std::cout << "Count: " << count << '\n';
    }

    /*
    Description: Prints the years in Descending order. The years already sorted in the ordered multi map.

    Time Complexity:
        -Best Case: O(n)
        -Worst Case: O(n)
    */
    void printByYearDescending()
    {
        int count = 0;
        for (auto itr = o_table.rbegin(); itr != o_table.rend(); itr++)
        {
            int year = (*itr).second->title_year;
            std::string title = (*itr).second->movie_title;

            if (year == -1)
                std::cout << title << "|"
                          << "N/A" << '\n';
            else
                std::cout << title << "|" << year << '\n';
            count++;
        }
        std::cout << "Count: " << count << '\n';
    }

    /*
    Description: Prints the movies from unordered table released in the year selected by the user. The year (int) is
                 taken as a key and the movie pointers are in the value
    Time Complexity:
        -Best Case: O(1) * O(n)
        -Worst Case: O(1) * O(n)
    */
    void printByYear(int year)
    {
        int count = 0;
        bool flag = false;
        auto its = u_table.equal_range(year);
        for (auto itr = its.first; itr != its.second; itr++)
        {
            flag = true;
            int year = (*itr).second->title_year;
            std::string title = (*itr).second->movie_title;

            if (year == -1)
                std::cout << title << "|"
                          << "N/A" << '\n';
            else
                std::cout << title << "|" << year << '\n';

            count++;
        }
        if (flag)
            std::cout << "Count: " << count << '\n';
        else
            std::cout << "No movies released in the given year are stored in the dataset." << '\n';
        return;
    }
};
