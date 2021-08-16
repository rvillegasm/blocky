#pragma once

#include "Transaction.hpp"
#include "utils/Crypto.hpp"

#include <string>
#include <array>
#include <vector>
#include <chrono>
#include <memory>


namespace blocky
{

    class Block
    {
    private:
        std::chrono::time_point<std::chrono::system_clock> m_timestamp = std::chrono::system_clock::now(); // UNIX timestamp
        std::vector<std::unique_ptr<Transaction>> m_transactions; // transactions (or just data to store on the chain)
        std::array<uint8_t, utils::Crypto::HASH_BYTES> m_previousHash = {}; // hash of the previous block, as an array of bytes
        uint64_t m_nonce = 0;
        std::array<uint8_t, utils::Crypto::HASH_BYTES> m_hash = {}; // hash as an array of bytes

        bool isMineCriteriaMet(int difficulty);

    public:
        Block();
        Block(
            std::chrono::time_point<std::chrono::system_clock> timestamp,
            std::vector<std::unique_ptr<Transaction>> transactions,
            const std::array<uint8_t, utils::Crypto::HASH_BYTES> &previousHash);

        void calculateHash(std::array<uint8_t, utils::Crypto::HASH_BYTES> &outHash);

        bool hasValidTransactions();
        void mineBlock(int difficulty);

        [[nodiscard]] const std::vector<std::unique_ptr<Transaction>> &getTransactions() const { return m_transactions; }
        [[nodiscard]] const std::array<uint8_t, utils::Crypto::HASH_BYTES> &getPreviousHash() const { return m_previousHash; }
        [[nodiscard]] const std::array<uint8_t, utils::Crypto::HASH_BYTES> &getHash() const { return m_hash; }
    };

}
