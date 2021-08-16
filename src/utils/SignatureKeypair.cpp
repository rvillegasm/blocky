#include "SignatureKeypair.hpp"

#include <sodium.h>

namespace blocky::utils
{

    SignatureKeypair::SignatureKeypair()
    {
        crypto_sign_keypair(m_publicKey.key.data(), m_secretKey.key.data());
    }

}