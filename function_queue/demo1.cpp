#include <iostream>
#include <cstring>
#include <ctime>
#include <map>
//#include <boost/function.hpp>

#include <tr1/functional>

using std::tr1::function ;


class function_map
{
 public :
    function_map (){}
 
    void register_ ( function<void()>& f , std::string name ) 
    {
	
	fun_map_[name] = f ;
    }

   void caller ( std::string name )
   {
        //std::pair<std::string, function<void()> > 
	std::map<std::string , function<void()> >::iterator  f =  fun_map_.find(name) ;
	
	if ( f == fun_map_.end () )
	{
	   std::cout << "function you called have not registered " <<std::endl ;
	   return ;
        }
	   f->second() ;
   }
 private :
   std::map<std::string , function<void()>  > fun_map_ ;
} ; // -- class function_map --



void func1 ()
{
  std::cout << "a+b= c" << std::endl ;
}

int main ( int argc ,char **argv )
{
  function_map  function_caller ;
 
 function<void()> f = &func1 ;

  function_caller.register_ (f,std::string("func1")) ;
 
  std::string name ;
 
  std::cout << "input function name "<< std::endl ;
  std::cin >> name ;

  function_caller.caller(name) ;

  return 0 ;
}
