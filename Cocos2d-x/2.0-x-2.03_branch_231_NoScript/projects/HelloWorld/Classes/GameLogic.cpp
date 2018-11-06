
#include "GameLogic.h"

//////////////////////////////////////////////////////////////////////////////////
//静态变�?
#include "cocos2d.h"

USING_NS_CC;

//索引变量
const unsigned char cbIndexCount=5;

//////////////////////////////////////////////////////////////////////////////////

//构造函�?
CGameLogic::CGameLogic()
{
    
}


//析构函数
CGameLogic::~CGameLogic()
{
}

//获取类型
unsigned char CGameLogic::GetCardType(const unsigned char cbCardData[], unsigned char cbCardCount)
{
	//简单牌�?
	switch (cbCardCount)
	{
        case 0:	//空牌
		{
			return CT_ERROR;
		}
        case 1: //单牌
		{
			return CT_SINGLE;
		}
        case 2:	//对牌火箭
		{
			//牌型判断
			if ((cbCardData[0]==0x4F)&&(cbCardData[1]==0x4E)) return CT_MISSILE_CARD;
			if (GetCardLogicValue(cbCardData[0])==GetCardLogicValue(cbCardData[1])) return CT_DOUBLE;
            
			return CT_ERROR;
		}
	}
    
	//分析扑克
	tagAnalyseResult AnalyseResult;
	AnalysebCardData(cbCardData,cbCardCount,AnalyseResult);
    
	//四牌判断
	if (AnalyseResult.cbBlockCount[3]>0)
	{
		//牌型判断
		if ((AnalyseResult.cbBlockCount[3]==1) && (cbCardCount==4)) return CT_BOMB_CARD;
		if ((AnalyseResult.cbBlockCount[3]==1) && (cbCardCount==6)) return CT_FOUR_TAKE_ONE;
		if ((AnalyseResult.cbBlockCount[3]==1)&&(cbCardCount==8)&&(AnalyseResult.cbBlockCount[1]==2)) return CT_FOUR_TAKE_TWO;
        
		return CT_ERROR;
	}
    
	//三牌判断
	if (AnalyseResult.cbBlockCount[2]>0)
	{
        // 三条判断
        if(cbCardCount == 3){
            return CT_THREE;
        }
		//连牌判断
		if (AnalyseResult.cbBlockCount[2]>1)
		{
			//变量定义
			unsigned char cbCardData=AnalyseResult.cbCardData[2][0];
			unsigned char cbFirstLogicValue=GetCardLogicValue(cbCardData);
            
			//错误过虑
			if (cbFirstLogicValue>=15) return CT_ERROR;
            
			//连牌判断
			for (unsigned char i=1;i<AnalyseResult.cbBlockCount[2];i++)
			{
				unsigned char cbCardData = AnalyseResult.cbCardData[2][i*3];
				if (cbFirstLogicValue!=(GetCardLogicValue(cbCardData)+i)) return CT_ERROR;
			}
		}
        
		//牌形判断
        if (AnalyseResult.cbBlockCount[2]*3==cbCardCount) return CT_THREE_LINE;// 三连类型
        if (AnalyseResult.cbBlockCount[2]*4==cbCardCount) return CT_THREE_TAKE_ONE;// 三带一�?
        if ((AnalyseResult.cbBlockCount[2]*5==cbCardCount)&&(AnalyseResult.cbBlockCount[1]==AnalyseResult.cbBlockCount[2])) return CT_THREE_TAKE_TWO;// 三带一�?
        
		return CT_ERROR;
	}
    
	//两张类型(对连类型)
	if (AnalyseResult.cbBlockCount[1]>=3)
	{
		//变量定义
		unsigned char cbCardData=AnalyseResult.cbCardData[1][0];
		unsigned char cbFirstLogicValue=GetCardLogicValue(cbCardData);
        
		//错误过虑
		if (cbFirstLogicValue>=15) return CT_ERROR;
        
		//连牌判断
		for (unsigned char i=1;i<AnalyseResult.cbBlockCount[1];i++)
		{
			unsigned char cbCardData=AnalyseResult.cbCardData[1][i*2];
			if (cbFirstLogicValue!=(GetCardLogicValue(cbCardData)+i)) return CT_ERROR;
		}
        
		//二连判断
		if ((AnalyseResult.cbBlockCount[1]*2)==cbCardCount) return CT_DOUBLE_LINE;
        
		return CT_ERROR;
	}
    
	//单张判断(单连类型)
	if ((AnalyseResult.cbBlockCount[0]>=5)&&(AnalyseResult.cbBlockCount[0]==cbCardCount))
	{
		//变量定义
		unsigned char cbCardData=AnalyseResult.cbCardData[0][0];
		unsigned char cbFirstLogicValue=GetCardLogicValue(cbCardData);
        
		//错误过虑
		if (cbFirstLogicValue>=15) return CT_ERROR;
        
		//连牌判断
		for (unsigned char i=1;i<AnalyseResult.cbBlockCount[0];i++)
		{
			unsigned char cbCardData=AnalyseResult.cbCardData[0][i];
			if (cbFirstLogicValue!=(GetCardLogicValue(cbCardData)+i)) return CT_ERROR;
		}
        
		return CT_SINGLE_LINE;
	}
    
	return CT_ERROR;
}

//排列扑克
void CGameLogic::SortCardList(unsigned char cbCardData[], unsigned char cbCardCount, unsigned char cbSortType)
{
	//数目过虑
	if (cbCardCount==0) return;
	if (cbSortType==ST_CUSTOM) return;
    
	//转换数�?
	unsigned char cbSortValue[MAX_COUNT];
	for (unsigned char i=0;i<cbCardCount;i++) cbSortValue[i]=GetCardLogicValue(cbCardData[i]);
    
	//排序操作
	bool bSorted=true;
	unsigned char cbSwitchData=0,cbLast=cbCardCount-1;
	do
	{
		bSorted=true;
		for (unsigned char i=0;i<cbLast;i++)
		{
			if ((cbSortValue[i]<cbSortValue[i+1])||
				((cbSortValue[i]==cbSortValue[i+1])&&(cbCardData[i]<cbCardData[i+1])))
			{
				//设置标志
				bSorted=false;
                
				//扑克数据
				cbSwitchData=cbCardData[i];
				cbCardData[i]=cbCardData[i+1];
				cbCardData[i+1]=cbSwitchData;
                
				//排序权位
				cbSwitchData=cbSortValue[i];
				cbSortValue[i]=cbSortValue[i+1];
				cbSortValue[i+1]=cbSwitchData;
			}
		}
		cbLast--;
	} while(bSorted==false);
    
	//数目排序
	if (cbSortType==ST_COUNT)
	{
		//变量定义
		unsigned char cbCardIndex=0;
        
		//分析扑克
		tagAnalyseResult AnalyseResult;
		AnalysebCardData(&cbCardData[cbCardIndex],cbCardCount-cbCardIndex,AnalyseResult);
        
		//提取扑克
		for (unsigned char i=0;i<CountArray(AnalyseResult.cbBlockCount);i++)
		{
			//拷贝扑克
			unsigned char cbIndex=CountArray(AnalyseResult.cbBlockCount)-i-1;
			memcpy(&cbCardData[cbCardIndex],AnalyseResult.cbCardData[cbIndex],AnalyseResult.cbBlockCount[cbIndex]*(cbIndex+1)*sizeof(unsigned char));
            
			//设置索引
			cbCardIndex+=AnalyseResult.cbBlockCount[cbIndex]*(cbIndex+1)*sizeof(unsigned char);
		}
	}
    
	return;
}


