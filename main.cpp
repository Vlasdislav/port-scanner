#include <cstring>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "address_port.hpp"
#include "validation.hpp"


int main(int argc, char **argv) {
    try {
        AddressPorts ap = validation::inputValidation(argc, argv).value();
        sockaddr_in addr;
        hostent *hp = gethostbyname(ap.address_.data());
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = PF_INET;
        memcpy(&addr.sin_addr, hp->h_addr, hp->h_length);
        std::cout << "Scanning Host " << ap.address_ << std::endl;
        clock_t st = clock();
        for (int port = ap.port_lhs_; port <= ap.port_rhs_; ++port) {
            addr.sin_port = htons(port);
            if (!fork()) {
                if (AddressPorts::chkport(addr)) {
                    std::cout << port << "\tOPEN" << std::endl;
                }
                exit(0);
            }
        }
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Done in " << static_cast<double>(clock() - st) / CLOCKS_PER_SEC << " seconds." << std::endl;
    } catch (const std::bad_optional_access& e) {
        std::cout << "Actual: ";
        for (int i = 1; i < argc; ++i) {
            std::cout << argv[i] << ' ';
        }
        std::cout << std::endl;
        std::cout << "Expected: <IP> <MIN_PORT> <MAX_PORT>" << std::endl;
    }
    return 0;
}
