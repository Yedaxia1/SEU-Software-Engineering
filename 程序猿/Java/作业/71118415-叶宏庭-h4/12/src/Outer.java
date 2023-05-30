
public class Outer {
	protected static class Inner{
		void Print()
		{
			System.out.println("Nested class print is called.");
		}
	}
	public static void main(String[] args)
	{
		//Nested class can be instanced by Outer class
		Outer.Inner i1=new Outer.Inner();
		i1.Print();
		
		Outer o1=new Outer();
		//Nested class can not be instanced by Object of Outer class
		//o1.Ineer i1=new o1.Inner();  Error!!!
	}
}