//删除扑克
bool CGameLogic::RemoveCardList(const unsigned char cbRemoveCard[], unsigned char cbRemoveCount, unsigned char cbCardData[], unsigned char cbCardCount)
{
	//定义变量
	unsigned char cbDeleteCount=0,cbTempCardData[MAX_COUNT];
	if (cbCardCount>CountArray(cbTempCardData)) return false;
	memcpy(cbTempCardData,cbCardData,cbCardCount*sizeof(cbCardData[0]));
    
	//置零扑克
	for (unsigned char i=0;i<cbRemoveCount;i++)
	{
		for (unsigned char j=0;j<cbCardCount;j++)
		{
			if (cbRemoveCard[i]==cbTempCardData[j])
			{
				cbDeleteCount++;
				cbTempCardData[j]=0;
				break;
			}
		}
	}
	if (cbDeleteCount!=cbRemoveCount) return false;
    
	//清理扑克
	unsigned char cbCardPos=0;
	for (unsigned char i=0;i<cbCardCount;i++)
	{
		if (cbTempCardData[i]!=0) cbCardData[cbCardPos++]=cbTempCardData[i];
	}
    
	return true;
}

//删除扑克
bool CGameLogic::RemoveCard(const unsigned char cbRemoveCard[], unsigned char cbRemoveCount, unsigned char cbCardData[], unsigned char cbCardCount)
{
    
	//定义变量
	unsigned char cbDeleteCount=0,cbTempCardData[MAX_COUNT];
	if (cbCardCount>CountArray(cbTempCardData)) return false;
	memcpy(cbTempCardData,cbCardData,cbCardCount*sizeof(cbCardData[0]));
    
	//置零扑克
	for (unsigned char i=0;i<cbRemoveCount;i++)
	{
		for (unsigned char j=0;j<cbCardCount;j++)
		{
			if (cbRemoveCard[i]==cbTempCardData[j])
			{
				cbDeleteCount++;
				cbTempCardData[j]=0;
				break;
			}
		}
	}
	if (cbDeleteCount!=cbRemoveCount) return false;
    
	//清理扑克
	unsigned char cbCardPos=0;
	for (unsigned char i=0;i<cbCardCount;i++)
	{
		if (cbTempCardData[i]!=0) cbCardData[cbCardPos++]=cbTempCardData[i];
	}
    
	return true;
}

//排列扑克
void CGameLogic::SortOutCardList(unsigned char cbCardData[], unsigned char cbCardCount)
{
	//获取牌型
	unsigned char cbCardType = GetCardType(cbCardData,cbCardCount);
    
	if( cbCardType == CT_THREE_TAKE_ONE || cbCardType == CT_THREE_TAKE_TWO )
	{
		//分析�?
		tagAnalyseResult AnalyseResult = {};
		AnalysebCardData( cbCardData,cbCardCount,AnalyseResult );
        
		cbCardCount = AnalyseResult.cbBlockCount[2]*3;
		memcpy( cbCardData,AnalyseResult.cbCardData[2],sizeof(unsigned char)*cbCardCount );
		for( int i = CountArray(AnalyseResult.cbBlockCount)-1; i >= 0; i-- )
		{
			if( i == 2 ) continue;
            
			if( AnalyseResult.cbBlockCount[i] > 0 )
			{
				memcpy( &cbCardData[cbCardCount],AnalyseResult.cbCardData[i],
                       sizeof(unsigned char)*(i+1)*AnalyseResult.cbBlockCount[i] );
				cbCardCount += (i+1)*AnalyseResult.cbBlockCount[i];
			}
		}
	}
	else if( cbCardType == CT_FOUR_TAKE_ONE || cbCardType == CT_FOUR_TAKE_TWO )
	{
		//分析�?
		tagAnalyseResult AnalyseResult = {};
		AnalysebCardData( cbCardData,cbCardCount,AnalyseResult );
        
		cbCardCount = AnalyseResult.cbBlockCount[3]*4;
		memcpy( cbCardData,AnalyseResult.cbCardData[3],sizeof(unsigned char)*cbCardCount );
		for( int i = CountArray(AnalyseResult.cbBlockCount)-1; i >= 0; i-- )
		{
			if( i == 3 ) continue;
            
			if( AnalyseResult.cbBlockCount[i] > 0 )
			{
				memcpy( &cbCardData[cbCardCount],AnalyseResult.cbCardData[i],
                       sizeof(unsigned char)*(i+1)*AnalyseResult.cbBlockCount[i] );
				cbCardCount += (i+1)*AnalyseResult.cbBlockCount[i];
			}
		}
	}
    
	return;
}

//逻辑数�?
unsigned char CGameLogic::GetCardLogicValue(unsigned char cbCardData)
{
	//扑克属�?
	unsigned char cbCardColor=GetCardColor(cbCardData);
	unsigned char cbCardValue=GetCardValue(cbCardData);
    
	//转换数�?
	if (cbCardColor==0x40) return cbCardValue+2;
	return (cbCardValue<=2)?(cbCardValue+13):cbCardValue;
}

