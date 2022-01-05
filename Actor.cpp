#include <list>
#include "MovieCollection.cpp"

struct Profile
{     // This struct will maintain year wise movies of actor and also its co-actors.
      std::multimap<int,Movie*> profileMap;
      std::map<std::string,std::list<Movie*> > co_actorMap;
};
class Actor
{
      public:
      // Mapping from string to Profile struct
      std::map <std::string,Profile> map;

      // This function will get all the movie nodes from movieCollection and will set up profile struct.
      void CreateIndex(MovieCollection* obj)
      {
            //iterating through all the movie nodes and maintaing profile
            for (auto &pr :obj->map)
            {
                  // Returns movie pointer
                  Movie* ptr = &pr.second;

                  // For actor 1
                  if (this->map.count((*ptr).actor_1_name) == 0 && (*ptr).actor_1_name != "")
                  {     //
                        std::list<Movie*> ptrs;
                        ptrs.push_back(ptr);
                        Profile profile;
                        profile.profileMap.insert({(*ptr).title_year,ptr});
                        profile.co_actorMap.insert({(*ptr).actor_2_name,ptrs});
                        profile.co_actorMap.insert({(*ptr).actor_3_name,ptrs});
                        this->map.insert({(*ptr).actor_1_name,profile});
                  }else if ((*ptr).actor_1_name != "")
                  {
                        auto it = this->map.find((*ptr).actor_1_name);
                        it->second.profileMap.insert({(*ptr).title_year,ptr});

                        if (it->second.co_actorMap.count((*ptr).actor_2_name) == 0 && (*ptr).actor_2_name != "")
                        {
                              std::list<Movie*> ptrs;
                              ptrs.push_back(ptr);
                              it->second.co_actorMap.insert({(*ptr).actor_2_name,ptrs});
                        }
                        else if ((*ptr).actor_2_name != "")
                             it->second.co_actorMap.at((*ptr).actor_2_name).push_back(ptr);

                        if (it->second.co_actorMap.count((*ptr).actor_3_name) == 0 && (*ptr).actor_3_name != "")
                        {
                              std::list<Movie*> ptrs;
                              ptrs.push_back(ptr);
                              it->second.co_actorMap.insert({(*ptr).actor_3_name,ptrs});
                        }
                        else if ((*ptr).actor_3_name != "")
                             it->second.co_actorMap.at((*ptr).actor_3_name).push_back(ptr);  
                        
                  }
                  //For actor 2
                  if (this->map.count((*ptr).actor_2_name) == 0 && (*ptr).actor_2_name != "")
                  {
                        std::list<Movie*> ptrs;
                        ptrs.push_back(ptr);
                        Profile profile;
                        profile.profileMap.insert({(*ptr).title_year,ptr});
                        profile.co_actorMap.insert({(*ptr).actor_1_name,ptrs});
                        profile.co_actorMap.insert({(*ptr).actor_3_name,ptrs});
                        this->map.insert({(*ptr).actor_2_name,profile});
                  }else if ((*ptr).actor_2_name != "")
                  {
                        auto it = this->map.find((*ptr).actor_2_name);
                        it->second.profileMap.insert({(*ptr).title_year,ptr});

                        if (it->second.co_actorMap.count((*ptr).actor_1_name) == 0 && (*ptr).actor_1_name != "")
                        {
                              std::list<Movie*> ptrs;
                              ptrs.push_back(ptr);
                              it->second.co_actorMap.insert({(*ptr).actor_1_name,ptrs});
                        }
                        else if ((*ptr).actor_1_name != "")
                             it->second.co_actorMap.at((*ptr).actor_1_name).push_back(ptr);

                        if (it->second.co_actorMap.count((*ptr).actor_3_name) == 0 && (*ptr).actor_3_name != "")
                        {
                              std::list<Movie*> ptrs;
                              ptrs.push_back(ptr);
                              it->second.co_actorMap.insert({(*ptr).actor_3_name,ptrs});
                        }
                        else if ((*ptr).actor_3_name != "")
                             it->second.co_actorMap.at((*ptr).actor_3_name).push_back(ptr);  
                        
                  }
                  // //For actor 3
                  if (this->map.count((*ptr).actor_3_name) == 0 && (*ptr).actor_3_name != "")
                  {
                        std::list<Movie*> ptrs;
                        ptrs.push_back(ptr);
                        Profile profile;
                        profile.profileMap.insert({(*ptr).title_year,ptr});
                        profile.co_actorMap.insert({(*ptr).actor_2_name,ptrs});
                        profile.co_actorMap.insert({(*ptr).actor_1_name,ptrs});
                        this->map.insert({(*ptr).actor_3_name,profile});
                  }else if ((*ptr).actor_3_name != "")
                  {
                        auto it = this->map.find((*ptr).actor_3_name);
                        it->second.profileMap.insert({(*ptr).title_year,ptr});

                        if (it->second.co_actorMap.count((*ptr).actor_2_name) == 0 && (*ptr).actor_2_name != "")
                        {
                              std::list<Movie*> ptrs;
                              ptrs.push_back(ptr);
                              it->second.co_actorMap.insert({(*ptr).actor_2_name,ptrs});
                        }
                        else if ((*ptr).actor_2_name != "")
                             it->second.co_actorMap.at((*ptr).actor_2_name).push_back(ptr);

                        if (it->second.co_actorMap.count((*ptr).actor_1_name) == 0 && (*ptr).actor_1_name != "")
                        {
                              std::list<Movie*> ptrs;
                              ptrs.push_back(ptr);
                              it->second.co_actorMap.insert({(*ptr).actor_1_name,ptrs});
                        }
                        else if ((*ptr).actor_1_name != "")
                             it->second.co_actorMap.at((*ptr).actor_1_name).push_back(ptr);  
                        
                  }
            }
      }

      void search(std::string actorName)
      {
            //returns all the movie pointers of given actor in log(n) time
            auto it = this->map.find(actorName);
            std::cout<<"Actor Name : " << it->first<< '\n'<<"\t\tMOVIES\n\n";
            //printing the movies
            for (auto &pr :it->second.profileMap)
            {
                  std::cout<<"Movie name : "<<(*pr.second).movie_title<<"  |  "<<"Year : "<<pr.first<<std::endl;
            }
      }
      
      void searchCoActors(std::string actorName)
      {
            //returns all the movie pointers of given actor in log(n) time
            auto it = this->map.find(actorName);
            std::cout<<"Actor Name : " << it->first<< '\n'<<"\t\tMOVIES\n\n";
            //printing the movies
            for (auto &pr :it->second.profileMap)
            {
                  std::cout<<"Movie : "<<(*pr.second).movie_title<<"  |  "<<"Year : "<<pr.first<<"  |   Co-Actors : ";
                  if ((*pr.second).actor_1_name != actorName )
                  std::cout<<(*pr.second).actor_1_name<<" | ";

                  if ((*pr.second).actor_2_name != actorName )
                  std::cout<<(*pr.second).actor_2_name<<" | ";

                  if ((*pr.second).actor_3_name != actorName )
                  std::cout<<(*pr.second).actor_3_name;

                  std::cout<<std::endl;
            }
      }

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

      void searchDoubleCoActors(std::string actorName)
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
            }
      }
};