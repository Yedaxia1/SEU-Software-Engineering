import java.util.*;
import static net.mindview.util.Print.*;

class MyException extends Exception{//异常类
	private int counter;//计数
	public MyException(int n) {counter=n;}
	public void f() throws MyException//用于抛出异常的函数
	{
		if(counter==0)//若计数为零，则不再抛出异常
			return ;
		else
		{
			throw this;//计数不为零，继续抛出异常
		}
	}
	public void dispose()//解决办法
	{
		counter--;
	}
}

public class Test {
	public static void main(String[] args)
	{
		MyException e=new MyException(5);//给定五次计数
		while(true)//恢复模型，while循环
		{
			try {
				e.f();//若抛出异常，则不再执行break，若不抛出异常，则break，结束循环体
				break;
			}catch(MyException a) {
				e.dispose();//异常解决办法
				print("Exception disposed!!");//每一次解决异常打印一次信息
			}
		}
		print("Program ending!!");//代表异常处理完成，程序结束
	}
}
