#include <string>
#include <vector>
#include <map>

class Movie
{
    public:
    std::string movie_title;
    std::vector<std::string> genre;
    int title_year;
    float imdb_score;
    std::string director_name;
    int director_facebook_likes;
    int num_critic_for_reviews;
    int duration;
    std::string actor_1_name;
    int actor_1_facebook_likes;
    std::string actor_2_name;
    int actor_2_facebook_likes;
    std::string actor_3_name;
    int actor_3_facebook_likes;
    int gross;
    int num_voted_users;
    int cast_total;
    short facenumber_in_poster;
    std::vector<std::string> plot_keywords;
    std::string movie_imdb_link;
    int num_user_for_reviews;
    std::string language;
    std::string country;
    std::string content_rating;
    int budget;
    float aspect_ratio;
    int movie_facebook_likes;
    std::string color;
};


// Map Implementation for movies sorted by their names.
class MovieCollection
{
    std::map <std::string, Movie> map;

    void importFromCSV()
    {
        
    }
};