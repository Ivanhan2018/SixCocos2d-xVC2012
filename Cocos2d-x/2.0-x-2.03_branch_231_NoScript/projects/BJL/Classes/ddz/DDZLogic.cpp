//
//  DDZLogic.cpp
//  Game
//
//  Created by zhouwei on 13-6-20.
//
//

#include "DDZLogic.h"
#include "cocos2d.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////

//�˿�����
const unsigned char	DDZLogic::m_cbCardData[54]=
{
    0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,	//���� A - K
    0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,	//÷�� A - K
    0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,	//���� A - K
    0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,	//���� A - K
    0x4E,0x4F,
};

///////////////////////////////////////////////////////////////////////////////////////////////////
//-------------------��Ӧ��Ӧ��Ϸ�߼�ֵ------------------
/// 14,15,3,4,5,6,7,8,9,10,11,12,13
/// 14,15,3,4,5,6,7,8,9,10,11,12,13
/// 14,15,3,4,5,6,7,8,9,10,11,12,13
/// 16,17
///////////////////////////////////////////////////////////////////////////////////////////////////

//��Ϸ�߼���ʵ��
//���캯��
DDZLogic::DDZLogic()
{
    //for (int i = 0; i < 54; i++)
    //{
    //    int value = getCardLogicValue(m_cbCardData[i]);
    //    CCLOG("value = %d",value);
    //}
}

//��������
DDZLogic::~DDZLogic()
{
}
//�����˿�
void DDZLogic::sortCardList(unsigned char cbCardData[], unsigned char cbCardCount, unsigned char cbSortType)
{
	//��Ŀ����
	if (cbCardCount==0) return;
    
	//ת����ֵ
	unsigned char cbSortValue[MAX_COUNT];
	for (unsigned char i=0;i<cbCardCount;i++) cbSortValue[i]=getCardLogicValue(cbCardData[i]);
    
	//�������
	bool bSorted=true;
	unsigned char cbThreeCount,cbLast=cbCardCount-1;
	do
	{
		bSorted=true;
		for (unsigned char i=0;i<cbLast;i++)
		{
			if ((cbSortValue[i]<cbSortValue[i+1])||
				((cbSortValue[i]==cbSortValue[i+1])&&(cbCardData[i]<cbCardData[i+1])))
			{
				//����λ��
				cbThreeCount=cbCardData[i];
				cbCardData[i]=cbCardData[i+1];
				cbCardData[i+1]=cbThreeCount;
				cbThreeCount=cbSortValue[i];
				cbSortValue[i]=cbSortValue[i+1];
				cbSortValue[i+1]=cbThreeCount;
				bSorted=false;
			}
		}
		cbLast--;
	} while(bSorted==false);
    
	//��Ŀ����
	if (cbSortType==ST_COUNT)
	{
		//�����˿�
		unsigned char cbIndex=0;
		tagAnalyseResult AnalyseResult;
		analysebCardData(cbCardData,cbCardCount,AnalyseResult);
        
		//��������
		memcpy(&cbCardData[cbIndex],AnalyseResult.cbFourCardData,sizeof(unsigned char)*AnalyseResult.cbFourCount*4);
		cbIndex+=AnalyseResult.cbFourCount*4;
        
		//��������
		memcpy(&cbCardData[cbIndex],AnalyseResult.cbThreeCardData,sizeof(unsigned char)*AnalyseResult.cbThreeCount*3);
		cbIndex+=AnalyseResult.cbThreeCount*3;
        
		//��������
		memcpy(&cbCardData[cbIndex],AnalyseResult.cbDoubleCardData,sizeof(unsigned char)*AnalyseResult.cbDoubleCount*2);
		cbIndex+=AnalyseResult.cbDoubleCount*2;
        
		//��������
		memcpy(&cbCardData[cbIndex],AnalyseResult.cbSignedCardData,sizeof(unsigned char)*AnalyseResult.cbSignedCount);
		cbIndex+=AnalyseResult.cbSignedCount;
	}
    
	return;
}
//�߼���ֵ
unsigned char DDZLogic::getCardLogicValue(unsigned char cbCardData)
{
	//�˿�����
	unsigned char cbCardColor=getCardColor(cbCardData);
	unsigned char cbCardValue=getCardValue(cbCardData);
    
	//ת����ֵ
	if (cbCardColor==0x40) return cbCardValue+2;
	return (cbCardValue<=2)?(cbCardValue+13):cbCardValue;
}

