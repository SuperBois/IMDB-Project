#include <list>
#include <map>
#include <iostream>
#include "MovieCollection.cpp"

class Director
{
      public:

      std::multimap <std::string, Movie*> map;


      void importFromMovieCollection(MovieCollection* obj)
      {
            std::multimap<std::string, Movie*>::iterator itr;

            for (auto &pr :obj->map)
            {
                  //returns movie pointer
                  Movie* ptr = &pr.second;
                  //mapping movie object pointers against there directors
                  this->map.insert({(*ptr).director_name,ptr});
            }
      }

      void search(std::string directorName)
      {
            //returns all the movies of given director in log(n) time
            auto it = this->map.equal_range(directorName);
            std::cout<<"Director Name : " << (it.first)->first<< '\n'<<"\t\tMOVIES\n ";
            //printing the movies
            for (auto itr = it.first; itr != it.second; ++itr) 
            {
                std::cout<< (*itr->second).movie_title << '\n';
            }
      }
};