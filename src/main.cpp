#include "utils/Crypto.hpp"

#include "Blockchain.hpp"
#include "Wallet.hpp"

#include <iostream>


int main()
{
    // Innit blockchain
    blocky::Blockchain simpleBlockchain;

    // Setup wallets
    const blocky::Wallet myWallet;
    const blocky::Wallet aliceWallet;

    // Create a transaction
    auto tx1 = std::make_unique<blocky::Transaction>(myWallet.getKeypair().getPublicKey(), aliceWallet.getKeypair().getPublicKey(), 60);
    // Sign with the private key
    tx1->signTransaction(myWallet.getKeypair());
    // Submit transaction
    simpleBlockchain.addTransaction(std::move(tx1));

    std::cout << "Starting mining block 1..." << std::endl;
    simpleBlockchain.minePendingTransaction(myWallet.getKeypair().getPublicKey());

    // Add more block and transactions
    auto tx2 = std::make_unique<blocky::Transaction>(myWallet.getKeypair().getPublicKey(), aliceWallet.getKeypair().getPublicKey(), 80);
    tx2->signTransaction(myWallet.getKeypair());
    simpleBlockchain.addTransaction(std::move(tx2));
    std::cout << "Starting mining block 2..." << std::endl;
    simpleBlockchain.minePendingTransaction(myWallet.getKeypair().getPublicKey());

    auto tx3 = std::make_unique<blocky::Transaction>(myWallet.getKeypair().getPublicKey(), aliceWallet.getKeypair().getPublicKey(), 100);
    tx3->signTransaction(myWallet.getKeypair());
    simpleBlockchain.addTransaction(std::move(tx3));
    std::cout << "Starting mining block 3..." << std::endl;
    simpleBlockchain.minePendingTransaction(myWallet.getKeypair().getPublicKey());

    // If transfer is successful, Alice's balance should be 240
    std::cout << "Alice's balance currently is: " << simpleBlockchain.getBalanceOfAddress(aliceWallet.getKeypair().getPublicKey()) << std::endl;
    std::cout << "My balance currently is: " << simpleBlockchain.getBalanceOfAddress(myWallet.getKeypair().getPublicKey()) << std::endl;

    // Check blockchain validity
    std::cout << "Is the blockchain valid?: " << (simpleBlockchain.isChainValid() ? "true" : "false") << std::endl;

    return 0;
}