//��ȡͬ������
unsigned char DDZLogic::getSampleCount(unsigned char cbCardData[], unsigned char cbCardCount, unsigned char cbCard)
{
    unsigned char cbCount = 0;
    for (int i = 0; i < cbCardCount; i++)
    {
        if (getCardValue(cbCardData[i]) == cbCard)
        {
            cbCount++;
        }
    }
    return  cbCount;
}
//�����˿�
void DDZLogic::analysebCardData(const unsigned char cbCardData[], unsigned char cbCardCount, tagAnalyseResult & AnalyseResult,bool bFlag)
{
	//���ý��
	memset(&AnalyseResult,0,sizeof(AnalyseResult));
    
	//�˿˷���
	for (unsigned char i=0;i<cbCardCount;i++)
	{
		//��������
		unsigned char cbSameCount=1,cbCardValueTemp=0;
		unsigned char cbLogicValue=getCardLogicValue(cbCardData[i]);
        
		//����ͬ��
		for (unsigned char j=i+1;j<cbCardCount;j++)
		{
			//��ȡ�˿�
			if (getCardLogicValue(cbCardData[j])!=cbLogicValue) break;
            
			//���ñ���
			cbSameCount++;
		}
        
		//���ý��
		switch (cbSameCount)
		{
            case 1:		//����
			{
				unsigned char cbIndex=AnalyseResult.cbSignedCount++;
				AnalyseResult.cbSignedCardData[cbIndex*cbSameCount]=cbCardData[i];
				break;
			}
            case 2:		//����
			{
				unsigned char cbIndex=AnalyseResult.cbDoubleCount++;
				AnalyseResult.cbDoubleCardData[cbIndex*cbSameCount]=cbCardData[i];
				AnalyseResult.cbDoubleCardData[cbIndex*cbSameCount+1]=cbCardData[i+1];
				break;
			}
            case 3:		//����
			{
                if (bFlag)
                {
                    unsigned char cbIndex=AnalyseResult.cbDoubleCount++;
                    AnalyseResult.cbDoubleCardData[cbIndex*2]=cbCardData[i];
                    AnalyseResult.cbDoubleCardData[cbIndex*2+1]=cbCardData[i+1];
                }else
                {
                    unsigned char cbIndex=AnalyseResult.cbThreeCount++;
                    AnalyseResult.cbThreeCardData[cbIndex*cbSameCount]=cbCardData[i];
                    AnalyseResult.cbThreeCardData[cbIndex*cbSameCount+1]=cbCardData[i+1];
                    AnalyseResult.cbThreeCardData[cbIndex*cbSameCount+2]=cbCardData[i+2];
                }
				break;
			}
            case 4:		//����
			{
				unsigned char cbIndex=AnalyseResult.cbFourCount++;
				AnalyseResult.cbFourCardData[cbIndex*cbSameCount]=cbCardData[i];
				AnalyseResult.cbFourCardData[cbIndex*cbSameCount+1]=cbCardData[i+1];
				AnalyseResult.cbFourCardData[cbIndex*cbSameCount+2]=cbCardData[i+2];
				AnalyseResult.cbFourCardData[cbIndex*cbSameCount+3]=cbCardData[i+3];
				break;
			}
		}
        
		//��������
		i+=cbSameCount-1;
	}
    
	return;
}

//ɾ���˿�
bool DDZLogic::removeCard(const unsigned char cbRemoveCard[], unsigned char cbRemoveCount, unsigned char cbCardData[], unsigned char cbCardCount)
{
	////��������
	////assert(cbRemoveCount<=cbCardCount);
	////�������
	//unsigned char cbDeleteCount=0,cbTempCardData[MAX_COUNT];
	////assert(cbCardCount<=CountArray(cbTempCardData));
	//memcpy(cbTempCardData,cbCardData,cbCardCount*sizeof(cbCardData[0]));
 //   
	////�����˿�
	//for (unsigned char i=0;i<cbRemoveCount;i++)
	//{
	//	for (unsigned char j=0;j<cbCardCount;j++)
	//	{
	//		if (cbRemoveCard[i]==cbTempCardData[j])
	//		{
	//			cbDeleteCount++;
	//			cbTempCardData[j]=0;
	//			break;
	//		}
	//	}
	//}
	//if (cbDeleteCount!=cbRemoveCount)
	//{
	//	//AfxMessageBox("ɾ������190",MB_OK);
	//	return false;
	//}
 //   
	////�����˿�
	//unsigned char cbCardPos=0;
	//for (unsigned char i=0;i<cbCardCount;i++)
	//{
	//	if (cbTempCardData[i]!=0) cbCardData[cbCardPos++]=cbTempCardData[i];
	//}
	return true;
}

