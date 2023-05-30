package myPackage;

class Base{
	void f(int i){
		System.out.println("f(int) is called!!");
	}
	void f(String i){
		System.out.println("f(String) is called!!");
	}
	void f(double i){
		System.out.println("f(double) is called!!");
	}
}

class Derive extends Base{
	void f(Boolean i){
		System.out.println("f(Boolean) is called!!");
	}
}

public class Test {
	public static void main(String[] args)
	{
		Derive a=new Derive();
		a.f(1);
		a.f("1");
		a.f(1.0);
		a.f(true);
	}
}
