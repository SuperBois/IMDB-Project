#include <iostream>
#include <unordered_map>
#include "MovieCollection.cpp"
#include "Actor.cpp"
#include "Director.cpp"
#include "MovieTable.cpp"
#include "GenreRatingMap.cpp"
#include "GenreTable.cpp"
#include "RatingTable.cpp"
#include "YearTable.cpp"

int main()
{
    // Master map that contains titles as keys and movie nodes as values.
    MovieCollection master;

    // Defining objects.
    YearTable year_index;
    RatingTable rating_index;
    GenreTable genre_index;
    GenreRatingMap genre_rating_index;
    Actor actor_index;
    MovieTable movie_index;
    Director director_index;

    // Creating Indices for fast lookup time.
    year_index.createIndex(&master);
    rating_index.createIndex(&master);
    genre_index.createIndex(&master);
    genre_rating_index.createIndex(&master);
    actor_index.createIndex(&master);
    movie_index.createIndex(&master);
    director_index.createIndex(&master);

    /*
        ACTOR RELATED FUNCTIONS.
    */

    // // --------------- Task - 1 ---------------  
    // actor_index.search("Brad Pitt");


    // // --------------- Task - 2 ---------------
    //actor_index.searchCoActors("Johnny Depp");
    

    // // --------------- Task - 3 ---------------
    // actor_index.searchUniqueCoActors("Francesca Capaldi");
    

    // // --------------- Task - 4 ---------------
    // actor_index.printCoActorsOfCoActors("Matt Damon");
    

    // // --------------- Task - 5 ---------------
    // actor_index.areCoActors("Matt Damon", "Igal Naor");


    /*
        DIRECTOR RELATED FUNCTIONS.
    */

    // // --------------- Task - 6 ---------------
    // director_index.search("Zack Snyder");


    // // --------------- Task - 7 ---------------
    // genre_index.printDirectorsOfGenre("Comedy");

    /*
        MOVIE RELATED FUNCTIONS.
    */
    
    // // --------------- Task - 8 ---------------
    // movie_index.printByName("Spider");
    

    // // --------------- Task - 9 ---------------
    // year_index.printByYear(2016);
    

    // // --------------- Task - 10 ---------------
    // year_index.printByYearDescending();
    // year_index.printByYearAscending();


    // // --------------- Task - 11 ---------------
    // genre_index.printByGenre("Action");


    // // --------------- Task - 12 ---------------
    // rating_index.printByRating();
    // rating_index.printByRating(8.4);
    

    // // --------------- Task - 13 ---------------
    // genre_rating_index.printByRating("Action");
    
}