//对比扑克
bool CGameLogic::CompareCard(const unsigned char cbFirstCard[], const unsigned char cbNextCard[], unsigned char cbFirstCount, unsigned char cbNextCount)
{
	//获取类型
	unsigned char cbNextType=GetCardType(cbNextCard,cbNextCount);
	unsigned char cbFirstType=GetCardType(cbFirstCard,cbFirstCount);
    
	//类型判断
	if (cbNextType==CT_ERROR) return false;
	if (cbNextType==CT_MISSILE_CARD) return true;
    
	//炸弹判断
	if ((cbFirstType!=CT_BOMB_CARD)&&(cbNextType==CT_BOMB_CARD)) return true;
	if ((cbFirstType==CT_BOMB_CARD)&&(cbNextType!=CT_BOMB_CARD)) return false;
    
	//规则判断
	if ((cbFirstType!=cbNextType)||(cbFirstCount!=cbNextCount)) return false;
    
	//开始对�?
	switch (cbNextType)
	{
        case CT_SINGLE:
        case CT_DOUBLE:
        case CT_THREE:
        case CT_SINGLE_LINE:
        case CT_DOUBLE_LINE:
        case CT_THREE_LINE:
        case CT_BOMB_CARD:
		{
			//获取数�?
			unsigned char cbNextLogicValue=GetCardLogicValue(cbNextCard[0]);
			unsigned char cbFirstLogicValue=GetCardLogicValue(cbFirstCard[0]);
            
			//对比扑克
			return cbNextLogicValue>cbFirstLogicValue;
		}
        case CT_THREE_TAKE_ONE:
        case CT_THREE_TAKE_TWO:
		{
			//分析扑克
			tagAnalyseResult NextResult;
			tagAnalyseResult FirstResult;
			AnalysebCardData(cbNextCard,cbNextCount,NextResult);
			AnalysebCardData(cbFirstCard,cbFirstCount,FirstResult);
            
			//获取数�?
			unsigned char cbNextLogicValue=GetCardLogicValue(NextResult.cbCardData[2][0]);
			unsigned char cbFirstLogicValue=GetCardLogicValue(FirstResult.cbCardData[2][0]);
            
			//对比扑克
			return cbNextLogicValue>cbFirstLogicValue;
		}
        case CT_FOUR_TAKE_ONE:
        case CT_FOUR_TAKE_TWO:
		{
			//分析扑克
			tagAnalyseResult NextResult;
			tagAnalyseResult FirstResult;
			AnalysebCardData(cbNextCard,cbNextCount,NextResult);
			AnalysebCardData(cbFirstCard,cbFirstCount,FirstResult);
            
			//获取数�?
			unsigned char cbNextLogicValue=GetCardLogicValue(NextResult.cbCardData[3][0]);
			unsigned char cbFirstLogicValue=GetCardLogicValue(FirstResult.cbCardData[3][0]);
            
			//对比扑克
			return cbNextLogicValue>cbFirstLogicValue;
		}
	}
	
	return false;
}

//构造扑�?
unsigned char CGameLogic::MakeCardData(unsigned char cbValueIndex, unsigned char cbColorIndex)
{
	return (cbColorIndex<<4)|(cbValueIndex+1);
}

//分析扑克
void CGameLogic::AnalysebCardData(const unsigned char cbCardData[], unsigned char cbCardCount, tagAnalyseResult & AnalyseResult)
{
	//设置结果
	memset(&AnalyseResult,0,sizeof(AnalyseResult));
    
	//扑克分析
	for (unsigned char i=0;i<cbCardCount;i++)
	{
		//变量定义
		unsigned char cbSameCount=1;
		unsigned char cbLogicValue=GetCardLogicValue(cbCardData[i]);
        
		//搜索同牌
		for (unsigned char j=i+1;j<cbCardCount;j++)
		{
			//获取扑克
			if (GetCardLogicValue(cbCardData[j])!=cbLogicValue) break;
            
			//设置变量
			cbSameCount++;
		}
        
		//设置结果
		unsigned char cbIndex=AnalyseResult.cbBlockCount[cbSameCount-1]++;
		for (unsigned char j=0;j<cbSameCount;j++) AnalyseResult.cbCardData[cbSameCount-1][cbIndex*cbSameCount+j]=cbCardData[i+j];
        
		//设置索引
		i+=cbSameCount-1;
	}
    
	return;
}

//分析分布
void CGameLogic::AnalysebDistributing(const unsigned char cbCardData[], unsigned char cbCardCount, tagDistributing & Distributing)
{
	//设置变量
	memset(&Distributing,0,sizeof(Distributing));
    
	//设置变量
	for (unsigned char i=0;i<cbCardCount;i++)
	{
		if (cbCardData[i]==0) continue;
        
		//获取属�?
		unsigned char cbCardColor=GetCardColor(cbCardData[i]);
		unsigned char cbCardValue=GetCardValue(cbCardData[i]);
        
		//分布信息
		Distributing.cbCardCount++;
		Distributing.cbDistributing[cbCardValue-1][cbIndexCount]++;
		Distributing.cbDistributing[cbCardValue-1][cbCardColor>>4]++;
	}
	return;
}

