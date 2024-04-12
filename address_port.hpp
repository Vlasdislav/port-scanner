#pragma once

#include <unistd.h>
#include <netdb.h>
#include <optional>


struct AddressPorts {
    AddressPorts() = default;

    AddressPorts(const std::string &address,
                const int &port_lhs,
                const int &port_rhs) :
        address_(address),
        port_lhs_(port_lhs),
        port_rhs_(port_rhs) {}
    
    AddressPorts(const AddressPorts& other) :
        address_(other.address_),
        port_lhs_(other.port_lhs_),
        port_rhs_(other.port_rhs_) {}

    AddressPorts& operator=(const AddressPorts& other) {
        if (this != &other) {
            AddressPorts(other).swap(*this);
        }
        return *this;
    }

    void swap(AddressPorts& other) {
        using std::swap;
        swap(address_, other.address_);
        swap(port_lhs_, other.port_lhs_);
        swap(port_rhs_, other.port_rhs_);
    }

    static bool chkport(sockaddr_in &addr) {
        int sock = socket(PF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            return false;
        }
        if (connect(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr))) {
            return false;
        }
        shutdown(sock, 2);
        close(sock);
        return true;
    }

    std::string address_;
    int port_lhs_;
    int port_rhs_;
};
