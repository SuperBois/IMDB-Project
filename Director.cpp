#include <list>
#include <map>
#include <iostream>

// Container for storing directors mapped to their movies. Uses STL multimap.
class Director
{
      private:
      std::multimap <std::string, Movie*> map;
      
      public:
      /* 
      Description: This function will get all the movie nodes from movieCollection and will set up multimap for director class.
      
      Time Complexity:
          -Best Case: O(n)
          -Worst Case: O(n)
      */
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
      /* 
      Description: Search and print movies of the given director.
      
      Time Complexity for searching:
          -Best Case: O(logn)
          -Worst Case: O(logn)

      Time Complexity for printing:
          -Best Case: O(n)
          -Worst Case: O(n)
      */
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