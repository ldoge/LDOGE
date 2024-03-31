// Copyright (c) 2009 - 2023 Satoshi Nakamoto
// Copyright (c) 2009 - 2023 The Bitcoin developers
// Copyright (c) 2009 - 2023 The Litedoge developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"
#include "chainparams.h"
#include "main.h"
#include "db.h"
#include "tinyformat.h"
#include "util.h"
#include "chainparamsseeds.h"
#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};



static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 * 
 * CBlock(hash=12630d16a9, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a9, nTime=1426450258, nBits=1e0fffff, nNonce=1312314, vtx=1, vchBlockSig=)
 *   CTransaction(hash=12630d16a9, nTime=1426450258, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
 *     CTxOut(empty)
 *   vMerkleTree: 12630d16a9
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint nBits, int nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "plz time stamp. stahp";
    const CScript genesisOutputScript = CScript() << ParseHex("0x0") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // Blocks 0 - 144999 are conventional difficulty calculation
        nMajorityEnforceBlockUpgrade = 750;
        nMajorityRejectBlockOutdated = 950;
        nMajorityWindow = 1000;
        BIP34Height = 99324612;
        BIP34Hash = uint256("0x4bd3308d384e80094e4659f9a3245e6f444688edbec0ad88b9a5dfd4be87454e");
        BIP65Height = 99324613; // 
        BIP66Height = 99324613; // 80d1364201e5df97e696c03bdd24dc885e8617b9de51e453c10a4f629b1e797a - this is the last block that could be v2, 1900 blocks past the last v2 block
        powLimit = CBigNum(~uint256(0) >> 20);
        fDigishieldDifficultyCalculation = false;
        fPowAllowMinDifficultyBlocks = false;
        fPowAllowDigishieldMinDifficultyBlocks = false;
        fPowNoRetargeting = false;
        nRuleChangeActivationThreshold = 750; // 95% of 10,080
        .nMinerConfirmationWindow = 1000; // 60 * 24 * 7 = 10,080 blocks, or one week
        vDeployments[DEPLOYMENT_TESTDUMMY].bit = 28;
        vDeployments[DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        vDeployments[DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        // XXX: BIP heights and hashes all need to be updated to Nyancoin values
        vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1612942090; // 
        vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1613546890; // 

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1612942090; // 
        vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 0; // Disabled

        // The best chain should have at least this much work.
        nMinimumChainWork = uint256("0x00000000000000000000000000000000000000000000000000fd6e84dd5364d4");  // Block 11461900

        // By default assume that the signatures in ancestors of this block are valid.
        defaultAssumeValid = uint256("0xb477d9bc0721a1b96547495404583d68123f471fdd1d4058a9adff2fa7452298");  // Block 11461900
        
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x65;
        pchMessageStart[1] = 0x44;
        pchMessageStart[2] = 0x15;
        pchMessageStart[3] = 0x06;
        nDefaultPort = 17014;
        nRPCPort = 17015;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        // CBlock(hash=000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90, nTime=1393221600, nBits=1e0fffff, nNonce=1312314, vtx=1, vchBlockSig=)
        // Coinbase(hash=12630d16a9, nTime=1426450258, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        // CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
        // CTxOut(empty)
        // vMerkleTree: 12630d16a9
        const char* pszTimestamp = "plz time stamp. stahp";
        // CTransaction txNew;
        // txNew.nTime = 1426450258;
        // txNew.vin.resize(1);
        // txNew.vout.resize(1);
        // txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        // txNew.vout[0].SetEmpty();
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1426450258, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1426450258;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 925125; 

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000032101032f27e7cdddb1196353f7fc9e1b6294717432135add95534f67c6"));
        assert(genesis.hashMerkleRoot == uint256("0x6e8089863e3811437cca6029c8eb113e0ddec4cb553e7cfdf8944c964cf86832"));

        vSeeds.push_back(CDNSSeedData("cloud.litedoge.info", "cloud.litedoge.info"));
        vSeeds.push_back(CDNSSeedData("seed01", "seed01.litedogeofficial.org"));
        vSeeds.push_back(CDNSSeedData("seed02", "seed02.litedogeofficial.org"));
        vSeeds.push_back(CDNSSeedData("seed03", "seed03.litedogeofficial.org"));
        vSeeds.push_back(CDNSSeedData("seed04", "seed04.litedogeofficial.org"));
        vSeeds.push_back(CDNSSeedData("seed05", "seed05.litedogeofficial.org"));
        vSeeds.push_back(CDNSSeedData("seed06", "seed06.litedogeofficial.org"));
        vSeeds.push_back(CDNSSeedData("seed07", "seed07.litedogeofficial.org"));
        vSeeds.push_back(CDNSSeedData("seed08", "seed08.litedogeofficial.org"));
        vSeeds.push_back(CDNSSeedData("lab-support-node0", "ldoge.nerdlabs001.com"));
        vSeeds.push_back(CDNSSeedData("lab-support-node1", "ldoge.nerdlabs001.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,90);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,8);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,171);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6, ARRAYLEN(pnSeed6));
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xbd;
        pchMessageStart[1] = 0xa5;
        pchMessageStart[2] = 0xd3;
        pchMessageStart[3] = 0xa7;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        nDefaultPort = 27099;
        nRPCPort = 27098;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 224610;
      
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000373f620a91549f65fe8c9938910e60a486d72b72376b8fad424c1762cce4"));
        
        vSeeds.push_back(CDNSSeedData("seed01", "seed01.litedogeofficial.org"));
        vSeeds.push_back(CDNSSeedData("seed02", "seed02.litedogeofficial.org"));
        vSeeds.push_back(CDNSSeedData("seed03", "seed03.litedogeofficial.org"));
        vSeeds.push_back(CDNSSeedData("seed04", "seed04.litedogeofficial.org"));
        vSeeds.push_back(CDNSSeedData("seed05", "seed05.litedogeofficial.org"));
        vSeeds.push_back(CDNSSeedData("seed06", "seed06.litedogeofficial.org"));
        vSeeds.push_back(CDNSSeedData("seed07", "seed07.litedogeofficial.org"));
        vSeeds.push_back(CDNSSeedData("seed08", "seed08.litedogeofficial.org"));
        vSeeds.push_back(CDNSSeedData("lab-support-node0", "ldoge.nerdlabs001.com"));
        vSeeds.push_back(CDNSSeedData("lab-support-node1", "ldoge.nerdlabs001.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,90);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,8);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,171);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xf2;
        pchMessageStart[1] = 0xa9;
        pchMessageStart[2] = 0xb7;
        pchMessageStart[3] = 0xca;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1426450258;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 1;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18445;
        nRPCPort = 18446;
        strDataDir = "regtest";

        assert(hashGenesisBlock == uint256("0x57c1442bbbb865ce8d3ac300e77cc8d584e8267e4670204235f07fdcb9554531"));
        
        vSeeds.push_back(CDNSSeedData("seed01", "seed01.litedogeofficial.org"));
        vSeeds.push_back(CDNSSeedData("seed02", "seed02.litedogeofficial.org"));
        vSeeds.push_back(CDNSSeedData("seed03", "seed03.litedogeofficial.org"));
        vSeeds.push_back(CDNSSeedData("lab-support-node0", "ldoge.nerdlabs001.com"));
        vSeeds.push_back(CDNSSeedData("lab-support-node1", "ldoge.nerdlabs001.com"));
    }
    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
