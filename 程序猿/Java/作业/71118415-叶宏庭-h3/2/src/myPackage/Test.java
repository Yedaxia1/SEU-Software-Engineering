package myPackage;
import pack1.*;

public class Test {
	public static void main(String[] args)
	{
		testClass a = new testClass();
		//a.f()  Error!! access limited!!!
		testClass2 c = new testClass2();  
	}
}
