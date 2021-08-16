#pragma once

#include "utils/Crypto.hpp"
#include "utils/SignatureKeypair.hpp"

#include <array>
#include <optional>
#include <ostream>


namespace blocky
{

    class Transaction
    {
    private:
        std::optional<utils::PublicSignatureKey> m_fromAddress = std::nullopt; // Origin address' public key
        utils::PublicSignatureKey m_toAddress = {}; // Destination address' public key
        double m_amount = 0.0;
        std::array<uint8_t, utils::Crypto::HASH_BYTES> m_hash = {};
        std::array<uint8_t, utils::Crypto::SIGN_BYTES> m_signature = {};

        void calculateHash();

    public:
        Transaction(const std::optional<utils::PublicSignatureKey> &fromAddress, const utils::PublicSignatureKey &toAddress, double amount);

        void signTransaction(const utils::SignatureKeypair &keypair);
        bool isValid();

        [[nodiscard]] const std::optional<utils::PublicSignatureKey> &getFromAddress() const { return m_fromAddress; }
        [[nodiscard]] const utils::PublicSignatureKey &getToAddress() const { return m_toAddress; }
        [[nodiscard]] double getAmount() const { return m_amount; }
        [[nodiscard]] const std::array<uint8_t, utils::Crypto::HASH_BYTES> &getHash() const { return m_hash; }
        [[nodiscard]] const std::array<uint8_t, utils::Crypto::SIGN_BYTES> &getSignature() const { return m_signature; }

        friend std::ostream &operator<<(std::ostream &os, const Transaction &transaction);
    };

}



