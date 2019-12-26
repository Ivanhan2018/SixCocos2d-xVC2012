#include<stdio.h>

//function RoomSeatIdTranformGameSeatId(CurRoomSeatID, MyRoomSeatID, MyGameSeatID)
//	-- 4 个位置
//	-- 逻辑ID左上角顺时针方向顺序 0132
//	-- 视图ID左上角顺时针方向顺序 1234
//	if 2 == CurRoomSeatID then
//		CurRoomSeatID = 3
//		elseif (3 == CurRoomSeatID) then
//		CurRoomSeatID = 2
//		end
//
//		if (2 == MyRoomSeatID) then
//			MyRoomSeatID = 3
//			elseif (3 == MyRoomSeatID) then
//			MyRoomSeatID = 2
//			end
//
//			local ViewIDIndex = (CurRoomSeatID - MyRoomSeatID + l_PlayCount)%l_PlayCount
//			local AdjustNewViewID = (MyGameSeatID + ViewIDIndex + l_PlayCount)%l_PlayCount
//			if 0 == AdjustNewViewID then
//				return MyGameSeatID + ViewIDIndex
//				end
//				return AdjustNewViewID
//end

enum eChairID
{
   ChairID_ERROR=-1,
   ChairID_LT=0,
   ChairID_RT=1,
   ChairID_LB=2,
   ChairID_RB=3,
};

enum eViewID
{
	ViewID_ERROR=-1,
	ViewID_LT=1,
	ViewID_RT=2,
	ViewID_LB=4,
	ViewID_RB=3,
};

// 捕鱼逻辑ID->视图ID
int getViewID(int iCurLogicID, int iMyLoginID, int iMyViewID)
{
	// 4 个位置
	int iSeatCount = 4;
	// 逻辑ID左上角顺时针方向顺序 0132
	// 视图ID左上角顺时针方向顺序 1234
	if (ChairID_LB == iCurLogicID)
		iCurLogicID = ChairID_RB;
	else if (ChairID_RB == iCurLogicID)
		iCurLogicID = ChairID_LB;
	if (ChairID_LB == iMyLoginID)
		iMyLoginID = ChairID_RB;
	else if (ChairID_RB == iMyLoginID)
		iMyLoginID = ChairID_LB;

	int iViewIDIndex = (iCurLogicID - iMyLoginID + iSeatCount)%iSeatCount;
	int iAdjustNewViewID = (iMyViewID + iViewIDIndex + iSeatCount)%iSeatCount;
	if ( 0 == iAdjustNewViewID )
		return iMyViewID + iViewIDIndex;
	return iAdjustNewViewID;
}

void test(int iMyLoginID, int iMyViewID)
{
	printf("----test iMyLoginID=%d,iMyViewID=%d----\n",iMyLoginID,iMyViewID);
	for(int i=0;i<4;i++)
	{
		int viewID=getViewID(i,iMyLoginID,iMyViewID);
		printf("viewID[iCurLogicID=%d]=%d\n",i,viewID);
	}
}

int main()
{
	test(ChairID_LT,ViewID_RB);
	return 0;
}