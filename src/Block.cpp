#include "Block.hpp"

#include <sstream>
#include <algorithm>


namespace blocky
{

    Block::Block()
    {
        calculateHash(m_hash);
    }

    Block::Block(
        std::chrono::time_point<std::chrono::system_clock> timestamp,
        std::vector<std::unique_ptr<Transaction>> transactions,
        const std::array<uint8_t, utils::Crypto::HASH_BYTES> &previousHash
    )
        : m_timestamp(timestamp), m_transactions(std::move(transactions)), m_previousHash(previousHash)
    {
        calculateHash(m_hash);
    }

    bool Block::hasValidTransactions()
    {
        // Traverse all transactions within the block, verifying them one by one
        for (const auto &tx : m_transactions)
        {
            if (!tx->isValid())
            {
                return false;
            }
        }
        return true;
    }

    void Block::mineBlock(int difficulty)
    {
        // Using proof-of-work to create a random hash until the acceptance criteria is met
        while (!isMineCriteriaMet(difficulty))
        {
            m_nonce += 1;
            calculateHash(m_hash);
        }
    }

    void Block::calculateHash(std::array<uint8_t, utils::Crypto::HASH_BYTES> &outHash)
    {
        std::stringstream ss;

        ss << m_timestamp.time_since_epoch().count();
        std::for_each(m_transactions.begin(), m_transactions.end(), [&ss](const auto &tx) { ss << *tx; });
        std::for_each(m_previousHash.begin(), m_previousHash.end(), [&ss](const uint8_t &byte) { ss << byte; });
        ss << m_nonce;

        utils::Crypto::simpleBLAKE2bHash(outHash.data(), outHash.size(), ss.str());
    }

    bool Block::isMineCriteriaMet(int difficulty)
    {
        // First 'difficulty' bytes of the hash need to be equal to 0
        for (int i = 0; i < difficulty; ++i)
        {
            if (m_hash[i] != 0)
            {
                return false;
            }
        }

        return true;
    }

}
