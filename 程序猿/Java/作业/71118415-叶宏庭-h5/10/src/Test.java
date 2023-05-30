import java.util.*;
import static net.mindview.util.Print.*;

//Command��
class Command{
	//String��
	private String str;
	private static int sub;
	//���캯����ʼ��String��
	Command(){str=("myString"+sub++);}
	//operation������ӡString��
	void operation() {print(str);}
}

class B{
	//��Command�������Queue��
	public static Command insertCommand(Command c,Queue<Command> qc)
	{
		qc.offer(c);
		return c;
	}
}

class C{
	//��ӡQueue
	public static void PrintQueue(Queue<Command> m)
	{
		for(Command i:m)
			i.operation();//����Command��operation����
	}
}

public class Test {
	public static void main(String[] args)
	{
		Queue<Command> qc=new LinkedList<Command>();
		//��Queue�в����Ǹ�Command����
		for(int i=0;i<10;i++)
			B.insertCommand(new Command(),qc);
		//��ӡQueue
		C.PrintQueue(qc);
	}
}
