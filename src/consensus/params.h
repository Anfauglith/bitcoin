// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Copyright (c) 2017 IoP Ventures LLC
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef IOP_CONSENSUS_PARAMS_H
#define IOP_CONSENSUS_PARAMS_H

#include "uint256.h"
#include <map>
#include <set>
#include <string>

namespace Consensus {

enum DeploymentPos
{
    DEPLOYMENT_TESTDUMMY,
    DEPLOYMENT_CSV, // Deployment of BIP68, BIP112, and BIP113.
    DEPLOYMENT_SEGWIT, // Deployment of BIP141, BIP143, and BIP147.
    // NOTE: Also add new deployments to VersionBitsDeploymentInfo in versionbits.cpp
    MAX_VERSION_BITS_DEPLOYMENTS
};

/**
 * Struct for each individual consensus rule change using BIP9.
 */
struct BIP9Deployment {
    /** Bit position to select the particular bit in nVersion. */
    int bit;
    /** Start MedianTime for version bits miner confirmation. Can be a date in the past */
    int64_t nStartTime;
    /** Timeout/expiry MedianTime for the deployment attempt. */
    int64_t nTimeout;
};

/**
 * Parameters that influence chain consensus.
 */
struct Params {
    uint256 hashGenesisBlock;
    int nSubsidyHalvingInterval;
    /* **** IOP CHANGE //
    IoP Chain uses the coinbase content to store the miner signature, so we can not enforce BIP34 in its current form.
    So deactivate the check for BIP34 completely. BIP65 and BIP66 are enforced from the beginning 
    // **** IOP CHANGE */
    /** Block height and hash at which BIP34 becomes active */
    // int BIP34Height;
    // uint256 BIP34Hash;
    /** Block height at which BIP65 becomes active */
    // int BIP65Height;
    /** Block height at which BIP66 becomes active */
    // int BIP66Height;
    /**
     * Minimum blocks including miner confirmation of the total of 2016 blocks in a retargeting period,
     * (nPowTargetTimespan / nPowTargetSpacing) which is also used for BIP9 deployments.
     * Examples: 1916 for 95%, 1512 for testchains.
     */
    uint32_t nRuleChangeActivationThreshold;
    uint32_t nMinerConfirmationWindow;
    BIP9Deployment vDeployments[MAX_VERSION_BITS_DEPLOYMENTS];
    /** Proof of work parameters */
    uint256 powLimit;
    bool fPowAllowMinDifficultyBlocks;
    bool fPowNoRetargeting;
    int64_t nPowTargetSpacing;
    int64_t nPowTargetTimespan;
    int64_t blocktimeAdjustmentHeight;
    int64_t blocktimeReductionFactor;
    int64_t DifficultyAdjustmentInterval() const { return nPowTargetTimespan / nPowTargetSpacing; }
    uint256 nMinimumChainWork;
    uint256 defaultAssumeValid;



     /* IoP beta release - Miner White List params */
     unsigned int minerWhiteListActivationHeight;
     std::set<std::string> minerWhiteListAdminPubKey;
     std::set<std::string> minerWhiteListAdminAddress;
     unsigned int minerCapSystemChangeHeight;
 
    //  int nPowSubsidyIncreaseHeight;
     /* Voting System Parameters */
    //  int ccBlockStartAdditionalHeight; // this amount of blocks is used to calculate the start of a CC. Current Height + n + User Provided CC height
     unsigned int ccLastCCBlockHeight;
};
} // namespace Consensus

#endif // IOP_CONSENSUS_PARAMS_H
