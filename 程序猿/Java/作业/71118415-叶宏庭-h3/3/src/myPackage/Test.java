package myPackage;
import pack1.*;

public class Test {
	public static void main(String[] args)
	{
		//in the same package testing
		testClass2 a=new testClass2();
		System.out.println(a.a1);//public data
		System.out.println(a.a2);//protected data
		//System.out.println(a.a3);  Access limited!! private data
		System.out.println(a.a4);//package access data
		a.f1();//public method
		a.f2();//protected method
		//a.f3();   Access limited!! private method
		a.f4();//package access method
		
		//in the different package
		testClass b=new testClass();
		System.out.println(b.a1);//public data
		//System.out.println(b.a2); Access limited!! protected data
		//System.out.println(b.a3); Access limited!! private data
		//System.out.println(b.a4); Access limited!! package access data
		b.f1();//public method
		//b.f2(); Access limited!! protected method
		//b.f3(); Access limited!! private method
		//b.f4(); Access limited!! package access method
	}
}