//出牌搜索
unsigned char CGameLogic::SearchOutCard( const unsigned char cbHandCardData[], unsigned char cbHandCardCount, const unsigned char cbTurnCardData[], unsigned char cbTurnCardCount,tagSearchCardResult *pSearchCardResult )
{
	//设置结果
	if( pSearchCardResult == NULL ) return 0;
    
	memset(pSearchCardResult,0,sizeof(tagSearchCardResult));
    
	//变量定义
	unsigned char cbResultCount = 0;
	tagSearchCardResult tmpSearchCardResult = {};
    
	//构造扑�?
	unsigned char cbCardData[MAX_COUNT];
	unsigned char cbCardCount=cbHandCardCount;
	memcpy(cbCardData,cbHandCardData,sizeof(unsigned char)*cbHandCardCount);
    
	//排列扑克
	SortCardList(cbCardData,cbCardCount,ST_ORDER);
    
	//获取类型
	unsigned char cbTurnOutType=GetCardType(cbTurnCardData,cbTurnCardCount);
    
	//出牌分析
	switch (cbTurnOutType)
	{
        case CT_ERROR:					//错误类型(首出�?
		{
			//提取各种牌型一�?
			if( !pSearchCardResult ) return 0;
            
			//是否一手出�?
			if( GetCardType(cbCardData,cbCardCount) != CT_ERROR )
			{
				pSearchCardResult->cbCardCount[cbResultCount] = cbCardCount;
				memcpy( pSearchCardResult->cbResultCard[cbResultCount],cbCardData,
                       sizeof(unsigned char)*cbCardCount );
				cbResultCount++;
			}
            
			//如果最小牌不是单牌，则提取
			unsigned char cbSameCount = 0;
			if( cbCardCount > 1 && GetCardValue(cbCardData[cbCardCount-1]) == GetCardValue(cbCardData[cbCardCount-2]) )
			{
				cbSameCount = 1;
				pSearchCardResult->cbResultCard[cbResultCount][0] = cbCardData[cbCardCount-1];
				unsigned char cbCardValue = GetCardValue(cbCardData[cbCardCount-1]);
				for( int i = cbCardCount-2; i >= 0; i-- )
				{
					if( GetCardValue(cbCardData[i]) == cbCardValue )
					{
						pSearchCardResult->cbResultCard[cbResultCount][cbSameCount++] = cbCardData[i];
					}
					else break;
				}
                
				pSearchCardResult->cbCardCount[cbResultCount] = cbSameCount;
				cbResultCount++;
			}
            
			//单牌
			unsigned char cbTmpCount = 0;
			if( cbSameCount != 1 )
			{
				cbTmpCount = SearchSameCard( cbCardData,cbCardCount,0,1,&tmpSearchCardResult );
				if( cbTmpCount > 0 )
				{
					pSearchCardResult->cbCardCount[cbResultCount] = tmpSearchCardResult.cbCardCount[0];
					memcpy( pSearchCardResult->cbResultCard[cbResultCount],tmpSearchCardResult.cbResultCard[0],
                           sizeof(unsigned char)*tmpSearchCardResult.cbCardCount[0] );
					cbResultCount++;
				}
			}
            
			//对牌
			if( cbSameCount != 2 )
			{
				cbTmpCount = SearchSameCard( cbCardData,cbCardCount,0,2,&tmpSearchCardResult );
				if( cbTmpCount > 0 )
				{
					pSearchCardResult->cbCardCount[cbResultCount] = tmpSearchCardResult.cbCardCount[0];
					memcpy( pSearchCardResult->cbResultCard[cbResultCount],tmpSearchCardResult.cbResultCard[0],
                           sizeof(unsigned char)*tmpSearchCardResult.cbCardCount[0] );
					cbResultCount++;
				}
			}
            
			//三条
			if( cbSameCount != 3 )
			{
				cbTmpCount = SearchSameCard( cbCardData,cbCardCount,0,3,&tmpSearchCardResult );
				if( cbTmpCount > 0 )
				{
					pSearchCardResult->cbCardCount[cbResultCount] = tmpSearchCardResult.cbCardCount[0];
					memcpy( pSearchCardResult->cbResultCard[cbResultCount],tmpSearchCardResult.cbResultCard[0],
                           sizeof(unsigned char)*tmpSearchCardResult.cbCardCount[0] );
					cbResultCount++;
				}
			}
            
			//三带一�?
			cbTmpCount = SearchTakeCardType( cbCardData,cbCardCount,0,3,1,&tmpSearchCardResult );
			if( cbTmpCount > 0 )
			{
				pSearchCardResult->cbCardCount[cbResultCount] = tmpSearchCardResult.cbCardCount[0];
				memcpy( pSearchCardResult->cbResultCard[cbResultCount],tmpSearchCardResult.cbResultCard[0],
                       sizeof(unsigned char)*tmpSearchCardResult.cbCardCount[0] );
				cbResultCount++;
			}
            
			//三带一�?
			cbTmpCount = SearchTakeCardType( cbCardData,cbCardCount,0,3,2,&tmpSearchCardResult );
			if( cbTmpCount > 0 )
			{
				pSearchCardResult->cbCardCount[cbResultCount] = tmpSearchCardResult.cbCardCount[0];
				memcpy( pSearchCardResult->cbResultCard[cbResultCount],tmpSearchCardResult.cbResultCard[0],
                       sizeof(unsigned char)*tmpSearchCardResult.cbCardCount[0] );
				cbResultCount++;
			}
            
			//单连
			cbTmpCount = SearchLineCardType( cbCardData,cbCardCount,0,1,0,&tmpSearchCardResult );
			if( cbTmpCount > 0 )
			{
				pSearchCardResult->cbCardCount[cbResultCount] = tmpSearchCardResult.cbCardCount[0];
				memcpy( pSearchCardResult->cbResultCard[cbResultCount],tmpSearchCardResult.cbResultCard[0],
                       sizeof(unsigned char)*tmpSearchCardResult.cbCardCount[0] );
				cbResultCount++;
			}
            
			//连对
			cbTmpCount = SearchLineCardType( cbCardData,cbCardCount,0,2,0,&tmpSearchCardResult );
			if( cbTmpCount > 0 )
			{
				pSearchCardResult->cbCardCount[cbResultCount] = tmpSearchCardResult.cbCardCount[0];
				memcpy( pSearchCardResult->cbResultCard[cbResultCount],tmpSearchCardResult.cbResultCard[0],
                       sizeof(unsigned char)*tmpSearchCardResult.cbCardCount[0] );
				cbResultCount++;
			}
            
			//三连
			cbTmpCount = SearchLineCardType( cbCardData,cbCardCount,0,3,0,&tmpSearchCardResult );
			if( cbTmpCount > 0 )
			{
				pSearchCardResult->cbCardCount[cbResultCount] = tmpSearchCardResult.cbCardCount[0];
				memcpy( pSearchCardResult->cbResultCard[cbResultCount],tmpSearchCardResult.cbResultCard[0],
                       sizeof(unsigned char)*tmpSearchCardResult.cbCardCount[0] );
				cbResultCount++;
			}
            
			////飞机
			//cbTmpCount = SearchThreeTwoLine( cbCardData,cbCardCount,&tmpSearchCardResult );
			//if( cbTmpCount > 0 )
			//{
			//	pSearchCardResult->cbCardCount[cbResultCount] = tmpSearchCardResult.cbCardCount[0];
			//	memcpy( pSearchCardResult->cbResultCard[cbResultCount],tmpSearchCardResult.cbResultCard[0],
			//		sizeof(unsigned char)*tmpSearchCardResult.cbCardCount[0] );
			//	cbResultCount++;
			//}
            
			//炸弹
			if( cbSameCount != 4 )
			{
				cbTmpCount = SearchSameCard( cbCardData,cbCardCount,0,4,&tmpSearchCardResult );
				if( cbTmpCount > 0 )
				{
					pSearchCardResult->cbCardCount[cbResultCount] = tmpSearchCardResult.cbCardCount[0];
					memcpy( pSearchCardResult->cbResultCard[cbResultCount],tmpSearchCardResult.cbResultCard[0],
                           sizeof(unsigned char)*tmpSearchCardResult.cbCardCount[0] );
					cbResultCount++;
				}
			}
            
			//搜索火箭
			if ((cbCardCount>=2)&&(cbCardData[0]==0x4F)&&(cbCardData[1]==0x4E))
			{
				//设置结果
				pSearchCardResult->cbCardCount[cbResultCount] = 2;
				pSearchCardResult->cbResultCard[cbResultCount][0] = cbCardData[0];
				pSearchCardResult->cbResultCard[cbResultCount][1] = cbCardData[1];
                
				cbResultCount++;
			}
            
			pSearchCardResult->cbSearchCount = cbResultCount;
			return cbResultCount;
		}
        case CT_SINGLE:					//单牌类型
        case CT_DOUBLE:					//对牌类型
        case CT_THREE:					//三条类型
		{
			//变量定义
			unsigned char cbReferCard=cbTurnCardData[0];
			unsigned char cbSameCount = 1;
			if( cbTurnOutType == CT_DOUBLE ) cbSameCount = 2;
			else if( cbTurnOutType == CT_THREE ) cbSameCount = 3;
            
			//搜索相同�?
			cbResultCount = SearchSameCard( cbCardData,cbCardCount,cbReferCard,cbSameCount,pSearchCardResult );
            
			break;
		}
        case CT_SINGLE_LINE:		//单连类型
        case CT_DOUBLE_LINE:		//对连类型
        case CT_THREE_LINE:			//三连类型
		{
			//变量定义
			unsigned char cbBlockCount = 1;
			if( cbTurnOutType == CT_DOUBLE_LINE ) cbBlockCount = 2;
			else if( cbTurnOutType == CT_THREE_LINE ) cbBlockCount = 3;
            
			unsigned char cbLineCount = cbTurnCardCount/cbBlockCount;
            
			//搜索连牌
			cbResultCount = SearchLineCardType( cbCardData,cbCardCount,cbTurnCardData[0],cbBlockCount,cbLineCount,pSearchCardResult );
            
			break;
		}
        case CT_THREE_TAKE_ONE:	//三带一�?
        case CT_THREE_TAKE_TWO:	//三带一�?
		{
			//效验牌数
			if( cbCardCount < cbTurnCardCount ) break;
            
			//如果是三带一或三带二
			if( cbTurnCardCount == 4 || cbTurnCardCount == 5 )
			{
				unsigned char cbTakeCardCount = cbTurnOutType==CT_THREE_TAKE_ONE?1:2;
                
				//搜索三带牌型
				cbResultCount = SearchTakeCardType( cbCardData,cbCardCount,cbTurnCardData[2],3,cbTakeCardCount,pSearchCardResult );
			}
			else
			{
				//变量定义
				unsigned char cbBlockCount = 3;
				unsigned char cbLineCount = cbTurnCardCount/(cbTurnOutType==CT_THREE_TAKE_ONE?4:5);
				unsigned char cbTakeCardCount = cbTurnOutType==CT_THREE_TAKE_ONE?1:2;
                
				//搜索连牌
				unsigned char cbTmpTurnCard[MAX_COUNT] = {};
				memcpy( cbTmpTurnCard,cbTurnCardData,sizeof(unsigned char)*cbTurnCardCount );
				SortOutCardList( cbTmpTurnCard,cbTurnCardCount );
				cbResultCount = SearchLineCardType( cbCardData,cbCardCount,cbTmpTurnCard[0],cbBlockCount,cbLineCount,pSearchCardResult );
                
				//提取带牌
				bool bAllDistill = true;
				for( unsigned char i = 0; i < cbResultCount; i++ )
				{
					unsigned char cbResultIndex = cbResultCount-i-1;
                    
					//变量定义
					unsigned char cbTmpCardData[MAX_COUNT];
					unsigned char cbTmpCardCount = cbCardCount;
                    
					//删除连牌
					memcpy( cbTmpCardData,cbCardData,sizeof(unsigned char)*cbCardCount );
					cbTmpCardCount -= pSearchCardResult->cbCardCount[cbResultIndex];
                    
					//分析�?
					tagAnalyseResult  TmpResult = {};
					AnalysebCardData( cbTmpCardData,cbTmpCardCount,TmpResult );
                    
					//提取�?
					unsigned char cbDistillCard[MAX_COUNT] = {};
					unsigned char cbDistillCount = 0;
					for( unsigned char j = cbTakeCardCount-1; j < CountArray(TmpResult.cbBlockCount); j++ )
					{
						if( TmpResult.cbBlockCount[j] > 0 )
						{
							if( j+1 == cbTakeCardCount && TmpResult.cbBlockCount[j] >= cbLineCount )
							{
								unsigned char cbTmpBlockCount = TmpResult.cbBlockCount[j];
								memcpy( cbDistillCard,&TmpResult.cbCardData[j][(cbTmpBlockCount-cbLineCount)*(j+1)],
                                       sizeof(unsigned char)*(j+1)*cbLineCount );
								cbDistillCount = (j+1)*cbLineCount;
								break;
							}
							else
							{
								for( unsigned char k = 0; k < TmpResult.cbBlockCount[j]; k++ )
								{
									unsigned char cbTmpBlockCount = TmpResult.cbBlockCount[j];
									memcpy( &cbDistillCard[cbDistillCount],&TmpResult.cbCardData[j][(cbTmpBlockCount-k-1)*(j+1)],
                                           sizeof(unsigned char)*cbTakeCardCount );
									cbDistillCount += cbTakeCardCount;
                                    
									//提取完成
									if( cbDistillCount == cbTakeCardCount*cbLineCount ) break;
								}
							}
						}
                        
						//提取完成
						if( cbDistillCount == cbTakeCardCount*cbLineCount ) break;
					}
                    
					//提取完成
					if( cbDistillCount == cbTakeCardCount*cbLineCount )
					{
						//复制带牌
						unsigned char cbCount = pSearchCardResult->cbCardCount[cbResultIndex];
						memcpy( &pSearchCardResult->cbResultCard[cbResultIndex][cbCount],cbDistillCard,
                               sizeof(unsigned char)*cbDistillCount );
						pSearchCardResult->cbCardCount[cbResultIndex] += cbDistillCount;
					}
					//否则删除连牌
					else
					{
						bAllDistill = false;
						pSearchCardResult->cbCardCount[cbResultIndex] = 0;
					}
				}
                
				//整理组合
				if( !bAllDistill )
				{
					pSearchCardResult->cbSearchCount = cbResultCount;
					cbResultCount = 0;
					for( unsigned char i = 0; i < pSearchCardResult->cbSearchCount; i++ )
					{
						if( pSearchCardResult->cbCardCount[i] != 0 )
						{
							tmpSearchCardResult.cbCardCount[cbResultCount] = pSearchCardResult->cbCardCount[i];
							memcpy( tmpSearchCardResult.cbResultCard[cbResultCount],pSearchCardResult->cbResultCard[i],
                                   sizeof(unsigned char)*pSearchCardResult->cbCardCount[i] );
							cbResultCount++;
						}
					}
					tmpSearchCardResult.cbSearchCount = cbResultCount;
					memcpy( pSearchCardResult,&tmpSearchCardResult,sizeof(tagSearchCardResult) );
				}
			}
            
			break;
		}
        case CT_FOUR_TAKE_ONE:		//四带两单
        case CT_FOUR_TAKE_TWO:		//四带两双
		{
			unsigned char cbTakeCount = cbTurnOutType==CT_FOUR_TAKE_ONE?1:2;
            
			unsigned char cbTmpTurnCard[MAX_COUNT] = {};
			memcpy( cbTmpTurnCard,cbTurnCardData,sizeof(unsigned char)*cbTurnCardCount );
			SortOutCardList( cbTmpTurnCard,cbTurnCardCount );
            
			//搜索带牌
			cbResultCount = SearchTakeCardType( cbCardData,cbCardCount,cbTmpTurnCard[0],4,cbTakeCount,pSearchCardResult );
            
			break;
		}
	}
    
	//搜索炸弹
	if ((cbCardCount>=4)&&(cbTurnOutType!=CT_MISSILE_CARD))
	{
		//变量定义
		unsigned char cbReferCard = 0;
		if (cbTurnOutType==CT_BOMB_CARD) cbReferCard=cbTurnCardData[0];
        
		//搜索炸弹
		unsigned char cbTmpResultCount = SearchSameCard( cbCardData,cbCardCount,cbReferCard,4,&tmpSearchCardResult );
		for( unsigned char i = 0; i < cbTmpResultCount; i++ )
		{
			pSearchCardResult->cbCardCount[cbResultCount] = tmpSearchCardResult.cbCardCount[i];
			memcpy( pSearchCardResult->cbResultCard[cbResultCount],tmpSearchCardResult.cbResultCard[i],
                   sizeof(unsigned char)*tmpSearchCardResult.cbCardCount[i]);
			cbResultCount++;
		}
	}
    
	//搜索火箭
	if (cbTurnOutType!=CT_MISSILE_CARD&&(cbCardCount>=2)&&(cbCardData[0]==0x4F)&&(cbCardData[1]==0x4E))
	{
		//设置结果
		pSearchCardResult->cbCardCount[cbResultCount] = 2;
		pSearchCardResult->cbResultCard[cbResultCount][0] = cbCardData[0];
		pSearchCardResult->cbResultCard[cbResultCount][1] = cbCardData[1];
        
		cbResultCount++;
	}
    
	pSearchCardResult->cbSearchCount = cbResultCount;
	return cbResultCount;
}

