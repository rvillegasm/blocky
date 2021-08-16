#include "Crypto.hpp"

#include <sodium.h>


namespace blocky::utils
{

    int Crypto::init()
    {
        return sodium_init();
    }

    void Crypto::simpleBLAKE2bHash(uint8_t *out, size_t outSize, const std::string &in)
    {
        crypto_generichash(out, outSize, reinterpret_cast<const unsigned char *>(in.c_str()), in.size(), nullptr, 0);
    }

    void Crypto::sign(uint8_t *signature, const uint8_t *data, size_t dataSize, const uint8_t *secretKey)
    {
        crypto_sign_detached(signature, nullptr, data, dataSize, secretKey);
    }

    bool Crypto::verifySignature(uint8_t *signature, const uint8_t *data, size_t dataSize, const uint8_t *publicKey)
    {
        return crypto_sign_verify_detached(signature, data, dataSize, publicKey) == 0;
    }

}