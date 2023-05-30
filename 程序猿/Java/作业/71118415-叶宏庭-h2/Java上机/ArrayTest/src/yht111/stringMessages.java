package yht111;
import java.util.*;

class Test{
	Test(String str)
	{
		System.out.println("Constructor(String) is called. argument= "+str);
	}
}

public class stringMessages {
	public static void main(String[] args)
	{
		Test []t1;
		Random r=new Random(20);
		t1 = new Test[r.nextInt(10)];
		
	}
}