//同牌搜索
unsigned char CGameLogic::SearchSameCard( const unsigned char cbHandCardData[], unsigned char cbHandCardCount, unsigned char cbReferCard, unsigned char cbSameCardCount,
								tagSearchCardResult *pSearchCardResult )
{
	//设置结果
	if( pSearchCardResult )
		memset(pSearchCardResult,0,sizeof(tagSearchCardResult));
	unsigned char cbResultCount = 0;
    
	//构造扑�?
	unsigned char cbCardData[MAX_COUNT];
	unsigned char cbCardCount=cbHandCardCount;
	memcpy(cbCardData,cbHandCardData,sizeof(unsigned char)*cbHandCardCount);
    
	//排列扑克
	SortCardList(cbCardData,cbCardCount,ST_ORDER);
    
	//分析扑克
	tagAnalyseResult AnalyseResult = {};
	AnalysebCardData( cbCardData,cbCardCount,AnalyseResult );
    
	unsigned char cbReferLogicValue = cbReferCard==0?0:GetCardLogicValue(cbReferCard);
	unsigned char cbBlockIndex = cbSameCardCount-1;
	do
	{
		for( unsigned char i = 0; i < AnalyseResult.cbBlockCount[cbBlockIndex]; i++ )
		{
			unsigned char cbIndex = (AnalyseResult.cbBlockCount[cbBlockIndex]-i-1)*(cbBlockIndex+1);
			if( GetCardLogicValue(AnalyseResult.cbCardData[cbBlockIndex][cbIndex]) > cbReferLogicValue )
			{
				if( pSearchCardResult == NULL ) return 1;
                
				//复制扑克
				memcpy( pSearchCardResult->cbResultCard[cbResultCount],&AnalyseResult.cbCardData[cbBlockIndex][cbIndex],
                       cbSameCardCount*sizeof(unsigned char) );
				pSearchCardResult->cbCardCount[cbResultCount] = cbSameCardCount;
                
				cbResultCount++;
			}
		}
        
		cbBlockIndex++;
	}while( cbBlockIndex < CountArray(AnalyseResult.cbBlockCount) );
    
	if( pSearchCardResult )
		pSearchCardResult->cbSearchCount = cbResultCount;
	return cbResultCount;
}

