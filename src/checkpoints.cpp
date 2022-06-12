// Copyright (c) 2009-2022 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 500;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
            (        0, uint256("0x0000032101032f27e7cdddb1196353f7fc9e1b6294717432135add95534f67c6") )
            (    42700, uint256("0x3522c34b2e5b91abb7bb683885dd336b9b0cd8571a092845a58025a2f941a7a3") )
            (    50000, uint256("0xe2518a90420c32e88445952b694821b7eeafde7dd8f5162d8483fc66d3b7983f") )
            (    51000, uint256("0x46cff8875c28e4e55235d510498c068779d1865a6d533406664604b235a8ade3") ) //first hardfork ever
            (    52000, uint256("0xb3fbca721a9e57095341b1d6d54381e24f88cd56993badde3539889cd1940b20") )
            (    70000, uint256("0xe14279d5fe5429fd1304c323119eece4278151449afd2e7fa2621de63964e2ab") )
            (    90000, uint256("0x97c1e8226b7ee719c54ea702453f24cbb9b39e88a5e599941d77acc836784cdc") )
            (   100000, uint256("0x66c3dc5287b869c16509347d5962b3adfc9e52823a0a965e8076fc261ebfd9ef") )
            (   110000, uint256("0xef1fa40fbd008a0045fdf09a0c4afef2d2730cffa56c4f40cd16cb426d3f58bf") )
            (   120000, uint256("0x8739e3c8e29a939b03d051f7f3a3f9f6cb4254967efb5f6d77ab15a387e3a831") )
            (   130000, uint256("0x270640ca3fab9af25014892772cc6f471680aba26c440de540d2b9a2b5ac09ed") )
            (   200000, uint256("0xe517d2b6f40d92f9450afecb435ebb70edd4f8a188ecc0117b08602d9320bd75") )
            (   300000, uint256("0x1d589c00e8bea984edd81d1c985acad28af6f513f71c4303d8fedecb9cc9f965") )
            (   400000, uint256("0x1557b8443a9de9ef1cbb914f3e7fb3891b2160d3ea18dbd1f46d1756548570b5") )
            (   500000, uint256("0x5b5f21b3ff0d909bc130a2389955975cc6e58bc676ade61673434fe8d930f3c8") )
            (   600000, uint256("0x3bdf1f7d71cb95cebb66dda6bc860fe4de9580a0683adb3f84b560b139054197") )
            (   700000, uint256("0x16c6932214d30322de1539f419996576b1c6d1986585d247080787f165a5bf35") )
            (   800000, uint256("0xe9a3372cd2b6a5c1fc74818775b8a364de3c8b20db810dd238eac0ab85c1c1d3") )
            (   900000, uint256("0xc059a2de4bb0136f2c0af90c89f2645a70abca796b718452b92ee97a9e04a36b") )
            (  1000000, uint256("0x24377a41647b0918f5c44578679c12ae8842dcbc497fd5413da5a898705a7aa3") )
            (  1100000, uint256("0xd96b9b58d11c9c846564ee115d3e36f91aac0d663d751288c398fd349fe077c9") )
            (  1200000, uint256("0xd5d0dbec072e43d794bc57e2d88fa003d9916978da4108435f43098a5cd78c50") )
            (  1300000, uint256("0x5f818bdb6704f5065ffb0d38d5473b09eab5696fd012ef0b290b27ddad75fe09") )
            (  1400000, uint256("0x3d88b60e2f6bf7d7e78c752d797811d4c1efd7a4211c1457585ec375552371fd") )
            (  1500000, uint256("0x97385486ca2652ceff14685ad2dc269e8ff5668f826615761e174bd926eb0633") )
            (  1600000, uint256("0xe70b72565caa8431c4e2e2269b8a3331f707d2eb75169bdaeaf1eb39736b70d2") )
            (  1700000, uint256("0xcd2441a689f3b6a369dcfd9324f223c4b1eb005d4be7123f986adbc52a8d4796") )
            (  1800000, uint256("0x02b6d682836b05f53fc85a0eca90d845131ce8985798a74b923d3de4d679bf4c") )
            (  1900000, uint256("0xc834124386d368c280f81f4f48677affc1cdef64ee3380d85b04b5c1f00131d7") )
            (  2000000, uint256("0x5fc1a697c6b49a1918322501d9d218c2e68170a517541b2bafdd381bdaa6a7d1") )
            (  2100000, uint256("0x9d04bfff84c1366483f2577c86b677b3368c3fb11955ec00d8a7cba0c9418fe7") )
            (  2200000, uint256("0x47b2bf72fb7b8eafa201721fe047bac2b0faabc5aa739df8fb652a94c31d62fe") )
            (  2300000, uint256("0x0fb119a44047163f2af374398ecd378aed7e40464c92cdb417883bd9d1596b06") )
            (  2400000, uint256("0xfbe34eb653d4aa77b946b2914ad89d9073d82139fe89056f44ce5ea833c47874") )
            (  2500000, uint256("0x1aa02240052528ea82fa83055524ea6c2c6b4acf6c24ff219ff80c085afb6a50") )
            (  2600000, uint256("0x5758da40c83d4417a7b83666ce9b0e0de3aa59172b6bd31b022f63e5f6144a0e") )
            (  2700000, uint256("0x863a6148b7de6add3f6f28129d83b754ff9e677c6ff1c7c53722553e65b03d81") )
            (  2800000, uint256("0x63fb321514c94ef2f27e8dc491f59d24f7dfa5a7f4c11685d7cba03116deea82") )
            (  2900000, uint256("0xedde2f9ef2042c0f2e1d1e41a5d0e808f6a1b00105cbc5391394256b62d6b347") )
            (  3000000, uint256("0x37dda6d876516d5e10e90051bec6af6d119ea4b5ed15341ceda5da632d7d03db") )
            (  3100000, uint256("0x9cb444db23b150a8960e40a236bfa84d7ef4baff0ae1e8f325090ec90056ba10") )
            (  3110000, uint256("0xefa52a06ef737a99d12cc1a56ada8a76755753c4191a130824c79d58a17e6771") )
            (  3120000, uint256("0xc83a18455827010dd774d0ca7b5d0ad2055a8734658dff2269fea87e5f8feaf7") )
            (  3130000, uint256("0x1ffa5f4cb56456474ed56c50dbb6633b63ce6e934f27265ff939e72e13d2d1ee") )
            (  3140000, uint256("0x3e167f869bdebd897f952080ef6e974b7c748710994ec709023c4b5e81206e4d") )
            (  3150000, uint256("0xa7d7c35d2a2f539d5bdaf2b10b5120e39735cd81cb01bc7a8ba15fab8d0265f2") )
            (  3160000, uint256("0x1b45c9164bc69a1ad00e13e85cb11311e77fda12e4e5e19ce720e9bc78f2a6f7") )
            (  3170000, uint256("0x5d4c124e1d79f47e5d73bdf3706384025a49338b503a37b154e9f11be9ec825d") )
            (  3180000, uint256("0x79add22825f0ea5f2d2a106f0a600b69edc28a6eaed90d4cfde51dfd71052697") )
            (  3190000, uint256("0x702357d4732d0ca9f82b5a3663086dbe579fb409a1c912667fb5a9164e22ab64") )
            (  3200000, uint256("0x224dae21a581d34452f78cb5ee1f1fd42ad34a314a907bcf64e2bccaae0b5371") )
            (  3300000, uint256("0x38dea4213b70234b8b48c2bb7cd9d0fc50905607abce528a71a4fcaa60ad61d4") )
            (  3400000, uint256("0xb378df6ff0049b9cd1d3170e26dfbb7d2d022d8e60e163aad167b23550fc6f59") )
            (  3410000, uint256("0x4079f0ddc3403af52f4343d63d0569142f8d2de167ed286d882952527cd3fd51") )
            (  3415000, uint256("0x0235a965317d8af19834acdb57ddc340591508c68872409cacf19b26e7e317e5") )
            (  3420000, uint256("0x5b575f84afb8a4c5bc4c49aea5481de045fd2d8c53aad277c9db025b3c61c3c3") )











    ;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // ppcoin: synchronized checkpoint (centrally broadcasted)
    uint256 hashSyncCheckpoint = 0;
    uint256 hashPendingCheckpoint = 0;
    CSyncCheckpoint checkpointMessage;
    CSyncCheckpoint checkpointMessagePending;
    uint256 hashInvalidCheckpoint = 0;
    CCriticalSection cs_hashSyncCheckpoint;

    // ppcoin: get last synchronized checkpoint
    CBlockIndex* GetLastSyncCheckpoint()
    {
        LOCK(cs_hashSyncCheckpoint);
        if (!mapBlockIndex.count(hashSyncCheckpoint))
            error("GetSyncCheckpoint: block index missing for current sync-checkpoint %s", hashSyncCheckpoint.ToString());
        else
            return mapBlockIndex[hashSyncCheckpoint];
        return NULL;
    }

    // ppcoin: only descendant of current sync-checkpoint is allowed
    bool ValidateSyncCheckpoint(uint256 hashCheckpoint)
    {
        if (!mapBlockIndex.count(hashSyncCheckpoint))
            return error("ValidateSyncCheckpoint: block index missing for current sync-checkpoint %s", hashSyncCheckpoint.ToString());
        if (!mapBlockIndex.count(hashCheckpoint))
            return error("ValidateSyncCheckpoint: block index missing for received sync-checkpoint %s", hashCheckpoint.ToString());

        CBlockIndex* pindexSyncCheckpoint = mapBlockIndex[hashSyncCheckpoint];
        CBlockIndex* pindexCheckpointRecv = mapBlockIndex[hashCheckpoint];

        if (pindexCheckpointRecv->nHeight <= pindexSyncCheckpoint->nHeight)
        {
            // Received an older checkpoint, trace back from current checkpoint
            // to the same height of the received checkpoint to verify
            // that current checkpoint should be a descendant block
            CBlockIndex* pindex = pindexSyncCheckpoint;
            while (pindex->nHeight > pindexCheckpointRecv->nHeight)
                if (!(pindex = pindex->pprev))
                    return error("ValidateSyncCheckpoint: pprev null - block index structure failure");
            if (pindex->GetBlockHash() != hashCheckpoint)
            {
                hashInvalidCheckpoint = hashCheckpoint;
                return error("ValidateSyncCheckpoint: new sync-checkpoint %s is conflicting with current sync-checkpoint %s", hashCheckpoint.ToString(), hashSyncCheckpoint.ToString());
            }
            return false; // ignore older checkpoint
        }

        // Received checkpoint should be a descendant block of the current
        // checkpoint. Trace back to the same height of current checkpoint
        // to verify.
        CBlockIndex* pindex = pindexCheckpointRecv;
        while (pindex->nHeight > pindexSyncCheckpoint->nHeight)
            if (!(pindex = pindex->pprev))
                return error("ValidateSyncCheckpoint: pprev2 null - block index structure failure");
        if (pindex->GetBlockHash() != hashSyncCheckpoint)
        {
            hashInvalidCheckpoint = hashCheckpoint;
            return error("ValidateSyncCheckpoint: new sync-checkpoint %s is not a descendant of current sync-checkpoint %s", hashCheckpoint.ToString(), hashSyncCheckpoint.ToString());
        }
        return true;
    }

    bool WriteSyncCheckpoint(const uint256& hashCheckpoint)
    {
        CTxDB txdb;
        txdb.TxnBegin();
        if (!txdb.WriteSyncCheckpoint(hashCheckpoint))
        {
            txdb.TxnAbort();
            return error("WriteSyncCheckpoint(): failed to write to db sync checkpoint %s", hashCheckpoint.ToString());
        }
        if (!txdb.TxnCommit())
            return error("WriteSyncCheckpoint(): failed to commit to db sync checkpoint %s", hashCheckpoint.ToString());

        Checkpoints::hashSyncCheckpoint = hashCheckpoint;
        return true;
    }

    bool AcceptPendingSyncCheckpoint()
    {
        LOCK(cs_hashSyncCheckpoint);
        if (hashPendingCheckpoint != 0 && mapBlockIndex.count(hashPendingCheckpoint))
        {
            if (!ValidateSyncCheckpoint(hashPendingCheckpoint))
            {
                hashPendingCheckpoint = 0;
                checkpointMessagePending.SetNull();
                return false;
            }

            CTxDB txdb;
            CBlockIndex* pindexCheckpoint = mapBlockIndex[hashPendingCheckpoint];
            if (!pindexCheckpoint->IsInMainChain())
            {
                CBlock block;
                if (!block.ReadFromDisk(pindexCheckpoint))
                    return error("AcceptPendingSyncCheckpoint: ReadFromDisk failed for sync checkpoint %s", hashPendingCheckpoint.ToString());
                if (!block.SetBestChain(txdb, pindexCheckpoint))
                {
                    hashInvalidCheckpoint = hashPendingCheckpoint;
                    return error("AcceptPendingSyncCheckpoint: SetBestChain failed for sync checkpoint %s", hashPendingCheckpoint.ToString());
                }
            }

            if (!WriteSyncCheckpoint(hashPendingCheckpoint))
                return error("AcceptPendingSyncCheckpoint(): failed to write sync checkpoint %s", hashPendingCheckpoint.ToString());
            hashPendingCheckpoint = 0;
            checkpointMessage = checkpointMessagePending;
            checkpointMessagePending.SetNull();
            LogPrintf("AcceptPendingSyncCheckpoint : sync-checkpoint at %s\n", hashSyncCheckpoint.ToString());
            // relay the checkpoint
            if (!checkpointMessage.IsNull())
            {
                BOOST_FOREACH(CNode* pnode, vNodes)
                    checkpointMessage.RelayTo(pnode);
            }
            return true;
        }
        return false;
    }

    // Automatically select a suitable sync-checkpoint 
    uint256 AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex->GetBlockHash();
    }

    // Check against synchronized checkpoint
    bool CheckSync(const uint256& hashBlock, const CBlockIndex* pindexPrev)
    {
        if (TestNet()) return true; // Testnet has no checkpoints
        int nHeight = pindexPrev->nHeight + 1;

        LOCK(cs_hashSyncCheckpoint);
        // sync-checkpoint should always be accepted block
        assert(mapBlockIndex.count(hashSyncCheckpoint));
        const CBlockIndex* pindexSync = mapBlockIndex[hashSyncCheckpoint];

        if (nHeight > pindexSync->nHeight)
        {
            // trace back to same height as sync-checkpoint
            const CBlockIndex* pindex = pindexPrev;
            while (pindex->nHeight > pindexSync->nHeight)
                if (!(pindex = pindex->pprev))
                    return error("CheckSync: pprev null - block index structure failure");
            if (pindex->nHeight < pindexSync->nHeight || pindex->GetBlockHash() != hashSyncCheckpoint)
                return false; // only descendant of sync-checkpoint can pass check
        }
        if (nHeight == pindexSync->nHeight && hashBlock != hashSyncCheckpoint)
            return false; // same height with sync-checkpoint
        if (nHeight < pindexSync->nHeight && !mapBlockIndex.count(hashBlock))
            return false; // lower height than sync-checkpoint
        return true;
    }

    bool WantedByPendingSyncCheckpoint(uint256 hashBlock)
    {
        LOCK(cs_hashSyncCheckpoint);
        if (hashPendingCheckpoint == 0)
            return false;
        if (hashBlock == hashPendingCheckpoint)
            return true;
        if (mapOrphanBlocks.count(hashPendingCheckpoint) 
            && hashBlock == WantedByOrphan(mapOrphanBlocks[hashPendingCheckpoint]))
            return true;
        return false;
    }

    // ppcoin: reset synchronized checkpoint to last hardened checkpoint
    bool ResetSyncCheckpoint()
    {
        LOCK(cs_hashSyncCheckpoint);
        const uint256& hash = mapCheckpoints.rbegin()->second;
        if (mapBlockIndex.count(hash) && !mapBlockIndex[hash]->IsInMainChain())
        {
            // checkpoint block accepted but not yet in main chain
            LogPrintf("ResetSyncCheckpoint: SetBestChain to hardened checkpoint %s\n", hash.ToString());
            CTxDB txdb;
            CBlock block;
            if (!block.ReadFromDisk(mapBlockIndex[hash]))
                return error("ResetSyncCheckpoint: ReadFromDisk failed for hardened checkpoint %s", hash.ToString());
            if (!block.SetBestChain(txdb, mapBlockIndex[hash]))
            {
                return error("ResetSyncCheckpoint: SetBestChain failed for hardened checkpoint %s", hash.ToString());
            }
        }
        else if(!mapBlockIndex.count(hash))
        {
            // checkpoint block not yet accepted
            hashPendingCheckpoint = hash;
            checkpointMessagePending.SetNull();
            LogPrintf("ResetSyncCheckpoint: pending for sync-checkpoint %s\n", hashPendingCheckpoint.ToString());
        }

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            if (mapBlockIndex.count(hash) && mapBlockIndex[hash]->IsInMainChain())
            {
                if (!WriteSyncCheckpoint(hash))
                    return error("ResetSyncCheckpoint: failed to write sync checkpoint %s", hash.ToString());
                LogPrintf("ResetSyncCheckpoint: sync-checkpoint reset to %s\n", hashSyncCheckpoint.ToString());
                return true;
            }
        }

        if (!WriteSyncCheckpoint(Params().HashGenesisBlock()))
            return error("ResetSyncCheckpoint: failed to write sync checkpoint genesis block");
        LogPrintf("ResetSyncCheckpoint: sync-checkpoint reset to genesis block\n");
        return true;
    }

    void AskForPendingSyncCheckpoint(CNode* pfrom)
    {
        LOCK(cs_hashSyncCheckpoint);
        if (pfrom && hashPendingCheckpoint != 0 && (!mapBlockIndex.count(hashPendingCheckpoint)) && (!mapOrphanBlocks.count(hashPendingCheckpoint)))
            pfrom->AskFor(CInv(MSG_BLOCK, hashPendingCheckpoint));
    }

    bool SetCheckpointPrivKey(std::string strPrivKey)
    {
        // Test signing a sync-checkpoint with genesis block
        CSyncCheckpoint checkpoint;
        checkpoint.hashCheckpoint = Params().HashGenesisBlock();
        CDataStream sMsg(SER_NETWORK, PROTOCOL_VERSION);
        sMsg << (CUnsignedSyncCheckpoint)checkpoint;
        checkpoint.vchMsg = std::vector<unsigned char>(sMsg.begin(), sMsg.end());

        std::vector<unsigned char> vchPrivKey = ParseHex(strPrivKey);
        CKey key;
        key.SetPrivKey(CPrivKey(vchPrivKey.begin(), vchPrivKey.end()), false); // if key is not correct openssl may crash
        if (!key.Sign(Hash(checkpoint.vchMsg.begin(), checkpoint.vchMsg.end()), checkpoint.vchSig))
            return false;

        // Test signing successful, proceed
        CSyncCheckpoint::strMasterPrivKey = strPrivKey;
        return true;
    }

    bool SendSyncCheckpoint(uint256 hashCheckpoint)
    {
        CSyncCheckpoint checkpoint;
        checkpoint.hashCheckpoint = hashCheckpoint;
        CDataStream sMsg(SER_NETWORK, PROTOCOL_VERSION);
        sMsg << (CUnsignedSyncCheckpoint)checkpoint;
        checkpoint.vchMsg = std::vector<unsigned char>(sMsg.begin(), sMsg.end());

        if (CSyncCheckpoint::strMasterPrivKey.empty())
            return error("SendSyncCheckpoint: Checkpoint master key unavailable.");
        std::vector<unsigned char> vchPrivKey = ParseHex(CSyncCheckpoint::strMasterPrivKey);
        CKey key;
        key.SetPrivKey(CPrivKey(vchPrivKey.begin(), vchPrivKey.end()), false); // if key is not correct openssl may crash
        if (!key.Sign(Hash(checkpoint.vchMsg.begin(), checkpoint.vchMsg.end()), checkpoint.vchSig))
            return error("SendSyncCheckpoint: Unable to sign checkpoint, check private key?");

        if(!checkpoint.ProcessSyncCheckpoint(NULL))
        {
            LogPrintf("WARNING: SendSyncCheckpoint: Failed to process checkpoint.\n");
            return false;
        }

        // Relay checkpoint
        {
            LOCK(cs_vNodes);
            BOOST_FOREACH(CNode* pnode, vNodes)
                checkpoint.RelayTo(pnode);
        }
        return true;
    }
}

