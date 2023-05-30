import java.util.*;
import static net.mindview.util.Print.*;

//自定义两个异常类
class MyException1 extends Exception{
	public void f()throws MyException1
	{
		throw new MyException1();
	}
};
class MyException2 extends MyException1{
	public void f()throws MyException2
	{
		throw new MyException2();
	}
};
class MyException3 extends MyException2{
	public void f()throws MyException3
	{
		throw new MyException3();
	}
};
public class Test {
	public static void main(String[] args)
	{
		MyException1 e=new MyException3();
		try {
			e.f();
		}catch(MyException3 a) {//先catch派生类的异常，防止被覆盖
			print("MyException3.f().");
		}catch(MyException2 a) {//先catch派生类的异常，防止被覆盖
			print("MyException2.f().");
		}catch(MyException1 a) {//最后catch基类异常
			print("MyException1.f().");
		}
		
	}
}
