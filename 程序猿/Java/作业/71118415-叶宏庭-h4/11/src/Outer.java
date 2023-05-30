
interface I1{
	void Print();
}

public class Outer {
	I1 f()
	{
		return new I1(){
			public void Print()
			{
				System.out.println("Print called in anonymous inner class.");
			}
		};
	}
	public static void main(String[] args)
	{
		Outer o1=new Outer();
		I1 i=o1.f();
		i.Print();
	}
}
