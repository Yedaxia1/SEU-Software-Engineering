package yht111;


class Test{
	Test()
	{
		this(2);
		System.out.println("default constructor is called.");
	}
	Test(int a)
	{
		System.out.println("Constructor(int) is called.");
	}
	void f1()
	{
		System.out.println("f1 is called");
		f2();
		this.f2();
	}
	void f2()
	{
		System.out.println("f2 is called");
	}
}

public class thisTest {
	public static void main(String[] args)
	{
		Test t1=new Test();
		t1.f1();
	}
}
