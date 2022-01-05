
// Custom Hash Table Implementation for 
class MovieTable
{
private:
#define SIZE_INDICES 794

    std::list<Movie *> table[SIZE_INDICES];

public:
    int hash(Movie *obj)
    {
        std::string str = (*obj).movie_title;
        int str1;
        int str2;
        if (str.at(0) == 'O')
        {
            return 793;
        }
        try
        {
            return stoi(str.substr(0, 1));
        }
        catch (const std::exception &e)
        {
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

    int hash(std::string str)
    {
        int str1;
        int str2;
        if (str.at(0) == 'O')
        {
            return 793;
        }
        try
        {
            return stoi(str.substr(0, 1));
        }
        catch (const std::exception &e)
        {
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

    /*
    Description:

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