//��ȡ����
unsigned char DDZLogic::getCardType(const unsigned char cbCardData[], unsigned char cbCardCount)
{
	//������
	switch (cbCardCount)
	{
        case 0:	//����
		{
			return CT_ERROR;
		}
        case 1: //����
		{
			return CT_SINGLE;
		}
        case 2:	//���ƻ��
		{
			//�����ж�
			if ((cbCardData[0]==0x4F)&&(cbCardData[1]==0x4E)||(cbCardData[0]==0x4E)&&(cbCardData[1]==0x4F)) return CT_MISSILE_CARD;
			if (getCardLogicValue(cbCardData[0])==getCardLogicValue(cbCardData[1])) return CT_DOUBLE;
            
			return CT_ERROR;
		}
	}
    
	//�����˿�
	tagAnalyseResult AnalyseResult;
	memset(&AnalyseResult,0,sizeof(AnalyseResult));
	analysebCardData(cbCardData,cbCardCount,AnalyseResult);
    
	//�����ж�
	if (AnalyseResult.cbFourCount>0)
	{
		//�����ж�
		if ((AnalyseResult.cbFourCount==1)&&(cbCardCount==4)) return CT_BOMB_CARD;
		if ((AnalyseResult.cbFourCount==1)&&(AnalyseResult.cbSignedCount==2)&&(cbCardCount==6)) return CT_FOUR_LINE_TAKE_ONE;
		if ((AnalyseResult.cbFourCount==1)&&(AnalyseResult.cbDoubleCount==2)&&(cbCardCount==8)) return CT_FOUR_LINE_TAKE_TWO;
        
        //ը����������ϳɷɻ������
		if (AnalyseResult.cbThreeCount==1&&AnalyseResult.cbSignedCount==1&&AnalyseResult.cbFourCount==1&&cbCardCount==8)
		{
			if (getCardLogicValue(AnalyseResult.cbFourCardData[0])-getCardLogicValue(AnalyseResult.cbThreeCardData[0])==1)
                return CT_THREE_LINE_TAKE_ONE;
			if (getCardLogicValue(AnalyseResult.cbThreeCardData[0])-getCardLogicValue(AnalyseResult.cbFourCardData[0])==1)
                return CT_THREE_LINE_TAKE_ONE;
		}
		//ը���������������
		if (AnalyseResult.cbThreeCount==2&&AnalyseResult.cbSignedCount==2&&AnalyseResult.cbFourCount==1&&cbCardCount==12)
		{
			if (getCardLogicValue(AnalyseResult.cbThreeCardData[0])-getCardLogicValue(AnalyseResult.cbThreeCardData[3])==1)
			{
				if (getCardLogicValue(AnalyseResult.cbFourCardData[0])-getCardLogicValue(AnalyseResult.cbThreeCardData[0])==1)
					return CT_THREE_LINE_TAKE_ONE;
				if (getCardLogicValue(AnalyseResult.cbThreeCardData[3])-getCardLogicValue(AnalyseResult.cbFourCardData[0])==1)
					return CT_THREE_LINE_TAKE_ONE;
                
			}
			if ((getCardLogicValue(AnalyseResult.cbThreeCardData[0])-getCardLogicValue(AnalyseResult.cbFourCardData[0])==1)&&
				(getCardLogicValue(AnalyseResult.cbFourCardData[0])-getCardLogicValue(AnalyseResult.cbThreeCardData[3])==1))
				return CT_THREE_LINE_TAKE_ONE;
		}
        
		return CT_ERROR;
	}
    
	//�����ж�
	if (AnalyseResult.cbThreeCount>0)
	{
		//��������
		if(AnalyseResult.cbThreeCount==1 && cbCardCount==3) return CT_THREE ;
        
		//�����ж�
		if (AnalyseResult.cbThreeCount>1)
		{
			//��������
			unsigned char cbCardData=AnalyseResult.cbThreeCardData[0];
			unsigned char cbFirstLogicValue=getCardLogicValue(cbCardData);
            
			//�������
			if (cbFirstLogicValue>=15) return CT_ERROR;
            
			//�����ж�
			for (unsigned char i=1;i<AnalyseResult.cbThreeCount;i++)
			{
				unsigned char cbCardData=AnalyseResult.cbThreeCardData[i*3];
				if (cbFirstLogicValue!=(getCardLogicValue(cbCardData)+i)) return CT_ERROR;
			}
		}
        
		//�����ж�
		if (AnalyseResult.cbThreeCount*3==cbCardCount) return CT_THREE_LINE;
		if (AnalyseResult.cbThreeCount*4==cbCardCount) return CT_THREE_LINE_TAKE_ONE;
		if ((AnalyseResult.cbThreeCount*5==cbCardCount)&&(AnalyseResult.cbDoubleCount==AnalyseResult.cbThreeCount)) return CT_THREE_LINE_TAKE_TWO;
        
		return CT_ERROR;
	}
    
	//��������
	if (AnalyseResult.cbDoubleCount>=3)
	{
		//��������
		unsigned char cbCardData=AnalyseResult.cbDoubleCardData[0];
		unsigned char cbFirstLogicValue=getCardLogicValue(cbCardData);
        
		//�������
		if (cbFirstLogicValue>=15) return CT_ERROR;
        
		//�����ж�
		for (unsigned char i=1;i<AnalyseResult.cbDoubleCount;i++)
		{
			unsigned char cbCardData=AnalyseResult.cbDoubleCardData[i*2];
			if (cbFirstLogicValue!=(getCardLogicValue(cbCardData)+i)) return CT_ERROR;
		}
        
		//�����ж�
		if ((AnalyseResult.cbDoubleCount*2)==cbCardCount) return CT_DOUBLE_LINE;
        
		return CT_ERROR;
	}
    
	//�����ж�
	if ((AnalyseResult.cbSignedCount>=5)&&(AnalyseResult.cbSignedCount==cbCardCount))
	{
		//��������
		unsigned char cbCardData=AnalyseResult.cbSignedCardData[0];
		unsigned char cbFirstLogicValue=getCardLogicValue(cbCardData);
        
		//�������
		if (cbFirstLogicValue>=15) return CT_ERROR;
        
		//�����ж�
		for (unsigned char i=1;i<AnalyseResult.cbSignedCount;i++)
		{
			unsigned char cbCardData=AnalyseResult.cbSignedCardData[i];
			if (cbFirstLogicValue!=(getCardLogicValue(cbCardData)+i)) return CT_ERROR;
		}
        
		return CT_SINGLE_LINE;
	}
	return CT_ERROR;
}

