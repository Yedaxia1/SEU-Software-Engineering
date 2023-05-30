package myPackage;

class Amphibian{
	void f(){
		System.out.println("f() is called!!");
	}
	void g(){
		System.out.println("g() is called!!");
	}
}

class Frog extends Amphibian{
}

public class Test {
	public static void main(String[] args)
	{
		Amphibian a= new Frog();
		a.f();
		a.g();
	}
}
