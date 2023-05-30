package yht111;


class Dog{
	private String name;
	Dog()
	{
		name=null;
	}
	Dog(String str)
	{
		name=str;
	}
	void bark()
	{
		System.out.println(name+":bark called by null argument");
	}
	void bark(int a)
	{
		System.out.println(name+":bark called by int argument. argument="+a);
	}
	void bark(String str)
	{
		System.out.println(name+":bark called by String argument. argument="+str);
	}
	void bark(float f)
	{
		System.out.println(name+":bark called by float argument. argument="+f);
	}
	void bark(double d)
	{
		System.out.println(name+":bark called by double argument. argument="+d);
	}
	void bark(int a,double d)
	{
		System.out.println(name+":bark called by two arguments(int and double)."
				+ " arguments:"+a+" and "+d);
	}
	void bark(double d,int a)
	{
		System.out.println(name+":bark called by two arguments(double and int)."
				+ " arguments:"+d+" and "+a);
	}
}

public class DogBark {
	public static void main(String[] args)
	{
		Dog d1=new Dog("Spot");
		d1.bark();
		d1.bark(5);
		d1.bark("wawawa");
		d1.bark(1.12f);
		d1.bark(1.23d);
		
		d1.bark(1, 1.21d);
		d1.bark(1.21d, 2);
	}
}
