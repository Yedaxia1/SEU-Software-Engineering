import java.util.*;
import static net.mindview.util.Print.*;

//�Զ��������쳣��
class MyException1 extends Exception{
	MyException1() throws MyException1
	{
		throw this;
	}
};
class MyException2 extends MyException1{
	/*
	 * �����๹��ǰ���ȵ��û��๹�캯������ʱ��δ���������๹�캯��������catch�޷���׽���๹�캯���׳����쳣
	 * ��ˣ������޷�ͨ��
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
