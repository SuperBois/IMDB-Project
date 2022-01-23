#include <list>
#include <iostream>

struct Profile
{     // This struct will maintain year wise movies of actor and also its co-actors.
      std::multimap<int,Movie*> yearWiseMap;
      std::map<std::string,std::list<Movie*> > co_actorMap;
};

// Container for storing Actors mapped to their profiles. Uses STL maps.
class Actor
{
      private:

            // Mapping from string to profile struct
            std::map <std::string,Profile> map;

            void createProfile(Movie* ptr, int index)
            {
                  // If actor is not in map already, then a new mapping is created from actor name to profile
                  // Setting list of pointers of movies 
                  std::list<Movie*> ptrs;
                  ptrs.push_back(ptr);

                  // Making new profile
                  Profile profile;
                  // Inserting year wise in profile map to maintain chronological order
                  profile.yearWiseMap.insert({(*ptr).title_year,ptr});
                  /* Inserting co-actors name and the linked list of pointers
                        in which both actor and its co-actors have worked*/

                  for (int ind = 0; ind < 3; ind++)
                  {
                        if(index != ind)
                              profile.co_actorMap.insert({(*ptr).actors[ind],ptrs});
                  }
                  this->map.insert({(*ptr).actors[index],profile});
            }

            void updateProfile(Movie* ptr,int index)
            {
                  // If actor is already present as key in map, then its profile is updated.
                  // Finding profile of actor  
                  auto it = this->map.find((*ptr).actors[index]);
                  // Inserting year and movie pointer in profile map. 
                  it->second.yearWiseMap.insert({(*ptr).title_year,ptr});

                  for (int ind = 0; ind < 3; ind++)
                  {
                        if(index != ind)
                        {
                              // If co-actor is not in co-actor map, a new mapping from co-actor to linked list is made.
                              if (it->second.co_actorMap.count((*ptr).actors[ind]) == 0 && (*ptr).actors[ind] != "")
                              {
                                    std::list<Movie*> ptrs;
                                    ptrs.push_back(ptr);
                                    it->second.co_actorMap.insert({(*ptr).actors[ind],ptrs});
                              }
                              /* If there is a co-actor already present in co-actorMap,
                              then the movie is inserted in the linked list of that co-actor*/
                              else if ((*ptr).actors[ind] != "")
                                    it->second.co_actorMap.at((*ptr).actors[ind]).push_back(ptr);   
                        }
                  }
            }

      public:

      /* 
      Description: This function will get all the movie nodes from movieCollection and will set up profile struct.
      
      Time Complexity:
          -Best Case: O(n)
          -Worst Case: O(n)
      */
      void createIndex(MovieCollection* obj)
      {
            // Iterating through all the movie nodes and maintaing profile
            for (auto &pr :obj->map)
            {
                  // Returns movie pointer
                  Movie* ptr = &pr.second;

                  for (int index = 0; index < 3; index++)
                  {
                        if (this->map.count((*ptr).actors[index]) == 0 && (*ptr).actors[index] != "")  
                              createProfile(ptr,index);
                        
                        else if ((*ptr).actors[index] != "")
                              updateProfile(ptr,index);
                  }
            }
      }

      /* 
      Description: Search and print movies of the given actor.
      
      Time Complexity for searching:
          -Best Case: O(logn)
          -Worst Case: O(logn)
      Time Complexity for printing:
          -Best Case: O(n)
          -Worst Case: O(n)
      */
      void search(std::string actorName)
      {
            // Returns all the movie pointers of given actor in log(n) time
            auto it = this->map.find(actorName);
            std::cout<<"Actor Name : " << it->first<< '\n'<<"\t\tMOVIES\n\n";

            // Printing the movies
            for (auto &pr :it->second.yearWiseMap)
            {
                  std::cout<<"Movie name : "<<(*pr.second).movie_title<<"  |  "<<"Year : "<<pr.first<<std::endl;
            }
      }
      
      /* 
      Description: Search and print movies and co actors of the given actor.
      
      Time Complexity for searching:
          -Best Case: O(logn)
          -Worst Case: O(logn)
      Time Complexity for printing:
          -Best Case: O(n)
          -Worst Case: O(n)
      */
      void searchCoActors(std::string actorName)
      {
            //returns all the movie pointers of given actor in log(n) time
            auto it = this->map.find(actorName);
            std::cout<<"Actor Name : " << it->first<< '\n'<<"\t\tMOVIES\n\n";
            //printing the movies
            for (auto &pr :it->second.yearWiseMap)
            {
                  std::cout<<"Movie : "<<(*pr.second).movie_title<<"  |  "<<"Year : "<<pr.first<<"  |   Co-Actors : ";
                  for (int index = 0;index < 3; index++)
                  {
                        if ((*pr.second).actors[index] != actorName )
                              std::cout<<(*pr.second).actors[index]<<" | ";
                  }

                  std::cout<<std::endl;
            }
      }

      /* 
      Description: Searches and prints unique co-actors of given actor and its movies
      
      Time Complexity for searching:
          -Best Case: O(logn)
          -Worst Case: O(logn)
      Time Complexity for printing:
          -Best Case: O(n2)
          -Worst Case: O(n2)
      */
      void searchUniqueCoActors(std::string actorName)
      {
            auto it = this->map.find(actorName);
            std::cout<<"Actor Name : " << it->first<< "\n\n"<< "CO-ACTORS\t\tMOVIE\t\t\t\t\t\t\tYEAR\n\n";
             
            for (auto &pr :it->second.co_actorMap)
            {
                  std::cout<<pr.first;

                  for (auto &pr2: pr.second)
                  {
                        std::cout<<"\t\t"<<(*pr2).movie_title<<"\t\t\t\t\t\t\t"<<(*pr2).title_year<<"\n";
                  }
            }
      }

      /* 
      Description: Searches and prints the co-actors of co_actors of given actor
      
      Time Complexity for searching:
          -Best Case: O(logn)
          -Worst Case: O(logn)
      Time Complexity for printing:
          -Best Case: O(n2)
          -Worst Case: O(n2)
      */
      void printCoActorsOfCoActors(std::string actorName)
      {
            auto it = this->map.find(actorName);
            int count = 0;
            for (auto &pr :it->second.co_actorMap)
            {
                  std::cout<<"CO ACTOR NUMBER "<<count<<" : "<<pr.first<<" : "<<'\n'<<std::endl;
                  auto it2 = this->map.find(pr.first);
                  for (auto &pr2 :it2->second.co_actorMap)
                  {
                        std::cout<<pr2.first<<" , ";
                  }
                  count++;
                  std::cout<<'\n'<<std::endl;
            }
      }
      /* 
      Description: Searches and tells if two actors are co-actors or not.
      
      Time Complexity for searching:
          -Best Case: O(logn)
          -Worst Case: O(logn)
      Time Complexity for printing:
          -Best Case: O(n)
          -Worst Case: O(n)
      */
      void areCoActors(std::string actor1,std::string actor2)
      {
            auto it = this->map.find(actor1);

            if (it->second.co_actorMap.count(actor2) != 0)
            {
                  auto it2 = it->second.co_actorMap.find(actor2);
                  for(auto &pr: it2->second)
                  {
                        std::cout<<(*pr).movie_title<<std::endl;
                  }
            }else{
                  std::cout<<"Not co-Actors"<<std::endl;
            }
      }
};