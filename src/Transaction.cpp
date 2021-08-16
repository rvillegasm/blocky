#include "Transaction.hpp"

#include <sstream>
#include <stdexcept>


namespace blocky
{

    Transaction::Transaction(const std::optional<utils::PublicSignatureKey> &fromAddress, const utils::PublicSignatureKey &toAddress, double amount)
        : m_fromAddress(fromAddress), m_toAddress(toAddress), m_amount(amount)
    {
        calculateHash();
    }

    void Transaction::calculateHash()
    {
        std::stringstream ss;
        ss << m_fromAddress.value_or(utils::PublicSignatureKey()) << m_toAddress << m_amount;

        utils::Crypto::simpleBLAKE2bHash( m_hash.data(), m_hash.size(), ss.str());
    }

    void Transaction::signTransaction(const utils::SignatureKeypair &keypair)
    {
        // The miner tx is valid
        if (!m_fromAddress.has_value())
        {
            return;
        }
        if (keypair.getPublicKey() != m_fromAddress.value())
        {
            throw std::runtime_error("Other wallet's transactions cannot be signed!");
        }

        utils::Crypto::sign(m_signature.data(), m_hash.data(), m_hash.size(), keypair.getSecretKey().key.data());
    }

    bool Transaction::isValid()
    {
        if (!m_fromAddress.has_value())
        {
            return true;
        }

        return utils::Crypto::verifySignature(m_signature.data(), m_hash.data(), m_hash.size(), m_fromAddress.value().key.data());
    }

    std::ostream &operator<<(std::ostream &os, const Transaction &transaction)
    {
        auto outputCollectionItem = [&os](const auto &item) { os << item; };

        os << "{ ";
        os << "m_fromAddress: " << transaction.m_fromAddress.value_or(utils::PublicSignatureKey())
           << " m_toAddress: " << transaction.m_toAddress
           << " m_amount: " << transaction.m_amount
           << " m_hash: ";
        std::for_each(transaction.m_hash.begin(), transaction.m_hash.end(), outputCollectionItem);
        os << " m_signature: ";
        std::for_each(transaction.m_signature.begin(), transaction.m_signature.end(), outputCollectionItem);
        os << " }";

        return os;
    }

}