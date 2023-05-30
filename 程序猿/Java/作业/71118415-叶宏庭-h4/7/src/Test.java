

class Outer{
	Inner Get_InnerObject(int i){return new Inner(i);}
	class Inner{
		Inner(int i){value=i;}
		private int value;
		void print(){System.out.println("value = "+value);}
	}
}

public class Test {
	public static void main(String[] args)
	{
		Outer o1=new Outer();
		Outer.Inner i1=o1.new Inner(5);
		Outer.Inner i2=o1.Get_InnerObject(10);
		i1.print();
		i2.print();
	}
}
