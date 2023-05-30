package myPackage;

class A{
	static final int n1=0;
	final int n2;
	A(int i)
	{
		n2=i;
	}
	void f()
	{
		System.out.println("n1="+n1+"; n2="+n2);
	}
}


public class Test {
	public static void main(String[] args)
	{
		A a1=new A(1);
		A a2=new A(2);
		a1.f();
		a2.f();//static 是同一块数据，所有对象共用，非static数据，每一个对象都有一块地址
	}
}