// ppcoin: sync-checkpoint master key
const std::string CSyncCheckpoint::strMasterPubKey = "048dd80d4ce2fb4bd05b70e3a7aaea1ffa68220c40958ce4404285b3f068a851e3288b6c229a7cf75c995eccde2b99910e701d227f3e358fec90c952e54a92a537";

std::string CSyncCheckpoint::strMasterPrivKey = "";

bool CSyncCheckpoint::RelayTo(CNode* pnode) const
{
    // don't relay to nodes which haven't sent their version message
    if (pnode->nVersion == 0)
        return false;
    // returns true if wasn't already sent
    if (pnode->hashCheckpointKnown != hashCheckpoint)
    {
        pnode->hashCheckpointKnown = hashCheckpoint;
        pnode->PushMessage("checkpoint", *this);
        return true;
    }
    return false;
}

// ppcoin: verify signature of sync-checkpoint message
bool CSyncCheckpoint::CheckSignature()
{
    CPubKey key(ParseHex(CSyncCheckpoint::strMasterPubKey));
    if (!key.Verify(Hash(vchMsg.begin(), vchMsg.end()), vchSig))
        return error("CSyncCheckpoint::CheckSignature() : verify signature failed");

    // Now unserialize the data
    CDataStream sMsg(vchMsg, SER_NETWORK, PROTOCOL_VERSION);
    sMsg >> *(CUnsignedSyncCheckpoint*)this;
    return true;
}

