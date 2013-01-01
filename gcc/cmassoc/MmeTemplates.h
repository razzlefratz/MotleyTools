/****************************************************************************
 *   
 *   Copyright(c) 2005 by Intellon Corp. ALL RIGHTS RESERVED.
 *   
 *   This Information is proprietary to Intellon Corporation, Ocala, Florida
 *   (Intellon) and MAY NOT be copied by any method or incorporated into
 *   another program without the express written consent of Intellon. This
 *   Information	or any portion thereof remains the property of Intellon. The
 *   Information	contained herein is believed to be accurate and Intellon
 *   assumes no responsibility or liability for its use in any way and conveys
 *   no license or title under any patent or copyright and makes no
 *   representation or warranty that this Information is free from patent or
 *   copyright infringement.
 *   
 *   
 *   File:		MmeTemplates.h
 *   
 *   Author(s):	Frank Aiello			2005/08/15
 *   Treina Cresse			2005/08/15
 *   
 *   Contains:	Manangement Message Templates
 *   
 *   --
 *   $File: //thunderbolt/software/main/common/include/MmeTemplates.h $
 *   $Revision: 1.2 $
 *   
 *   $Change: 120684 $
 *   $Author: charlesmaier $
 *   $DateTime: 2009/06/01 20:42:51 $
 *   
 ****************************************************************************/

#ifndef __CCMMETEMP_H__
#define __CCMMETEMP_H__

//Note: This File is shared outside of FW. Do not use FW specific includes or code

#include "generic.h" 
#include "PowerAVProtocol.h"

#if defined(INT_MNT) || defined(__CC_ARM) || defined(ENGINEERING_SW)
#include "EngineeringMmeTemplates.h"
#else

// MME Type - 2 LSB's

enum 

{
	eReq = 0x0000,
	eCnf = 0x0001,
	eInd = 0x0002,
	eRsp = 0x0003
};


// MME Type - 3 MSB's

enum 

{
	eCC = 0x0000,
	eCP = 0x2000,
	eNN = 0x4000,
	eCM = 0x6000,
	eMS = 0x8000,
	eVS = 0xA000
};


//0b000 0b001 0b010 0b011 0b100 0b101

#endif

#ifdef WIN32

#define __packed

#pragma pack(push, mmes, 1)
#endif

// Station <-> Central Coordination// ------------------------------------------------------------

//0x0000 CC_CCO_APPOINT (REQ, CNF)

__packed class CC_CCO_APPOINT 

