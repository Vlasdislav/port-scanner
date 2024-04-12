#pragma once

#include <string>
#include "address_port.hpp"


namespace validation {
    std::optional<int> stringToInt(const std::string &str) {
        if (str[0] == '0') {
            return std::nullopt;
        }
        int res = 0;
        for (auto c : str) {
            if ('0' <= c && c <= '9') {
                res *= 10;
                res += c - '0';
            } else {
                return std::nullopt;
            }
        }
        return res;
    }

    std::optional<std::string> addressValidation(const std::string &address) {
        hostent *he = gethostbyname(address.data());
        if (he != nullptr) {
            return address;
        }
        herror("gethostbyname");
        return std::nullopt;
    }

    std::optional<AddressPorts> inputValidation(const int argc, char **argv) {
        if (argc == 4) {
            std::optional<std::string> opt_address = addressValidation(argv[1]);
            std::optional<int> opt_port_lhs = stringToInt(argv[2]);
            std::optional<int> opt_port_rhs = stringToInt(argv[3]);
            if (opt_address && opt_port_lhs && opt_port_rhs) {
                if (opt_port_lhs.value() <= opt_port_rhs.value()) {
                    return AddressPorts {
                        opt_address.value(),
                        opt_port_lhs.value(),
                        opt_port_rhs.value()
                    };
                }
            }
        }
        return std::nullopt;
    }
} // namespace validation
