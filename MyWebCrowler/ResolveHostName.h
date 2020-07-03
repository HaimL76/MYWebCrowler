#pragma once
#include <string>
#include <windows.h>

using namespace std;

class ResolveHostName
{
public:
	virtual string& Resolve(string& url) = 0;
};

class RegularResolveHostName : ResolveHostName
{
public:
	string& Resolve(string& url) 
	{
        try {
            use_WSA x;

            hostent* h = gethostbyname(url.c_str());
            unsigned char* addr = reinterpret_cast<unsigned char*>(h->h_addr_list[0]);
            std::copy(addr, addr + 4, std::ostream_iterator<unsigned int>(std::cout, "."));
        }
        catch (std::exception const& exc) {
            std::cerr << exc.what() << "\n";
            return EXIT_FAILURE;
        }
	}
};

