#include <iostream>
#include "boost/asio.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

void print ( const boost::system::error_code & )
{
	std::cout<< "Hello World" << std::endl ;
}

void another_print ( const boost::system::error_code & e )
{
        std::cout << " ok five second , called the binded method now " << std::endl ;


	std::cout << "Hello Aimer " << std::endl ;
}

int main ()
{
	boost::asio::io_service io ;
	
	boost::asio::deadline_timer tt ( io ,	boost::posix_time::seconds(5)) ;
	
//	std::cout << " ok five second , called the binded method now " << std::endl ;

	tt.async_wait( &another_print ) ;
	
	io.run () ;
	
	return 0 ;
}
