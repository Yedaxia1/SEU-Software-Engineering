
interface A {
	void print1();
}

interface B extends A {
	void print2();
}

interface C extends A {
	void print3();
}

interface D extends B,C {
	void print4();
}

class E implements D{
	public void print1()
	{
		System.out.println("Print1() in E.");
	}
	public void print2()
	{
		System.out.println("Print2() in E.");
	}
	public void print3()
	{
		System.out.println("Print3() in E.");
	}
	public void print4()
	{
		System.out.println("Print4() in E.");
	}
}

public class Test {
	public static void main(String[] args)
	{
		D myI=new E();
		myI.print1();
		myI.print2();
		myI.print3();
		myI.print4();
	}
}
