// Custom Hash Table Implementation for 
class MovieTable
{
private:
// 26 alphabets, 10 digits and one special character '#' from which movie titles begin.
/* Each of the 26 alphabet and '#' is mapped to the second character which can again be another alphabet, or a dot,
    or a comma, or a colon.

    In total, possibilities for first two characters of a movie title 
            = 27 (alphabets + '#') * 29 (alphabets +' ,' + '.' + ':') + 10 (digits) = 793 possibilities.
    
    One index is left out for movies that begin with non-ascii, unicode, or other special characters.
*/
#define SIZE_INDICES 794

    std::list<Movie *> table[SIZE_INDICES];

public:

    /*
    Description: Accepts a movie pointer and hashes based on the first two characters of the movie title.
                 The returned index is then used to insert into the linked list object present at that index.

    Time Complexity:
        -Best Case: O(1)
        -Worst Case: O(1)
    */

int hash(std::string str)
    {
        int str1;
        int str2;
        if (str.at(0) == 'O')
        {
            return 793;
        }
        // If first alphabet of str is digit, then it is returned as index.
        try
        {
            return stoi(str.substr(0, 1));
        }
        // Else there is alphabets or special characters in first two alphabets
        catch (const std::exception &e)
        {   
            /* 
               If character at position 0 or 1 is other then a-z , ',' , ':' , '.'
               then 793 index is returned.
               Else the first two alphabets are hashed based on their ascii values.
            */
            if ((97 <= (int(tolower(str.at(0)))) && (int(tolower(str.at(0)))) <= 122 || str.at(0) == '#') && (97 <= (int(tolower(str.at(1)))) && (int(tolower(str.at(0)))) <= 122 || str.at(1) == ',' || str.at(1) == ':' || str.at(1) == '.'))
            {
                if (str.at(0) == '#')
                    str1 = 26;
                else
                    str1 = int(tolower(str.at(0))) - 97;

                if (str.at(1) == ',')
                    str2 = 26;
                else if (str.at(1) == ':')
                    str2 = 27;
                else if (str.at(1) == '.')
                    str2 = 28;
                else
                    str2 = (int(tolower(str.at(1))) - 97);

                return ((str1 * 29) + str2) + 10;
            }
            else
                return 793;
        };
    }


    // Overloaded hash function that accepts movie title as input.
    
    int hash(Movie* obj)
    {
        return hash((*obj).movie_title);
    }

    /*
    Description: Accepts a pointer to the master array containing movie nodes and inserts movie pointers into the
                 created table at hashed locations returned from hash function.

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
    Description: Prints movies given a partial name or a complete name.

    Time Complexity:
        Index into which the movie can be located is found in O(1) constant time through hash function.

        -Best Case: O(1) . O(n)
        -Worst Case: O(1) . O(n)
    */

    void printByName(std::string name)
    {
        std::list<Movie *>::iterator itr;
        std::list<Movie *> list_obj = table[hash(name)];

        std::string substring = name.substr(2);
        int count = 0;
        for (itr = list_obj.begin(); itr != list_obj.end(); itr++)
        {
            if (substring == (*itr)->movie_title.substr(2,substring.length()))
            {
                std::cout<<(*itr)->movie_title<<std::endl;
                count++;
            }
        }
        std::cout << "Count: " << count;
    }
};
