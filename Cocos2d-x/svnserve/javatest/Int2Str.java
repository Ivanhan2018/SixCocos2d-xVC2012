/** *//**
 * 文件名：Int2Str.java
 */

public class Int2Str{
    
    //1,粮食;2,木材;3,铁;4,皮 5,黄宝石,6,红宝石,7,绿宝石,8,黑铁
    public static int GetResourceSaleIDFromResName(String strRes)
   {
	if(strRes.equals("粮食"))
		return 1;
	if(strRes.equals("木材"))
		return 2;
	if(strRes.equals("铁"))
		return 3;
	if(strRes.equals("皮"))
		return 4;
	if(strRes.equals("黄宝石"))
		return 5;
	if(strRes.equals("红宝石"))
		return 6;
	if(strRes.equals("绿宝石"))
                return 7;
	if(strRes.equals("黑铁"))
		return 8;

	return 0;
    }

    //通过职业ID获取英雄职业
    public static String GetHeroOccupationByOccupationID(int nOccupationID)
    {
	String strOccupation;
	switch(nOccupationID)
	{
	case 1:
		strOccupation ="圣骑士";
		break;
	case 2:
		strOccupation ="战士";
		break;
	case 3:
		strOccupation ="弓箭手";
		break;
	case 4:
		strOccupation ="法师";
		break;
	case 5:
		strOccupation="牧师";
		break;
	default :
		strOccupation ="未知";
	}
	return strOccupation;
    }

    public static void main(String[] args)
    {
        String Str = "黄宝石";
        int id = Int2Str.GetResourceSaleIDFromResName(Str);
        System.out.println("黄宝石 的整数形式为：" + id);

        int nOccupationID=2;
        System.out.println("整数" + nOccupationID + "转化成字符串："+ Int2Str.GetHeroOccupationByOccupationID(nOccupationID));
    }
}