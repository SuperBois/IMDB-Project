// Container for storing ratings mapped to movies. Custom Implementation of Hash Table. 
class RatingTable
{
    private:
    #define SIZE 101

    // Creating an array of lists. Each list stores pointers to movie nodes.
    std::list<Movie *> table[SIZE];

    // Hash functions.
    int hash(Movie *obj)
    {
        return (int)(obj->imdb_score * 10) % SIZE;
    }

    int hash(double rating)
    {
        return (int)(rating * 10) % SIZE;
    }

    public:
    /*
    Description: Takes as input a pointer to the master array containing movie title as keys
                 and movie nodes as values and creates a multi map with year as keys and values are pointer
                 to movie nodes.

    Time Complexity:
        -Best Case: O(n)
        -Worst Case: O(n)
    */
    void createIndex(MovieCollection *obj)
    {
        std::multimap<std::string, Movie>::iterator itr;
        for (itr = obj->map.begin(); itr != obj->map.end(); itr++)
        {
            // Storing address of the value (movie node) present in map.
            Movie *ptr = &((*itr).second);

            // Hashing this pointer into the array of lists.
            int position = hash(ptr);

            // Insert at head.
            table[position].push_front(ptr);
        }
    }

    /*
    Description: Prints all the movies rating-wise (highest to lowest).
                 Keys are already sorted as we have used in-built multi_map.

    Time Complexity:
        -Best Case: O(n)
        -Worst Case: O(n)
    */
    void printByRating()
    {
        std::list<Movie *>::iterator itr;
        int index = SIZE - 1;
        int count = 0;
        while (index > 0)
        {
            for (itr = table[index].begin(); itr != table[index].end(); itr++)
            {
                std::cout << (*itr)->movie_title << "|" << (*itr)->imdb_score << '\n';
                count++;
            }
            index--;
        }
        std::cout << "Count: " << count;
    }

    /*
    Description: Prints the movies from custom-made container released in the rating selected by the user. The rating (double) is
                 taken as a key and the movie pointers are in the value. Fetching valid key (rating) takes O(1) time.

    Time Complexity:
        -Best Case: O(1) * O(n) = O(n)
        -Worst Case: O(1) * O(n) = O(n)
    */
    void printByRating(double rating)
    {
        std::list<Movie *>::iterator itr;

        // Valid rating
        if (0 <= rating <= 10)
        {
            // Hashed location of list object that is mapped to input rating.
            std::list<Movie *> list_obj = table[hash(rating)];
            
            int count = 0;
            
            // Iterating over the hashed list object.
            for (itr = list_obj.begin(); itr != list_obj.end(); itr++)
            {
                std::cout << (*itr)->movie_title << "|" << (*itr)->imdb_score << '\n';
                count++;
            }
            
            std::cout << "Count: " << count;
            return;
        }
        std::cout << "Invalid Rating" << '\n';
        return;
    }
};
 