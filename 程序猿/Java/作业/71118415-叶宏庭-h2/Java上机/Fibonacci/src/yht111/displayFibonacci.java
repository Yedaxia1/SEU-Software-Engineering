package yht111;


class Fibonacci{
	private int num1=1;
	private int num2=1;
	public void getFibonacciNum(int sub)
	{
		System.out.print(num1+","+num2+",");
		for(int i=2;i<sub;i++)
		{
			int temp=num2;
			num2=num1+num2;
			num1=temp;
			System.out.print(num2+",");
		}
		System.out.println();
		num1=1;
		num2=1;
	}
}

public class displayFibonacci {
	public static void main(String[] args)
	{
		Fibonacci f1=new Fibonacci();
		f1.getFibonacciNum(10);
		f1.getFibonacciNum(15);
	}
}
