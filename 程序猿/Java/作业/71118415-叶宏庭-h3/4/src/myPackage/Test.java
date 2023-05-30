package myPackage;

class A{
	A(int i){System.out.println("a constructor is called!!"+i);}
}
class B{
	B(int i){System.out.println("b constructor is called!!"+i);}
}
class C{
	C(int i){System.out.println("c constructor is called!!"+i);}
}

class Root{
	A m1=new A(1);
	B m2=new B(1);
	C m3=new C(1);
	Root(){System.out.println("Root constructor is called!!");}
}

class Stem extends Root{
	A m4=new A(2);
	B m5=new B(2);
	C m6=new C(2);
	Stem(){System.out.println("Stem constructor is called!!");}
}

public class Test {
	public static void main(String[] args)
	{
		Stem s1=new Stem();
	}
}
