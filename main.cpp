#include <iostream>
#include "MovieCollection.cpp"
#include "AVL.cpp"
#include <list>
#include <unordered_map>

class MovieAVL:public AVL<Movie>
{
    // Insert into AVL on basis of movie ratings.
    virtual int compare(Movie movie1, Movie movie2)
    {
        if (movie1.imdb_score == movie2.imdb_score) return 0;
        else if (movie1.imdb_score < movie2.imdb_score) return -1;
        return 1;
    }

};

// Search movies released in a given year
class YearTable
{
    private:
    // If i were to do it properly i.e., user filters out a year and provides a title, then would've used this.
    // std::unordered_map<int, std::multimap<string, Movie*>> table;
    
    // Print a movie given a release year. O(n) print time as finding a year is O(1) here.
    std::unordered_multimap<int, Movie*> u_table;

    // Print movies in order of release years. O(n) print time as years are already sorted in this container.
    std::multimap<int, Movie*> o_table;

    public:
    void createIndex(MovieCollection* obj)
    {
        std::multimap<std::string, Movie>::iterator itr;
        for (itr = obj->map.begin(); itr != obj->map.end(); itr++)
        {
            int year = (*itr).second.title_year;
            Movie* movieptr = &(*itr).second;
            // The proper way.
            // table.insert(year, createMap(year));
            o_table.insert({year, movieptr});
            u_table.insert({year, movieptr});
        }
        
    }

    // Years are already sorted in ordered_multimap. Print takes O(n) best, average and worst time.
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

    // Years are already sorted in ordered_multimap. Print takes O(n) best, average and worst time.
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


    // Fetching a year from unordered table takes O(1) time. Print takes O(n) time.
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


// Print movies Rating-wise
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