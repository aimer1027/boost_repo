#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <queue.h>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>



class process :
		 public boost::enabled_shared_from_this<process>
{
 public:
	typedef  boost::shared_ptr<process>  ProcessPtr_t ;
	static ProcessPtr_t
	 starter( boost::asio::io_service &io ,int time_piece, int need_time , bool isBlock )
	{
		// in this method i will create an process object and 
		// pass the time_piece and need time value to it 
		// then use the time async method bind the next method -- > the create a process method 
		
		return ProcessPtr_t ( new process( io, time_piece, need_time , isBlock ) ) ;	
		
	}
	
	void create()
	{
		// hello i am the create a process , i will wait for 2 secs and then call the get ready method 
		// which means a proces is created , and allocated running time_piece time and the get ready 
		// to finish the event or task allocated to it 
	}
	

	void ready ()
	{
		// hello , i am ready function , i will wait for 2 seconds and change the state
		// into the running state 
	}

	void running ()
	{
		// hello , i am running the most difficult method , i would like to check 
		// need_time and timepiece which one is bigger if the need_time is bigger 
		// after time_piece seconds from now on , i would like update need_time -= time_piece 
		
		// and change my state into the get ready state 
	
		// and if the need_time < time_piece , after need_time seconds later 
		// i would like change my status into the exit method by bind the next method 
	}
	
	void finish_exit ()
	{
		// print out finish message 
		// and not update expired time value  
	}

	void blocked ()
	{
		// if blocked_ == true , this method can run 
		// pop the event_queue and then change the state into the get ready 
	}
	
	
 private :

	process ( boost::asio::io_service &io ,  int time_piece , int current_event_time_cost, bool isBlock )
					:time_piece_(time_piece) ,
					event_time_consume_(current_event_time_cost),
					blocked_(isBlock),
					timer_(io, boost::posix_time::seconds(0))
					{}
   	int time_piece_ ;
	int event_time_consume_ ;
	
	boost::asio::deadline_timer timer_ ;
	
	bool blocked_; 
	// this boolean variable is used to present whether the process could be blocked by other events
  	queue<int> event_queue_;
}  ; // class -- process -- 
