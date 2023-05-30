import java.util.*;
import static net.mindview.util.Print.*;

//自定义两个异常类
class MyException1 extends Exception{
	MyException1(String a){super(a);}
};
class MyException2 extends Exception{
	MyException2(String a){super(a);}
};


class MyExceptions extends Exception{
	public void f() throws MyException2//f（）抛出MyException2类型异常
	{
		try {
			g();//调用g()
		}catch(Exception a)//catch g()抛出的异常
		{
			print(a.getMessage()+"catched in MyExceptions.f()!");//打印异常信息
			throw new MyException2("MyException2!");//抛出MyException2类型异常
		}
	}
	public void g() throws MyException1
	{
		throw new MyException1("MyException1!");
	}
}

public class Test {
	public static void main(String[] args)
	{
		MyExceptions e=new MyExceptions();
		try {
			e.f();//调用f()
		}catch(Exception a) {//catch f()抛出的异常
			print(a.getMessage()+"catched in Test.main()!");
		}
	}
}
