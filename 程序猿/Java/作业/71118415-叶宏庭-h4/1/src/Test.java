
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
 * ����Derived�Ķ���aʱ���ȵ���Base���constructor����constructor�е�����print()
 * print()��abstract method�����Ե�����Derived��print(),���value��ֵ��
 * �����ڻ�δ��ʼ��Derived class������Ĭ��ֵΪ0
 * ����main()�е���a.print(),��ʱ�����Ѿ���ʼ����ϣ��������value��ֵΪ1
 */
