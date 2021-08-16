#pragma once

#include "utils/SignatureKeypair.hpp"


namespace blocky
{

    class Wallet
    {
    private:
        utils::SignatureKeypair m_keypair = {};

    public:
        Wallet() = default;

        [[nodiscard]] const utils::SignatureKeypair &getKeypair() const { return m_keypair; }
    };

}



