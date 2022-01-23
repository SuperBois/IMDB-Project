#include <iterator>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "Movie.cpp"

// Map Implementation for movies sorted by their names. Uses STL multimap.
class MovieCollection
{
    private:
    
    // Parses string to integer and returns -1 if string is empty
    int stringToInt(std::string str)
    {
        return stoi((str == "") ? ("-1") : (str));
    }

    // Parses string to long and returns -1 if string is empty
    long stringToLong(std::string str)
    {
        return atol((str == "") ? ("-1") : (str.c_str()));
    }

    // Parses string to double and returns -1 if string is empty
    double stringToDouble(std::string str)
    {
        return stod((str == "") ? ("-1") : (str));
    }

    public:
    
    std::multimap <std::string, Movie> map;
    // Default Contructor
    MovieCollection()
    {
        importFromCSV("Data\\IMDB_Top5000-SEECS.csv");
    }
    void importFromCSV(std::string path)
    {
        // File pointer
        std::fstream fin;

        // For storing each row of data 
        std::string line;

        // For storing each field of row
        std::string word;
        std::string title;
        // For storing each field of row in array
        std::vector<std::string> row;

        // Open an existing file
        fin.open(path, std::ios::in);

        // Ignoring row with only field names 
        getline(fin, line);

        // Loop runs until we reach EOF (end of file) character
        while(getline(fin,line))
        {
            // Clears row vector in each iteration 
            row.clear();

            // Creating stringstream for each row 
            std::stringstream str(line);

            // For the fileds with "," ignoring "," within that field.  
            if (str.peek() == '"')
            {
                str >> std::quoted(word);
                std::string discard;

                // Pushing field values into row vector
                row.push_back(word);

                // Discards any string after '"' and before next delimeter i.e ",".
                std::getline(str, discard, ',');
            }
            // Getting other field values of row.
            while(getline(str,word,','))
            {
                // Pushing in row vector.
                row.push_back(word);
            }

            /*
            1) Creating movie object with extracted fields of csv file.
            2) Setting default value as -1 for empty int and long fields
            3) Setting default value as "" i.e empty string for empty string fields.
            */
            
            Movie movie( row[0],row[1], stringToInt(row[2]), stringToDouble(row[3]), row[4], stringToInt(row[5]), stringToInt(row[6]),
                         stringToInt(row[7]), row[8], stringToInt(row[9]), row[10], stringToInt(row[11]), row[12], 
                         stringToInt(row[13]), stringToInt(row[14]), stringToInt(row[15]), stringToInt(row[16]), stringToInt(row[17]),row[18], row[19],
                         stringToInt(row[20]), row[21], row[22], row[23], stringToLong(row[24]), stringToDouble(row[25]), stringToLong(row[26]), row[27] );


            // Creating map with KEY as MOVIE TITLE and VALUE as MOVIE OBJECT.
            this->map.insert({movie.movie_title,movie});
        }
    }
};