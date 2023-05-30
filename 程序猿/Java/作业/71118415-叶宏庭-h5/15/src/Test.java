import java.util.*;
import static net.mindview.util.Print.*;

//自定义两个异常类
class MyException1 extends Exception{
	MyException1() throws MyException1
	{
		throw this;
	}
};
class MyException2 extends MyException1{
	/*
	 * 派生类构造前会先调用基类构造函数，此时还未进入派生类构造函数，所以catch无法捕捉基类构造函数抛出的异常
	 * 因此，编译无法通过
	 */
	MyException2()
	{
		try {
			new MyException1();
		}catch(MyException1 e){
			print("catched MyException1's object!!");
		}
	}
};

public class Test {
	public static void main(String[] args)
	{
		MyException2 e=new MyException2();
	}
}
