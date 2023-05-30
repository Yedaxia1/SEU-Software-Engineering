import java.util.*;
import static net.mindview.util.Print.*;

//自定义三个异常类
class MyException1 extends Exception{
	MyException1(String a){super(a);}
};
class MyException2 extends Exception{
	MyException2(String a){super(a);}
};
class MyException3 extends Exception{
	MyException3(String a){super(a);}
};

class MyExceptions extends Exception{
	private int counter;//计数
	public MyExceptions() {counter=0;}
	public void f() throws MyException1,MyException2,MyException3//用于抛出异常的函数
	{
		int temp=counter;
		counter++;
		if(temp%3==0)//模3为0，抛出MyException1
			throw new MyException1("MyException1");
		else if(temp%3==1)//模3为1，抛出MyException1
			throw new MyException2("MyException2");
		else//模3为2，抛出MyException1
			throw new MyException3("MyException3");
	}
}

public class Test {
	public static void main(String[] args)
	{
		MyExceptions e=new MyExceptions();
		for(int i=0;i<3;i++)//三次循环
		{
			try {
				e.f();//三次循环，每次抛出不同类型的Exception
			}catch(Exception a) {//采用一个catch捕捉异常
				print(a.getMessage());//打印异常信息
			}
		}
	}
}
