#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include "Movie.cpp"
// Map Implementation for movies sorted by their names.
class MovieCollection
{
    std::map <std::string, Movie> map;

    //parses string to integer and returns -1 if string is empty
    int stringToInt(std::string str)
    {
        return stoi((str == "") ? ("-1") : (str));
    }

    //parses string to long and returns -1 if string is empty
    long stringToLong(std::string str)
    {
        return atol((str == "") ? ("-1") : (str.c_str()));
    }

    //parses string to float and returns -1 if string is empty
    float stringToFloat(std::string str)
    {
        return stof((str == "") ? ("-1") : (str));
    }

    public:
    //Contructor
    MovieCollection()
    {
          importFromCSV("Data\\IMDB_Top5000-SEECS.csv");
    }
    void importFromCSV(std::string path)
    {
        // File pointer
        std::fstream fin;
        //for storing each row of data 
        std::string line;
        //for storing each field of row
        std::string word;
        //for storing each field of row in array
        std::vector<std::string> row;

        // Open an existing file
        fin.open(path, std::ios::in);
        //ignoring row with only field names 
        getline(fin, line);

        //until the end of file, while loop runs
        while(getline(fin,line))
        {
            //clears row vector in each iteration 
            row.clear();
            //creating movie object for each row
            Movie movie;
            //creating stringstream for each row 
            std::stringstream str(line);

            //for the fileds with "," ignoring "," within that field.  
            if (str.peek() == '"')
            {
                str >> std::quoted(word);
                std::string discard;
                //pushing field values into row vector
                row.push_back(word);
                //discards any string after '"' and before next delimeter i.e ",".
                std::getline(str, discard, ',');
            }else
            {//getting other field values of row.
                while(getline(str,word,','))
                {
                    //pushing in row vector.
                    row.push_back(word);
                }
            }

            //creating stringstream for each genre which will have "|" as a delimeter
            std::stringstream genres(row[1]);
            while(getline(genres, word, '|'))
            {
                //pushing each genre in genre vector of movie object
                movie.genre.push_back(word);
            }

            //creating stringstream for each plot_keyword which will have "|" as a delimeter
            std::stringstream plots(row[18]);
            while(getline(plots, word, '|'))
            {
                //pushing each plot_keyword in plot_keywords vector of movie object
                movie.plot_keywords.push_back(word);
            }
            

            /*
            1) Initiliazing movie fields with extracted fields of csv file.
            2) Setting default value as -1 for empty int and long fields
            3) Setting default value as "" i.e empty string for empty string fields.
            */
            movie.movie_title = row[0];
            movie.title_year = stringToInt(row[2]);
            movie.imdb_score = stringToFloat(row[3]);
            movie.director_name = row[4];
            movie.director_facebook_likes = stringToInt(row[5]);
            movie.num_critic_for_reviews = stringToInt(row[6]);
            movie.duration = stringToInt(row[7]);
            movie.actor_1_name = row[8];
            movie.actor_1_facebook_likes = stringToInt(row[9]);
            movie.actor_2_name = row[10];
            movie.actor_2_facebook_likes = stringToInt(row[11]);
            movie.actor_3_name = row[12];
            movie.actor_3_facebook_likes = stringToInt(row[13]);
            movie.gross = stringToInt(row[14]);
            movie.num_voted_users = stringToInt(row[15]);
            movie.cast_total = stringToInt(row[16]);
            movie.facenumber_in_poster = stringToInt(row[17]);
            movie.movie_imdb_link = row[19];
            movie.num_user_for_reviews = stringToInt(row[20]);
            movie.language = row[21];
            movie.country = row[22];
            movie.content_rating = row[23];
            movie.budget = stringToLong(row[24]);
            movie.aspect_ratio = stringToFloat(row[25]);
            movie.movie_facebook_likes = stringToLong(row[26]);
            movie.color = row[27];

            //creating map with KEY as MOVIE TITLE and VALUE as MOVIE OBJECT.
            this->map.insert({movie.movie_title,movie});
        }
    }
};