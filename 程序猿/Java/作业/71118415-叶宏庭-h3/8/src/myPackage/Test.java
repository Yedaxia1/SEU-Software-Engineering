package myPackage;

class A{
	final void f()
	{
		
	}
}

class B extends A{
	void f()//Cannot override the final method from A,final �������ɱ�override
	{
		
	}
}

public class Test {
	public static void main(String[] args)
	{
	}
}