//�Ա��˿�
bool DDZLogic::compareCard(const unsigned char cbFirstCard[], const unsigned char cbNextCard[], unsigned char cbFirstCount, unsigned char cbNextCount)
{
	//��ȡ����
	unsigned char cbNextType=getCardType(cbNextCard,cbNextCount);
	unsigned char cbFirstType=getCardType(cbFirstCard,cbFirstCount);
    
	//�����ж�
	if (cbNextType==CT_ERROR) return false;
	//ASSERT(cbNextType!=CT_ERROR);
	if (cbNextType==CT_MISSILE_CARD) return true;
    
	//ը���ж�
	if ((cbFirstType!=CT_BOMB_CARD)&&(cbNextType==CT_BOMB_CARD)) return true;
	if ((cbFirstType==CT_BOMB_CARD)&&(cbNextType!=CT_BOMB_CARD)) return false;
    
	//�����ж�
	if ((cbFirstType==cbNextType)&&(cbFirstCount!=cbNextCount)) return false;
    if (cbFirstType!=cbNextType) return false;
	//��ʼ�Ա�
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
			//��ȡ��ֵ
			unsigned char cbNextLogicValue=getCardLogicValue(cbNextCard[0]);
			unsigned char cbFirstLogicValue=getCardLogicValue(cbFirstCard[0]);
            
			//�Ա��˿�
			return cbNextLogicValue>cbFirstLogicValue;
		}
        case CT_THREE_LINE_TAKE_ONE:
        case CT_THREE_LINE_TAKE_TWO:
		{
			//�����˿�
			tagAnalyseResult NextResult;
			tagAnalyseResult FirstResult;
			analysebCardData(cbNextCard,cbNextCount,NextResult);
			analysebCardData(cbFirstCard,cbFirstCount,FirstResult);
			
			if (NextResult.cbFourCount>0&&NextResult.cbThreeCount>0)
			{
				if (getCardLogicValue(NextResult.cbFourCardData[0])>getCardLogicValue(NextResult.cbThreeCardData[0]))
                    NextResult.cbThreeCardData[0]= NextResult.cbFourCardData[0];
			}
            
			if (FirstResult.cbFourCount>0&&FirstResult.cbThreeCount>0)
			{
				if (getCardLogicValue(FirstResult.cbFourCardData[0])>getCardLogicValue(FirstResult.cbThreeCardData[0]))
                    FirstResult.cbThreeCardData[0]= FirstResult.cbFourCardData[0];
			}
			////////////////////////////////
            
			//��ȡ��ֵ
			unsigned char cbNextLogicValue=getCardLogicValue(NextResult.cbThreeCardData[0]);
			unsigned char cbFirstLogicValue=getCardLogicValue(FirstResult.cbThreeCardData[0]);
            
			//�Ա��˿�
			return cbNextLogicValue>cbFirstLogicValue;
		}
        case CT_FOUR_LINE_TAKE_ONE:
        case CT_FOUR_LINE_TAKE_TWO:
		{
			//�����˿�
			tagAnalyseResult NextResult;
			tagAnalyseResult FirstResult;
			analysebCardData(cbNextCard,cbNextCount,NextResult);
			analysebCardData(cbFirstCard,cbFirstCount,FirstResult);
            
			//��ȡ��ֵ
			unsigned char cbNextLogicValue=getCardLogicValue(NextResult.cbFourCardData[0]);
			unsigned char cbFirstLogicValue=getCardLogicValue(FirstResult.cbFourCardData[0]);
            
			//�Ա��˿�
			return cbNextLogicValue>cbFirstLogicValue;
		}
	}
    
	return false;
}

unsigned char DDZLogic::getCardCount(unsigned char cbCardData[], unsigned char cbCardCount,unsigned char cbCenterCard)
{
    unsigned char cbCount = 0;
    for (unsigned char i = 0; i < cbCardCount; i++)
    {
        if (getCardValue(cbCardData[i]) == getCardValue(cbCenterCard))
        {
            cbCount++;
        }
    }
    return cbCount;
}
//����ͬ��(�����ƣ�ƥ���ƣ������ƣ�������)
bool DDZLogic::searchSampleCard(unsigned char cbHandCardData[], unsigned char cbHandCardCount,unsigned char cbCardData[], unsigned char cbCardCount,unsigned char cbCard, tagOutCardResult& OutCardResult)
{
    unsigned char cbTempCardData[20];
    unsigned char cbTempCardCount = cbCardCount;
    memset(cbTempCardData, 0, 20);
    
    memcpy(cbCardData,cbCardData, cbHandCardCount);
    
    bool ret = searchOutCard(cbHandCardData,cbHandCardCount,cbCardData,cbCardCount,OutCardResult);
    bool result = false;
    if (ret)
    {
        unsigned char cbValue = getCardValue(cbCard);
        for (int i = 0; i < OutCardResult.cbCardCount; i++)
        {
            if (cbValue == getCardValue(OutCardResult.cbResultCard[i]))
            {
                result = true;
                return true;
            }
        }
        
        //û���ҵ������� �ݹ�����
        if (!result)
        {
            //memcpy(cbTempCardData, OutCardResult.cbResultCard, OutCardResult.cbCardCount);
            //���¸����������������ʵ���
            //memset(OutCardResult.cbResultCard, 0, MAX_COUNT);
            //searchSampleCard(cbHandCardData, cbHandCardCount,cbTempCardData, cbCardCount,cbCard,OutCardResult);
            
            
            unsigned char cbHandCard[20];
            unsigned char cbHandCout = cbHandCardCount;
            memcpy(cbHandCard, cbHandCardData, sizeof(cbHandCard));
            
            removeCard(OutCardResult.cbResultCard, OutCardResult.cbCardCount, cbHandCard, cbHandCardCount);
            cbHandCout -= OutCardResult.cbCardCount;
            
            searchSampleCard(cbHandCard, cbHandCout,OutCardResult.cbResultCard, cbCardCount,cbCard,OutCardResult);
        }
    }
    
    return ret;
}

