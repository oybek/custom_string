
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>

#include "string.h"

int main() {
	using namespace std;

	std::vector<dev::string> vs;

	std::copy( std::istream_iterator<dev::string>( std::cin ), std::istream_iterator<dev::string>(), std::back_inserter( vs ) );

	std::sort( vs.rbegin(), vs.rend() );

	std::copy( vs.begin(), vs.end(), std::ostream_iterator<dev::string>( std::cout, "\n" ) );

	return 0;
}


