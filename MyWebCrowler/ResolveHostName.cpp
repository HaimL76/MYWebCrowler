#include "ResolveHostName.h"
#include "InitializeWinsock.h"
#include <iterator>
#include <iostream>
#include <sstream>

using namespace std;

string& RegularResolveHostName::Resolve(string& hostName)
{
    bool result = InitializeWinsock::Initialize();

    try {
        hostent* h = gethostbyname(hostName.c_str());

        if (h != 0 && h->h_addr_list)
        {
            unsigned char* addr = reinterpret_cast<unsigned char*>(h->h_addr_list[0]);

            hostName.clear();

            if (addr != 0) 
            {
                ostringstream oss;

                copy(addr, addr + 4, std::ostream_iterator<unsigned int>(oss, "."));
                hostName.append(oss.str()).erase(hostName.length() - 1, 1);
            }
        }
    }
    catch (std::exception const& exc) {
        //std::cerr << exc.what() << "\n";
        //return EXIT_FAILURE;
    }

    return hostName;
}