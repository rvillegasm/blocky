#pragma once

#include "Block.hpp"

#include <memory>


namespace blocky
{

    class Blockchain
    {
    private:
        std::vector<std::unique_ptr<Block>> m_chain;
        int m_difficulty = 1;
        std::vector<std::unique_ptr<Transaction>> m_pendingTransactions;
        double m_miningReward = 100.0;

        static std::unique_ptr<Block> createGenesisBlock();

    public:
        Blockchain();

        void addTransaction(std::unique_ptr<Transaction> tx);
        void minePendingTransaction(const utils::PublicSignatureKey &miningRewardAddress);

        double getBalanceOfAddress(utils::PublicSignatureKey address);
        bool isChainValid();

        [[nodiscard]] const Block &getLatestBlock() const { return *m_chain.back(); }
    };

}



