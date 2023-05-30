import pack1.*;
import pack2.*;


public class Test {
	public static void main(String[]args)
	{
		TestClass a=new TestClass();//Error!! TestClass类名冲突，pack1和pack2中都有该类
	}
}
