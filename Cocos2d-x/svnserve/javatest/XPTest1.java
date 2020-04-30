import java.math.BigDecimal;
public class XPTest1 {


public static void main(String[] args) {
double x = Math.log(5);
System.out.println(x);//1.6094379124341003
double x1 = Math.log10(5);
System.out.println(x1);//0.6989700043360189
System.out.println(3/2);//1
float float_a = 0.05f;
float float_b = 0.01f;
System.out.println(float_a+float_b);//0.060000002
double double_a = 0.05d;
double double_b = 0.01d;
System.out.println(double_a+double_b);//0.060000000000000005
BigDecimal bigDecimal_a1 = new BigDecimal(float_a+"");
BigDecimal bigDecimal_b1 = new BigDecimal(float_b+"");
System.out.println(bigDecimal_a1.add(bigDecimal_b1));//0.06
BigDecimal bigDecimal_a2 = new BigDecimal(double_a+"");
BigDecimal bigDecimal_b2 = new BigDecimal(double_b+"");
System.out.println(bigDecimal_a2.add(bigDecimal_b2));//0.06
}
}
