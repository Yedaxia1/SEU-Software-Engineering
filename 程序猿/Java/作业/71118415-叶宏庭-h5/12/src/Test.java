import java.util.*;
import static net.mindview.util.Print.*;

class MyException extends Exception{//�쳣��
	private int counter;//����
	public MyException(int n) {counter=n;}
	public void f() throws MyException//�����׳��쳣�ĺ���
	{
		if(counter==0)//������Ϊ�㣬�����׳��쳣
			return ;
		else
		{
			throw this;//������Ϊ�㣬�����׳��쳣
		}
	}
	public void dispose()//����취
	{
		counter--;
	}
}

public class Test {
	public static void main(String[] args)
	{
		MyException e=new MyException(5);//������μ���
		while(true)//�ָ�ģ�ͣ�whileѭ��
		{
			try {
				e.f();//���׳��쳣������ִ��break�������׳��쳣����break������ѭ����
				break;
			}catch(MyException a) {
				e.dispose();//�쳣����취
				print("Exception disposed!!");//ÿһ�ν���쳣��ӡһ����Ϣ
			}
		}
		print("Program ending!!");//�����쳣������ɣ��������
	}
}
