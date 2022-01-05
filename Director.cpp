#include <list>
#include <map>
#include <iostream>

// Container for storing directors mapped to their movies. Uses STL multimap.
class Director
{
      private:
      std::multimap <std::string, Movie*> map;
      
      public:
      void createIndex(MovieCollection* obj)
      {
            std::multimap<std::string, Movie*>::iterator itr;

            for (auto &pr :obj->map)
            {
                  // Returns movie pointer
                  Movie* ptr = &pr.second;
                  
                  // Mapping movie object pointers against there directors
                  this->map.insert({(*ptr).director_name,ptr});
            }
      }

      void search(std::string directorName)
      {
            // Returns all the movies of given director in log(n) time
            auto it = this->map.equal_range(directorName);
            
            std::cout<<"Director Name : " << (it.first)->first<< '\n'<<"\t\tMOVIES\n ";
            
            // Printing the movies
            for (auto itr = it.first; itr != it.second; ++itr) 
            {
                std::cout<< (*itr->second).movie_title << '\n';
            }
      }

};