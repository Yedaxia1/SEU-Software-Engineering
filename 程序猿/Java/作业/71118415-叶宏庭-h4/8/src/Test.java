

class Outer{
	Outer(int i){Outer_value=i;}
	private int Outer_value;
	private void print(){System.out.println("Outer_print is called."
			+ " Outer_value = "+Outer_value);}
	class Inner{
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
	}
}

public class Test {
	public static void main(String[] args)
	{
		Outer o1=new Outer(5);
		o1.f();
	}
}
