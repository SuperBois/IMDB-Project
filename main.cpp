#include <iostream>
#include "MovieCollection.cpp"
#include "AVL.cpp"


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

int main()
{
    MovieCollection master;

    Movie movie_1("Phantom","Action|Crime|Drama",1999,8,
    "David Lynch",0,143,112,"Sissy Spacek",874,"Richard Farnsworth",262,
    "Everett McGill",201,6197866,63733,1351,0,"1950s|drug overdose|gang|gang war|new york city",
    "http://www.imdb.com/title/tt0166896/?ref_=fn_tt_tt_1",414,"English",
    "France","G",10000000,2.35,0,"Color");

    Movie movie_2("Taha","Action|Crime|Drama",1999,9,
    "David Lynch",0,143,112,"Sissy Spacek",874,"Richard Farnsworth",262,
    "Everett McGill",201,6197866,63733,1351,0,"1950s|drug overdose|gang|gang war|new york city",
    "http://www.imdb.com/title/tt0166896/?ref_=fn_tt_tt_1",414,"English",
    "France","G",10000000,2.35,0,"Color");

    Movie movie_3("SherazNoob","Action|Crime|Drama",1999,9.7,
    "David Lynch",0,143,112,"Sissy Spacek",874,"Richard Farnsworth",262,
    "Everett McGill",201,6197866,63733,1351,0,"1950s|drug overdose|gang|gang war|new york city",
    "http://www.imdb.com/title/tt0166896/?ref_=fn_tt_tt_1",414,"English",
    "France","G",10000000,2.35,0,"Color");
    
    MovieAVL obj;
    obj.insert(movie_1);
    obj.insert(movie_2);

    // Name | Year | Rating is the print format.
    obj.print();

    obj.insert(movie_3);
    obj.print();
    obj.remove(movie_3);
}