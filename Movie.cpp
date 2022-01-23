#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>

class Movie
{
    public:
    std::string movie_title;
    std::vector<std::string> genre;
    int title_year;
    double imdb_score;
    std::string director_name;
    int director_facebook_likes;
    int num_critic_for_reviews;
    int duration;
    std::string actors[3];
    int actor_facebook_likes[3];
    int gross;
    int num_voted_users;
    int cast_total;
    int facenumber_in_poster;
    std::vector<std::string> plot_keywords;
    std::string movie_imdb_link;
    int num_user_for_reviews;
    std::string language;
    std::string country;
    std::string content_rating;
    int budget;
    double aspect_ratio;
    int movie_facebook_likes;
    std::string color;

    // Default constructor
    Movie(){}

    // Overloaded constructor. Accepts 28 fields related to each movie.
    Movie(std::string movie_title,std::string genre,int title_year,
    double imdb_score,std::string director_name,int director_facebook_likes,
    int num_critic_for_reviews,int duration,std::string actor_1_name,
    int actor_1_facebook_likes,std::string actor_2_name,int actor_2_facebook_likes,
    std::string actor_3_name,int actor_3_facebook_likes,int gross,int num_voted_users,
    int cast_total,int facenumber_in_poster,std::string plot_keywords,std::string movie_imdb_link,
    int num_user_for_reviews,std::string language,std::string country,std::string content_rating,
    long budget,double aspect_ratio,long movie_facebook_likes,std::string color)
    {
        std::string word;
        this->movie_title = movie_title;

        // Creating stringstream for each genre which will have "|" as a delimeter
        std::stringstream str(genre);
        
        while(getline(str,word,'|'))
        {
            // Pushing each genre in genre vector of movie object
            this->genre.push_back(word);
        }
        this->title_year = title_year;
        this->imdb_score = imdb_score;
        this->director_name = director_name;
        this->director_facebook_likes = director_facebook_likes;
        this->num_critic_for_reviews = num_critic_for_reviews;
        this->duration = duration;
        this->actors[0] = actor_1_name;
        this->actor_facebook_likes[0] = actor_1_facebook_likes;
        this->actors[1] = actor_2_name;
        this->actor_facebook_likes[1] = actor_2_facebook_likes;        
        this->actors[2] = actor_3_name;
        this->actor_facebook_likes[2] = actor_3_facebook_likes;
        this->gross = gross;
        this->num_voted_users = num_voted_users;
        this->cast_total = cast_total;
        this->facenumber_in_poster = facenumber_in_poster;

        // Creating stringstream for each plot_keyword which will have "|" as a delimeter
        std::stringstream plot_words(plot_keywords);
        while(getline(plot_words,word,'|'))
        {
            // Pushing each plot_keyword in plot_keywords vector of movie object
            this->plot_keywords.push_back(word);
        }
        this->movie_imdb_link = movie_imdb_link;
        this->num_user_for_reviews = num_user_for_reviews;
        this->language = language;
        this->country = country;
        this->content_rating = content_rating;
        this->budget = budget;
        this->aspect_ratio = aspect_ratio;
        this->movie_facebook_likes = movie_facebook_likes;
        this->color = color;
        
    }

    std::string toString()
    {
        return movie_title + "|" + std::to_string(title_year) + "|" + std::to_string(imdb_score);
    }
};