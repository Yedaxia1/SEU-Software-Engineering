import java.util.*;
import static net.mindview.util.Print.*;

//�Զ��������쳣��
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
	private int counter;//����
	public MyExceptions() {counter=0;}
	public void f() throws MyException1,MyException2,MyException3//�����׳��쳣�ĺ���
	{
		int temp=counter;
		counter++;
		if(temp%3==0)//ģ3Ϊ0���׳�MyException1
			throw new MyException1("MyException1");
		else if(temp%3==1)//ģ3Ϊ1���׳�MyException1
			throw new MyException2("MyException2");
		else//ģ3Ϊ2���׳�MyException1
			throw new MyException3("MyException3");
	}
}

public class Test {
	public static void main(String[] args)
	{
		MyExceptions e=new MyExceptions();
		for(int i=0;i<3;i++)//����ѭ��
		{
			try {
				e.f();//����ѭ����ÿ���׳���ͬ���͵�Exception
			}catch(Exception a) {//����һ��catch��׽�쳣
				print(a.getMessage());//��ӡ�쳣��Ϣ
			}
		}
	}
}
