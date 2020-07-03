#include "ResolveHostName.h"
#include "InitializeWinsock.h"
#include <iostream>
#include <iterator>

string& RegularResolveHostName::Resolve(string& hostName)
{
    bool result = InitializeWinsock::Initialize();

    try {
        hostent* h = gethostbyname(hostName.c_str());

        if (h != 0 && h->h_addr_list)
        {
            unsigned char* addr = reinterpret_cast<unsigned char*>(h->h_addr_list[0]);
        }
    }
    catch (std::exception const& exc) {
        //std::cerr << exc.what() << "\n";
        //return EXIT_FAILURE;
    }

    return hostName;
}