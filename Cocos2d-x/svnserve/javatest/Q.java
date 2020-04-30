import java.math.BigDecimal;

public class Q {

/*
* 加法运算
*/
public static String jia(double d1,double d2){
BigDecimal b1 = new BigDecimal(d1+"");
BigDecimal b2 = new BigDecimal(d2+"");
return b1.add(b2).toPlainString();
}


/*
* 减法运算
*/
public static String jian(double d1,double d2){
BigDecimal b1 = new BigDecimal(d1+"");
BigDecimal b2 = new BigDecimal(d2+"");
return b1.subtract(b2).toPlainString();
}
/*
* 乘法运算
*/
public static String cheng(double d1,double d2){
BigDecimal b1 = new BigDecimal(d1+"");
BigDecimal b2 = new BigDecimal(d2+"");
return b1.multiply(b2).toPlainString();
}
/*
* 除法运算
*/
public static String chu(double d1,double d2,int point){
BigDecimal b1 = new BigDecimal(d1+"");
BigDecimal b2 = new BigDecimal(d2+"");
return b1.divide(b2,point,BigDecimal.ROUND_HALF_UP).toPlainString();
}
public static void main(String[] args) {
double double_a = 0.05d;
double double_b = 0.01d;
System.out.println(Q.jia(double_a, double_b));//0.06
System.out.println(Q.jian(double_a, double_b));//0.04
System.out.println(Q.cheng(double_a, double_b));//0.0005
System.out.println(Q.chu(double_a, double_b,0));//5
}
}