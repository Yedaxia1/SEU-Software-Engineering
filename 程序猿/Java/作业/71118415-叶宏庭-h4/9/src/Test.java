

class Outer{
	Outer(int i){Outer_value=i;}
	private int Outer_value;
	private void print()
	{	
		System.out.println("Outer_print is called."
			+ " Outer_value = "+Outer_value);
		//can't access to the inner class's field!!!
		//System.out.printllln("Inner_value = "+Inner_value);}
	}
	class Inner{
		private int Inner_value=6;
		void modify()
		{
			Outer_value++;
			print();
		}
	}
	void f()
	{
		print();
		Inner I1=new Inner();
		I1.modify();
		//inner class's private field, Accessed by object of inner class!!!
		System.out.println("I1's Inner_value = "+I1.Inner_value);
	}
}

public class Test {
	public static void main(String[] args)
	{
		Outer o1=new Outer(5);
		o1.f();
	}
}
