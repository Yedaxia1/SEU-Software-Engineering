import pack2.*;

class A implements MyInterface{
	public void print1()
	{
		System.out.println("Print1.");
	}
	public void print2()
	{
		System.out.println("Print2.");
	}
	public void print3()
	{
		System.out.println("Print3.");
	}
}

public class Test {
	public static void main(String[] args)
	{
		MyInterface i=new A();
		i.print1();
		i.print2();
		i.print3();
	}
}
