
abstract class Base{
	Base()
	{
		System.out.println("In the base class.");
		print();
	}
	abstract void print();
}

class Derived extends Base{
	int value=1;
	void print()
	{
		System.out.println("In the derived class.");
		System.out.println(value);
	}
}


public class Test {
	public static void main(String[] args)
	{
		Derived a=new Derived();
		System.out.println("In the main method, call a.print()");
		a.print();
	}
}
/*
 * 创造Derived的对象a时，先调用Base类的constructor，在constructor中调用了print()
 * print()是abstract method，所以调用了Derived的print(),输出value的值，
 * 但由于还未初始化Derived class，所以默认值为0
 * 再在main()中调用a.print(),此时对象已经初始化完毕，所以输出value的值为1
 */
