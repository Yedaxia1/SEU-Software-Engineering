package myPackage;

class A{
	static int n1=g();
	int n2=f();
	A(){System.out.println("A constructor is called!!");}
	int f()
	{
		System.out.println("n2 initialization!");
		return 1;
	}
	static int g()
	{
		System.out.println("class A loading by g()");
		return 1;
	}
}

class B extends A{
	static int n3=g1();
	int n4=f1();
	B(){System.out.println("B constructor is called!!");}
	int f1()
	{
		System.out.println("n3 initialization!");
		return 1;
	}
	static int g1()
	{
		System.out.println("class B loading by g1()");
		return 1;
	}
}

public class Test {
	public static void main(String[] args)
	{
		B b= new B();
	}
}