//带牌类型搜索(三带一，四带一�?
unsigned char CGameLogic::SearchTakeCardType( const unsigned char cbHandCardData[], unsigned char cbHandCardCount, unsigned char cbReferCard, unsigned char cbSameCount, unsigned char cbTakeCardCount,
									tagSearchCardResult *pSearchCardResult )
{
	//设置结果
	if( pSearchCardResult )
		memset(pSearchCardResult,0,sizeof(tagSearchCardResult));
	_BYTE_ cbResultCount = 0;
    
	//效验
	if( cbSameCount != 3 && cbSameCount != 4 )
		return cbResultCount;
	if( cbTakeCardCount != 1 && cbTakeCardCount != 2 )
		return cbResultCount;
    
	//长度判断
    if( cbSameCount == 3 && cbHandCardCount < cbSameCount + cbTakeCardCount){
        return cbResultCount;
    }
    
	if( cbSameCount == 4 ){
        if( cbTakeCardCount != 2 ){
            return cbResultCount;
        }
        if(cbHandCardCount < cbSameCount + 2){
            return cbResultCount;
        }
    }
    
	//构造扑�?
	_BYTE_ cbCardData[MAX_COUNT];
	_BYTE_ cbCardCount=cbHandCardCount;
	memcpy(cbCardData,cbHandCardData,sizeof(_BYTE_)*cbHandCardCount);
    
	//排列扑克
	SortCardList(cbCardData,cbHandCardCount,ST_ORDER);
    
	//搜索同张
	tagSearchCardResult SameCardResult = {};
	_BYTE_ cbSameCardResultCount = SearchSameCard( cbCardData,cbCardCount,cbReferCard,cbSameCount,&SameCardResult );
    
	if( cbSameCardResultCount > 0 )
	{
		//分析扑克
		tagAnalyseResult AnalyseResult;
		AnalysebCardData(cbCardData,cbCardCount,AnalyseResult);
        
		//需要牌�?
		_BYTE_ cbNeedCount = cbSameCount+cbTakeCardCount;
		if( cbSameCount == 4 ) cbNeedCount += cbTakeCardCount;
        
		//提取带牌
		for( _BYTE_ i = 0; i < cbSameCardResultCount; i++ )
		{
			bool bMerge = false;
            
			for( _BYTE_ j = cbTakeCardCount-1; j < CountArray(AnalyseResult.cbBlockCount); j++ )
			{
				for( _BYTE_ k = 0; k < AnalyseResult.cbBlockCount[j]; k++ )
				{
					//从小到大
					_BYTE_ cbIndex = (AnalyseResult.cbBlockCount[j]-k-1)*(j+1);
                    
					//过滤相同�?
					if( GetCardValue(SameCardResult.cbResultCard[i][0]) ==
                       GetCardValue(AnalyseResult.cbCardData[j][cbIndex]) )
						continue;
                    
					//复制带牌
					_BYTE_ cbCount = SameCardResult.cbCardCount[i];
					memcpy( &SameCardResult.cbResultCard[i][cbCount],&AnalyseResult.cbCardData[j][cbIndex],
                           sizeof(_BYTE_)*cbTakeCardCount );
					SameCardResult.cbCardCount[i] += cbTakeCardCount;
                    
					if( SameCardResult.cbCardCount[i] < cbNeedCount ) continue;
                    
					if( pSearchCardResult == NULL ) return 1;
                    
					//复制结果
					memcpy( pSearchCardResult->cbResultCard[cbResultCount],SameCardResult.cbResultCard[i],
                           sizeof(_BYTE_)*SameCardResult.cbCardCount[i] );
					pSearchCardResult->cbCardCount[cbResultCount] = SameCardResult.cbCardCount[i];
					cbResultCount++;
                    
					bMerge = true;
                    
					//下一组合
					break;
				}
                
				if( bMerge ) break;
			}
		}
	}
    
	if( pSearchCardResult )
		pSearchCardResult->cbSearchCount = cbResultCount;
	return cbResultCount;
}

