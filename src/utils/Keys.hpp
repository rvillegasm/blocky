#pragma once

#include <array>
#include <algorithm>
#include <ostream>


namespace blocky::utils
{

    struct PublicSignatureKey
    {
        static constexpr uint32_t PUBLIC_KEY_BYTES = 32U;

        std::array<uint8_t, PUBLIC_KEY_BYTES> key = {};

        bool operator==(const PublicSignatureKey &rhs) const
        {
            return key == rhs.key;
        }

        bool operator!=(const PublicSignatureKey &rhs) const
        {
            return !(rhs == *this);
        }

        friend std::ostream &operator<<(std::ostream &os, const PublicSignatureKey &k)
        {
            std::for_each(k.key.begin(), k.key.end(), [&os](const auto &item) { os << item; });
            return os;
        }
    };

    struct SecretSignatureKey
    {
        static constexpr uint32_t SECRET_KEY_BYTES = 32U + 32U;

        std::array<uint8_t, SECRET_KEY_BYTES> key = {};

        bool operator==(const SecretSignatureKey &rhs) const
        {
            return key == rhs.key;
        }

        bool operator!=(const SecretSignatureKey &rhs) const
        {
            return !(rhs == *this);
        }

        friend std::ostream &operator<<(std::ostream &os, const SecretSignatureKey &k)
        {
            std::for_each(k.key.begin(), k.key.end(), [&os](const auto &item) { os << item; });
            return os;
        }
    };

}


