class A
{
public void Func1(){ System.out.println("This is Func1 ");}
public void Func2(){ System.out.println("This is Func2 ");}
}

class B extends A
{
public void Func3(){ System.out.println("This is Func3 ");}
public void Func4(){ System.out.println("This is Func4 ");}
}


public class inheritanceAB
{
public static void main(String[] args){
 B b=new B();
 b.Func1();
 b.Func2(); 
 b.Func3();
 b.Func4();   
}        
}