//��������
bool DDZLogic::searchOutCard(const unsigned char cbHandCardData[], unsigned char cbHandCardCount, const unsigned char cbTurnCardData[], unsigned char cbTurnCardCount, tagOutCardResult& OutCardResult)
{
	//���ý��
	memset(&OutCardResult, 0, sizeof(OutCardResult));
    
	//�����˿�
	unsigned char cbCardData[MAX_COUNT];
	unsigned char cbCardCount=cbHandCardCount;
	memcpy(cbCardData,cbHandCardData,sizeof(unsigned char)*cbHandCardCount);
    
	//�����˿�
	sortCardList(cbCardData,cbCardCount,ST_ORDER);
	//��ȡ����
	unsigned char cbTurnOutType=getCardType(cbTurnCardData,cbTurnCardCount);
    
	//���Ʒ���
	switch (cbTurnOutType)
	{
        case CT_ERROR:					//��������
		{
			return false;
		}
        case CT_SINGLE:					//��������
		{
			//��ȡ��ֵ
			unsigned char cbLogicValue=getCardLogicValue(cbTurnCardData[0]);
			//�����˿�
			tagAnalyseResult AnalyseResult;
			analysebCardData(cbCardData,cbCardCount,AnalyseResult);
			//Ѱ�ҵ���
			for (unsigned char i=0;i<AnalyseResult.cbSignedCount;i++)
			{
				unsigned char cbIndex=AnalyseResult.cbSignedCount-i-1;
				if (getCardLogicValue(AnalyseResult.cbSignedCardData[cbIndex])>cbLogicValue)
				{
					//���ý��
					OutCardResult.cbCardCount=cbTurnCardCount;
					memcpy(OutCardResult.cbResultCard,&AnalyseResult.cbSignedCardData[cbIndex],sizeof(unsigned char)*cbTurnCardCount);
					return true;
				}
			}
			//ȫ������
			for (WORD i=0;i<cbCardCount;i++)
			{
				if (getCardLogicValue(cbCardData[cbCardCount-i-1])>cbLogicValue)
				{
					memcpy(OutCardResult.cbResultCard,&cbCardData[cbCardCount-i-1],sizeof(unsigned char)*cbTurnCardCount);
                    OutCardResult.cbCardCount = cbTurnCardCount;
					return true;
				}
			}
			break;
		}
        case CT_DOUBLE:					//��������
            
		{
			//��ȡ��ֵ
			unsigned char cbLogicValue=getCardLogicValue(cbTurnCardData[0]);
			//�����˿�
			tagAnalyseResult AnalyseResult;
			analysebCardData(cbCardData,cbCardCount,AnalyseResult);
			//Ѱ�Ҷ���
			for (unsigned char i=0;i<AnalyseResult.cbDoubleCount;i++)
			{
				unsigned char cbIndex=(AnalyseResult.cbDoubleCount-i-1)*2;
				if (getCardLogicValue(AnalyseResult.cbDoubleCardData[cbIndex])>cbLogicValue)
				{
					//���ý��
					OutCardResult.cbCardCount=cbTurnCardCount;
					memcpy(OutCardResult.cbResultCard,&AnalyseResult.cbDoubleCardData[cbIndex],sizeof(unsigned char)*cbTurnCardCount);
					return true;
				}
			}
			//������
			for (unsigned char i=0;i<AnalyseResult.cbThreeCount;i++)
			{
				unsigned char cbIndex=(AnalyseResult.cbThreeCount-i-1)*3;
				if (getCardLogicValue(AnalyseResult.cbThreeCardData[cbIndex])>cbLogicValue)
				{
					//���ý��
					OutCardResult.cbCardCount=cbTurnCardCount;
					memcpy(OutCardResult.cbResultCard,&AnalyseResult.cbThreeCardData[cbIndex],sizeof(unsigned char)*cbTurnCardCount);
                    
					return true;
				}
			}
			break;
		}
            
        case CT_THREE:					//��������
		{
			//��ȡ��ֵ
			unsigned char cbLogicValue=getCardLogicValue(cbTurnCardData[0]);
			//�����˿�
			tagAnalyseResult AnalyseResult;
			analysebCardData(cbCardData,cbCardCount,AnalyseResult);
			for (unsigned char i=0;i<AnalyseResult.cbThreeCount;i++)
			{
				unsigned char cbIndex=(AnalyseResult.cbThreeCount-i-1)*3;
				if (getCardLogicValue(AnalyseResult.cbThreeCardData[cbIndex])>cbLogicValue)
				{
					//���ý��
					OutCardResult.cbCardCount=cbTurnCardCount;
					memcpy(OutCardResult.cbResultCard,&AnalyseResult.cbThreeCardData[cbIndex],sizeof(unsigned char)*cbTurnCardCount);
					return true;
				}
			}
			break;
		}
        case CT_SINGLE_LINE:		//��������
		{
			//�����ж�
			if (cbCardCount<cbTurnCardCount) break;
            
			//��ȡ��ֵ
			unsigned char cbLogicValue=getCardLogicValue(cbTurnCardData[0]);
            
			//��������
			for (unsigned char i=(cbTurnCardCount-1);i<cbCardCount;i++)
			{
				//��ȡ��ֵ
				unsigned char cbHandLogicValue=getCardLogicValue(cbCardData[cbCardCount-i-1]);
                
				//�����ж�
				if (cbHandLogicValue>=15) break;
				if (cbHandLogicValue<=cbLogicValue) continue;
                
				//��������
				unsigned char cbLineCount=0;
				for (unsigned char j=(cbCardCount-i-1);j<cbCardCount;j++)
				{
					if ((getCardLogicValue(cbCardData[j])+cbLineCount)==cbHandLogicValue)
					{
						//��������
						OutCardResult.cbResultCard[cbLineCount++]=cbCardData[j];
                        
						//����ж�
						if (cbLineCount==cbTurnCardCount)
						{
							OutCardResult.cbCardCount=cbTurnCardCount;
							return true;
						}
					}
				}
			}
            
			break;
		}
        case CT_DOUBLE_LINE:		//��������
		{
			//�����ж�
			if (cbCardCount<cbTurnCardCount) break;
            
			//��ȡ��ֵ
			unsigned char cbLogicValue=getCardLogicValue(cbTurnCardData[0]);
            
			//��������
			for (unsigned char i=(cbTurnCardCount-1);i<cbCardCount;i++)
			{
				//��ȡ��ֵ
				unsigned char cbHandLogicValue=getCardLogicValue(cbCardData[cbCardCount-i-1]);
                
				//�����ж�
				if (cbHandLogicValue<=cbLogicValue) continue;
				if ((cbTurnCardCount>1)&&(cbHandLogicValue>=15)) break;
                
				//��������
				unsigned char cbLineCount=0;
				for (unsigned char j=(cbCardCount-i-1);j<(cbCardCount-1);j++)
				{
					if (((getCardLogicValue(cbCardData[j])+cbLineCount)==cbHandLogicValue)
						&&((getCardLogicValue(cbCardData[j+1])+cbLineCount)==cbHandLogicValue))
					{
						//��������
						OutCardResult.cbResultCard[cbLineCount*2]=cbCardData[j];
						OutCardResult.cbResultCard[(cbLineCount++)*2+1]=cbCardData[j+1];
                        
						//����ж�
						if (cbLineCount*2==cbTurnCardCount)
						{
							OutCardResult.cbCardCount=cbTurnCardCount;
							return true;
						}
					}
				}
			}
            
			break;
		}
        case CT_THREE_LINE:				//��������
        case CT_THREE_LINE_TAKE_ONE:	//����һ��
        case CT_THREE_LINE_TAKE_TWO:	//����һ��
		{
			//�����ж�
			if (cbCardCount<cbTurnCardCount) break;
            
			//��ȡ��ֵ
			unsigned char cbLogicValue=0;
			for (unsigned char i=0;i<cbTurnCardCount-2;i++)
			{
				cbLogicValue=getCardLogicValue(cbTurnCardData[i]);
				if (getCardLogicValue(cbTurnCardData[i+1])!=cbLogicValue) continue;
				if (getCardLogicValue(cbTurnCardData[i+2])!=cbLogicValue) continue;
				break;
			}
            
			//������ֵ
			unsigned char cbTurnLineCount=0;
			if (cbTurnOutType==CT_THREE_LINE_TAKE_ONE) cbTurnLineCount=cbTurnCardCount/4;
			else if (cbTurnOutType==CT_THREE_LINE_TAKE_TWO) cbTurnLineCount=cbTurnCardCount/5;
			else cbTurnLineCount=cbTurnCardCount/3;
            
			//��������
			for (unsigned char i=cbTurnLineCount*3-1;i<cbCardCount;i++)
			{
				//��ȡ��ֵ
				unsigned char cbHandLogicValue=getCardLogicValue(cbCardData[cbCardCount-i-1]);
                
				//�����ж�
				if (cbHandLogicValue<=cbLogicValue) continue;
				if ((cbTurnLineCount>1)&&(cbHandLogicValue>=15)) break;
                
				//��������
				unsigned char cbLineCount=0;
				for (unsigned char j=(cbCardCount-i-1);j<(cbCardCount-2);j++)
				{
					//���ñ���
					OutCardResult.cbCardCount=0;
                    
					//�����ж�
					if ((getCardLogicValue(cbCardData[j])+cbLineCount)!=cbHandLogicValue) continue;
					if ((getCardLogicValue(cbCardData[j+1])+cbLineCount)!=cbHandLogicValue) continue;
					if ((getCardLogicValue(cbCardData[j+2])+cbLineCount)!=cbHandLogicValue) continue;
                    
					//��������
					OutCardResult.cbResultCard[cbLineCount*3]=cbCardData[j];
					OutCardResult.cbResultCard[cbLineCount*3+1]=cbCardData[j+1];
					OutCardResult.cbResultCard[(cbLineCount++)*3+2]=cbCardData[j+2];
                    
					//����ж�
					if (cbLineCount==cbTurnLineCount)
					{
						//��������
						OutCardResult.cbCardCount=cbLineCount*3;
                        
						//�����˿�
						unsigned char cbLeftCardData[MAX_COUNT];
						unsigned char cbLeftCount=cbCardCount-OutCardResult.cbCardCount;
						memcpy(cbLeftCardData,cbCardData,sizeof(unsigned char)*cbCardCount);
						removeCard(OutCardResult.cbResultCard,OutCardResult.cbCardCount,cbLeftCardData,cbCardCount);
                        
						//�����˿�
						tagAnalyseResult AnalyseResultLeft;
						analysebCardData(cbLeftCardData,cbLeftCount,AnalyseResultLeft);
                        
						//���ƴ���
						if (cbTurnOutType==CT_THREE_LINE_TAKE_ONE)
						{
							//��ȡ����
							for (unsigned char k=0;k<AnalyseResultLeft.cbSignedCount;k++)
							{
								//��ֹ�ж�
								if (OutCardResult.cbCardCount==cbTurnCardCount) break;
                                
								//�����˿�
								unsigned char cbIndex=AnalyseResultLeft.cbSignedCount-k-1;
								unsigned char cbSignedCard=AnalyseResultLeft.cbSignedCardData[cbIndex];
								OutCardResult.cbResultCard[OutCardResult.cbCardCount++]=cbSignedCard;
							}
                            
							//��ȡ����
							for (unsigned char k=0;k<AnalyseResultLeft.cbDoubleCount*2;k++)
							{
								//��ֹ�ж�
								if (OutCardResult.cbCardCount==cbTurnCardCount) break;
                                
								//�����˿�
								unsigned char cbIndex=(AnalyseResultLeft.cbDoubleCount*2-k-1);
								unsigned char cbSignedCard=AnalyseResultLeft.cbDoubleCardData[cbIndex];
								OutCardResult.cbResultCard[OutCardResult.cbCardCount++]=cbSignedCard;
							}
                            
							//��ȡ����
							for (unsigned char k=0;k<AnalyseResultLeft.cbThreeCount*3;k++)
							{
								//��ֹ�ж�
								if (OutCardResult.cbCardCount==cbTurnCardCount) break;
                                
								//�����˿�
								unsigned char cbIndex=(AnalyseResultLeft.cbThreeCount*3-k-1);
								unsigned char cbSignedCard=AnalyseResultLeft.cbThreeCardData[cbIndex];
								OutCardResult.cbResultCard[OutCardResult.cbCardCount++]=cbSignedCard;
							}
                            
							//��ȡ����
							//for (unsigned char k=0;k<AnalyseResultLeft.cbFourCount*4;k++)
							//{
							//	//��ֹ�ж�
							//	if (OutCardResult.cbCardCount==cbTurnCardCount) break;
                            
							//	//�����˿�
							//	unsigned char cbIndex=(AnalyseResultLeft.cbFourCount*4-k-1);
							//	unsigned char cbSignedCard=AnalyseResultLeft.cbFourCardData[cbIndex];
							//	OutCardResult.cbResultCard[OutCardResult.cbCardCount++]=cbSignedCard;
							//}
						}
                        
						//���ƴ���
						if (cbTurnOutType==CT_THREE_LINE_TAKE_TWO)
						{
							//��ȡ����
							for (unsigned char k=0;k<AnalyseResultLeft.cbDoubleCount;k++)
							{
								//��ֹ�ж�
								if (OutCardResult.cbCardCount==cbTurnCardCount) break;
                                
								//�����˿�
								unsigned char cbIndex=(AnalyseResultLeft.cbDoubleCount-k-1)*2;
								unsigned char cbCardData1=AnalyseResultLeft.cbDoubleCardData[cbIndex];
								unsigned char cbCardData2=AnalyseResultLeft.cbDoubleCardData[cbIndex+1];
								OutCardResult.cbResultCard[OutCardResult.cbCardCount++]=cbCardData1;
								OutCardResult.cbResultCard[OutCardResult.cbCardCount++]=cbCardData2;
							}
                            
							//��ȡ����
							for (unsigned char k=0;k<AnalyseResultLeft.cbThreeCount;k++)
							{
								//��ֹ�ж�
								if (OutCardResult.cbCardCount==cbTurnCardCount) break;
                                
								//�����˿�
								unsigned char cbIndex=(AnalyseResultLeft.cbThreeCount-k-1)*3;
								unsigned char cbCardData1=AnalyseResultLeft.cbThreeCardData[cbIndex];
								unsigned char cbCardData2=AnalyseResultLeft.cbThreeCardData[cbIndex+1];
								OutCardResult.cbResultCard[OutCardResult.cbCardCount++]=cbCardData1;
								OutCardResult.cbResultCard[OutCardResult.cbCardCount++]=cbCardData2;
							}
                            
							//��ȡ����
							for (unsigned char k=0;k<AnalyseResultLeft.cbFourCount;k++)
							{
								//��ֹ�ж�
								if (OutCardResult.cbCardCount==cbTurnCardCount) break;
                                
								//�����˿�
								unsigned char cbIndex=(AnalyseResultLeft.cbFourCount-k-1)*4;
								unsigned char cbCardData1=AnalyseResultLeft.cbFourCardData[cbIndex];
								unsigned char cbCardData2=AnalyseResultLeft.cbFourCardData[cbIndex+1];
								OutCardResult.cbResultCard[OutCardResult.cbCardCount++]=cbCardData1;
								OutCardResult.cbResultCard[OutCardResult.cbCardCount++]=cbCardData2;
							}
						}
                        
						//����ж�
						if (OutCardResult.cbCardCount==cbTurnCardCount) return true;
					}
				}
			}
            
			break;
		}
	}
	//����ը��
	if ((cbCardCount>=4)&&(cbTurnOutType!=CT_MISSILE_CARD))
	{
		//��������
		unsigned char cbLogicValue=0;
		if (cbTurnOutType==CT_BOMB_CARD) cbLogicValue=getCardLogicValue(cbTurnCardData[0]);
        
		//����ը��
		for (unsigned char i=3;i<cbCardCount;i++)
		{
			//��ȡ��ֵ
			unsigned char cbHandLogicValue=getCardLogicValue(cbCardData[cbCardCount-i-1]);
            
			//�����ж�
			if (cbHandLogicValue<=cbLogicValue) continue;
            
			//ը���ж�
			unsigned char cbTempLogicValue=getCardLogicValue(cbCardData[cbCardCount-i-1]);
            
            unsigned char j = 1;
			for ( ; j<4; j++)
			{
				if (getCardLogicValue(cbCardData[cbCardCount+j-i-1])!=cbTempLogicValue) break;
			}
			if (j!=4) continue;
            
			//���ý��
			OutCardResult.cbCardCount=4;
			OutCardResult.cbResultCard[0]=cbCardData[cbCardCount-i-1];
			OutCardResult.cbResultCard[1]=cbCardData[cbCardCount-i];
			OutCardResult.cbResultCard[2]=cbCardData[cbCardCount-i+1];
			OutCardResult.cbResultCard[3]=cbCardData[cbCardCount-i+2];
            
			return true;
		}
	}
    
	//�������
	if ((cbCardCount>=2)&&(cbCardData[0]==0x4F)&&(cbCardData[1]==0x4E))
	{
		//���ý��
		OutCardResult.cbCardCount=2;
		OutCardResult.cbResultCard[0]=cbCardData[0];
		OutCardResult.cbResultCard[1]=cbCardData[1];
        
		return true;
	}
    
	return false;
}
//���������
LONG DDZLogic::getMaxScore(const LONG bGameScore[])
{
    
	LONG ReMaxScore = 0;
	ReMaxScore = (bGameScore[0]>bGameScore[1])?bGameScore[0]:bGameScore[1];
	ReMaxScore = (bGameScore[2]>ReMaxScore)?bGameScore[2]:ReMaxScore;
	return ReMaxScore;
}