//连牌搜索
unsigned char CGameLogic::SearchLineCardType( const unsigned char cbHandCardData[], unsigned char cbHandCardCount, unsigned char cbReferCard, unsigned char cbBlockCount, unsigned char cbLineCount,tagSearchCardResult *pSearchCardResult )
{
	//设置结果
	if( pSearchCardResult )
		memset(pSearchCardResult,0,sizeof(tagSearchCardResult));
	_BYTE_ cbResultCount = 0;
    
	//定义变量
	_BYTE_ cbLessLineCount = 0;
	if( cbLineCount == 0 )
	{
		if( cbBlockCount == 1 )
			cbLessLineCount = 5;
		else if( cbBlockCount == 2 )
			cbLessLineCount = 3;
		else cbLessLineCount = 2;
	}
	else cbLessLineCount = cbLineCount;
    
	_BYTE_ cbReferIndex = 2;
	if( cbReferCard != 0 )
	{
		cbReferIndex = GetCardLogicValue(cbReferCard)-cbLessLineCount+1;
	}
	//超过A
	if( cbReferIndex + cbLessLineCount > 14 ) return cbResultCount;
    
    
	//长度判断
	if( cbHandCardCount < cbLessLineCount*cbBlockCount ) return cbResultCount;
    
    
	//构造扑�?
	_BYTE_ cbCardData[MAX_COUNT];
	_BYTE_ cbCardCount=cbHandCardCount;
	memcpy(cbCardData,cbHandCardData,sizeof(_BYTE_)*cbHandCardCount);
    
	//排列扑克
	SortCardList(cbCardData,cbCardCount,ST_ORDER);
    
	//分析扑克
	tagDistributing Distributing = {};
	AnalysebDistributing(cbCardData,cbCardCount,Distributing);
    
	//搜索顺子
	_BYTE_ cbTmpLinkCount = 0;
	for (_BYTE_ cbValueIndex=cbReferIndex;cbValueIndex<13;cbValueIndex++)
	{
		//继续判断
		if ( Distributing.cbDistributing[cbValueIndex][cbIndexCount]<cbBlockCount )
		{
			if( cbTmpLinkCount < cbLessLineCount )
			{
				cbTmpLinkCount=0;
				continue;
			}
			else cbValueIndex--;
		}
		else
		{
			cbTmpLinkCount++;
			//寻找最长连
			if( cbLineCount == 0 ) continue;
		}
        
		if( cbTmpLinkCount >= cbLessLineCount )
		{
			if( pSearchCardResult == NULL ) return 1;
            
			//复制扑克
			_BYTE_ cbCount = 0;
			for( _BYTE_ cbIndex = cbValueIndex+1-cbTmpLinkCount; cbIndex <= cbValueIndex; cbIndex++ )
			{
				_BYTE_ cbTmpCount = 0;
				for (_BYTE_ cbColorIndex=0;cbColorIndex<4;cbColorIndex++)
				{
					for( _BYTE_ cbColorCount = 0; cbColorCount < Distributing.cbDistributing[cbIndex][3-cbColorIndex]; cbColorCount++ )
					{
						pSearchCardResult->cbResultCard[cbResultCount][cbCount++]=MakeCardData(cbIndex,3-cbColorIndex);
                        
						if( ++cbTmpCount == cbBlockCount ) break;
					}
					if( cbTmpCount == cbBlockCount ) break;
				}
			}
            
			//设置变量
			pSearchCardResult->cbCardCount[cbResultCount] = cbCount;
			cbResultCount++;
            
			if( cbLineCount != 0 )
			{
				cbTmpLinkCount--;
			}
			else
			{
				cbTmpLinkCount = 0;
			}
		}
	}
    
	//特殊顺子
	if( cbTmpLinkCount >= cbLessLineCount-1 && cbReferIndex == 13 )
	{
		if( Distributing.cbDistributing[0][cbIndexCount] >= cbBlockCount ||
           cbTmpLinkCount >= cbLessLineCount )
		{
			if( pSearchCardResult == NULL ) return 1;
            
			//复制扑克
			_BYTE_ cbCount = 0;
			_BYTE_ cbTmpCount = 0;
			for( _BYTE_ cbIndex = cbReferIndex-cbTmpLinkCount; cbIndex < 13; cbIndex++ )
			{
				cbTmpCount = 0;
				for (_BYTE_ cbColorIndex=0;cbColorIndex<4;cbColorIndex++)
				{
					for( _BYTE_ cbColorCount = 0; cbColorCount < Distributing.cbDistributing[cbIndex][3-cbColorIndex]; cbColorCount++ )
					{
						pSearchCardResult->cbResultCard[cbResultCount][cbCount++]=MakeCardData(cbIndex,3-cbColorIndex);
                        
						if( ++cbTmpCount == cbBlockCount ) break;
					}
					if( cbTmpCount == cbBlockCount ) break;
				}
			}
			//复制A
			if( Distributing.cbDistributing[0][cbIndexCount] >= cbBlockCount )
			{
				cbTmpCount = 0;
				for (_BYTE_ cbColorIndex=0;cbColorIndex<4;cbColorIndex++)
				{
					for( _BYTE_ cbColorCount = 0; cbColorCount < Distributing.cbDistributing[0][3-cbColorIndex]; cbColorCount++ )
					{
						pSearchCardResult->cbResultCard[cbResultCount][cbCount++]=MakeCardData(0,3-cbColorIndex);
                        
						if( ++cbTmpCount == cbBlockCount ) break;
					}
					if( cbTmpCount == cbBlockCount ) break;
				}
			}
            
			//设置变量
			pSearchCardResult->cbCardCount[cbResultCount] = cbCount;
			cbResultCount++;
		}
	}
    
	if( pSearchCardResult )
		pSearchCardResult->cbSearchCount = cbResultCount;
	return cbResultCount;
}

