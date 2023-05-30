import java.util.*;
import static net.mindview.util.Print.*;

//Command类
class Command{
	//String域
	private String str;
	private static int sub;
	//构造函数初始化String域
	Command(){str=("myString"+sub++);}
	//operation方法打印String域
	void operation() {print(str);}
}

class B{
	//将Command对象插入Queue中
	public static Command insertCommand(Command c,Queue<Command> qc)
	{
		qc.offer(c);
		return c;
	}
}

class C{
	//打印Queue
	public static void PrintQueue(Queue<Command> m)
	{
		for(Command i:m)
			i.operation();//调用Command的operation方法
	}
}

public class Test {
	public static void main(String[] args)
	{
		Queue<Command> qc=new LinkedList<Command>();
		//向Queue中插入是个Command对象
		for(int i=0;i<10;i++)
			B.insertCommand(new Command(),qc);
		//打印Queue
		C.PrintQueue(qc);
	}
}
