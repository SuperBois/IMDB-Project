#include <iostream>
#include "MovieCollection.cpp"
#include <list>
#include <unordered_map>


// Container for year related functions.
class YearTable
{
    private:
    
    // Print a movie given a release year. O(n) print time as finding a year is O(1) here.
    std::unordered_multimap<int, Movie*> u_table;

    // Print movies in order of release years. O(n) print time as years are already sorted in this container.
    std::multimap<int, Movie*> o_table;

    public:
    /*
    Description: Takes as input a pointer to the master array containing movie title as keys 
                 and movie nodes as values and creates a multi map with year as keys and pointer 
                 movie nodes 

    Time Complexity: 
        -Best Case: O(n)
        -Worst Case: O(n)
    */
    void createIndex(MovieCollection* obj)
    {
        std::multimap<std::string, Movie>::iterator itr;
        for (itr = obj->map.begin(); itr != obj->map.end(); itr++)
        {
            int year = (*itr).second.title_year;
            Movie* movieptr = &(*itr).second;

            o_table.insert({year, movieptr});
            u_table.insert({year, movieptr});
        }
        
    }

    /*
    Description: Prints the years in ascending order. The years already sorted in the ordered multi map

    Time Complexity: 
        -Best Case: O(n)
        -Worst Case: O(n)
    */
    void printByYearAscending()
    {
        int count = 0;
        for (auto itr = o_table.begin(); itr != o_table.end(); itr++)
        {
            std::cout << (*itr).second -> movie_title << "|" << (*itr).second -> title_year << '\n';
            count++;
        }
        std::cout << "Count: " << count << '\n';
    }

