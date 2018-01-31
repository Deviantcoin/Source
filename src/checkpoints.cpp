// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 5000;

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
        (0,	Params().HashGenesisBlock() )
		(11, uint256("0xe888335045b9a26f0e5c23d397531bdf0675c2e82ee770a0f8a8df07b48b242a"))
		(26, uint256("0xa1d3531bfe1c0a057f5218ddec9459f5adb214f5c4ac1dcf6fc4dbe71fec1d4a"))
		(42, uint256("0xe09bc55c77d399a647143c6581e7e9581ef0cde4333af5b73c848b6bdc556524"))
		(49, uint256("0xf74b1c9c869e8f647163d6de5a76870ccf19027bccb2e13de8bae71e9deabf5b"))
		(527, uint256("0x0444f8c42866530a0ff5bfb81b9fb57ac847eaea71ae6081bbdc80402e07a373"))
		(1548, uint256("0x8150c0deaa6ba6562f968c712698bbcfefb2e621a41c9b66d02c6b84898636dd"))
		(2192, uint256("0xca69d14c613732e23f9716b3bbafc3fd9aaba7df3bce634d6a35d155a79f1ac3"))
		(2620, uint256("0x19abcbb1acd7d4d09861cc156139210463206b270bf82c0b838e7dd639029d58"))
		(2621, uint256("0x69cec274d07108577ddeaab3ba57aa94091f85b6741c3915edec0ef7bc7c61ff"))
		(2622, uint256("0xc68061fa2a4f83574bd2908eb3485d4e7bcfd662df641c66626d86448c300176"))
		(3082, uint256("0xd7464b2009ecbcfc82240856aa23cc5d6f51d1179445f5465ebafa512d33b18e"))
		
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

    // Automatically select a suitable sync-checkpoint 
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();
        if (nHeight <= pindexSync->nHeight){
            return false;
        }
        return true;
    }
}
