#ifndef __DEV_STRING_HPP__
#define __DEV_STRING_HPP__

#include <cassert>

namespace dev {
	class	string
	{
	public:
		string()
		{
			len = 0;
			cap = 1;
			buf = new char [ cap ];
			buf[ len ] = '\0';
		}

		string( const char* s )
		{
			if( s == nullptr )
			{
				len = 0;
				cap = 1;
				buf = new char [ cap ];
				buf[ len ] = '\0';
			}
			else
			{
				len = std::strlen( s );
				cap = len+1;
				buf = new char [ cap ];
				memcpy( static_cast<void*>( buf ), static_cast<const void*>( s ), sizeof( char )*len );
				buf[ len ] = '\0';
			}
		}

		string( const string & s )
		{
			if( s.buf == nullptr )
			{
				len = 0;
				cap = 1;
				buf = new char [ cap ];
				buf[ len ] = '\0';
			}
			else
			{
				len = s.len;
				cap = len+1;
				buf = new char [ cap ];
				memcpy( static_cast<void*>( buf ), static_cast<const void*>( s.buf ), sizeof( char )*len );
				buf[ len ] = '\0';
			}
		}

		string( string && s )
		{
			delete [] buf;

			buf = s.buf;
			len = s.len;
			cap = s.cap;

			s.len = 0;
			s.cap = 1;
			s.buf = new char [ cap ];
			s.buf[ len ] = '\0';
		}

		~string()	{ delete [] buf; }

		size_t capacity() const		{ return cap; }
		size_t length() const		{ return len; }
		const char * c_str() const	{ return buf; }

		string& operator=( const string& s )
		{
			if( buf == s.buf ) { return *this; }

			reserve( s.len+1 );

			len = s.len;
			memcpy( static_cast<void*>( buf ), static_cast<const void*>( s.buf ), sizeof( char )*s.len );
			buf[ len ] = '\0';

			return *this;
		}

		string& operator=( string&& s )
		{
			if ( buf == s.buf )  { return * this; }

			delete [] buf;

			buf = s.buf;
			len = s.len;
			cap = s.cap;

			s.len = 0;
			s.cap = 1;
			s.buf = new char [ cap ];
			s.buf[ len ] = '\0';

			return *this;
		}

		void reserve( size_t new_cap )
		{
			if( new_cap <= cap ) { return; }

			char * tmp = new char [ new_cap ];
			memcpy( static_cast<void*>( tmp ), static_cast<const void*>( buf ), len );

			cap = new_cap;

			delete [] buf;
			buf = tmp;
			buf[ len ] = '\0';
		}

		void push_back( const char c )
		{
			if( buf == nullptr )
			{
				cap = 2;
				len = 1;
				buf = new char [ cap ];
				buf[ len-1 ] = c;
				buf[ len ] = '\0';
			}
			else
			{
				if( len+1 >= cap )
				{
					reserve( cap*2 );
				}
				buf[ len ] = c;
				buf[ ++len ] = '\0';
			}
		}

		bool operator<( const string & s ) const
		{
			return std::strncmp( c_str(), s.c_str(), std::min( len, s.length() ) ) < 0;
		}

		const char operator[]( size_t i ) const {
			return buf[i];
		}

		friend const string operator+( const string &, const string & );

		friend
		std::istream & operator>>( std::istream & in, string & s )
		{
			s.len = 0;

			while( in.peek() && isspace( in.peek() ) )
			{
				in.get();
			}
			while( in.peek() && isgraph( in.peek() ) )
			{
				s.push_back( in.get() );
			}

			return in;
		}

		friend
		std::ostream & operator<<( std::ostream & out, const string & s )
		{
			std::copy( s.buf, s.buf+s.len, std::ostream_iterator<char>( out ) );
			return out;
		}

	private:
		size_t len = 0, cap = 0;
		char * buf = nullptr;
	};

	const string operator+( const string & s1, const string & s2 )
	{
		string s;
		s.len = s.cap = s1.length() + s2.length() + 1;
		s.buf = new char [s.len];

		std::memcpy( static_cast<void*>( s.buf ), static_cast<const void*>( s1.buf ), sizeof(char)*s1.length() );
		std::memcpy( static_cast<void*>( s.buf+s1.length() ), static_cast<const void*>( s2.buf ), sizeof(char)*s2.length()+1 );

		return s;
	}

	const string operator+( const string & s1, const char * s2 )
	{
		return s1 + string( s2 );
	}

	const string operator+( const char * s1, const string & s2 )
	{
		return string( s1 ) + s2;
	}
}

#endif

