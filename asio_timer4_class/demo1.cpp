#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class compiler
{
 public :
	compiler ( boost::asio::io_service &io ):
		timer_(io,boost::posix_time::seconds(1)) ,counter_(0)
	{
	    timer_.async_wait( boost::bind(&compiler::read_in_source_file ,this) ) ;
	}

	~compiler ()
	{
	   std::cout << "finish compiling " << std::endl ; 
	}
	
	void read_in_source_file ()
	{
	   std::cout << " read in source file " << std::endl ;
	   
           timer_.expires_at( timer_.expires_at() + boost::posix_time::seconds(1) ) ;
		
	   timer_.async_wait (boost::bind(&compiler::compile_source_file , this ) ) ;
	}

	void compile_source_file ()
	{
	   std::cout << "compiling source file " << std::endl ;
	   
	   timer_.expires_at(timer_.expires_at() + boost::posix_time::seconds(1) ) ;
	
	   timer_.async_wait ( boost::bind(&compiler::link_bind_step , this )) ;
	}
	
	void link_bind_step ()
	{
	    std::cout << "linking and binding target files" << std::endl ;
	
	   timer_.expires_at(timer_.expires_at() + boost::posix_time::seconds(1)) ;
	
	   timer_.async_wait ( boost::bind( &compiler::run_program_step , this )) ; 
	}
	
	void run_program_step ()
	{
	    std::cout << "executing executable binary file " << std::endl ;
	
	    std::cout << " time end " << std::endl ;
	}
 private :
	int counter_ ;
	boost::asio::deadline_timer timer_ ;
} ;

int main ()
{
	boost::asio::io_service io ;
	compiler c(io ) ;
	
	io.run () ;
	return 0 ;
}
