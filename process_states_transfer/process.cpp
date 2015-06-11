#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

class process : public boost::enable_shared_from_this<process>
{
 public :
	typedef boost::shared_ptr<process> ProcessPtr_t ;
	
	static ProcessPtr_t starter ( boost::asio::io_service &io ,
		int time_piece , int need_time , bool isBlock )
	{
		return ProcessPtr_t( new process(io, time_piece, need_time , isBlock)) ;
	}
	
	void create()
	{
	   std::cout <<"------------[state ] create ----------------------" <<std::endl ;
	   std::cout << " create a process " << std::endl ;
	
	   timer_.expires_at( timer_.expires_at() + boost::posix_time::seconds(2)) ;
	
	   std::cout << " a process is created going to ready state " << std::endl ;
	
	  timer_.async_wait( boost::bind( &process::ready , shared_from_this ())) ;
	
	  std::cout <<"------------[state ] ready  ----------------------" <<std::endl ;


	  std::cout<<std::endl ; std::cout<<std::endl ;
		
	}
	
	void ready ()
	{
            //std::cout <<"-----------------[state] ready---------------"<<std::endl ;
	    std::cout << "prepare resources " << std::endl ;
		
     	    timer_.expires_at ( timer_.expires_at() + boost::posix_time::seconds(2) ) ;
	    
	    std::cout << "process is ready , going to running state " << std::endl   ;
	
	   
	     std::cout <<"--------------[state] running----------------"<<std::endl ;
	
	    timer_.async_wait( boost::bind(&process::running , shared_from_this ())) ;

            std::cout<<std::endl ; std::cout<<std::endl ;

	}
	
	void running ()
	{
//		std::cout << "---------------- [state ] running-------------" <<std::endl ;
		std::cout << " process is running " << std::endl ;
	
	if ( isBlock_ )  // running --- > blocked 
	{	
		int blocked_time ; 

		isBlock_ = false ;

		std::cout << "high priority event coming in put blocked time(second)" << std::endl ;
		std::cin >>blocked_time ;
		
	         timer_.expires_at( timer_.expires_at() + boost::posix_time::seconds(blocked_time)) ;
	

		std::cout << "-------------[state ] blocking ---------------------"<<std::endl ;

	 std::cout << " ok currently cpu is busy with the new coming high priority event "<<std::endl ;


		timer_.async_wait ( boost::bind( &process::blocked , shared_from_this())) ;

	         std::cout<<std::endl ; std::cout<<std::endl ;

	} // -- if -- 
	else
	{   
	        if ( time_piece_ > event_time_consume_ )
		{
		   // this means event that the process is running 
		// could get done in a piece of time_piece , so 
		// there is no need to transfer the state into the ready 
		
		// after the event_time_consume_ seconds go to exit state directly
		
		 timer_.expires_at( timer_.expires_at() +
				boost::posix_time::seconds( event_time_consume_ ) ) ;
		
		std::cout << "----------------[state] exiting----------------------"<< std::endl ;
	
		
		timer_.async_wait( boost::bind( &process::exit , shared_from_this())) ;
	
		 std::cout<<std::endl ; std::cout<<std::endl ;

		}
		
	        else
		{
			// this means that the event couldn't be done 
		// in one time piece
		
			// need state transfer into ready state and transfer into running several times
			
	timer_.expires_at (timer_.expires_at() + boost::posix_time::seconds(time_piece_ )) ;
	// do not forget update the event_time_consume
		
		event_time_consume_ -= time_piece_ ;
		
		std::cout <<"time piece exhaust , going to ready state " << std::endl ;
	
		std::cout <<"------------[state ] ready ---------------------" <<std::endl ;

		timer_.async_wait( boost::bind(&process::ready, shared_from_this())) ;
		
		 std::cout<<std::endl ; std::cout<<std::endl ;
		
	   }
	} // -- else --
 } // method running 

	void blocked( )
	{

	timer_.expires_at( timer_.expires_at() + boost::posix_time::seconds(2)) ;
	
	std::cout <<"------------[state ] ready  ----------------------" <<std::endl ;
	
	timer_.async_wait( boost::bind(&process::ready, shared_from_this())) ;

//	 std::cout <<"------------[leave state ] blocked ----------------------" <<std::endl ;

	
		 std::cout<<std::endl ; std::cout<<std::endl ;

	}

	
	void exit ()
	{
		//std::cout <<"------------[state ] exit ----------------------" <<std::endl ;

		std::cout << " process finish the event , exit " << std::endl ;
		
	    //	std::cout <<"------------[leave state ] exit ----------------------" <<std::endl ;

	}

private :
	process( boost::asio::io_service &io , int time_piece, int need_time, bool isBlock ):
	   time_piece_(time_piece) , event_time_consume_(need_time), isBlock_(isBlock) ,
		timer_(io , boost::posix_time::seconds(1))
	{} 
	
	int time_piece_ ;
	int event_time_consume_ ;
	bool isBlock_ ;
	boost::asio::deadline_timer timer_ ;
} ;


int main ( int argc , char **argv )
{
 boost::asio::io_service io ;
 
 int timer_piece = 4 ;// seconds
 int event_need_time = 10 ; // seconds 
 bool blocked = true ; 

 process::ProcessPtr_t p = process::starter ( io ,timer_piece, event_need_time , blocked ) ;


 std::cout <<"now create a process starting " << std::endl ;

 p->create () ;
	
 io.run() ;

 return 0 ;
}
