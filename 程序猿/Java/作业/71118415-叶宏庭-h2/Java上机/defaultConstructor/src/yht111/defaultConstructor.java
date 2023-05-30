package yht111;


class defaultTest{
	defaultTest()
	{
		System.out.println("Defalut constructor called.");
	}
	defaultTest(String str)
	{
		System.out.println("Constructor called."+str);
	}
	
}

public class defaultConstructor {
	public static void main(String[] args)
	{
		defaultTest t1=new defaultTest();
		defaultTest t2=new defaultTest("JAVA HOMEWORK");
	}
}
