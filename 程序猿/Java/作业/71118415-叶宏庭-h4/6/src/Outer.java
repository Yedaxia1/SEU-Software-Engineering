
public class Outer {
	Inner Get_InnerObject(int i){return new Inner(i);}
	class Inner{
		Inner(int i){value=i;}
		private int value;
		void print(){System.out.println("value = "+value);}
	}
	public static void main(String[] args)
	{
		Outer o1=new Outer();
		Inner I1=o1.Get_InnerObject(10);
		I1.print();
		
	}
}