{
public:
	enum 
	{
		eMMType = 0x0000,

// CC_CCO_APPOINT

		eMMTypeReq = eCC | eMMType | eReq,

// .Req

		eMMTypeCnf = eCC | eMMType | eCnf // .Cnf

	};
	class EEAppointmentResult 
	{
	public:
		enum 
		{
			eSuccess = 0,
			eFailureRejected = 1,
			eFailureUnknownSTA = 2
		};
	};
	__packed class Req 
	{
	public:
		CCMACAddress mMACAddress;

// MAC address of the STA that should become the new CCo

	};
	__packed class Cnf 
	{
	public:
		uint8 mResult;

// 0=accepted, 1=rejected, 2=unknown MAC address

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0x0008 CC_LINK_INFO (REQ, CNF, IND, RSP )

__packed class CC_LINK_INFO 

{
public:
	enum 
	{
		eMMType = 0x0008,

// CC_LINK_INFO

		eMMTypeReq = eCC | eMMType | eReq,

// .Req

		eMMTypeCnf = eCC | eMMType | eCnf,

// .Cnf

		eMMTypeInd = eCC | eMMType | eInd,

// .Ind

		eMMTypeRsp = eCC | eMMType | eRsp // .Rsp

	};
	__packed class CLinkInfo 
	{
	public:
		uint8 mLID;
	};
	__packed class Req 
	{

// The message field for this MME is NULL

	};
	__packed class Cnf 
	{
	public:
		uint8 mNumberLinkInfo;

// Number of LinkInfo fields to follow

	};
	__packed class Ind 
	{
	public:
		uint8 mNumberLinkInfo;

// Number of LinkInfo fields to follow

	};
	__packed class Rsp 
	{

// The message field for this MME is NULL

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
		Ind IND;
		Rsp RSP;
	};
};


//0x0014 CC_DISCOVER_LIST (REQ, CNF)

__packed class CC_DISCOVER_LIST 

{
public:
	enum 
	{
		eMMType = 0x0014,

// CC_DISCOVER_LIST

		eMMTypeReq = eCC | eMMType | eReq,

// .Req

		eMMTypeCnf = eCC | eMMType | eCnf,

// .Cnf

		eMMTypeInd = eCC | eMMType | eInd // .Ind		

	};
	enum 
	{
		eMaxMmeDataSize = 4500 //Force Allocation of 4 Mme Buffers to guarantee
 //we can account for Max Stations of 254 and
 //Max Networks of 16.

	};
	__packed class CCSTAInfo 
	{
	public:
		CCMACAddress mMACAddr;
		uint8 mTEI;
		uint8 mSameNetwork;
		uint8 mSNID_Acess;
		uint8 mCCoCapabilities_Status;
		uint8 mSignalLevel;
		uint8 mAverageBLE;
	};
	__packed class CCNetInfo 
	{
	public:
		CCNetworkID mNID;
		uint8 mSNID;
		uint8 mHybridMode;
		uint8 mNumSlots;
		uint8 mCoordinatingStatus;
		uint16 mOffset;
	};
	__packed class Req 
	{
	public:

//NULL

	};
	__packed class Cnf 
	{
	public:
		enum 
		{
			eBaseSize = 1,
			eArrayUnitSize = 12,
			eMaxSTA = 124
		};
		uint8 mNumStations;

//Number of Discovered stations

		CCSTAInfo mSTAInfos [eMaxSTA];

//Arrray of Discovered Station Infos

	};
	__packed class Cnf_Part2 
	{
	public:
		enum 
		{
			eBaseSize = 1,
			eArrayUnitSize = 13,
			eMaxNet = 115
		};
		uint8 mNumNetworks;

//Number of Discovered Networks

		CCNetInfo mNetInfos [eMaxNet];

//Arrray of Discovered Network Infos

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
		Cnf IND;
	};
};


//0x002C CC_WHO_RU (REQ, CNF)

__packed class CC_WHO_RU 

{
public:
	enum 
	{
		eMMType = 0x002C,

// CC_WHO_RU

		eMMTypeReq = eCC | eMMType | eReq,

// .Req

		eMMTypeCnf = eCC | eMMType | eCnf // .Cnf

	};
	__packed class Req 
	{
	public:
		CCNetworkID mNID;

// Network identifier

	};
	__packed class Cnf 
	{
	public:
		CCNetworkID mNID;

// Network identifier

		CCMACAddress mCMAC;

// MAC address of AVLN's CCo

		CCHFID mHFID;

// AVLN's "human-friendly" identifier

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


// Station <-> Station// ------------------------------------------------------------//0x6004 CM_ENCRYPTED_PAYLOAD (IND, RSP)

__packed class CM_ENCRYPTED_PAYLOAD 

{
public:
	enum 
	{
		eMMType = 0x0004,

// CM_ENCRYPTED_PAYLOAD

		eMMTypeInd = eCM | eMMType | eInd,

// .Ind

		eMMTypeRsp = eCM | eMMType | eRsp // .Rsp	

	};
	enum 
	{
		eStatus_UnAssoc_L0 = 0,
		eStatus_UnAssoc_L1 = 1,
		eStatus_UnAssoc_L2 = 2,
		eStatus_UnAssoc_L3 = 3,
		eStatus_Assoc_NotPCoCap = 4,
		eStatus_Assoc_PCoCap = 5,
		eStatus_CCo_ofAVLN = 8
	};
	__packed class Ind 
	{
	public:
		enum 
		{
			eFixedLen = 24,
			eMinRFLen = 0,
			eMaxRFLen = 15
		};
		uint8 mPEKS;

//Payload Encryption Key Select

		uint8 mAVLNStatus;

//AVLN status

		uint8 mPID;

//Protocol ID

		uint16 mPRN;

//Protocol Run Number

		uint8 mPMN;

//Protocol Message Number

		CCEncryptionKey mIV;

//IV

		uint16 mLength;

//Length of MME in Encrypted Payload

		uint8 mRFiller [16];

//Random Filler (Encrypted)

	};
	__packed class Ind_Part2 
	{
	public:
		uint8 mMMEBody [1024];

//MME (Encrypted)

	};
	__packed class Ind_Part3 
	{
	public:
		enum 
		{
			eFixedLen = 9
		};
		uint32 mCRC;

//CRC

		uint8 mPID_E;

//Protocol ID (Encrypted)

		uint16 mPRN_E;

//Protocol Run Number(Encrypted)

		uint8 mPMN_E;

//Protocol Message Number(Encrypted)

		uint8 mPAD [c128bitInBytes];

//Padding to adjust to 16 byte boundary

//uint8 mRFLen; //Random Filler length (0-15) (Encrypted) - alway last byte of MME

	};
	__packed class Rsp 
	{
	public:
		enum 
		{
			eSuccess = 0,
			eFailure = 1,
			eAbort = 2
		};
		uint8 mResult;

//Result

		uint8 mPID;

//Protocol ID

		uint16 mPRN;

//Protocol Run Number

	};
	__packed union 
	{
		Ind IND;
		Rsp RSP;
	};
};


//0x6008 CM_SET_KEY (REQ, CNF)

__packed class CM_SET_KEY 

{
public:
	enum 
	{
		eMMType = 0x0008,

// CM_SET_KEY

		eMMTypeReq = eCM | eMMType | eReq,

// .Req

		eMMTypeCnf = eCM | eMMType | eCnf // .Cnf		

	};

// Key Types

	enum 
	{

// eKeyType_DAK = 0,not used

		eKeyType_NMK = 1,
		eKeyType_NEK = 2,
		eKeyType_TEK = 3,
		eKeyType_HASH = 4,
		eKeyType_NonceOnly = 5
	};

// Request Types

	enum 
	{
		eReqType_Direct = 0,
		eReqType_Relayed = 1,
		eReqType_Reserved = 255
	};
	__packed class Req 
	{
	public:
		uint8 mKeyType;

// Key Type

		uint32 mMyNonce;

// My Nonce

		uint32 mYourNonce;

// Your Nonce

		uint8 mPID;

// Protocol ID

		uint16 mPRN;

// Protocol Run Number

		uint8 mPMN;

// Protocol Message Number

		uint8 mCCoCapability;

// CCo Capabilities

		CCNetworkID mNID;

// NID

		uint8 mNewEKS;

// New EKS

		CCEncryptionKey mAESKey;

// New AES Encryption Key

	};
	__packed class Cnf 
	{
	public:
		enum 
		{
			eFailure = 0,
			eSuccess = 1
		};
		uint8 mResult;

// Result

		uint32 mMyNonce;

// My Nonce

		uint32 mYourNonce;

// Your Nonce

		uint8 mPID;

// Protocol ID

		uint16 mPRN;

// Protocol Run Number

		uint8 mPMN;

// Protocol Message Number

		uint8 mCCoCapability;

// CCo Capabilities

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0x600C CM_GET_KEY (REQ, CNF)

__packed class CM_GET_KEY 

{
public:
	enum 
	{
		eMMType = 0x000C,

// CM_GET_KEY

		eMMTypeReq = eCM | eMMType | eReq,

// .Req

		eMMTypeCnf = eCM | eMMType | eCnf // .Cnf		

	};

// Result Codes

	enum tResult 
	{
		eResult_KeyGranted = 0,
		eResult_RequestRefused = 1,
		eResult_BadMethod_Key = 2 //eResult_WaitForUserInput = 2,
 //eResult_RequestTimeOut = 3,
 //eResult_InvalidKeyType = 4,
 //eResult_Reserved = 255

	};
	__packed class Req 
	{
	public:
		uint8 mReqType;

// Req Type

		uint8 mKeyType;

// Req Type

		CCNetworkID mNID;

// Network identifier

		uint32 mMyNonce;

// My Nonce

		uint8 mPID;

// Protocol ID

		uint16 mPRN;

// Protocol Run Number

		uint8 mPMN;

// Protocol Message Number

		CCHashKey mHashKey;

// Hash Key

	};
	__packed class Cnf 
	{
	public:
		uint8 mResult;

// Status of Request

		uint8 mKeyType;

// Key Type

		uint32 mMyNonce;

// My Nonce

		uint32 mYourNonce;

// Your Nonce

		CCNetworkID mNID;

// Network identifier

		uint8 mEKS;

// EKS

		uint8 mPID;

// Protocol ID

		uint16 mPRN;

// Protocol Run Number

		uint8 mPMN;

// Protocol Message Number

		__packed union 
		{
			CCHashKey mHashKey;

// Hash or Encryption Key

			CCEncryptionKey mKey;
		};
	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0x6020 CM_BRG_INFO (REQ, CNF)

__packed class CM_BRG_INFO 

{
public:
	enum 
	{
		eMMType = 0x0020,

// CM_BRG_INFO

		eMMTypeReq = eCM | eMMType | eReq,

// .Req

		eMMTypeCnf = eCM | eMMType | eCnf // .Cnf		

	};
	class EEBSF 
	{
	public:
		enum 
		{
			eNotBridge = 0,
			eBridge = 1
		};
	};

/*CCMMESubFrame_V1::eMMEHeaderSz(19) + Cnf::eBaseSize(3) 
 *   + Cnf::eArrayUnitSize(6) * eMaxBDAs(248) < 1514*/

	__packed class Req 
	{
	public:

//NULL

	};
	__packed class Cnf 
	{
	public:
		enum 
		{
			eBaseSize = 3,
			eArrayUnitSize = 6,
			eMaxBDA = 248
		};
		uint8 mBSF;

//Bridging Station Flag

		uint8 mBTEI;

//Local TEI

		uint8 mNBDA;

//Number of Bridged Destinations

		CCMACAddress mBDA [eMaxBDA];

//Array of Bridged Destination Address

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0x6030 CM_CONN_INFO (REQ, CNF)

__packed class CM_CONN_INFO 

{
public:
	enum 
	{
		eMMType = 0x0030,

// CM_CONN_INFO

		eMMTypeReq = eCM | eMMType | eReq,

// .Req

		eMMTypeCnf = eCM | eMMType | eCnf // .Cnf		

	};
	enum 
	{
		eBaseSize = 1,
		eConnInfoBaseSize = 6
	};
	class EERequestType 
	{
	public:
		enum 
		{
			eAllActiveConns = 0,
			eCIDSpecified = 1,
			eGLIDSpecified = 2
		};
	};
	enum 
	{
		eMaxConnInfos = 64
	};
	__packed class CCConnInfoBase 
	{
	public:
		uint16 mCID;
		uint8 mSTEI;
		uint8 mDTEI;
		uint8 mLLID_F;

//0x00 for not present

		uint8 mLLID_R;

//0x00 for not present

	};
	__packed class CCConnInfo 
	{
	public:
		CCConnInfoBase mBase;
		uint8 mCSPEC_Ptr;

//use type CCCSPEC_pkd

	};
	__packed class Req 
	{
	public:
		uint8 mRequestType;
		uint16 mCID;
		uint8 mGLID;
	};
	__packed class Cnf 
	{
	public:
		uint8 mNumConns;
		CCConnInfo mConnInfos [eMaxConnInfos];

//TODO: this MME will be fragmented with variable length CCConnInfo

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0x6034 CM_STA_CAP (REQ, CNF)

__packed class CM_STA_CAP 

{
public:
	enum 
	{
		eMMType = 0x0034,

// CM_STA_CAP

		eMMTypeReq = eCM | eMMType | eReq,

// .Req

		eMMTypeCnf = eCM | eMMType | eCnf // .Cnf

	};
	__packed class Req 
	{
	};
	__packed class Cnf 
	{
	public:
		uint8 mAVVersion;
		CCMACAddress mMacAddress;
		CCMACAddress::CCOUI mOUI;
		uint8 mAutoConnect;
		uint8 mSmoothing;
		uint8 mCCoCapability;
		uint8 mProxyCapable;
		uint8 mBackupCco;
		uint8 mSoftHandOver;
		uint8 mTwoSymFC;
		uint16 mMaxFL_AV;
		uint8 mHomePlug1p1Cap;
		uint8 mHomePlug1p0Interop;
		uint8 mRegulatoryCap;
		uint8 mBidirectionalBursting;
		uint16 mImplementationVer;
	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0x6038 CM_NW_INFO (REQ, CNF)

__packed class CM_NW_INFO 

{
public:
	enum 
	{
		eMMType = 0x0038,

// CM_NW_INFO

		eMMTypeReq = eCM | eMMType | eReq,

// .Req

		eMMTypeCnf = eCM | eMMType | eCnf // .Cnf		

	};
	class EEStaRole 
	{
	public:
		enum 
		{
			eSTA = 0,
			eProxyCCo = 1,
			eCCo = 2
		};
	};
	class EEAccessType 
	{
	public:
		enum 
		{
			eInHome = 0,
			eAccess = 1
		};
	};
	__packed class CCNWInfo 
	{
	public:
		CCNetworkID mNID;
		uint8 mSNID;
		uint8 mTEI;
		uint8 mStationRole;
		CCMACAddress mCCoAddress;
		uint8 mAccess;
		uint8 mNumCordNWs;
	};
	__packed class Req 
	{
	public:

//NULL

	};
	__packed class Cnf 
	{
	public:
		uint8 mNumAVLNs;

// Number of AVLNs station is a member of

		CCNWInfo mNWInfos [cMaxAVLN2Join];
	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0x603C CM_GET_BEACON (REQ, CNF)

__packed class CM_GET_BEACON 

{
public:
	enum 
	{
		eMMType = 0x003C,

// CM_GET_BEACON

		eMMTypeReq = eCM | eMMType | eReq,

// .Req

		eMMTypeCnf = eCM | eMMType | eCnf // .Cnf		

	};
	enum 
	{
		eFixedPayLoadSize = 12,
		eBMISize = 132 - eFixedPayLoadSize
	};
	__packed class Req 
	{
	public:
		CCNetworkID mNID;
	};
	__packed class Cnf 
	{
	public:
		uint8 mFixedPayLoad [eFixedPayLoadSize];

// Beacon fixed payload

		uint8 mBMI [eBMISize];

// Beacon Management Information

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0x6040 CM_HFID (REQ, CNF)

__packed class CM_HFID 

{
public:
	enum 
	{
		eMMType = 0x0040,

// CM_HFID

		eMMTypeReq = eCM | eMMType | eReq,

// .Req

		eMMTypeCnf = eCM | eMMType | eCnf // .Cnf		

	};
	enum 
	{
		eProvideHFID_Manufacturer = 0x00,
		eProvideHFID_User = 0x01,
		eProvideHFID_AVLN = 0x02,
		eSetHFID_User = 0x03,
		eSetHFID_AVLN = 0x04,
		eFailure = 0xff
	};
	__packed struct CCNIDAndHFID 
	{
		CCNetworkID mNID;
		CCHFID mHFID;
	};
	__packed union ReqestsUnion 
	{
		CCNetworkID mNID;
		CCHFID mHFID;
		CCNIDAndHFID mNID_HFID;
	};
	__packed class Req 
	{
	public:
		uint8 mReqType;
		ReqestsUnion mRequestFields;
	};
	__packed class Cnf 
	{
	public:
		uint8 mResType;
		CCHFID mHFID;
	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0x6048 CM_NW_STATS (REQ, CNF)

__packed class CM_NW_STATS 

{
public:
	enum 
	{
		eMMType = 0x0048,

// CM_NW_STATS

		eMMTypeReq = eCM | eMMType | eReq,

// .Req

		eMMTypeCnf = eCM | eMMType | eCnf // .Cnf		

	};
	enum 
	{
		eBaseSize = 1,
		eArrayUnitSize = 8,
		eMaxSTAs = 186
	};
	__packed class CCSTAInfo 
	{
	public:
		CCMACAddress mSTAAddress;
		uint8 mAvgTxPhyRate_Mbps;
		uint8 mAvgRxPhyRate_Mbps;
	};

/*CCMMESubFrame_V1::eMMEHeaderSz(19) + Cnf::eBaseSize(1) 
 *   + Cnf::eArrayUnitSize(8) * eMaxSTAs(186) < 1514*/

	__packed class Req 
	{
	public:

//NULL

	};
	__packed class Cnf 
	{
	public:
		uint8 mNumSTAs;

// Number of stations in the AVLNs

		CCSTAInfo mStaInfos [eMaxSTAs];
	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


// 0x604C CM_LINK_STATS (REQ, CNF)

__packed class CM_LINK_STATS 

{
public:
	enum 
	{
		eMMType = 0x004C,

// CM_LINK_STATS

		eMMTypeReq = eCM | eMMType | eReq,

// .Req

		eMMTypeCnf = eCM | eMMType | eCnf // .Cnf

	};
	enum 
	{
		eResetStat = 0x00,
		eGetStat = 0x01,
		eGetThenResetStat = 0x02
	};
	enum 
	{
		eTx = 0x00,
		eRx = 0x01
	};
	enum 
	{
		eNon_ManagementLink = 0x00,
		eManagementLink = 0x01
	};
	enum 
	{
		eSuccess = 0x00,
		eFailure = 0x01
	};
	enum 
	{
		eMaxLatBins = 0xff
	};

// Max num of bins which latency info is collected

	__packed class TxLink 
	{
	public:
		uint16 mBeaconPeriodCnt;

// Currently not supported

		uint32 mNumMSDUTxd;

// Currently not supported

		uint32 mNumOctetsTxd;

// Currently not supported

		uint32 mNumSegGen;

// Currently not supported

		uint32 mNumSegSuccessTxd;

// Currently not supported

		uint32 mNumSegDropped;

// Currently not supported

		uint32 mNumPBTxd;

// Num of PBs transmitted

		uint32 mNumMPDUsTxd;

// Num of MPDUs transmitted

		uint32 mNumBurstsTxd;

// Currently not supported

		uint32 mNumMPDUSACKs;

// Num of MPDUs successfully ACK

		uint8 mNumLatBins;

// Currently not supported

		uint8 mLatBinGran;

// Currently not supported

		uint32 mNumPBsLatBinTxd [eMaxLatBins];

// Future

	};
	__packed class RxLink 
	{
	public:
		uint16 mBeaconPeriodCnt;

// Currently not supported

		uint32 mNumMSDURxd;

// Currently not supported

		uint32 mNumOctetsRxd;

// Currently not supported

		uint32 mNumSegRxdSuccess;

// Currently not supported

		uint32 mNumSegRxdMissed;

// Currently not supported

		uint32 mNumPBRxd;

// Num of PBs received

		uint32 mNumBurstsRxd;

// Currently not supported

		uint32 mNumMPDURxd;

// Num of MPDUs received

		uint32 mNumICVFails;

// Currently not supported

	};
	__packed class Req 
	{
	public:
		uint8 mReqType;

// Reset/Get/GetThenReset

		uint8 mReqID;

// Request ID

		CCNetworkID mNID;

// Network ID

		uint8 mLID;

// Link ID

		uint8 mTLFlag;

// 0x00 = Tx, 0x01 = Rx

		uint8 mManagement;

// 0x00 Non-Management, 0x01 Management link

		CCMACAddress mMACAddress;

// Mac Address of the Destination when TLFlag = 0x00

	};
	__packed class Cnf 
	{
	public:
		uint8 mReqID;

// Request ID

		uint8 mResType;

// Success = 0

		__packed union 
		{
			TxLink Tx;
			RxLink Rx;
		};

//Stats

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


// Manufacturer Specific// ------------------------------------------------------------//0x8000 MS_PB_ENC (REQ, CNF)

__packed class MS_PB_ENC 

{
public:
	enum 
	{
		eMMType = 0x0000,

// MS_PB_ENC

		eMMTypeReq = eMS | eMMType | eReq,

// .Req

		eMMTypeCnf = eMS | eMMType | eCnf // .Cnf

	};
	enum 
	{
		eSSC = 0x01,
		eRNMK = 0x02,
		eGetStatus = 0x03
	};
	enum 
	{
		eSuccess = 0x00,
		eFailure = 0x01
	};
	__packed class Req 
	{
	public:
		uint8 mPB_ACTION;

//PEKS to be set

	};
	__packed class Cnf 
	{
	public:
		uint8 mStatus;

// Success = 0

		uint8 mAVLNMembership;

// AVLN Membership Status

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


// Vendor Specific// ------------------------------------------------------------

class EEModuleID 

{

//used by VS_ST_MAC, VS_WR_MOD, VS_RD_MOD, VS_MOD_NVM

public:
	enum 
	{
		eSoftLoader = 0x00,
		eFirmware = 0x01,
		ePib = 0x02,
		eFirmwareAndPib = 0x03,
		e1stRSVDModuleID = 0x04,
		eModuleOperation = 0x08,
		eForceFlashWrite = 0x10,
		eDoNotReboot = 0x020,
		eUseAltSections = 0x040,
		eForceToSection = 0x080
	};
private:
	enum 
	{
		eSoftloaderPibAddress = 0x01000000 // Reserve 16KB of SDRAM

	};
public:

//Used by Device Manager when communicating with a Flashless device

	static uint32 GetSoftloaderPibAddress () 
	{
		return (eSoftloaderPibAddress);
	}
};


//0xA000 VS_SW_VER (REQ, CNF)

__packed class VS_SW_VER 

{
public:
	enum 
	{
		eMMType = 0x0000,

// VS_SW_VER

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf,

// .Cnf

		eVerSz = 128 // Version String Size, determined by version.inc

	};
	enum 
	{
		eSuccess = 0x00,
		eFail = 0x01
	};
	enum 
	{
		eINT6000 = 0x01,
		eINT6300 = 0x02,
		eINT6400 = 0x03
	};

// Device ID

	enum 
	{
		eNoUpdate = 0,
		eCanUpdate = 1
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint32 mCookie;

// message ID

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		uint8 mDeviceID;

// DeviceID

		uint8 mVersionLen;

// Version String length

		char mVersion [eVerSz];

// Firmware Version String

		uint8 mRSVD;
		uint32 mCookie;

// message ID

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA004 VS_WR_MEM (REQ, CNF)

__packed class VS_WR_MEM 

{
public:
	enum 
	{
		eMMType = 0x0004,

// VS_WR_MEM

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf,

// .Cnf

		eMaxDataSz = 1024,
		eMaxSDRAMSz = (1024 * 1024 * 32),

// Sdram Size = 32Mb

		eSdram16Mb = (1024 * 1024 * 16)
	};
	enum 
	{
		eSuccess = 0x00,
		eInvalidAddress = 0x10,
		eInvalidLength = 0x14
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint32 mAddress;

// Write Address

		uint32 mLength;

// Write Length

		uint8 mData [eMaxDataSz];

// Write Data

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		uint32 mAddress;

// Address From Request

		uint32 mLength;

// Length From Request

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA008 VS_RD_MEM (REQ, CNF)

__packed class VS_RD_MEM 

{
public:
	enum 
	{
		eMMType = 0x0008,

// VS_RD_MEM

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf,

// .Cnf

		eMaxDataSz = 1024,
		eMaxSDRAMSz = (1024 * 1024 * 32),

// Sdram Size = 32Mb

		eSdram16Mb = (1024 * 1024 * 16)
	};
	enum 
	{
		eSuccess = 0x00,
		eInvalidAddress = 0x10,
		eInvalidLength = 0x14
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint32 mAddress;

// Read Address

		uint32 mLength;

// Read Length

		uint8 mDataSize;

// Data Size

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		uint32 mAddress;

// Address From Request

		uint32 mLength;

// Read Length

		uint8 mData [eMaxDataSz];

// Data Read

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA00C VS_ST_MAC (REQ, CNF)

__packed class VS_ST_MAC 

{
public:
	enum 
	{
		eMMType = 0x000C,

// VS_ST_MAC

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf	

	};
	enum 
	{
		eSuccess = 0x00,
		eInvalidModuleID = 0x10,
		eInvalidCmd = 0x38
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mModuleID;

// Module Image to start

		uint8 res [3];
		uint32 mImageLoadAddr;
		uint32 mImageLength;
		uint32 mImageChksum;
		uint32 mImageStartAddr;
	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		uint8 mModuleID;

// Module Image to start

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA010 VS_GET_NVM (REQ, CNF)

__packed class VS_GET_NVM 

{
public:
	enum 
	{
		eMMType = 0x0010,

// VS_GET_NVM

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf,

// .Cnf

		eMaxDataSz = 1024
	};
	enum 
	{
		eSuccess = 0x00,
		eNVMNotPresent = 0x10
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		uint32 mNVMType;

// NVM Type Code

		uint32 mNVMPage;

// NVM Page Size

		uint32 mNVMBlock;

// NVM Block Size

		uint32 mNVMSize;

// NVM Memory Size

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA01C VS_RS_DEV (REQ, CNF)

__packed class VS_RS_DEV 

{
public:
	enum 
	{
		eMMType = 0x001C,

// VS_RS_DEV

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf	

	};
	enum 
	{
		eSuccess = 0x00,
		eFail = 0x01
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA020 VS_WR_MOD (REQ, CNF)

__packed class VS_WR_MOD 

{
public:
	enum 
	{
		eMMType = 0x0020,

// VS_WR_MOD

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf,

// .Cnf

		eMaxDataSz = 1024
	};
	enum 
	{
		eSuccess = 0x00,
		eInvalidModuleID = 0x10,
		eInvalidLength = 0x12,
		eInvalidChkSum = 0x14,
		eInvalidOffset = 0x20,
		eBlocked = 0x40
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint16 mModuleID;

// Module ID

		uint16 mLength;

// Length in bytes to transfer

		uint32 mOffset;

// Offset into Module

		uint32 mChkSum;

// Checksum

		uint8 mData [eMaxDataSz];

// Write Data

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		uint16 mModuleID;

// Module ID

		uint16 mLength;

// Length in bytes to transferred

		uint32 mOffset;

// Offset into Module

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA024 VS_RD_MOD (REQ, CNF)

__packed class VS_RD_MOD 

{
public:
	enum 
	{
		eMMType = 0x0024,

// VS_RD_MOD

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf,

// .Cnf

		eMaxDataSz = 1024 // bytes

	};
	enum 
	{
		eSuccess = VS_WR_MOD::eSuccess,
		eInvalidModuleID = VS_WR_MOD::eInvalidModuleID,
		eInvalidLength = VS_WR_MOD::eInvalidLength,
		eInvalidChkSum = VS_WR_MOD::eInvalidChkSum,
		eInvalidOffset = VS_WR_MOD::eInvalidOffset
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint16 mModuleID;

// Module ID

		uint16 mLength;

// Number of bytes to read

		uint32 mOffset;

// Offset into Module

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		uint8 mRes1 [3];

// Reserved

		uint16 mModuleID;

// Module ID

		uint16 mLength;

// Number of bytes to read

		uint32 mOffset;

// Offset into Module

		uint32 mChkSum;

// Checksum

		uint8 mData [eMaxDataSz];

// Data

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA028 VS_MOD_NVM (REQ, CNF)

__packed class VS_MOD_NVM 

{
public:
	enum 
	{
		eMMType = 0x0028,

// VS_MOD_NVM

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf,

// .Cnf

		eMaxDataSz = 1024
	};
	enum NvmErrorCode 
	{
		eSuccess = 0x00,
		eInvalidModId = 0x10,
		eNVMNotPresent = 0x14,
		eNVMTooSmall = 0x18,
		eNVMHdrChkSum = 0x1C,
		eNVMSecChkSum = 0x20,
		eInvalidPIB = 0x24,
		eSlTooLarge = 0x28,
		eNVMfileTooLarge = 0x2C,
		eFwButNoPib = 0x42,
		eBadPibChecksum= 0x44,
		eDakNotZero = 0x46,
		eMacMismatch = 0x48,
		eMfgHfidMismatch = 0x50,
		eBadBindFacDef = 0x52,
		eBadBindTemplatePib = 0x54,
		eBadBindWorkingPib = 0x56,
		eErrorGenChecksumSPib = 0x58,
		eBadBindScratchPib = 0x5A,
		eNoFirmwareVersion = 0x5C,
		eVersionMismatch = 0x5E,
		eErrorGenChecksumO1Pib = 0x60,
		eErrorGenChecksumO2Pib = 0x62,
		eErrorGenChecksumWPib = 0x64,
		eInvalidFWVersion = 0x66
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mModuleID;

// Module ID

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		uint8 mModuleID;

// Module ID

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA02C VS_WD_RPT (REQ, IND)

__packed class VS_WD_RPT 

{
public:
	enum 
	{
		eMMType = 0x002C,

// VS_RD_MOD

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeInd = eVS | eMMType | eInd,

// .Ind

		eMaxDataSz = 1450 // bytes

	};
	enum 
	{
		eSuccess = 0x00,
		eFail = 0x01
	};
	enum 
	{
		eNumPartsDefault = 1,
		eCurrPartDefault = 1
	};
	enum 
	{
		eReadLog = 0x01,
		eClearLog = 0x02,
		eReadandClearLog = 0x03
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint16 mSessionId;

// Session ID

		uint8 mCmd;

// Clear report

	};
	__packed class Ind 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		uint16 mSessionId;

// Session ID

		uint8 mNumParts;

// number of parts(response MMEs)

		uint8 mCurPart;

// Current part(response MME)

		uint16 mDataLength;

// number of bytes in current part

		uint8 mDataOffset;

// Offset from mData[0] at which real data starts

		uint8 mData [eMaxDataSz];

// Data

	};
	__packed union 
	{
		Req REQ;
		Ind IND;
	};
};


//0xA030 VS_LNK_STATS (REQ, CNF)

const CCMACAddress cBroadcastTxStatsMACAddressObj = 

{
	0xff,
	0xff,
	0xff,
	0xff,
	0xff,
	0xff
};

const CCMACAddress cMultinetworkBroadcastTxRxStatsMACAddressObj = 

{
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00
};

__packed class VS_LNK_STATS 

{
public:
	enum 
	{
		eMMType = 0x0030,

// VS_LNK_STATS

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf

	};
	enum 
	{
		eRead = 0x00,
		eClear = 0x01,
		e1stInvCtrl = 0x02
	};
	enum 
	{
		eTx = 0x00,
		eRx = 0x01,
		eTxRx = 0x02,
		e1stInvDir = 0x03
	};
	enum 
	{
		e1stSum = 0xF8,
		e1stSumAll = 0xFC,
		eSumCSMA = 0xF8,
		eSumLink = 0xF9,
		eSumBoth = 0xFA,
		eSumRSVD = 0xFB,
		eSumAllCSMA = 0xFC,
		eSumAllLink = 0xFD,
		eSumAllBoth = 0xFF
	};
	enum 
	{
		eSuccess = 0x00,
		eInvalidCtrl = 0x01,
		eInvalidDir = 0x02,
		eInvalidLID = 0x10,
		eInvalidMAC = 0x20
	};
	__packed class RxIntervalStats 
	{
	public:
		uint8 mRxPhyRate_Mbps;
		uint64 mNumPBRxd_Passed;
		uint64 mNumPBRxd_Failed;
		uint64 mSumTurboBER_Passed;
		uint64 mSumTurboBER_Failed;
	};
	__packed class TxLink 
	{
	public:

//Transmitted MDPU Info

		uint64 mNumMPDUTxd_ACKd;
		uint64 mNumMPDUTxd_Collsion;
		uint64 mNumMPDUTxd_OutOfResources;

//Transmitted PB Info

		uint64 mNumPBTxd_Passed;
		uint64 mNumPBTxd_Failed;
	};
	__packed class RxLink 
	{
	public:

//Received MPDU Info

		uint64 mNumMPDURxd;
		uint64 mNumMPDURxd_OutOfResources;

//Received PB Info

		uint64 mNumPBRxd_Passed;
		uint64 mNumPBRxd_Failed;
		uint64 mSumTurboBER_Passed;
		uint64 mSumTurboBER_Failed;

//Detailed Received PB Info

		uint8 mNumRxInterval;
		RxIntervalStats mRxIntervalStats [cMaxNonDfltTMPerTEI];
	};
	__packed class TxRxLink 
	{
	public:
		TxLink Tx;
		RxLink Rx;
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mControl;

//Read or clear

		uint8 mDirection;

//Tx or Rx

		uint8 mLID;

//LID

		CCMACAddress mMACAddress;

//PeerMACAddress

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		uint8 mDirection;

//Tx or Rx

		uint8 mLID;

//LID

		uint8 mTEI;

//TEI

		__packed union 
		{
			TxLink Tx;
			RxLink Rx;
			TxRxLink TxRx;
		};

//Stats

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA034 VS_SNIFFER (REQ, CNF, IND)

#if !defined(INT_MNT) && !defined(__CC_ARM)

__packed class VS_SNIFFER 

{
public:
	enum 
	{
		eMMType = 0x0034,

// VS_SNIFFER

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf,

// .Cnf

		eMMTypeInd = eVS | eMMType | eInd // .Ind

	};
	enum 
	{
		eDisable = 0x00,
		eEnable = 0x01,
		eNoChange = 0x02,
		e1stInvCtrl = 0x03
	};
	enum 
	{
		eTx = 0x00,
		eRx = 0x01
	};
	enum 
	{
		eSuccess = 0x00,
		eInvalidCtrl = 0x10
	};
	enum 
	{
		eReg = 0x00,
		eRSVD = 0x01
	};
	__packed class Sniffer 
	{
	public:
		uint8 mDirection;

//Tx or Rx

		uint64 mSysTime;

//System Time Stamp

		uint32 mBeaconTime;

//Beacon Period Time Stamp

		uint8 mAVFC [cAVFCSize_bytes];

//AV frame control

		uint8 mBeaconBody [cBeaconPBSize_bytes];

//(Optional) Beacon Body

	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mSniffCtrl;

//Disable, enable or no change

		uint32 mRSVD;
	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		uint8 mSniffState;

//Disabled or enabled

		CCMACAddress mSnifferDA;

//Address to which Sniffer Data will be sent (broadcast if disabled)

		uint8 mRSVD;
	};
	__packed class Ind 
	{
	public:
		enum 
		{
			eBaseSize = 4
		};
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mSnifferType;

//Regular or RSVD

		Sniffer Reg;

//Sniffer Data

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
		Ind IND;
	};
};


#endif

//0xA038 VS_NW_INFO (REQ, CNF)

__packed class VS_NW_INFO 

{
public:
	enum 
	{
		eMMType = 0x0038,

// VS_NW_INFO

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf

	};
	class EEStaRole 
	{
	public:
		enum 
		{
			eSTA = 0,
			eProxyCCo = 1,
			eCCo = 2
		};
	};

/*CCMMESubFrame_V0::eMMEHeaderSz(17) + Cnf::eBaseSize(4)
 *   + CCNWInfo::eBaseSize(18) + CCNWInfo::eArrayUnitSize(15) * eMaxSTAs(98) < 1514*/

	__packed class CCSTAInfo 
	{
	public:
		CCMACAddress mSTAAddress;
		uint8 mSTATEI;
		CCMACAddress mSTA1stBrgAddress;
		uint8 mAvgTxPhyRate_Mbps;
		uint8 mAvgRxPhyRate_Mbps;
	};
	__packed class CCNWInfo 
	{
	public:
		enum 
		{
			eBaseSize = 18,
			eArrayUnitSize = 15,
			eMaxSTAs = 98
		};
		CCNetworkID mNID;
		uint8 mSNID;
		uint8 mTEI;
		uint8 mStationRole;
		CCMACAddress mCCoAddress;
		uint8 mCCoTEI;
		uint8 mNumSTAs;
		CCSTAInfo mStaInfos [eMaxSTAs];
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

	};
	__packed class Cnf 
	{
	public:
		enum 
		{
			eBaseSize = 4
		};
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mNumAVLNs;

// Number of AVLNs station is a member of

		CCNWInfo mNWInfo;
	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA040 VS_CP_RPT (REQ, IND)

__packed class VS_CP_RPT 

{
public:
	enum 
	{
		eMMType = 0x0040,

// CP_RPT

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeInd = eVS | eMMType | eInd,

// .Ind

		eMaxDataSz = 1430 // bytes

	};
	enum 
	{
		eSuccess = 0x00,
		eFail = 0x01
	};
	enum eCommands 
	{
		eReadLog = 0x01,
		eClearLog = 0x02,
		eUnsolicitedUpdatesOnOff = 0x04,
		eClearLock = 0x08,
		eAutoLockFeatureControl = 0x10,
		eAutoLockFeatureOn = 0x20
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint16 mSessionId;

// Session ID

		uint8 mCmd;

// Commands to execute, as per eCommands enum.

	};
	__packed class Ind 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus: 3;

// Success = 0

		uint8 mMajorVersionBit0: 1;

// Version. 0=old, 1=new (extended)

		uint8 mBufferIsLocked: 1;

// if 0 then buffer is unlocked (accepts entries)

		uint8 mAutoLockOnResetIsOn: 1;

// if 0 then the buffer will not auto-lock on a reset

		uint8 mUnsolicitedUpdatesIsOn: 1;

// if 0 then Unsolicited Updates feature not enabled

		uint8 mUnsolicited: 1;

// 0 = this is in response to Req, 1 = unsolicited

		uint8 mMajorVersion;

// Valid only when mMajorVersionBit0=1. Must change every time there is a field mismatch

		uint8 mMinorVersion;

// Valid only when mMajorVersionBit0=1. Changes when new fields allocated from the reserved fields

		uint16 mReserved1;
		uint32 mReserved2;

// Reserved for future use.

		uint32 mReserved3;

// Reserved for future use.

		uint32 mReserved4;

// Reserved for future use.

		uint16 mSessionId;

// Session ID

		uint32 mTotalBufferSize;

// Total size of Check Point buffer

		uint32 mBlockOffset;

// Offset of this block of data from start of buffer

		uint32 mByteIndexOfNextPos;

// Index of the next position where next event will be stored.

		uint8 mNumParts;

// number of parts (response MMEs)

		uint8 mCurPart;

// Current part (response MME)

		uint16 mRDataLength;

// number of bytes in mRData, starting at mRData[0]

		uint8 mRDataOffset;

// Offset from mData[0] at which real data starts

		uint8 mRData [eMaxDataSz];

// Data

	};
	__packed union 
	{
		Req REQ;
		Ind IND;
	};
};


//0xA048 VS_FR_LBK (REQ, CNF)

__packed class VS_FR_LBK 

{
public:
	enum 
	{
		eMMType = 0x0048,

// VS_RD_MOD

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf,

// .Cnf

		eMaxDataSz = 1038 // bytes

	};
	enum 
	{
		eSuccess = 0x00,
		eFail = 0x01,
		eInvalidDuration = 0x20,
		eInvalidLength = 0x12,
		eAlreadySet = 0x24
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mDuration;

// Time duration

		uint8 mRes;
		uint16 mLength;

// Number of octets in frame

		uint8 mData [eMaxDataSz];
	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		uint8 mDuration;

// Time duration

		uint16 mLength;

// Number of octets in frame

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA04C VS_LBK_STAT (REQ, CNF)

__packed class VS_LBK_STAT 

{
public:
	enum 
	{
		eMMType = 0x004C,

// VS_RD_MOD

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf,

// .Cnf

		eMaxDataSz = 1038 // bytes

	};
	enum 
	{
		eSuccess = 0x00,
		eFail = 0x01
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		uint8 mLbkStat;

// loopback status

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA050 VS_SET_KEY (REQ, CNF)

__packed class VS_SET_KEY 

{
public:
	enum 
	{
		eMMType = 0x0050,

// VS_SET_KEY

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf

	};
	enum 
	{
		eSuccess = 0x00,
		eInvalid_PEKS = 0x10,
		eInvalid_PIB = 0x11,
		eInvalid_PEKS_EncPayload = 0x12,
		eRemote_Fail = 0x13,
		eInvalidRemote_Answer = 0x14,
		eRemoteDecryptionFailed = 0x15
	};

//local set //local set //remote set //remote cnf failure //remote cnf is not cnf //remote decryption error

	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mPEKS;

//PEKS to be set

		CCEncryptionKey mKEY;

//NMK to be set

		uint8 mPEKS_EncPayload;

//PEKS to be used for remote set with in Encrypted Payload MME

//note: 0x0f is no remote set

		CCMACAddress mRemoteDA;

//Remote Station Address

		CCEncryptionKey mKEY_EncPayload;

//DAK for encrypted payload

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA054 VS_MFG_STRING (REQ, CNF)

__packed class VS_MFG_STRING 

{
public:
	enum 
	{
		eMMType = 0x0054,

// VS_SW_VER

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf

	};
	enum 
	{
		eSuccess = 0x00,
		eFail = 0x01
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		uint8 mMStrLength;

// Manufacturing String length

		char mMfgStr [cHFIDSz];

// Firmware Version String

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA058 VS_RD_CBLOCK (REQ, CNF)

__packed class VS_RD_CBLOCK 

{
public:
	enum 
	{
		eMMType = 0x0058,

// VS_SW_VER

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf

	};
	enum 
	{
		eSuccess = 0x00,
		eFail = 0x01,
		eNoFlash = 0x10
	};
	enum 
	{
		eMaxSize = 128,
		eConfigSize = 76
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		uint8 mConfLength;

// Configuration block length

		char mConfBlock [eMaxSize];

// Firmware Version String

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA05C VS_SET_SDRAM (REQ, CNF) - (Softloader only)

__packed class VS_SET_SDRAM 

{
public:
	enum 
	{
		eMMType = 0x005C,

// VS_SET_SDRAM

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf

	};
	enum 
	{
		eSuccess = 0x00,
		eFail = 0x01,
		eInvalidChkSum = 0x30,
		eBISTFailed = 0x34
	};
	enum 
	{
		eConfigSize = 32
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mSDRAMConfig [SDRAM_SIZE];

// Configuration block

		uint32 mChkSum;

// Check Sum

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA060 VS_HST_ACTION (IND, RSP)

__packed class VS_HST_ACTION 

{
public:
	enum 
	{
		eMMType = 0x0060,

// VS_HST_ACTION

		eMMTypeInd = eVS | eMMType | eInd,

// .Ind

		eMMTypeRsp = eVS | eMMType | eRsp // .Rsp

	};
	enum 
	{
		eSuccess = 0x00,
		eFail = 0x01
	};
	enum 
	{
		eLoader=0,
		eFirmware,
		ePIB,
		eFW_PIB,
		eLoaderSDRAM,
		eResetToFacDefaults
	};
	__packed class Ind 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mActionReq;

// Action Requested

	};
	__packed class Rsp 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

	};
	__packed union 
	{
		Ind IND;
		Rsp RSP;
	};
};


//0xA068 VS_OP_ATTRIBUTES (REQ, CNF)

__packed class VS_OP_ATTRIBUTES 

{
public:
	enum 
	{
		eMMType = 0x0068,

// VS_OP_ATTRIBUTES

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf

	};
	enum 
	{
		eSuccess = 0x00,
		eFail = 0x01,
		eNotSupported = 0x02
	};
	enum 
	{
		eMaxSize = 1024
	};
	enum 
	{
		eBinary = 0x00,
		eXml = 0x01,
		eDelimitedString = 0x02,
		eNameValuePair = 0x03
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint32 mCookie;

// message ID

		uint8 mRType;

// data formate requested

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint16 mStatus;

// Success = 0

		uint32 mCookie;

// message ID

		uint8 mRType;

// data formate returned

		uint16 mSize;

// Length of Data Field

		uint8 mData [eMaxSize];

// Data Field

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA06C VS_ENET_SETTINGS (REQ, CNF)

__packed class VS_ENET_SETTINGS 

{
public:
	enum 
	{
		eMMType = 0x006C,

// VS_ENET_SETTINGS

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf

	};

// CONTROL

	enum 
	{
		eRead = 0x00,
		eWrite = 0x01,
		e1stInvCtrl = 0x02
	};

// STATUS

	enum 
	{
		eSuccess = 0x00,
		eInvalidCtrl = 0x01,
		eSuccessWrite = 0x02,
		eInvalidWriteParam = 0x03
	};

// AUTO_NEGOTIATE Default value is 0x01

	enum 
	{
		eAutoNegotiateDisabled = 0x00,
		eAutoNegotiateEnabled = 0x01
	};

// ADVCAPS

	enum 
	{
		eAdvCapabilitiesMask = 0x0f
	};

// ETH_SPEED, ETH_DUPLEX

	enum 
	{
		e10Mbps = 0,
		e100Mbps = 1,
		e1000Mbps = 2,
		eHalfDuplex = 0,
		eFullDuplex = 1
	};

// ETH_LINK_STATUS

	enum 
	{
		eLinkOff = 1,
		eLinkOn = 2
	};

// ETHFLOW_CONTROL default value is 0x03

	enum 
	{
		eRxTxFlowCtrlDisabled = 0x00,
		eTxFlowCtrlEnabled = 0x01,
		eRxFlowCtrlEnabled = 0x02,
		eRxTxFlowCtrlEnabled = 0x03,
		eTxFlowCtrlMask = 0x01,
		eRxFlowCtrlMask = 0x02,
		eRxTxFlowCtrlMask = 0x03
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mControl;

//Read or Write

		uint8 mAutoNegotiate;

// 0x01 = ON is the defaulted value

		uint8 mAdvertisementCapabilities;

// Bit 0 – 100 Full, Bit 1 – 100 Half, Bit 2 – 10 Full, Bit 3 – 10 Half

		uint8 mEnetSpeed;

//(0 = 10Mbps, 1 = 100 Mbps, 2 = 1000 Mbps)

		uint8 mEnetDuplex;

//(0 = Half Duplex, 1 = Full Duplex)

		uint8 mEnetFlowControl;

// 0x00 = Tx/Rx Flow Cntl Disabled, 0x01 = Tx Flow Cntl Enabled

// 0x02 = Rx Flow Cntl Enabled, 0x03 = Tx/Rx Flow control Enabled

	};
	__packed class Cnf // READ Confirm
 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		uint8 mEnetSpeed;

//(0 = 10Mbps, 1 = 100 Mbps, 2 = 1000 Mbps)

		uint8 mEnetDuplex;

//(0 = Half Duplex, 1 = Full Duplex)

		uint8 mEnetLinkStatus;

//(1 = OFF, 2 = ON)

		uint8 mEnetFlowControl;

// 0x00 = Tx/Rx Flow Cntl Disabled, 0x01 = Tx Flow Cntl Enabled

// 0x02 = Rx Flow Cntl Enabled, 0x03 = Tx/Rx Flow control Enabled

	};
	__packed class CnfWrite // Write Confirm
 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success write = 0x02

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
		CnfWrite CNFW;
	};
};


//0xA070 VS_TONE_MAP_CHAR (REQ, CNF)

__packed class VS_TONE_MAP_CHAR 

{
public:
	enum 
	{
		eMMType = 0x0070,

// VS_TONE_MAP_CHAR

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf

	};
	enum 
	{
		eSuccess = 0x00,
		eUnknownMACAddress = 0x01,
		eUnknownSlot = 0x02
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		CCMACAddress mMACAddress;
		uint8 mTMSlot;
	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		uint8 mTMSlot;

// Slot requested

		uint8 mNumTMs;

// Number of Tone maps

		uint16 mNumActiveCarrs;

// Number of active Carriers

		uint8 mModPerCarrs [cTonePairsPerSym];

//Modulation per Carrier

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA074 VS_NW_INFO_STATS (REQ, CNF)

__packed class VS_NW_INFO_STATS 

{
public:
	enum 
	{
		eMMType = 0x0074,

// VS_NW_INFO_STATS

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf

	};
	enum 
	{
		eMaxSTAs = 96
	};

/*CCMMESubFrame_V0::eMMEHeaderSz(17) + Cnf::eBaseSize(24)
 *   + CCSTAInfo::eArrayUnitSize(15) * eMaxSTAs(96) << 1514*/

	__packed class CCSTAInfo 
	{
	public:
		CCMACAddress mSTAAddress;
		uint8 mSTATEI;
		CCMACAddress mSTA1stBrgAddress;
		uint8 mAvgTxPhyRate_Mbps;
		uint8 mAvgRxPhyRate_Mbps;
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mFirstTEI;
	};
	__packed class Cnf 
	{
	public:
		enum 
		{
			eBaseSize = 25,
			eArrayUnitSize = 15
		};
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mFirstTEI;
		uint8 mInAVLN;
		CM_NW_INFO::CCNWInfo mNWInfo;
		uint8 mCCoTEI;
		uint8 mNumSTAs;
		CCSTAInfo mStaInfos [eMaxSTAs];
	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA078 VS_SLAVE_MEM (REQ, CNF)

__packed class VS_SLAVE_MEM 

{
public:
	enum 
	{
		eMMType = 0x0078,

// VS_SLAVE_MEM

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf

	};
	enum EEResult 
	{
		eSuccess = 0x00,
		eFailure = 0x01
	};
	enum EEAuthorizationMode 
	{
		eRetainSlave = 0,

// Retain the slave in the AVLN

		eEjectSlave = 1,

// Eject the slave from the AVLN

		eEjectSlave_TryNextMaster = 2 // Eject the slave and try next best Master

	};
	enum EEAssociationRetryTimeout 
	{
		eUseRetrySchedule = 0x00,
		eDonotRetry = 0x0f
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		CCMACAddress mMACAddress;

// Macaddress of the slave

		uint8 mAuthorizationMode;

// Authorization Mode of the slave

		uint8 mAssociationRetryTimeout;

// Time to wait before retrying to association on a slave

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA07C VS_FAC_DEFAULTS (REQ, CNF)

__packed class VS_FAC_DEFAULTS 

{
public:
	enum 
	{
		eMMType = 0x007C,

// VS_FAC_DEFAULTS

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf	

	};
	enum 
	{
		eSuccess = 0x00,
		eFailure = 0x01
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA084 VS_MULTICAST_INFO (REQ, CNF)

__packed class VS_MULTICAST_INFO 

{
public:
	enum 
	{
		eMMType = 0x0084,

// VS_MCAST_INFO

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf

	};
	enum 
	{
		eReqAll = 0x00,
		eReqGroup = 0x01
	};
	enum 
	{
		eSuccess = 0x00,
		eInvalidCtrl = 0x01,
		eAddressNotFound = 0x02
	};
	enum 
	{
		eAllowSources = 0x00,
		eBlockSources = 0x01
	};
	__packed class CCMemberInfo 
	{
	public:
		enum 
		{
			eBaseSize = 9
		};
		CCMACAddress mMemberAddress;
		uint8 mMemberTEI;
		uint8 mSourceMode;
		uint8 mNumSources;
		CCIPv6Address_pkd mSourceAdddress [cMaxSourcesPerMember];
	};
	__packed class CCGroupInfo 
	{
	public:
		enum 
		{
			eBaseSize = 17
		};
		CCIPv6Address_pkd mGroupAddress;
		uint8 mNumMembers;
		CCMemberInfo mMemberInfo [2];

//max is cMaxMACAddPerGroup

	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mReqType;

//All, Addresses

		CCIPv6Address_pkd mGroupAddress;
	};
	__packed class Cnf 
	{
	public:
		enum 
		{
			eBaseSize = 6
		};
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mReqType;

//All, Addresses

		uint8 mStatus;

// Success = 0

		uint8 mNumGroups;
		CCGroupInfo mGroupInfo [2];

//max is cMaxGroups

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};

__packed class VS_CLASS_CONN_MMEs 

{
public:
	enum tStatus 
	{
		eSuccess = 0x00,
		eInvalidControl = 0x01,
		eInvalidVolatility = 0x02,

//only for VS_CLASSIFICATION

		eInvalidClassifier = 0x03,
		eTooManyClassifiers = 0x04,

//in VS_CLASSIFICATION and VS_CONN_ADD - classifier, in VS_CONN_INFO - requests

		eRepeatClassifier = 0x05,
		eNotFound = 0x06,

//in VS_CONN_XXX - CID, in VS_CLASSIFICATION - Rule Set

		eLinkUpdateInProgress = 0x07,
		eInvalidConfiguration = 0x08,
		eInvalidCSPEC_Version = 0x10,
		eInvalidCSPEC = 0x11,
		eInvalidCSPEC_PropCSPEC = 0x1F,
		eNoLocalResource = 0x20,
		eNoLocalResource_PropCSPEC = 0x2F,
		eInvalidPeer = 0x30,
		ePeerCnfTimedOut = 0x31,
		ePeerRejection = 0x40,
		ePeerRejection_PropCSPEC = 0x4F,
	};
	__packed class CCClassifierRule 
	{
	public:

//Copied from CCClassifierObj_PIB

		uint8 mClassifierPID;

//EEClassifierPID::tPID

		uint8 mIndividualOperand;

//EEClassificationOperand::tIndividualOperand

		uint8 mClassifierValue [cMaxClassifierLength];
	};
	__packed class CCClassRuleSet 
	{
	public:
		uint8 mClassificationOperand;

//EEClassificationOperand::tOperand

		uint8 mNumClassifiers;
		CCClassifierRule mClassifierObj [cMaxAutoCClsfrs];
	};
	__packed class CCClassification 
	{
	public:
		uint8 mAction;

//EEClassificationAction::tAct

		CCClassRuleSet mClassRuleSet;
	};
	__packed class CCSimpCSPEC 
	{

//Same as CCSimplifiedCSPEC_PIB

	public:
		uint16 mCSPECversion;

// CSPEC Version 0x00 = EECSPECVersion::eSimpCSPEC (current version)

		uint8 mConnCAP;

// Connection Channel Access Priority - CAP0/CAP1/CAP2/CAP3

		uint8 mConnCoQoSPrio;

// Connection CoQoS Priority for Bandwidth Management

		uint16 mConnRate;

// Avg predicted App Data Rate of the Conn(units 10 Kbps, Max is 90 Mbps)

		uint32 mConnTTL;

// Conn Time To Live (units in us)- Min is 10 millisecs, Maximum is 2 seconds

	};
	__packed class CCVlanCSPEC 
	{

//Same as CCVLANCSPEC_PIB

	public:
		uint16 mCSPECversion;

// CSPEC Version 0x02 = EECSPECVersion::eVlanCSPEC

		uint32 mVlanTag;

// Whole VLAN tag (including Ethertype) To be Inserted into the frame

		uint32 mRSVD;

// Reserved

	};
	enum 
	{
		eConnMMTypeIndMask = 0xFFF3,
		eConnMMTypeInd = 0x00C2
	};
	__packed class CCConnInfo 
	{
	public:
		uint8 mSNID;

// SNID of STAs involved in this Link

		CM_CONN_INFO::CCConnInfoBase mBase;
		CCSimpCSPEC mSimpCSPEC;

// Simplified CSPEC

	};
};


//0xA088 VS_CLASSIFICATION (REQ, CNF)

__packed class VS_CLASSIFICATION 

{
public:
	enum 
	{
		eMMType = 0x0088,

// VS_CLASSIFICATION

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf

	};
	enum 
	{
		eSaveClassifer = 0x00,
		eRemoveClassifer = 0x01
	};

//TODO: eReadAllClassifers, eClearAllClassifers

	enum 
	{
		eSaveToRunTime = 0x00,
		eSaveToPIB = 0x01
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mControl;

//Save, Read, Clear

		uint8 mVolatility;
		VS_CLASS_CONN_MMEs::CCClassification mClassification;

//VS_CLASS_CONN_MMEs::CCSimpCSPEC mSimpCSPEC; // Simplified CSPEC

//or

//VS_CLASS_CONN_MMEs::CCVlanCSPEC mVlanCSPEc; //VLAN Tag CSPEC

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		VS_CLASS_CONN_MMEs::CCSimpCSPEC mProposedCSPEC;

// Simplified CSPEC that would not have been rejected (at the time).

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA090 VS_RX_TONE_MAP_CHAR (REQ, CNF)

__packed class VS_RX_TONE_MAP_CHAR 

{
public:
	enum 
	{
		eMMType = 0x0090,

// VS_RX_TONE_MAP_CHAR

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf

	};
	__packed class Cnf 
	{
	public:
		VS_TONE_MAP_CHAR::Cnf mToneMapChar;
		uint8 mGIL;
		uint8 mAvgAGC_Gain;
	};
	__packed union 
	{
		VS_TONE_MAP_CHAR::Req REQ;
		Cnf CNF;
	};
};


//0xA094 VS_SET_LED_BEHAVIOR (REQ, CNF)

__packed class VS_SET_LED_BEHAVIOR 

{
public:
	enum 
	{
		eMMType = 0x0094,

// VS_SET_LED_BEHAVIOR

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf	

	};
	enum 
	{
		eSuccess = 0x00,
		eFailure = 0x01
	};
	enum 
	{
		eMaxFunctionalites = 64
	};
	__packed class CFunctBehavior 
	{
	public:
		uint8 mFunctionality;

//EELEDControl::tLEDFunctionality

		uint8 mBehavior;

//EELEDControl::tLEDFunctionality

		uint8 mAdditionalInfo1;
		uint8 mAdditionalInfo2;
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mNumBehaviors;
		CFunctBehavior mFunctBehaviorArray [eMaxFunctionalites];
	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA098 VS_WRITE_AND_EXECUTE_APPLET (REQ, CNF)

__packed class VS_WRITE_AND_EXECUTE_APPLET 

{
public:
	enum 
	{
		eMMType = 0x0098,

// VS_WRITE_AND_EXECUTE_APPLET

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf	

	};
	enum 
	{
		eStatus_Success = 0x0,
		eStatus_DestinationAddressNotAligned = 0x1,
		eStatus_EntryPointNotAligned = 0x2,
		eStatus_EntryPointOutOfBoundary = 0x4,
		eStatus_ChecksumError = 0x8,
		eStatus_OutOfMemory = 0x10,
		eStatus_OffsetLengthMismatch = 0x20,
		eStatus_MemoryNotOperational = 0x40,
		eStatus_BadLength = 0x80
	};
	enum 
	{
		Flags_ExecuteMask = 0x1,
		Flags_AbsoluteAddressMask = 0x2
	};
	enum 
	{
		MemType_Ignore = 0,
		MemType_Auto = 0x1,
		MemType_ITCM = 0x2,
		MemType_DTCM = 0x3,
		MemType_SRAM = 0x4,
		MemType_SDRAM = 0x5
	};
	enum 
	{
		eMinDataSize = 4,
		eMaxDataSize = 1400
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint32 mClientSessionId;
		uint32 mServerSessionId;
		uint32 mFlags;
		uint8 mAllowedMemTypes [8];
		uint32 mTotalLength;
		uint32 mCurrentPartLength;
		uint32 mCurrentPartDestinationAddress;
		uint32 mStartAddress;
		uint32 mChecksum;
		uint32 mReserved [2];
		uint8 mAppletImage [eMaxDataSize];
	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint32 mStatus;
		uint32 mClientSessionId;
		uint32 mServerSessionId;
		uint32 mFlags;
		uint8 mAllowedMemTypes [8];

//uint32 mReserved1;

		uint32 mTotalLength;
		uint32 mCurrentPartLength;
		uint32 mCurrentPartDestinationAddress;
		uint32 mStartAddress;
		uint32 mChecksum;
		uint32 mReserved [2];
		uint32 mCurrentPartAbsoluteAddress;
		uint32 mAbsoluteStartAddress;
	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA09C VS_MDIO_COMMAND (REQ, CNF)

__packed class VS_MDIO_COMMAND 

{
public:
	enum 
	{
		eMMType = 0x009C,

// VS_MDIO_COMMAND

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf	

	};
	enum 
	{
		eSuccess = 0x00,
		eFailure = 0x01,
		eRead = 0x00,
		eWrite = 0x01
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mOperation;

// READ or WRITE

		uint8 mPhyAddr;

// PHY Address Field

		uint8 mRegisterAddr;

// Register Address Field

		uint16 mData;

// Present only if OPERATION is WRITE,

// bit 15 is transmitted 1st following TA field.

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		uint16 mData;

// Data field echoed back if WRITE, otherwise read data.

		uint8 mPhyAddr;

// PHY Address Field

		uint8 mRegisterAddr;

// Register Address Field

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA0A0 VS_SLAVE_REG (IND,RSP)

__packed class VS_SLAVE_REG 

{
public:
	enum 
	{
		eMMType = 0x00A0,

// VS_SLAVE_REG

		eMMTypeInd = eVS | eMMType | eInd,

// .Ind

	};
	enum 
	{
		eSuccess = 0x00,
		eFailure = 0x01
	};
	enum EERegistrationStatus 
	{
		eSlaveLeft = 0,

// Slave left/ejected from the AVLN

		eSlaveAuthenticated = 1,

// Slave joined the AVLN

		eAVLNFull = 2 // AVLN full, slave could not be authenticated

	};
	__packed class Ind 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mRegistrationStatus;

// Registration status of the slave

		CCMACAddress mMACAddress;

// Macaddress of the slave

		uint8 mTEI;

// TEI of the slave

	};
	__packed union 
	{
		Ind IND;
	};
};


//0xA0A4 VS_BANDWIDTH_LIMITING (REQ, CNF)

__packed class VS_BANDWIDTH_LIMITING 

{
public:
	enum 
	{
		eMMType = 0x00A4,

// VS_BANDWIDTH_LIMITING

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf	

	};
	enum 
	{
		eSuccess = 0x00,
		eFailure = 0x01
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint32 mUplinkLimit;

// Uplink throughput limit in bits per second

		uint32 mDownlinkLimit;

// Downlink throughput limit in bits per second

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA0A8 VS_SNID_OPERATION (REQ, CNF)

__packed class VS_SNID_OPERATION 

{
public:
	enum 
	{
		eMMType = 0x00A8,

// VS_SNID_OPERATION

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf	

	};
	enum 
	{
		eSuccess = 0x00,
		eFailure = 0x01
	};
	enum 
	{
		eRead = 0x00,
		eWrite = 0x01
	};
	enum 
	{
		eNormalOperation = 0x00
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mOperationType;

// OpType = eRead/eWrite

		uint8 mSNID;

// H3C uses value 1 thru 4

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		uint8 mSNID;

// Only return SNID if READ Operation

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA0AC VS_NN_MITIGATE (REQ, CNF)

__packed class VS_NN_MITIGATE 

{
public:
	enum 
	{
		eMMType = 0x00AC,

// VS_NN_MITIGATE

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf	

	};
	enum 
	{
		eSuccess = 0x00,
		eFailure = 0x01
	};
	enum 
	{
		eMitigateDisable = 0x00,
		eMitigateStatic = 0x01,
		eMitigateDynamic = 0x02,
		eMitigateDynamicInStaticMode = 0x03
	};
	enum 
	{
		eStrongestCorrel = 0x04CB,
		eWeakestCorrel = 0x1398
	};
	enum 
	{
		eNormalOutput = 0x00,
		eReduce6DBOutput = 0x01
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mMitigateOperation;

// Mitigate operation = Disable/Enable

		uint32 mAutoCorrelThreshold;

// StrongestCorrel/WeakestCorrel

		uint32 mOutputPowerLevel;

// Normal/6BDReduce

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA0B0 VS_MODULE_OPERATION (REQ, CNF)

__packed class VS_MODULE_OPERATION 

{
public:
	enum 
	{
		eMMType = 0x00B0,

// VS_MODULE_OPERATION

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf	

	};

//enum { eMaxDataLen = 1400, eMaxModPerSession = 100, eMaxModOpPerMME = 5 };

	enum 
	{
		eMaxDataLen = 1400,
		eMaxModPerSession = 30,
		eMaxModOpPerMME = 1
	};

//TODO: Temporary set

	class EEModule_Operation 
	{
	public:
		enum tID 
		{
			eReadMod_Memory = 0x00,
			eReadMod_NVM = 0x01,
			eStartWriteSession = 0x10,
			eWriteMod_Memory = 0x11,
			eCommitMod_NVM = 0x12
		};
	};
	__packed class CCommit_Code 
	{
	public:
		__packed struct tCommitAsBitField 
		{
			uint32 mForceToBlankNVM: 1;
			uint32 mDoNoReset: 1;
			uint32 mRsvd2: 1;
			uint32 mRsvd3: 1;
			uint32 mRsvd4: 1;
			uint32 mRsvd5: 1;
			uint32 mRsvd6: 1;
			uint32 mRsvd7: 1;
			uint32 mRsvdW1_2: 24;
		};
		__packed union 
		{
			tCommitAsBitField mCode;
			uint32 mCommitAsWord;
		};
	};
	class EEModule_Status 
	{
	public:
		enum tStatus 
		{

//Sucess

			eSuccess = 0x00,

//Success

//MME Parameter Issues

			eInvalid_NumModOps = 0x10,

//Invalid Number of Module Operations

			eInvalid_ModOperation = 0x11,

//Invalid Module Operation ID

			eInvalid_Session_ID = 0x12,

//Invalid Session ID

			eInvalid_NumModules = 0x13,

//Invalid_ Num Module Operation Specific Data

			eModule_ID_NotFound = 0x14,

//Module ID not Found

			eInvalid_ModuleLen = 0x15,

//Invalid Module Length

			eInvalid_ModIdx = 0x16,

//Invalid Module Index

			eInvalid_DataLen = 0x17,

//Invalid Data Length

			eInvalid_ModOffest = 0x18,

//Unexpected Offset

			eInvalid_CommitActionCode = 0x19,

//Invalid Commit Code

			eBlocked_PreviousCommit = 0x1A,

//Operation Block by previous Commit

			eDuplicate_ModuleID = 0x1B,

//Duplicate Module ID/SubID

			eInvalid_ModuleID = 0x1C,

//Invalid Module ID/SubID

//NVM Issues

			eNVM_NotPresent = 0x20,

//NVM not Present

			eNVM_Small = 0x21,

//NVM too small

			eUnsupportedFlash = 0x22,

//Unsupported Flash

//Module Issues

			eInvalid_Module_CheckSum = 0x30,

//Invalid Module checksum

			eModule_Error = 0x31,

//Individual Module Error

			eModuleNotAvailableInNvmOrMem = 0x32,

//The expected module is not available in Nvm or Memory.

//Intellon Module Issues

			eInvalid_Header_CheckSum = 0x40,

//Invalid Header Checksum

			eInvalid_FW_ImageCheckSum = 0x41,

//Invalid FW Checksum

			eFW_ImageTooLarge = 0x42,

//Invalid FW Checksum

			eSoftLoaderTooLarge = 0x43,

//Soft-loader is too large

			eInvalid_PIB_CheckSum = 0x44,

//Invalid PIB Checksum

			eNoFWVersion = 0x45,

//No Firmware Version

			eCommitFW_WO_PIB = 0x46,

//FW Commit but no PIB

			eVersion_MisMatch = 0x47,

//Version Mismatch

			eInvalid_PIB = 0x50,

//Invalid PIB

			eDAKNotZero = 0x51,

//DAK not zero

			eMAC_MisMatch = 0x52,

//MAC mismatch

			eDAK_MisMatch = 0x53,

//DAK mismatch

			eMfgHFID_MisMatch = 0x54,

//Mfg HFID mismatch

			eBadBind_FactoryPIB = 0x55,

//Bad bind to FAC. Default PIB

			eBadBind_TemplatePIB = 0x56,

//Bad bind to template PIB

			eBadBind_WorkingPIB = 0x57,

//Bad bind to working PIB

			eBadBind_ScratchPIB = 0x58,

//Bad Bind Scratch PIB

			eCSGenErr_ScratchPIB = 0x59,

//Error Generating Checksum Scratch PIB

			eCSGenErr_O1PIB = 0x5a,

//Checksum Error O1 PIB

			eCSGenErr_O2PIB = 0x5b,

//Checksum Error O2 PIB

			eCSGenErr_WorkingPIB = 0x5c,

//Checksum Error Working PIB

// Miscellaneous Issues

			eUnknownError = 0xFF,
		};
	};
	__packed class CStatusWord 
	{
	public:
		uint16 mStatus;

// Success = 0

		uint16 mErrorCode;
	};

//-**************************-//

	__packed class CModOpDataHdr 
	{
	public:
		uint16 mModOperation;
		uint16 mModOpDataLen;
		uint32 mRSVD;
	};

//-*Read Module Operation*-//

	__packed class CRead_Req_Data 
	{
	public:
		CModOpDataHdr mDataHdr;
		uint16 mModule_ID;
		uint16 mModule_SubID;
		uint16 mDataLen;
		uint32 mModOffset;
	};
	__packed class CRead_Cnf_Data 
	{
	public:
		enum 
		{
			eBaseSize = (sizeof (CModOpDataHdr) + 10)
		};
		CModOpDataHdr mDataHdr;
		uint16 mModule_ID;
		uint16 mModule_SubID;
		uint16 mDataLen;
		uint32 mModOffset;
		uint8 mData [eMaxDataLen];
	};

//-*Start Write Session Module Operation*-//

	__packed class CModuleInfo 
	{
	public:
		uint16 mModule_ID;
		uint16 mModule_SubID;
		uint32 mModule_Len;
		uint32 mModule_CheckSum;
	};
	__packed class CStart_Req_Data 
	{
	public:
		enum 
		{
			eBaseSize = (sizeof (CModOpDataHdr) + 5)
		};
		CModOpDataHdr mDataHdr;
		uint32 mSession_ID;
		uint8 mNumModules;
		CModuleInfo mModuleInfo [eMaxModPerSession];
	};
	__packed class CStart_Cnf_Data 
	{
	public:
		enum 
		{
			eBaseSize = (sizeof (CModOpDataHdr) + 5)
		};
		CModOpDataHdr mDataHdr;
		uint32 mSession_ID;
		uint8 mNumModules;
		CStatusWord mModStatus [eMaxModPerSession];
	};

//-*Write Module Operation*-//

	__packed class CWrite_Req_Data 
	{
	public:
		enum 
		{
			eBaseSize = (sizeof (CModOpDataHdr) + 15)
		};
		CModOpDataHdr mDataHdr;
		uint32 mSession_ID;
		uint8 mModIndex;
		uint16 mModule_ID;
		uint16 mModule_SubID;
		uint16 mDataLen;
		uint32 mModOffest;
		uint8 mData [eMaxDataLen];
	};
	__packed class CWrite_Cnf_Data 
	{
	public:
		CModOpDataHdr mDataHdr;
		uint32 mSession_ID;
		uint8 mModIndex;
		uint16 mModule_ID;
		uint16 mModule_SubID;
		uint16 mDataLen;
		uint32 mModOffest;
	};

//-*Commit Module Operation*-//

	__packed class CCommit_Req_Data 
	{
	public:
		CModOpDataHdr mDataHdr;
		uint32 mSession_ID;
		CCommit_Code mCommitActionCode;
		uint32 mPrivate;
	};
	__packed class CCommit_Cnf_Data 
	{
	public:
		enum 
		{
			eBaseSize = (sizeof (CModOpDataHdr) + 9)
		};
		CModOpDataHdr mDataHdr;
		uint32 mSession_ID;
		CCommit_Code mCommitActionCode;
		uint8 mNumModules;
		CStatusWord mModStatus [eMaxModPerSession];
	};

//-**************************-//

	__packed class Req 
	{
	public:
		enum 
		{
			eBaseSize = 8
		};
		CCMACAddress::CCOUI mOUI;

// OUI

		uint32 mRSVD;
		uint8 mNumModOps;
		__packed union UUModOpData 
		{
			CModOpDataHdr mHeader;
			CRead_Req_Data mRead_OpData;
			CStart_Req_Data mStart_OpData;
			CWrite_Req_Data mWrite_OpData;
			CCommit_Req_Data mCommit_OpData;
		}
		mModOpData;
	};
	__packed class Cnf 
	{
	public:
		enum 
		{
			eBaseSize = 12
		};
		CCMACAddress::CCOUI mOUI;

// OUI

		CStatusWord mMMEStatus;
		uint32 mRSVD;
		uint8 mNumModOps;
		__packed union UUModOpData 
		{
			CModOpDataHdr mHeader;
			CRead_Cnf_Data mRead_OpData;
			CStart_Cnf_Data mStart_OpData;
			CWrite_Cnf_Data mWrite_OpData;
			CCommit_Cnf_Data mCommit_OpData;
		}
		mModOpData;
	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA0B4 VS_DIAG_NETWORK_PROBE (REQ, CNF)

__packed class VS_DIAG_NETWORK_PROBE 

{
public:
	enum 
	{
		eMMType = 0x00B4,

// VS_DIAG_NETWORK_PROBE

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf // .Cnf	

	};
	enum 
	{
		eUnAssocSTA = 0,
		eAssocSTA = 1,
		eAuthSTA = 2,
		eUnAssocSTA_SNID = 0xff
	};
	enum 
	{
		eRead = 0,
		eReadAndClear = 1
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mControl;

//Read or clear

	};
	__packed class CCNetInfo 
	{
	public:
		CC_DISCOVER_LIST::CCNetInfo mNetInfo;
		CCMACAddress mCCoMACAddress;
		uint16 mAvgPhyRate;
		uint8 mNumGoodAssocAuthenticate;
		uint8 mNumBad_CouldNotAssoc;
		uint8 mNumBad_Assoc_Failure;
		uint8 mNumBad_CouldNotAuth;
		uint8 mNumLeave;
		uint8 mNumLeave_SameMaster;
		uint8 mNumLeave_NextMaster;
		uint8 mNumLeave_Never;
	};
	__packed class Cnf 
	{
	public:
		enum 
		{
			eBaseSize = 7
		};
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mControl;

//Read or clear

		uint8 mAssoc_State;

// Association State

		uint8 mSNID;

// SNID

		uint8 mNumNetworks;

// Number of networks discovered

		CCNetInfo mNetworkInfo [cMaxNetworks];

// Info about network discovered[i]; 0 <= i < cMaxNetworks

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA0B8 VS_PL_LNK_STATUS (REQ, CNF)

__packed class VS_PL_LNK_STATUS 

{
public:
	enum 
	{
		eMMType = 0x00B8,

// VS_SW_VER

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf,

// .Cnf

	};
	enum 
	{
		eSuccess = 0x00,
		eFail = 0x01
	};
	enum 
	{
		eNoLink = 0,
		eHasLink = 1
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Success = 0

		uint8 mLnkStatus;

// Link Status

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA0BC VS_GPIO_STATE_CHANGE (REQ, CNF)

__packed class VS_GPIO_STATE_CHANGE 

{
public:
	enum 
	{
		eMMType = 0x00BC,

// VS_SW_VER

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf,

// .Cnf

		eMMTypeInd = eVS | eMMType | eInd,

// .Ind

		eMaxNumEvents = 32,
	};
	enum EEStatus 
	{
		eSuccess = 0x00,
		eInvalidControl = 0x01,
		eInvalidOutputGPIOIndex = 0x10,
		eUserPatternNumberNotFound = 0x20,
	};
	enum EEStateControl 
	{
		eDisabled = 0x00,

// OFF State

		eEnabled = 0x01,

// ON State

		eToggle = 0x02,

// if currently ON (enabled) then OFF (disabled)

	};
	__packed class CCEvent 
	{
	public:
		uint16 mEventID;

// Event identifier

		uint16 mEventState;

// State of the event GPIO

	};
	__packed class CCEvents_State 
	{
	public:
		uint8 mNumOfEvents;

// number of events

		CCEvent mListOfEvents [eMaxNumEvents];
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mUserEventID;

// user defined event

		uint8 mStateControl;

// State to change the LED Event

		uint8 mRsvd [4];

// reserved

	};
	__packed class Cnf 
	{
	public:
		enum 
		{
			eBaseSize = 8
		};
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// MME status

		uint8 mRsvd [4];

// reserved

		CCEvents_State mEventsStateTbl;

// LED Event State table

	};
	__packed class Ind 
	{
	public:
		enum 
		{
			eBaseSize = 8
		};
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mInputGPIOIndex;

//Index of the Input GPIO

		uint8 mRsvd [4];

// reserved

		CCEvents_State mEventsStateTbl;

// LED Event State table

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
		Ind IND;
	};
};


//0xA0C0 VS_CONN_ADD (REQ, CNF, IND)

__packed class VS_CONN_ADD 

{
public:
	enum 
	{
		eMMType = 0x00C0,

// VS_CONN_ADD

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf,

// .Cnf

		eMMTypeInd = eVS | eMMType | eInd // .Ind	

	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint32 mRequestID;

//Identifier generated by HLE to uniquely identify the request

		uint32 mRsvd;

// Reserved for future used

		CCMACAddress mApplicationDA;

// Application destination address

		VS_CLASS_CONN_MMEs::CCClassification mClassification;

//note: action field is RSVD

//VS_CLASS_CONN_MMEs::CCSimpCSPEC mSimpCSPEC; // Simplified CSPEC

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint32 mRequestID;

//Identifier generated by HLE to uniquely identify the request

		uint8 mStatus;

// MME Status - 0 == success

		uint16 mErrRecoveryCode;

// Used by Intellon

		uint32 mRsvd;

// Reserved

		uint16 mCID;

// Only valid when Status == success (byte 0 = Orig TEI, byte 1 = LID

		CCMACAddress mRejectMAC;

// MAC address of the STA that rejected the new Connection

		VS_CLASS_CONN_MMEs::CCSimpCSPEC mProposedCSPEC;

// Simplified CSPEC that would not have been rejected (at the time).

	};
	__packed class Ind 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint32 mRsvd;

// Reserved

		VS_CLASS_CONN_MMEs::CCConnInfo mConnInfo;

// Connection Info

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
		Ind IND;
	};
};


//0xA0C4 VS_CONN_MOD (REQ, CNF, IND)

__packed class VS_CONN_MOD 

{
public:
	enum 
	{
		eMMType = 0x00C4,

// VS_CONN_MOD

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf,

// .Cnf

		eMMTypeInd = eVS | eMMType | eInd // .Ind	

	};
	enum 
	{
		eSuspend = 0x00,
		eResume = 0x01,
		eModCSPEC = 0x02 // Currently not supported

	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint32 mRequestID;

//Identifier generated by HLE to uniquely identify the request

		uint32 mRsvd;

// Reserved

		uint16 mCID;

//Connection ID obtained from VS_CONN_ADD.CNF

		uint8 mModControl;

//0x00 = Suspend, 0x01 = Resume

		VS_CLASS_CONN_MMEs::CCSimpCSPEC mSimpCSPEC;

// Currently not supported

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint32 mRequestID;

//Identifier generated by HLE to uniquely identify the request

		uint8 mStatus;

// MME Status - 0 == success

		uint16 mErrRecoveryCode;

// Used by Intellon

		uint32 mRsvd;

// Reserved

		CCMACAddress mRejectMAC;

// Currently not supported

		VS_CLASS_CONN_MMEs::CCSimpCSPEC mProposedCSPEC;

// Currently not supported

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
		VS_CONN_ADD::Ind IND;
	};
};


//0xA0C8 VS_CONN_REL (REQ, CNF, IND)

__packed class VS_CONN_REL 

{
public:
	enum 
	{
		eMMType = 0x00C8,

// VS_CONN_REL

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf,

// .Cnf

		eMMTypeInd = eVS | eMMType | eInd // .Ind	

	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint32 mRequestID;

//Identifier generated by HLE to uniquely identify the request

		uint32 mRsvd;

//Reseved

		uint16 mCID;

//Connection ID obtained from VS_CONN_ADD.CNF

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint32 mRequestID;

//Identifier generated by HLE to uniquely identify the request

		uint8 mStatus;

// MME Status - 0 == success

		uint16 mErrRecoveryCode;

// Used by Intellon

		uint32 mRsvd;

// Reserved

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
		VS_CONN_ADD::Ind IND;
	};
};


//0xA0CC VS_CONN_INFO (REQ, CNF, IND)

__packed class VS_CONN_INFO 

{
public:
	enum 
	{
		eMMType = 0x00CC,

// VS_CONN_INFO

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf,

// .Cnf

		eMMTypeInd = eVS | eMMType | eInd,

// .Ind

		eMMTypeRsp = eVS | eMMType | eRsp,

// .Rsp

	};
	enum 
	{
		eReqAllActiveConnForThisStation = 0x00,

//Request to provide information for all active Connections for this station

		eReqConnWithSpecifiedCID = 0x01,

//Request to provide information for a Connection with the specified CID

		eReserved = 0x02,

//Reserved

		eReqAllActiveConnForThisVicinity = 0x03,

//Request to provide information for all active Connections for this vicinity

		eReqWhenTotalBandWidthExceeded = 0x04,

//Request to provide information when a certain Bandwidth used

		e1stRSVDReq = 0x05,

//used to validate (cannot be greater than 31)

		eCancelAllRequests = 0xff //Cancel all previous requests from this source

	};
	enum 
	{
		cMaxCnfConnInfos = cMaxVicinityStreams,
		eMaxRspConnInfos = 5
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mReqType;

//Valid Request type = 0x00/0x01/0x03

		uint32 mRsvd;

//Reseved

		uint16 mCSPECVer;

//CSPEC Version 0x01 = Current version

		uint16 mCID;

//Connection ID obtained from VS_CONN_ADD.CNF valid when mRwqType = 0x01

		uint16 mTotalBandWidthUsed;

//Total Bandwidth used to trigger notification

	};
	__packed class BWConnInfo 
	{
	public:
		VS_CLASS_CONN_MMEs::CCConnInfo mConnInfo;

// Connetion Info

		uint16 mBandWidthUsed;

// Bandwidth used

	};
	__packed class Cnf 
	{
	public:
		enum 
		{
			eBaseSize = 12
		};
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mReqType;

// Request type from the request MME

		uint8 mStatus;

// Confirm Status

		uint16 mErrCode;

//

		uint32 mRsvd;

//Reseved

		uint8 mNumConn;

// Number of connection: 0x00 = No connection

		BWConnInfo mBwConnInfo [cMaxCnfConnInfos];

//

	};
	__packed class Rsp//must be less than 120 bytes
 
	{
	public:
		enum 
		{
			eBaseSize = 8
		};
		CCMACAddress::CCOUI mOUI;

// OUI

		uint32 mRsvd;

//Reseved

		uint8 mNumConn;

// Number of connection: 0x00 = No connection

		VS_CLASS_CONN_MMEs::CCConnInfo mConnInfo [eMaxRspConnInfos];

//

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
		Cnf IND;
		Rsp RSP;
	};
};


//0xA0D0 VS_MULTIPORT_LNK_STA (REQ, CNF)

__packed class VS_MULTIPORT_LNK_STA 

{
public:
	enum 
	{
		eMMType = 0x00D0,

// VS_MULTIPORT_LNK_STA

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf,

// .Cnf

	};
	enum 
	{
		cMaxPorts = 32,
	};

// Operation is not in range returns eUnsupport

// Data is not in range returns eProcessFail

	enum 
	{
		eSuccess = 0x00,
		eUnsupport = 0x01,
		eProcessFail = 0x02
	};
	enum 
	{
		eRead = 0x00,
		eWrite = 0x01,
		eInvalid = 0x02
	};
	__packed class EthPortInfo 
	{
	public:
		uint8 mPhyAddr;

// Address of a Phy at the MDIO interface

		uint16 mRegAddr;

// Register Address

		uint8 mLinkStaBitNum;

// Link status bit number in the probe register

		uint8 mLinkStaOnSense;

// Link Status ON-OFF indication

	};
	__packed class MultiLinkInfo 
	{
	public:
		uint8 mLinkStatus;

// Link status

		EthPortInfo mEthPortInfo;

// Ethernet port info

	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mOpType;

// Read or Write operation

		uint8 mNumPorts;

//Number of ports - 1 - 32.

		EthPortInfo mEthPortInfo [cMaxPorts];

// Ethernet port info

	};
	__packed class Cnf 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Confirm Status

		uint8 mOpType;

// Read or Write operation

		uint8 mNumPorts;

// valid if mOpType is read

		__packed union 
		{
			MultiLinkInfo mMultiPortInfoArray [cMaxPorts];

// Link Status

			EthPortInfo mEthPortInfoArray [cMaxPorts];

// Ethernet port info

		};
	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//0xA0D8 VS_CUSTOM_INFO (REQ, CNF)

__packed class VS_CUSTOM_INFO 

{
public:
	enum 
	{
		eMMType = 0x00D8,

// VS_CUSTOM_INFO

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf,

// .Cnf

		eMMTypeInd = eVS | eMMType | eInd,

// .Ind

	};
	enum 
	{
		eSupportedVersionId1 = 1,
		eSupportedInfoId1 = 1
	};
	enum 
	{
		eSupportedVersionId2 = 1,
		eSupportedInfoId2 = 2
	};
	enum 
	{
		eSupportedVersionId3 = 1,
		eSupportedInfoId3 = 3
	};
	enum 
	{
		eMaxDataSize = 1024
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint32 mVersion;

//version

		uint32 mInfoId;

//Info ID

		uint16 mDataSize;

// Data size

		uint8 mData [eMaxDataSize];

// Data

	};
	__packed class Cnf 
	{
	public:
		enum 
		{
			eSuccess = 0,
			eFailureDueToVersionOrId = 1,
			eUnknownFailure = 2
		};
		CCMACAddress::CCOUI mOUI;

// OUI

		uint32 mVersion;

//version

		uint32 mInfoId;

//Info ID

		uint8 mStatus;

// Confirm Status

		uint16 mDataSize;

// Data size

		uint8 mData [eMaxDataSize];

// Data

	};
	__packed class Ind 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

		uint32 mVersion;

//version

		uint32 mInfoId;

//Info ID

		uint16 mDataSize;

// Data size

		uint8 mData [eMaxDataSize];

// Data

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
		Ind IND;
	};
};


//0xA0DC VS_EM_ID_TABLE (REQ, CNF)

__packed class VS_EM_ID_TABLE 

{
public:
	enum 
	{
		eMMType = 0x00DC,

// VS_EM_ID_TABLE

		eMMTypeReq = eVS | eMMType | eReq,

// .Req

		eMMTypeCnf = eVS | eMMType | eCnf,

// .Cnf

	};
	enum 
	{
		eMaxDataSize = 1024
	};
	__packed class Req 
	{
	public:
		CCMACAddress::CCOUI mOUI;

// OUI

	};
	__packed class Cnf 
	{
	public:
		enum 
		{
			eSuccess = 0,
			eNoSuchTable = 1
		};
		CCMACAddress::CCOUI mOUI;

// OUI

		uint8 mStatus;

// Confirm Status

		uint32 mNumOfCustomDevices;

//Num of Custom Device in the Enum ID Table

		uint8 mData [eMaxDataSize];

// Data

	};
	__packed union 
	{
		Req REQ;
		Cnf CNF;
	};
};


//****************************MME Frame for V0 and V1 w/ and w/o VLAN***************************

#if !defined(INT_MNT) && !defined(__CC_ARM)

__packed class CCMMENTRY 

{
public:
	enum 
	{
		eMaxMmeData = 1495
	};

//1518 - 23(Max MME header)

public:
	__packed union 
	{

// MME Payloads

// Station <-> Central Coordination

		CC_CCO_APPOINT mCC_CCO_APPOINT;

// CCo is told by user to appoint other STA as CCo

		CC_LINK_INFO mCC_LINK_INFO;

// Gets information about link(s)

		CC_DISCOVER_LIST mCC_DISCOVER_LIST;

// Discover List

		CC_WHO_RU mCC_WHO_RU;

// Asks for CCo's MAC address and HFID

// Station <-> Station

		CM_ENCRYPTED_PAYLOAD mCM_ENCRYPTED_PAYLOAD;

// Encrypted Payload

		CM_SET_KEY mCM_SET_KEY;

// Set Encryption Key

		CM_GET_KEY mCM_GET_KEY;

// Get Encryption Key

		CM_BRG_INFO mCM_BRG_INFO;

// Bridge Info

		CM_CONN_INFO mCM_CONN_INFO;

// Connection Info

		CM_NW_INFO mCM_NW_INFO;

// Network Info

		CM_NW_STATS mCM_NW_STATS;

// Network Stats

		CM_GET_BEACON mCM_GET_BEACON;

// Get Beacon Information

		CM_LINK_STATS mCM_LINK_STATS;

// Link Status Info

// Manufacturer Specific

		MS_PB_ENC mMS_PB_ENC;

// Push Button Encryption Control

// Vendor Specific

		VS_SW_VER mVS_SW_VER;

// Get Device/SW version

		VS_WR_MEM mVS_WR_MEM;

// Write MAC Memory

		VS_RD_MEM mVS_RD_MEM;

// Read MAC Memory

		VS_ST_MAC mVS_ST_MAC;

// Start MAC

		VS_GET_NVM mVS_GET_NVM;

// Get NVM Parameters

		VS_RS_DEV mVS_RS_DEV;

// Reset Device

		VS_WR_MOD mVS_WR_MOD;

// Write Module Data

		VS_RD_MOD mVS_RD_MOD;

// Read Module Data

		VS_MOD_NVM mVS_MOD_NVM;

// Write Module Data to NVM

		VS_WD_RPT mVS_WD_RPT;

// Watchdog Event Log

		VS_LNK_STATS mVS_LNK_STATS;

// Link Statistics

		VS_SNIFFER mVS_SNIFFER;

// Sniffer

		VS_NW_INFO mVS_NW_INFO;

// VS version of Network Info

		VS_CP_RPT mVS_CP_RPT;

// Check Point

		VS_FR_LBK mVS_FR_LBK;

// Frame Multiple Loopback

		VS_LBK_STAT mVS_LBK_STAT;

// Loopback status request

		VS_SET_KEY mVS_SET_KEY;

// Set Encryption Key

		VS_MFG_STRING mVS_MFG_STRING;

// manufacturing string

		VS_RD_CBLOCK mVS_RD_CBLOCK;

// Get SDRAM configuration block

		VS_SET_SDRAM mVS_SET_SDRAM;

// Set SDRAM configuration block

		VS_HST_ACTION mVS_HST_ACTION;

// Host Action MME for embedded Host

		VS_OP_ATTRIBUTES mVS_OP_ATTRIBUTES;

// Get Device Operational Attributes

		VS_ENET_SETTINGS mVS_ENET_SETTINGS;

// Ethernet PHY Settings

		VS_TONE_MAP_CHAR mVS_TONE_MAP_CHAR;

// Tone Map Characteristics

		VS_NW_INFO_STATS mVS_NW_INFO_STATS;

// Network Information & Statistics

		VS_FAC_DEFAULTS mVS_FAC_DEFAULTS;

// Reset to Factory Defaults

		VS_MULTICAST_INFO mVS_MULTICAST_INFO;

// Multicast Infomation

		VS_RX_TONE_MAP_CHAR mVS_RX_TONE_MAP_CHAR;

// Recieve Tone Map Characteristics

		VS_SET_LED_BEHAVIOR mVS_SET_LED_BEHAVIOR;

// Set LED Behavior

		VS_WRITE_AND_EXECUTE_APPLET mVS_WRITE_AND_EXECUTE_APPLET;

// Write and execute applet

		VS_MDIO_COMMAND mVS_MDIO_COMMAND;

// Send MDIO Command

		VS_CLASSIFICATION mVS_CLASSIFICATION;

// Classification

		VS_SLAVE_MEM mVS_SLAVE_MEM;

// Slave Membership

		VS_SLAVE_REG mVS_SLAVE_REG;

// Slave Registration Update

		VS_BANDWIDTH_LIMITING mVS_BANDWIDTH_LIMITING;

// Bandwidth limiting

		VS_SNID_OPERATION mVS_SNID_OPERATION;

// Set SNID (Applicable to Master/Slave mode only)

		VS_NN_MITIGATE mVS_NN_MITIGATE;

// Neighbor Network Mitigation support

		VS_MODULE_OPERATION mVS_MODULE_OPERATION;

// Module Operation

		VS_DIAG_NETWORK_PROBE mVS_DIAG_NETWORK_PROBE;

// Diagnostic Network Probe

		VS_PL_LNK_STATUS mVS_PL_LNK_STATUS;

// Current Link Status

		VS_GPIO_STATE_CHANGE mVS_GPIO_STATE_CHANGE;

// GPIO Remote control state change

		VS_CONN_ADD mVS_CONN_ADD;

// Add new Connection

		VS_CONN_MOD mVS_CONN_MOD;

// Modify an existing Connection

		VS_CONN_REL mVS_CONN_REL;

// Release a connection

		VS_CONN_INFO mVS_CONN_INFO;

// Query Connection INFO from STA/NetWork/Vicinity

		VS_MULTIPORT_LNK_STA mVS_MULTIPORT_LNK_STA;

// Access Multi-port link status

		VS_CUSTOM_INFO mVS_CUSTOM_INFO;

// Custom Info

		VS_EM_ID_TABLE mVS_EM_ID_TABLE;

// Custom Enum ID Table

#if defined(ENGINEERING_SW)

		ENGINEERING_UNION 

#endif

//max size

		uint8 mMaxSizeBuffer [eMaxMmeData];

//1518 - 23(Max MME header)

	};
};

__packed class CCMMESubFrame_V0 

{
public:
	uint16 mEtherType;

// IEEE-assigned Ethertype

	uint8 mMMV;

// MME version

	uint16 mMMTYPE;

// MME type

	CCMMENTRY mMMEntry;

// MME Payloads

public:
	enum 
	{
		eMMEHeaderSz = 17
	};
};

__packed class CCMMESubFrame_V1 

{
public:
	uint16 mEtherType;

// IEEE-assigned Ethertype

	uint8 mMMV;

// MME version

	uint16 mMMTYPE;

// MME type

	uint16 mFMI;

// FMI bits 0-3 and FN_MI bits 4-7 and FMSN bits 8-15

	CCMMENTRY mMMEntry;

// MME Payloads

public:
	enum 
	{
		eMMEHeaderSz = 19
	};
};

__packed class CCMMESubFrame_VX 

{
public:
	uint16 mEtherType;

// IEEE-assigned Ethertype

	uint8 mMMV;

// MME version

	uint16 mMMTYPE;

// MME type

};

__packed class CCMMESubFrame_V0_VLAN 

{
public:
	uint8 mVLANTag [cVLANTagSz];

//VLAN Tag

	uint16 mEtherType;

// IEEE-assigned Ethertype

	uint8 mMMV;

// MME version

	uint16 mMMTYPE;

// MME type

	CCMMENTRY mMMEntry;

// MME Payloads

public:
	enum 
	{
		eMMEHeaderSz = 21
	};
};

__packed class CCMMESubFrame_V1_VLAN 

{
public:
	uint8 mVLANTag [cVLANTagSz];

//VLAN Tag

	uint16 mEtherType;

// IEEE-assigned Ethertype

	uint8 mMMV;

// MME version

	uint16 mMMTYPE;

// MME type

	uint16 mFMI;

// FMI bits 0-3 and FN_MI bits 4-7 and FMSN bits 8-15

	CCMMENTRY mMMEntry;

// MME Payloads

public:
	enum 
	{
		eMMEHeaderSz = 23
	};
};

__packed class CCMMESubFrame_VX_VLAN 

{
public:
	uint8 mVLANTag [cVLANTagSz];

//VLAN Tag

	uint16 mEtherType;

// IEEE-assigned Ethertype

	uint8 mMMV;

// MME version

	uint16 mMMTYPE;

// MME type

};

__packed class CCMMEFrame 

{
public:
	CCMACAddress mODA;

// Original destination address

	CCMACAddress mOSA;

// Original source address

	__packed union 
	{
		CCMMESubFrame_V0 mRegular_V0;
		CCMMESubFrame_V1 mRegular_V1;
		CCMMESubFrame_V0_VLAN mVLAN_V0;
		CCMMESubFrame_V1_VLAN mVLAN_V1;
		CCMMESubFrame_VX mGeneric_Reg;
		CCMMESubFrame_VX_VLAN mGeneric_VLAN;
	};
};


#endif

//****************************MME Frame for V0 w/ and w/o VLAN**********************************

#if !defined(INT_MNT) && !defined(__CC_ARM)

__packed class CCMMEBody 

{
public:
	uint8 mMMV;

// MME version

	uint16 mMMTYPE;

// MME type

	__packed union 
	{

// MME Payloads

// Manufacturer Specific

		MS_PB_ENC mMS_PB_ENC;

// Push Button Encryption Control

// Vendor Specific

		VS_SW_VER mVS_SW_VER;

// Get Device/SW version MME

		VS_WR_MEM mVS_WR_MEM;

// Write MAC Memory MME

		VS_RD_MEM mVS_RD_MEM;

// Read MAC Memory MME

		VS_ST_MAC mVS_ST_MAC;

// Start MAC MME

		VS_GET_NVM mVS_GET_NVM;

// Get NVM Parameters MME

		VS_RS_DEV mVS_RS_DEV;

// Reset Device MME

		VS_WR_MOD mVS_WR_MOD;

// Write Module Data MME

		VS_RD_MOD mVS_RD_MOD;

// Read Module Data MME

		VS_MOD_NVM mVS_MOD_NVM;

// Write Module Data to NVM MME

		VS_WD_RPT mVS_WD_RPT;

// Watchdog Event Log MME

		VS_LNK_STATS mVS_LNK_STATS;

// Link Statistics MME

		VS_SNIFFER mVS_SNIFFER;

// Sniffer MME

		VS_NW_INFO mVS_NW_INFO;

// VS version of Network Info MME

		VS_CP_RPT mVS_CP_RPT;

// Check Point MME

		VS_FR_LBK mVS_FR_LBK;

// Frame Multiple Loopback

		VS_LBK_STAT mVS_LBK_STAT;

// Loopback status request

		VS_SET_KEY mVS_SET_KEY;

// Set Encryption Key

		VS_MFG_STRING mVS_MFG_STRING;

// manufacturing string

		VS_RD_CBLOCK mVS_RD_CBLOCK;

// Get SDRAM configuration block

		VS_SET_SDRAM mVS_SET_SDRAM;

// Set SDRAM configuration block

		VS_HST_ACTION mVS_HST_ACTION;

// Host Action MME for embedded Host

		VS_ENET_SETTINGS mVS_ENET_SETTINGS;

// Ethernet PHY Settings MME

		VS_TONE_MAP_CHAR mVS_TONE_MAP_CHAR;

// Tone Map Characteristics MME

		VS_OP_ATTRIBUTES mVS_OP_ATTRIBUTES;
		VS_NW_INFO_STATS mVS_NW_INFO_STATS;

// Network Information & Statistics MME

		VS_FAC_DEFAULTS mVS_FAC_DEFAULTS;

// Reset to Factory Defaults

		VS_MULTICAST_INFO mVS_MULTICAST_INFO;

// Multicast Infomation

		VS_RX_TONE_MAP_CHAR mVS_RX_TONE_MAP_CHAR;

//Recieve Tone Map Characteristics

		VS_SET_LED_BEHAVIOR mVS_SET_LED_BEHAVIOR;

//Set LED Behavior

		VS_WRITE_AND_EXECUTE_APPLET mVS_WRITE_AND_EXECUTE_APPLET;

// write and execute applet

		VS_CLASSIFICATION mVS_CLASSIFICATION;

// Classification

		VS_SLAVE_MEM mVS_SLAVE_MEM;

// Slave Membership

		VS_SLAVE_REG mVS_SLAVE_REG;

// Slave Registration Update

		VS_BANDWIDTH_LIMITING mVS_BANDWIDTH_LIMITING;

// Bandwidth limiting

		VS_SNID_OPERATION mVS_SNID_OPERATION;

// Set SNID (Applicable to Master/Slave mode only)

		VS_DIAG_NETWORK_PROBE mVS_DIAG_NETWORK_PROBE;

// Diagnostic Network Probe

		VS_PL_LNK_STATUS mVS_PL_LNK_STATUS;

//Current Link Status

		VS_GPIO_STATE_CHANGE mVS_GPIO_STATE_CHANGE;

// GPIO Remote control state change

		VS_CONN_ADD mVS_CONN_ADD;

// Add new Connection

		VS_CONN_MOD mVS_CONN_MOD;

// Modify an existing Connection

		VS_CONN_REL mVS_CONN_REL;

// Release a connection

		VS_CONN_INFO mVS_CONN_INFO;

// Query Connection INFO from STA/NetWork/Vicinity

		VS_MULTIPORT_LNK_STA mVS_MULTIPORT_LNK_STA;

// Access Multi-port link status

		VS_CUSTOM_INFO mVS_CUSTOM_INFO;

// Custom Info

		VS_EM_ID_TABLE mVS_EM_ID_TABLE;

// Custom Enum ID Table

#if defined(ENGINEERING_SW)

		ENGINEERING_UNION 

#endif

//max size

		uint8 mMaxSizeBuffer [1493];

//1514 - 4(crc) - 17(MME header)

	};
};


/* Genric MME Class */

__packed class CCGenericMMEFrm 

{
public:
	CCMACAddress mODA;

// Original destination address

	CCMACAddress mOSA;

// Original source address

	uint16 mMTYPE;

// IEEE-assigned Ethertype

	CCMMEBody mMMEBody;
public:
	enum 
	{
		eMMEHeaderSz = 17
	};
};


/* Genric MME Class (VLAN)*/

__packed class CCVLANTagdMMEFrm 

{
public:
	CCMACAddress mODA;

// Original destination address

	CCMACAddress mOSA;

// Original source address

	uint8 mVLANTag [cVLANTagSz];
	uint16 mMTYPE;

// IEEE-assigned Ethertype

	CCMMEBody mMMEBody;
public:
	enum 
	{
		eVlanMMEHeaderSz = 21
	};
};


#endif

#ifdef WIN32

//#undef __packed

#pragma pack(pop, mmes)
#endif

#endif  // end !(__CCMMETEMP_H___)


/*=============================================================================
 *   END 
 *   =============================================================================*/

