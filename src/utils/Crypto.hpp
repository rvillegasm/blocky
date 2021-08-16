#pragma once

#include <string>
#include <array>
#include <cstdint>


namespace blocky::utils
{

    class Crypto
    {
    public:
        static constexpr uint32_t HASH_BYTES = 32U;
        static constexpr uint32_t SIGN_BYTES = 64U;

        static int init();

        static void simpleBLAKE2bHash(uint8_t *out, size_t outSize, const std::string &in);

        static void sign(uint8_t *signature, const uint8_t *data, size_t dataSize, const uint8_t *secretKey);
        static bool verifySignature(uint8_t *signature, const uint8_t *data, size_t dataSize, const uint8_t *publicKey);
    };

}