//�Ƿ�������
bool DDZLogic::islinkCard(unsigned char cbCardData[], unsigned char cbCardCount,tagOutCardResult& OutCardResult)
{
    memset(&OutCardResult.cbResultCard, 0 , sizeof(OutCardResult.cbResultCard));
    OutCardResult.cbCardCount= 0;
    
    unsigned char cbCard = getCardLogicValue(cbCardData[0]);
    int j = 0;
    for (int i = 0; i < cbCardCount; i++)
    {
        unsigned char cbRetCard = isHasCardData(cbCard, cbCardData, cbCardCount);
        if (cbRetCard > 0&& cbCard<15)//&& cbCard<15 xiaohua
        {
            OutCardResult.cbResultCard[j] = cbRetCard;
            OutCardResult.cbCardCount++;
            
            j++;
            cbCard--;
        }else
        {
            break;
        }
    }

    if (OutCardResult.cbCardCount >= 5)
    {
        return  true;
    }
    return false;
}

//�Ƿ���˫��
bool DDZLogic::isDoublelinkCard(unsigned char cbCardData[], unsigned char cbCardCount,tagAnalyseResult& AnalyseResult)
{
    memset(&AnalyseResult, 0, sizeof(AnalyseResult));
    analysebCardData(cbCardData,cbCardCount,AnalyseResult,true);
    
    for (int i = 0; i < AnalyseResult.cbDoubleCount * 2; i++)
    {
        CCLOG("%d",AnalyseResult.cbDoubleCardData[i]);
    }
    if (AnalyseResult.cbDoubleCount >= 3 )
    {

        bool bRet = false;
        int nLink = 0;
        for (int i = 0; i < AnalyseResult.cbDoubleCount; i++)
        {
            unsigned char cbFirstCardData = getCardLogicValue(AnalyseResult.cbDoubleCardData[i*2]);
            unsigned char cbSecondCardData = getCardLogicValue(AnalyseResult.cbDoubleCardData[i*2+2]);
			if(cbFirstCardData>=15)break; //xiaohua
            if (cbFirstCardData == cbSecondCardData + 1)
            {
                AnalyseResult.cbDoubleCardData[nLink*2] =
                AnalyseResult.cbDoubleCardData[i*2];
                AnalyseResult.cbDoubleCardData[nLink*2+1] =
                AnalyseResult.cbDoubleCardData[i*2+1];
                nLink++;
            }else
            {
                //��������
                if (nLink >= 2)
                {
                    AnalyseResult.cbDoubleCardData[nLink*2] =
                    AnalyseResult.cbDoubleCardData[i*2];
                    AnalyseResult.cbDoubleCardData[nLink*2+1] =
                    AnalyseResult.cbDoubleCardData[i*2+1];
                    
                    AnalyseResult.cbDoubleCount = nLink + 1;
                    bRet = true;
                }else
                {
                  nLink = 0;
                }
            }
        }
        return bRet;
    }
    
    return false;
}

