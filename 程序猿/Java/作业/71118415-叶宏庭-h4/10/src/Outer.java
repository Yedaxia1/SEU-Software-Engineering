
interface I1{
	void Print();
}

public class Outer {
	I1 f()
	{
		class Method_InnerClass implements I1{
			public void Print()
			{
				System.out.println("Print in Method_InnerClass.");
			}
		}
		return new Method_InnerClass();
	}
	public static void main(String[] args)
	{
		Outer o1=new Outer();
		I1 i=o1.f();
		i.Print();
	}
}
