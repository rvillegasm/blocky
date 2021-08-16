#include "Blockchain.hpp"

#include <stdexcept>


namespace blocky
{

    Blockchain::Blockchain()
    {
        utils::Crypto::init();
        m_chain.push_back(createGenesisBlock());
    }

    void Blockchain::addTransaction(std::unique_ptr<Transaction> tx)
    {
        if (!tx->getFromAddress().has_value())
        {
            throw std::runtime_error("To add a transaction, it must include an origin address (fromAddress)!");
        }
        if (!tx->isValid())
        {
            throw std::runtime_error("Cannot add invalid transaction to the blockchain!");
        }
        // Add transaction to mempool
        m_pendingTransactions.push_back(std::move(tx));
    }

    void Blockchain::minePendingTransaction(const utils::PublicSignatureKey &miningRewardAddress)
    {
        // Package all pending transactions together into the same block
        const Block &latestBlock = getLatestBlock();
        auto newBlock = std::make_unique<Block>(std::chrono::system_clock::now(), std::move(m_pendingTransactions), latestBlock.getHash());
        // Mine the newly create block
        newBlock->mineBlock(m_difficulty);
        m_chain.push_back(std::move(newBlock));
        // Put the miner fee (reward) transaction into pendingTransactions
        m_pendingTransactions.clear();
        m_pendingTransactions.emplace_back(std::make_unique<Transaction>(std::nullopt, miningRewardAddress, m_miningReward));
    }

    double Blockchain::getBalanceOfAddress(utils::PublicSignatureKey address)
    {
        double balance = 0.0;
        for (const auto &block : m_chain)
        {
            for (const auto &tx : block->getTransactions())
            {
                if (tx->getFromAddress() == address)
                {
                    balance -= tx->getAmount();
                }
                else if (tx->getToAddress() == address)
                {
                    balance += tx->getAmount();
                }
            }
        }

        return balance;
    }

    bool Blockchain::isChainValid()
    {
        for (int i = 1; i < m_chain.size(); ++i)
        {
            const auto &currentBlock = m_chain[i];
            const auto &previousBlock = m_chain[i - 1];

            if (!currentBlock->hasValidTransactions())
            {
                return false;
            }

            std::array<uint8_t, utils::Crypto::HASH_BYTES> currentHash = {};
            currentBlock->calculateHash(currentHash);
            if (currentBlock->getHash() != currentHash)
            {
                return false;
            }

            std::array<uint8_t, utils::Crypto::HASH_BYTES> previousHash = {};
            previousBlock->calculateHash(previousHash);
            if (currentBlock->getPreviousHash() != previousHash)
            {
                return false;
            }
        }

        return true;
    }

    std::unique_ptr<Block> Blockchain::createGenesisBlock()
    {
        return std::make_unique<Block>();
    }


}