//�Ƿ�ӵ��������
unsigned char DDZLogic::isHasCardData(unsigned char cbCenterCardData,unsigned char cbCardData[], unsigned char cbCardCount)
{
    for (int i = 0; i < cbCardCount; i++)
    {
        //CCLOG("%d",cbCardData[i]);
        if (cbCenterCardData == getCardLogicValue(cbCardData[i]))
        {
            return cbCardData[i];
        }
    }
    return  0;
}

unsigned char DDZLogic::getBackbeiLv( unsigned char* _data,unsigned char _num )
{
	sortCardList(_data,_num,ST_ORDER);
	WORD _unmBeilv=1;
	do 
	{
		//--��ը
		if ((_data[0]==0x4F)&&(_data[1]==0x4E))
		{
			_unmBeilv *=4;break;
		}

		//--������
		if(_data[0]==0x4F || _data[0]==0x4E )
		{
			_unmBeilv *=2;break;
		}

		//--����
		if(_data[0]==_data[1] &&  _data[1]==_data[2] )
		{
			_unmBeilv *=6;break;
		}

		//--ͬ��
		BYTE type =getCardColor(_data[0]);
		if (type==getCardColor(_data[1]) && type==getCardColor(_data[2]))
		{
			_unmBeilv*=3;
		}

		//--˳��
		BYTE cbFirstLogicValue=getCardLogicValue(_data[0]);
		if(cbFirstLogicValue<=14)
		{
			for (int i=0;i<_num;i++)
			{
				if (cbFirstLogicValue!=(getCardLogicValue(_data[i])+i))
					break;
				else if (i==(_num-1)){
					_unmBeilv*=3;
				}
			}
		}

	} while (0);
	return _unmBeilv;
}

unsigned char DDZLogic::getLastTask( unsigned char* _data,unsigned char _num,unsigned char _key )
{
	WORD type=getCardType(_data,_num);
	if (type == _key)
	{
		switch(_key)
		{
		case CT_SINGLE:
			return 2;
		case CT_DOUBLE:
			return 2;
		case CT_SINGLE_LINE:
			return 3;
		case CT_DOUBLE_LINE:
			return 3;
		case	CT_THREE_LINE:
			return 3;
		case CT_THREE_LINE_TAKE_ONE:
			return 3;
		case CT_THREE_LINE_TAKE_TWO:
			return 3;
		case CT_BOMB_CARD:
			return 4;
		case CT_MISSILE_CARD:
			return 5;
		}
	}
	return 1;
}

bool DDZLogic::isWangZha(unsigned char cbCardData[], unsigned char cbCardCount)
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
