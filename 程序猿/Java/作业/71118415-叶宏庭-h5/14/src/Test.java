import java.util.*;
import static net.mindview.util.Print.*;

//�Զ��������쳣��
class MyException1 extends Exception{
	MyException1(String a){super(a);}
};
class MyException2 extends Exception{
	MyException2(String a){super(a);}
};


class MyExceptions extends Exception{
	public void f() throws MyException2//f�����׳�MyException2�����쳣
	{
		try {
			g();//����g()
		}catch(Exception a)//catch g()�׳����쳣
		{
			print(a.getMessage()+"catched in MyExceptions.f()!");//��ӡ�쳣��Ϣ
			throw new MyException2("MyException2!");//�׳�MyException2�����쳣
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
			e.f();//����f()
		}catch(Exception a) {//catch f()�׳����쳣
			print(a.getMessage()+"catched in Test.main()!");
		}
	}
}