// ppcoin: process synchronized checkpoint
bool CSyncCheckpoint::ProcessSyncCheckpoint(CNode* pfrom)
{
    if (!CheckSignature())
        return false;

    LOCK(Checkpoints::cs_hashSyncCheckpoint);
    if (!mapBlockIndex.count(hashCheckpoint))
    {
        // We haven't received the checkpoint chain, keep the checkpoint as pending
        Checkpoints::hashPendingCheckpoint = hashCheckpoint;
        Checkpoints::checkpointMessagePending = *this;
        LogPrintf("ProcessSyncCheckpoint: pending for sync-checkpoint %s\n", hashCheckpoint.ToString());
        // Ask this guy to fill in what we're missing
        if (pfrom)
        {
            PushGetBlocks(pfrom, pindexBest, hashCheckpoint);
            // ask directly as well in case rejected earlier by duplicate
            // proof-of-stake because getblocks may not get it this time
            pfrom->AskFor(CInv(MSG_BLOCK, mapOrphanBlocks.count(hashCheckpoint)? WantedByOrphan(mapOrphanBlocks[hashCheckpoint]) : hashCheckpoint));
        }
        return false;
    }

    if (!Checkpoints::ValidateSyncCheckpoint(hashCheckpoint))
        return false;

    CTxDB txdb;
    CBlockIndex* pindexCheckpoint = mapBlockIndex[hashCheckpoint];
    if (!pindexCheckpoint->IsInMainChain())
    {
        // checkpoint chain received but not yet main chain
        CBlock block;
        if (!block.ReadFromDisk(pindexCheckpoint))
            return error("ProcessSyncCheckpoint: ReadFromDisk failed for sync checkpoint %s", hashCheckpoint.ToString());
        if (!block.SetBestChain(txdb, pindexCheckpoint))
        {
            Checkpoints::hashInvalidCheckpoint = hashCheckpoint;
            return error("ProcessSyncCheckpoint: SetBestChain failed for sync checkpoint %s", hashCheckpoint.ToString());
        }
    }

    if (!Checkpoints::WriteSyncCheckpoint(hashCheckpoint))
        return error("ProcessSyncCheckpoint(): failed to write sync checkpoint %s", hashCheckpoint.ToString());
    Checkpoints::checkpointMessage = *this;
    Checkpoints::hashPendingCheckpoint = 0;
    Checkpoints::checkpointMessagePending.SetNull();
    LogPrintf("ProcessSyncCheckpoint: sync-checkpoint at %s\n", hashCheckpoint.ToString());
    return true;
}