    /*
    Description: Prints the years in Descending order. The years already sorted in the ordered multi map

    Time Complexity: 
        -Best Case: O(n)
        -Worst Case: O(n)
    */
    void printByYearDescending()
    {
        int count = 0;
        for (auto itr = o_table.rbegin(); itr != o_table.rend(); itr++)
        {
            int year = (*itr).second -> title_year;
            std::string title = (*itr).second -> movie_title;

            if (year == -1)
                std::cout << title << "|" << "N/A" << '\n';
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
            int year = (*itr).second -> title_year;
            std::string title = (*itr).second -> movie_title;

            if (year == -1)
                std::cout << title << "|" << "N/A" << '\n';
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


class RatingTable
{
    private:
    #define SIZE 101

    // Creating an array of lists. Each list stores pointers to movie nodes.
    std::list<Movie*> table[SIZE];
    

    // Hash functions.
    int hash(Movie* obj)
    {
        return (int) (obj -> imdb_score * 10) % SIZE;
    }

    int hash(double rating)
    {
        return (int) (rating * 10) % SIZE;
    }

    public:

    // Create an index from the master array containing movies sorted by their ratings.
    /*
    Description: Takes as input a pointer to the master array containing movie title as keys 
                 and movie nodes as values and creates a multi map with year as keys and pointer 
                 movie nodes 

    Time Complexity: 
        -Best Case: O(n)
        -Worst Case: O(n)
    */
    void createIndex(MovieCollection* obj)
    {
        std::multimap<std::string, Movie>::iterator itr;
        for (itr = obj->map.begin(); itr != obj->map.end(); itr++)
        {
            // Storing address of the value (movie node) present in map.
            Movie* ptr = &((*itr).second);

            // Hashing this pointer into the array of lists.
            int position = hash(ptr);

            // Insert at head.
            table[position].push_front(ptr);
        }
    }

    // Print all movies in order of highest rating to lowest.

    /*
    Description: Prints all the movies rating-wise (highest to lowest)
    Time Complexity: 
        -Best Case: O(n)
        -Worst Case: O(n)
    */
    void printByRating()
    {
        std::list<Movie*>::iterator itr;
        int index = SIZE - 1;
        int count = 0;
        while (index > 0)
        {
            for (itr = table[index].begin(); itr != table[index].end(); itr++)
            {
                std::cout << (*itr) -> movie_title << "|" << (*itr) -> imdb_score << '\n';
                count++;
            }
            index--;
        }
        std::cout << "Count: " << count;
    }
    // Print all movies of a given rating.

    /*
    Description: Prints the movies from custom-made container released in the rating selected by the user. The rating (double) is 
                 taken as a key and the movie pointers are in the value. Fetching valid key (rating) takes O(1) time.
    Time Complexity: 
        -Best Case: O(1) * O(n)
        -Worst Case: O(1) * O(n)
    */
    void printByRating(double rating)
    {
        std::list<Movie*>::iterator itr;
        if (0 <= rating <= 10)
        {
            std::list<Movie*> list_obj = table[hash(rating)];
            int count = 0;
            for (itr = list_obj.begin(); itr != list_obj.end(); itr++)
            {
                std::cout << (*itr) -> movie_title << "|" << (*itr) -> imdb_score << '\n';
                count++;
            }
            std::cout << "Count: " << count;
            return;
        }
        std::cout << "Invalid Rating" << '\n';
        return;
    }
};


class GenreTable
{
    private:
    std::multimap<std::string, Movie*> table;
    

    public:
    /*
    Description: Takes as input a pointer to the master array containing movie title as keys 
                 and movie nodes as values and creates a multi map with year as keys and pointer 
                 movie nodes 

    Time Complexity: 
        -Best Case: O(n)
        -Worst Case: O(n)
    */
    void createIndex(MovieCollection* obj)
    {
        std::multimap<std::string, Movie>::iterator itr;
        for (itr = obj->map.begin(); itr != obj->map.end(); itr++)
        {
            std::vector<std::string> genres = (*itr).second.genre;
            Movie* movie = &(*itr).second;

            // Map each movie pointer to its respective genres.
            for (std::string genre : genres)
                table.insert({genre, movie});
        }
        
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
            std::cout << (*itr).second -> movie_title << "|" << (*itr).first << '\n';
            count++;
        }
        if (flag) std::cout << "Count: " << count << '\n';
        else std::cout << "Genre does not exist." << '\n';
        return;
    }

};

class GenreRatingTable
{
    private:
    std::map<std::string, std::multimap<double, Movie*>> table;
    public:
    /*
    Description: Takes as input a pointer to the master array containing genre as keys 
                 and a multi map as values whose keys are ratings and movie nodes as 
                 values

    Time Complexity: 
        -Best Case: O(n)
        -Worst Case: O(n^2)
    */
    void createIndex(MovieCollection* obj)
    {
        std::multimap<std::string, Movie>::iterator itr;
        for (itr = obj->map.begin(); itr != obj->map.end(); itr++)
        {
            std::vector<std::string> genres = (*itr).second.genre;
            double rating = (*itr).second.imdb_score;
            Movie* movie = &(*itr).second;

            for (std::string genre: genres)
            {
                if (table.count(genre) == 0)
                {
                    std::multimap<double, Movie*> rating_map;
                    rating_map.insert({rating, movie});
                    table.insert({genre, rating_map});
                }
                else
                    table.find(genre)->second.insert({rating, movie});
            }

   
        }
    }

    // Finding genre is constant time. Never more than 5 steps. O(1) find time, then O(n) print time.

    /*
    Description: Prints the movies rating-wise (highest to lowest) from the genre selected by the user
    Time Complexity: 
        -Best Case: O(1) * O(n)
        -Worst Case: O(1) * O(n)
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
        if (flag) std::cout << "Count: " << count << '\n';
        else std::cout << "Genre does not exist." << '\n';
        return;
    }
};

int main()
{
    // Master map that contains titles as keys and movie nodes as values.
    MovieCollection master;


    YearTable obj1;
    obj1.createIndex(&master);
    // obj1.printByYearDescending();
    // obj1.printByYear(2016);

    // Rating index. Movie pointers are inserted sorted by their ratings.
    RatingTable obj2;

    // Import data from the master array into the index.
    obj2.createIndex(&master);

    // // Print movies of a given rating.
    obj2.printByRating(9.3);

    // // Print movies in order of decreasing ratings.
    // obj2.printByRating();
    GenreTable obj3;
    obj3.createIndex(&master);
    // obj3.printByGenre("Romance");

    GenreRatingTable obj4;
    obj4.createIndex(&master);
    // obj4.printByRating("Action");
    
}