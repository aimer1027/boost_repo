AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=boost_demo1

BOOST_PATH=/unixC/Boost/boost_1_58_0

boost_demo1_SOURCES=\
	demo1.cpp

boost_demo1_CXXFLAGS=\
	-I$(BOOST_PATH) -D_FILE_OFFSET_BITS=64 -ggdb -Wall -O0

boost_demo1_LDADD=\
	-lpthread -lm -lboost_system -lboost_thread \
	-lboost_program_options -lrt

boost_demo1_LDFLAGS=\
	-fPIC -rdynamic -L$(BOOST_PATH)/stage/lib -pthread
