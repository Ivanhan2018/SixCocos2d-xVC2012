#ifndef GAME_LOGIC_HEAD_FILE
#define GAME_LOGIC_HEAD_FILE

#include "Packet.h"
#include "CMD_Game.h"

#pragma once


//////////////////////////////////////////////////////////////////////////////////

//鎺掑簭绫诲瀷
#define ST_ORDER					1									//澶у皬鎺掑簭
#define ST_COUNT					2									//鏁扮洰鎺掑簭
#define ST_CUSTOM					3									//鑷畾鎺掑簭

//////////////////////////////////////////////////////////////////////////////////

//鍒嗘瀽缁撴瀯
struct tagAnalyseResult
{
	unsigned char 							cbBlockCount[4];					//鎵戝厠鏁扮洰
	unsigned char							cbCardData[4][MAX_COUNT];			//鎵戝厠鏁版嵁
};

//鍑虹墝缁撴灉
struct tagOutCardResult
{
	unsigned char							cbCardCount;						//鎵戝厠鏁扮洰
	unsigned char							cbResultCard[MAX_COUNT];			//缁撴灉鎵戝厠
};

//鍒嗗竷淇℃伅
struct tagDistributing
{
	unsigned char							cbCardCount;						//鎵戝厠鏁扮洰
	unsigned char							cbDistributing[15][6];				//鍒嗗竷淇℃伅
};

//鎼滅储缁撴灉
struct tagSearchCardResult
{
	unsigned char							cbSearchCount;						//缁撴灉鏁扮洰
	unsigned char							cbCardCount[MAX_COUNT];				//鎵戝厠鏁扮洰
	unsigned char							cbResultCard[MAX_COUNT][MAX_COUNT];	//缁撴灉鎵戝厠
};

//////////////////////////////////////////////////////////////////////////////////

//娓告垙閫昏緫绫?
class CGameLogic
{
	//鍙橀噺瀹氫箟
protected:
    
	//鍑芥暟瀹氫箟
public:
	//鏋勯€犲嚱鏁?
	CGameLogic();
	//鏋愭瀯鍑芥暟
	virtual ~CGameLogic();
    
	//绫诲瀷鍑芥暟
public:
	//鑾峰彇绫诲瀷
	unsigned char GetCardType(const unsigned char cbCardData[], unsigned char cbCardCount);
	//鑾峰彇鏁板€?
	unsigned char GetCardValue(unsigned char cbCardData) { return cbCardData&MASK_VALUE; }
	//鑾峰彇鑺辫壊
	unsigned char GetCardColor(unsigned char cbCardData) { return cbCardData&MASK_COLOR; }
    
	//鎺у埗鍑芥暟
public:

	//鎺掑垪鎵戝厠
	void SortCardList(unsigned char cbCardData[], unsigned char cbCardCount, unsigned char cbSortType);
	//鍒犻櫎鎵戝厠
	bool RemoveCardList(const unsigned char cbRemoveCard[], unsigned char cbRemoveCount, unsigned char cbCardData[], unsigned char cbCardCount);
	//鍒犻櫎鎵戝厠
	bool RemoveCard(const unsigned char cbRemoveCard[], unsigned char cbRemoveCount, unsigned char cbCardData[], unsigned char cbCardCount);
	//鎺掑垪鎵戝厠
	void SortOutCardList(unsigned char cbCardData[], unsigned char cbCardCount);
    
	//閫昏緫鍑芥暟
public:
	//閫昏緫鏁板€?
	unsigned char GetCardLogicValue(unsigned char cbCardData);
	//瀵规瘮鎵戝厠
	bool CompareCard(const unsigned char cbFirstCard[], const unsigned char cbNextCard[], unsigned char cbFirstCount, unsigned char cbNextCount);
	//鍑虹墝鎼滅储
	unsigned char SearchOutCard( const unsigned char cbHandCardData[], unsigned char cbHandCardCount, const unsigned char cbTurnCardData[], unsigned char cbTurnCardCount,tagSearchCardResult *pSearchCardResult );
	//鍚岀墝鎼滅储
	unsigned char SearchSameCard( const unsigned char cbHandCardData[], unsigned char cbHandCardCount, unsigned char cbReferCard, unsigned char cbSameCardCount,tagSearchCardResult *pSearchCardResult );
	//杩炵墝鎼滅储
	unsigned char SearchLineCardType( const unsigned char cbHandCardData[], unsigned char cbHandCardCount, unsigned char cbReferCard, unsigned char cbBlockCount, unsigned char cbLineCount,tagSearchCardResult *pSearchCardResult );
	//甯︾墝绫诲瀷鎼滅储(涓夊甫涓€锛屽洓甯︿竴绛?
	unsigned char SearchTakeCardType( const unsigned char cbHandCardData[], unsigned char cbHandCardCount, unsigned char cbReferCard, unsigned char cbSameCount, unsigned char cbTakeCardCount,tagSearchCardResult *pSearchCardResult );
	//鎼滅储椋炴満
	unsigned char SearchThreeTwoLine( const unsigned char cbHandCardData[], unsigned char cbHandCardCount, tagSearchCardResult *pSearchCardResult );
    
	//鍐呴儴鍑芥暟
public:
	//鏋勯€犳墤鍏?
	unsigned char MakeCardData(unsigned char cbValueIndex, unsigned char cbColorIndex);
	//鍒嗘瀽鎵戝厠锛堝垎鍒壘鍑?寮犵殑鐗岋紝2寮犵殑鐗岋紝3寮犵殑鐗岋紝4寮犵殑鐗岋級
	void AnalysebCardData(const unsigned char cbCardData[], unsigned char cbCardCount, tagAnalyseResult & AnalyseResult);
	//鍒嗘瀽鍒嗗竷
	void AnalysebDistributing(const unsigned char cbCardData[], unsigned char cbCardCount, tagDistributing & Distributing);
};

//////////////////////////////////////////////////////////////////////////////////

#endif