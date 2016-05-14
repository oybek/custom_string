
#define BOOST_TEST_MODULE stringtest
#include <boost/test/included/unit_test.hpp>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include "string.h"

BOOST_AUTO_TEST_SUITE ( string_unit_test ) // name of the test suite is stringtest

BOOST_AUTO_TEST_CASE ( check_constructor )
{
	{
		dev::string s;
		BOOST_CHECK(std::strncmp(s.c_str(), "", s.length()) == 0);
	}
	{
		dev::string s = nullptr;
		BOOST_CHECK(s.length() == 0);
	}
	{
		dev::string s = "hello";
		BOOST_CHECK(std::strncmp(s.c_str(), "hello", s.length()) == 0);
	}
	{
		dev::string s = "";
		BOOST_CHECK(std::strncmp(s.c_str(), "", s.length()) == 0);
	}
}

BOOST_AUTO_TEST_CASE ( check_self_copy_assignment )
{
	{
		dev::string s;
		s = s;
		BOOST_CHECK(strncmp(s.c_str(), "", s.length()) == 0);
	}
	{
		dev::string s = nullptr;
		s = s;
		BOOST_CHECK(strncmp(s.c_str(), "", s.length()) == 0);
	}
	{
		dev::string s = "";
		s = s;
		BOOST_CHECK(strncmp(s.c_str(), "", s.length()) == 0);
	}
	{
		dev::string s = "hello";
		s = s;
		BOOST_CHECK(strncmp(s.c_str(), "hello", s.length()) == 0);
	}
}

BOOST_AUTO_TEST_CASE ( check_self_move_assignment )
{
	{
		dev::string s;
		s = std::move( s );
		BOOST_CHECK( std::strncmp( s.c_str(), "", s.length() ) == 0 );
	}
	{
		dev::string s = nullptr;
		s = std::move( s );
		BOOST_CHECK( std::strncmp( s.c_str(), "", s.length() ) == 0 );
	}
	{
		dev::string s = "";
		s = std::move( s );
		BOOST_CHECK( std::strncmp( s.c_str(), "", s.length() ) == 0 );
	}
	{
		dev::string s = "hello";
		s = std::move( s );
		BOOST_CHECK( std::strncmp( s.c_str(), "hello", s.length() ) == 0 );
	}
}

BOOST_AUTO_TEST_CASE ( check_move_assignment )
{
	{
		dev::string s = "hello";
		{
			dev::string tmp;
			s = std::move(tmp);
		}
		BOOST_CHECK(std::strncmp(s.c_str(), "", s.length()) == 0);
	}
	{
		dev::string s = "hello";
		{
			dev::string tmp = nullptr;
			s = std::move(tmp);
		}
		BOOST_CHECK(std::strncmp(s.c_str(), "", s.length()) == 0);
	}
	{
		dev::string s = "hello";
		{
			dev::string tmp = "";
			s = std::move(tmp);
		}
		BOOST_CHECK(std::strncmp( s.c_str(), "", s.length() ) == 0 );
	}
	{
		dev::string s = "hello";
		{
			dev::string tmp = "home";
			s = std::move(tmp);
		}
		BOOST_CHECK(std::strncmp( s.c_str(), "home", s.length() ) == 0 );
	}
}

BOOST_AUTO_TEST_CASE ( check_push_back )
{
	dev::string s;
	s.push_back( 'c' );
	s.push_back( 'a' );
	s.push_back( 't' );
	printf( "%s\n", s.c_str() );

	BOOST_CHECK( s.length() == 3	);
	BOOST_CHECK( s.capacity() == 4	);

	std::cout << s.capacity() << std::endl;

	BOOST_CHECK( std::strncmp( s.c_str(), "cat", s.length() ) == 0 );
}

BOOST_AUTO_TEST_CASE ( check_push_back_and_concat )
{
	dev::string s1, s2;

	s1.push_back( 'c' );
	s1.push_back( 'a' );
	s1.push_back( 't' );
	s1.push_back( 's' );

	BOOST_CHECK( s1.length() == 4 );

	s2.push_back( 'e' );
	s2.push_back( 'a' );
	s2.push_back( 't' );

	BOOST_CHECK( s2.length() == 3 );

	s2 = s1 + s2;

	BOOST_CHECK( std::strncmp( s2.c_str(), "catseat", s2.length() ) == 0 );
}

BOOST_AUTO_TEST_SUITE_END( )

