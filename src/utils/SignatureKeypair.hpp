#pragma once

#include "Keys.hpp"


namespace blocky::utils
{

    class SignatureKeypair
    {
    private:
        PublicSignatureKey m_publicKey;
        SecretSignatureKey m_secretKey;

    public:
        SignatureKeypair();

        [[nodiscard]] const PublicSignatureKey &getPublicKey() const { return m_publicKey; }
        [[nodiscard]] const SecretSignatureKey &getSecretKey() const { return m_secretKey; }
    };

}



