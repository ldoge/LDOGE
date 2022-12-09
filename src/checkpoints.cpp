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
            (        1, uint256("0x8340e43b90828268419b18cfd40bbb1082c48d314ccd6f980eb5649b9503a5cc") )
            (       10, uint256("0x51e921bd45e607c9afc4f393aa9376e91dcc4fe410998dc3220b3d9dcc986031") )
            (      100, uint256("0xaa7114900059c905d6ac4c17c6fb4422d9ff16e241ab14104529b63ac41db8e3") )
            (      500, uint256("0xb586093f6d74c62e5b31e0cee334aec84cad3c53f69969271c52fb6dd3915911") )
            (      750, uint256("0x0bca3e379edbabf60dfe7a7c7d7c647cb32e9465f400d71eacbdc24464d56881") )
            (      775, uint256("0x9e9915c5523bccf938a3fa2790e450d405bcec4f3792a61777762a6040868981") )
            (      800, uint256("0xffbec1ff3aef421a717a06b3d245e1047fe560ebf41451d2b92d89bde688becb") )
            (      850, uint256("0xa5f1b9a29c6ea116487b72dc3c14c2c72fc96a9e8d04c5584ec7fd0bb485a923") )
            (      900, uint256("0x20e37e4f119497735ad20120bc49f1798c8d5bed445b802c36fff6ca31bb2a6e") )
            (      950, uint256("0xb9bfa30fb8654da75f7d38954419b88d22abf70c665ec2ebe4b0bde93370287e") )
            (      975, uint256("0x3088fc3b53ba01cfb0c1a22e02260dd2d65205290de49e5e0bac7c369abe58f5") )
            (     1000, uint256("0x0b8f35d5f8b2193c7d3387ec1eebfcc85542135fda57a9b55fc1689c98be486a") )
            (     1250, uint256("0x0b8c690d34ed51c8091c42e8457c74ec31b588e4166f4176e7dd156146b2b769") )
            (     2000, uint256("0x44e0027a7354e256a2ec259591d13a9588d0410c423ae6fc2b067bfc9671408b") )
            (     2500, uint256("0x03ffd3394a80fa450e11135e2bf4d8faec423efc75b8493a572291b862747e59") )
            (     3000, uint256("0x5723e6320ff6a874799d2f9bd755dda03c76dc7a1973c3de950c4a801b9a0380") )
            (     3750, uint256("0xac36f8412d8bdb6f31ed7f25b6814b3d76302b1b3ca9bc9080713e581db9762b") )
            (     4000, uint256("0x91263d39203077149075e6fb4de83275050fdeeea435144804f44c02c7f9a172") )
            (     5000, uint256("0x4080a0f099f47402e76d626077b80c0fd87140482d3441e84128122751089b95") )
            (     5500, uint256("0x6e112af3ddfcf2f5b95c99b422008f7526e047ffd357ff640f3028c77c6ee9b3") )
            (     5750, uint256("0x240f45d9f06744beba51b1387dbde604be32cbe4cfffb8a386d8e944dcb4895a") )
            (     6000, uint256("0xe4be6b2121828adc3ba61691d6d27f81fada1f6ce4bab3cb9b485d717bb6a977") )
            (     6025, uint256("0x331cbe0dba242c203b64080a1cadf6befccdf055613986821c3c1e061f8fa22e") )
            (     6100, uint256("0x201945534fb013d7ec38da646332ff94acaaffd416be5463c9df35ee80263b6d") )
            (     6250, uint256("0xb68a442c28a9721725e7c163c8745ffeec9067fcc49381fd28c55c551a37f806") )
            (     6300, uint256("0xb490a980c52a236cb0e104baa4b275bbb6c3a164b32d385307d36bd9e41ff414") )
            (     6500, uint256("0xddea84f1319c53a592fc005b7cbb703b6797f60d1817f4e0c4b11af1eeb11e95") )
            (     6700, uint256("0x3001a024d925fc3803f3b5a52c1e3c59c1bd5cd4aa04e120748b70667d8c89c0") )
            (     6900, uint256("0x1c8c2edccc1505e979122777befcd0df8c2cbe20ef71ee1e50b30342a93b67fa") )
            (     7000, uint256("0xcf3813a337cbd0f4f5a83c08c649095a814832418322cc195966012cabe415ff") )
            (     7500, uint256("0xc6c1a6f6f3e9737b2d850b3ee20b70054b48ec09a03ce3deb427c50ec15a8e80") )
            (     7750, uint256("0x32a60afd5c6ada2999945ce0ed356e56a6508833de9cbb378a2f7bde6904198c") )
            (     7950, uint256("0x69d2e1aba30658eb06336c564f53cd9542d04e1be86edee6b7b9f6ff23b8eea3") )
            (     8000, uint256("0xb3d0df43c60ce93853cbae43061c9c1bea89eddbf4b621ed1880c85fc065051c") )
            (     9000, uint256("0x3e64239e6fdeb3fbdcc204a10124fbe90c017298491194c45f28f35ed04ab24e") )
            (    10000, uint256("0x684e3f696c52c1098678af79daeabd1f719f8bbf7450b694ca18d30a3403b5b7") )
            (    20000, uint256("0xf931e068bbeb87d6d41d9c04b2c2eb4b32413bcbdf4353dff42bb1d12564929e") )
            (    30000, uint256("0x223a52e9335eb6cbc39157e55721b3f17b50bf3b0b63b01940ed56bcf462a967") )
            (    40000, uint256("0xd7397dfafe4187dec15d410bf9fd04a97102ebe453f26f36f4a18995617c80d0") )
            (    40500, uint256("0x673451c7f1500ea26eb73937207d8944105d7083d10babce9456e2db606449fe") )
            (    41000, uint256("0xd20f7edb22dbb767d24e7c5b11a3eafac0a31b2e76f9e74935139491ef50a532") )
            (    41500, uint256("0x6398c76f2a53e2c06bd4256efe8ffbede6a80ebe079bf1a72e9f70bc1b15384e") )
            (    42000, uint256("0x351201b850ba062c7a1f2640817afee21e51f3eed1671edc84ee0c15a8bdef47") )
            (    42250, uint256("0x4924aca05def717e3261bbb51a14d5f293a966117fbb52e4b39dad7ccefbfe60") )
            (    42500, uint256("0x8960c690f875495557361810b179440f0bd7bf19212c4eaf5060bceafe1fb8db") )
            (    42700, uint256("0x3522c34b2e5b91abb7bb683885dd336b9b0cd8571a092845a58025a2f941a7a3") )
            (    42800, uint256("0x8f1572051e200416e063143a2df1dbd954cdd8c07e3c18a52975ee983e967d14") )
            (    42900, uint256("0x916ef8572a77de294ca84581df1ac925be04b0f63129af71b79330266919d785") )
            (    42950, uint256("0x870218ddb84c0d4b58abe6fe3756dcb9086084cfb12cd452ae09c62744a04e64") )
            (    43000, uint256("0xde47c9a45480f99e8f5542f487873fd8fd8091eafa74deb7faa8a5705b70cd17") )
            (    45000, uint256("0x776c8dedce6ff8f9c2d13f8c94cf8015a2b85ca16ed60c9880a6f21e067d0e2a") )
            (    46000, uint256("0xd0cfa488b2cd227aa539905d01f2e065155f10bf9bd498f6f6378f0c5099e8ae") )
            (    47000, uint256("0xa963e6a461d0c7171c1e92883cdcef44b95f5611a29dd94d9cc403b3ce20685d") )
            (    48000, uint256("0x370cd2e8549d3d663ed3632464422a8c9549ca37c39c209d725a7f69796f7272") )
            (    49000, uint256("0x40aebc3ccfa296109e6a8037ca729888003b32bfd3850a1cfe3fd1f5f3b938eb") )
            (    49100, uint256("0xa07ecbdb8b6fa00a54cbfd77b76e47cc08c4688e15f512b255c22f0ad3bf79b8") )
            (    49200, uint256("0x89d9baced62e5cf233f9a1a6db45c31cf23f627bac16a893c75a4b832f30569b") )
            (    49500, uint256("0xb8f44eacf603f3ed488b519177841e5fddd5cc25d2b9dbff4b9874599914987c") )
            (    49750, uint256("0x09deae291124815ac6dbeb4ca5769c668ee6cd7cc39b53bb332371d395a53e5e") )
            (    50000, uint256("0xe2518a90420c32e88445952b694821b7eeafde7dd8f5162d8483fc66d3b7983f") )
            (    50500, uint256("0x3cf556bea282b78ef76bd4fd1a855a6e865de1a02d519c330b4e14bcc3e47254") )
            (    51000, uint256("0x46cff8875c28e4e55235d510498c068779d1865a6d533406664604b235a8ade3") ) //first hardfork ever
            (    51001, uint256("0xd68a3a22b66476f1deaceadf93afba76ad1783dc68fd97312cb9791a7ccd7781") )
            (    51100, uint256("0xc5bf8e58b7e6e7db37b6dccc1f412e5582bf6eb4533e5fc51230a1f4be3efb5a") )
            (    52000, uint256("0xb3fbca721a9e57095341b1d6d54381e24f88cd56993badde3539889cd1940b20") )
            (    52500, uint256("0x7f8702c2e9e26569b645fa10b2d7925a580ee39576f6451d0b7228e7aa6ee114") )
            (    55000, uint256("0xdb196a2fc3cfead392608e9f133dca6217173fa1c1fabcf1b20f413d60bb930c") )
            (    60000, uint256("0x71d24e1a35618d912ae014913f7e8f0eb0cb9b4f9dd279452c1e569f48386fec") )
            (    62500, uint256("0x96e8cab3a6702fcb5803fb58605ae988063fc11410cd6fc4a9216dac137ca22c") )
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
            (  3450000, uint256("0x9e5be94304bf1297cd897cc19c79cf58d3d7a456d7940b715bc89aa0e28bba15") )
            (  3452753, uint256("0xdcad10d37ee4d8e8ba1879186e01e2f1df96b2183b9e9b38550ea086427cfe2c") )
            (  3453000, uint256("0x7c99a9a9186a7529a9c98af0a6d78ce07382cc1b31b4fe73cc49bc698ac10f9f") )
            (  3455000, uint256("0x219db3d77782313906655bee9f94196e97e63d37e7c22b9aec1ee86f10c8cb3b") )
            (  3458000, uint256("0xbf14b6cc1f88a967fa2ed4ddfaaabbcbc5d5532f5e12990a36d97c37cbe4620f") )
            (  3460000, uint256("0x94d1b72660acb46e38e2f320c7bab254556719e6e541b672c49f1534f662e27b") )
            (  3461000, uint256("0x794691feb1cbc75fb541aa2ba93b16e67d29bf1a267cff85525594aabd23ba95") )
            (  3462000, uint256("0x13ebe5030a2eb3e4602c91c67071827c0e0bf4883e40490bfc3bdb4a32b7444b") )
            (  3465000, uint256("0xaf32cacd0fd487ea3a8be3555894870ec47a3a0ada33ec588f62c2935d4ae98f") )
            (  3468000, uint256("0x0db720de476421048bfcc7c7e3c3bfc5c5ddac43edf614c9968ffb44473e2e75") )
            (  3469000, uint256("0x3c50b80372bcfab08b2686d5423586fb6d3e67aef015a80bfeb3c609c09da95b") )
            (  3470000, uint256("0x0e1e65229f4d7170e8d3f39f3338c9ef0f38acbafa6e788d2e46e03d15d6a3df") )
            (  3500000, uint256("0x6b78f4503525562dd25af65ca4503a39f952971b5fd2e156fec6902d6ecf7bed") )
            (  3600000, uint256("0xf088071944a095fb038a4c8374b4afbf65f6c5b5fd50e20889261366626a26ac") )
            (  3650000, uint256("0x6a99179ee067b2953b35fd0eb9ff6e63c24434672f195f05ff46402406465bd0") )
            (  3653000, uint256("0x045bd71684665c6553b96fcc972f6159b850cf2039b66d555cf2eb0a64d6a2e1") )












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