//搜索飞机
unsigned char CGameLogic::SearchThreeTwoLine( const unsigned char cbHandCardData[], unsigned char cbHandCardCount, tagSearchCardResult *pSearchCardResult )
{
	//设置结果
	if( pSearchCardResult )
		memset(pSearchCardResult,0,sizeof(tagSearchCardResult));
    
	//变量定义
	tagSearchCardResult tmpSearchResult = {};
	tagSearchCardResult tmpSingleWing = {};
	tagSearchCardResult tmpDoubleWing = {};
	unsigned char cbTmpResultCount = 0;
    
	//搜索连牌
	cbTmpResultCount = SearchLineCardType( cbHandCardData,cbHandCardCount,0,3,0,&tmpSearchResult );
    
	if( cbTmpResultCount > 0 )
	{
		//提取带牌
		for( unsigned char i = 0; i < cbTmpResultCount; i++ )
		{
			//变量定义
			unsigned char cbTmpCardData[MAX_COUNT];
			unsigned char cbTmpCardCount = cbHandCardCount;
            
			//不够�?
			if( cbHandCardCount-tmpSearchResult.cbCardCount[i] < tmpSearchResult.cbCardCount[i]/3 )
			{
				unsigned char cbNeedDelCount = 3;
				while( cbHandCardCount+cbNeedDelCount-tmpSearchResult.cbCardCount[i] < (tmpSearchResult.cbCardCount[i]-cbNeedDelCount)/3 )
					cbNeedDelCount += 3;
				//不够连牌
				if( (tmpSearchResult.cbCardCount[i]-cbNeedDelCount)/3 < 2 )
				{
					//废除连牌
					continue;
				}
                
				//拆分连牌
				RemoveCard( tmpSearchResult.cbResultCard[i],cbNeedDelCount,tmpSearchResult.cbResultCard[i],
                           tmpSearchResult.cbCardCount[i] );
				tmpSearchResult.cbCardCount[i] -= cbNeedDelCount;
			}
            
			if( pSearchCardResult == NULL ) return 1;
            
			//删除连牌
			memcpy( cbTmpCardData,cbHandCardData,sizeof(unsigned char)*cbHandCardCount );
			
			cbTmpCardCount -= tmpSearchResult.cbCardCount[i];
            
			//组合飞机
			unsigned char cbNeedCount = tmpSearchResult.cbCardCount[i]/3;
            
			unsigned char cbResultCount = tmpSingleWing.cbSearchCount++;
			memcpy( tmpSingleWing.cbResultCard[cbResultCount],tmpSearchResult.cbResultCard[i],
                   sizeof(unsigned char)*tmpSearchResult.cbCardCount[i] );
			memcpy( &tmpSingleWing.cbResultCard[cbResultCount][tmpSearchResult.cbCardCount[i]],
                   &cbTmpCardData[cbTmpCardCount-cbNeedCount],sizeof(unsigned char)*cbNeedCount );
			tmpSingleWing.cbCardCount[i] = tmpSearchResult.cbCardCount[i]+cbNeedCount;
            
			//不够带翅膀
			if( cbTmpCardCount < tmpSearchResult.cbCardCount[i]/3*2 )
			{
				unsigned char cbNeedDelCount = 3;
				while( cbTmpCardCount+cbNeedDelCount-tmpSearchResult.cbCardCount[i] < (tmpSearchResult.cbCardCount[i]-cbNeedDelCount)/3*2 )
					cbNeedDelCount += 3;
				//不够连牌
				if( (tmpSearchResult.cbCardCount[i]-cbNeedDelCount)/3 < 2 )
				{
					//废除连牌
					continue;
				}
                
				//拆分连牌
				RemoveCard( tmpSearchResult.cbResultCard[i],cbNeedDelCount,tmpSearchResult.cbResultCard[i],
                           tmpSearchResult.cbCardCount[i] );
				tmpSearchResult.cbCardCount[i] -= cbNeedDelCount;
                
				//重新删除连牌
				memcpy( cbTmpCardData,cbHandCardData,sizeof(unsigned char)*cbHandCardCount );
				
				cbTmpCardCount = cbHandCardCount-tmpSearchResult.cbCardCount[i];
			}
            
			//分析�?
			tagAnalyseResult  TmpResult = {};
			AnalysebCardData( cbTmpCardData,cbTmpCardCount,TmpResult );
            
			//提取翅膀
			unsigned char cbDistillCard[MAX_COUNT] = {};
			unsigned char cbDistillCount = 0;
			unsigned char cbLineCount = tmpSearchResult.cbCardCount[i]/3;
			for( unsigned char j = 1; j < CountArray(TmpResult.cbBlockCount); j++ )
			{
				if( TmpResult.cbBlockCount[j] > 0 )
				{
					if( j+1 == 2 && TmpResult.cbBlockCount[j] >= cbLineCount )
					{
						unsigned char cbTmpBlockCount = TmpResult.cbBlockCount[j];
						memcpy( cbDistillCard,&TmpResult.cbCardData[j][(cbTmpBlockCount-cbLineCount)*(j+1)],
                               sizeof(unsigned char)*(j+1)*cbLineCount );
						cbDistillCount = (j+1)*cbLineCount;
						break;
					}
					else
					{
						for( unsigned char k = 0; k < TmpResult.cbBlockCount[j]; k++ )
						{
							unsigned char cbTmpBlockCount = TmpResult.cbBlockCount[j];
							memcpy( &cbDistillCard[cbDistillCount],&TmpResult.cbCardData[j][(cbTmpBlockCount-k-1)*(j+1)],
                                   sizeof(unsigned char)*2 );
							cbDistillCount += 2;
                            
							//提取完成
							if( cbDistillCount == 2*cbLineCount ) break;
						}
					}
				}
                
				//提取完成
				if( cbDistillCount == 2*cbLineCount ) break;
			}
            
			//提取完成
			if( cbDistillCount == 2*cbLineCount )
			{
				//复制翅膀
				cbResultCount = tmpDoubleWing.cbSearchCount++;
				memcpy( tmpDoubleWing.cbResultCard[cbResultCount],tmpSearchResult.cbResultCard[i],
                       sizeof(unsigned char)*tmpSearchResult.cbCardCount[i] );
				memcpy( &tmpDoubleWing.cbResultCard[cbResultCount][tmpSearchResult.cbCardCount[i]],
                       cbDistillCard,sizeof(unsigned char)*cbDistillCount );
				tmpDoubleWing.cbCardCount[i] = tmpSearchResult.cbCardCount[i]+cbDistillCount;
			}
		}
        
		//复制结果
		for( unsigned char i = 0; i < tmpDoubleWing.cbSearchCount; i++ )
		{
			unsigned char cbResultCount = pSearchCardResult->cbSearchCount++;
            
			memcpy( pSearchCardResult->cbResultCard[cbResultCount],tmpDoubleWing.cbResultCard[i],
                   sizeof(unsigned char)*tmpDoubleWing.cbCardCount[i] );
			pSearchCardResult->cbCardCount[cbResultCount] = tmpDoubleWing.cbCardCount[i];
		}
		for( unsigned char i = 0; i < tmpSingleWing.cbSearchCount; i++ )
		{
			unsigned char cbResultCount = pSearchCardResult->cbSearchCount++;
            
			memcpy( pSearchCardResult->cbResultCard[cbResultCount],tmpSingleWing.cbResultCard[i],
                   sizeof(unsigned char)*tmpSingleWing.cbCardCount[i] );
			pSearchCardResult->cbCardCount[cbResultCount] = tmpSingleWing.cbCardCount[i];
		}
	}
    
	return pSearchCardResult==NULL?0:pSearchCardResult->cbSearchCount;
}

//////////////////////////////////////////////////////////////////////////////////
