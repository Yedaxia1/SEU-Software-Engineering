import java.util.*;

class Generator{
	private static int sub;
	private static String[]movies={"Cat","Dog","Tiger","Lion","Monkey","Sneak","Pig"};
	public String next()
	{
		return movies[(sub++)%movies.length];//ȡ�������ʵ���ַ��б��ѭ��
	}
	public ArrayList arrayList(int n)
	{
		ArrayList<String> m=new ArrayList<String>();
		for(int i=0;i<n;i++)
			m.add(this.next());
		return m;
	}
}
public class Test {
	public static void main(String[] args)
	{
		//���������
		Generator a=new Generator();
		
		//������������󴴽�һ��ArrayList������ֵ��List����
		List<String> myList=a.arrayList(7);
		//���ԭʼList
		System.out.println("Initial list = "+myList);
		//ȡList��һ��sublist
		List<String> sub=myList.subList(1, 4);
		//���sublist
		System.out.println("SubList = "+sub);
		//��List���Ƴ�sublist
		myList.removeAll(sub);
		//����Ƴ����List
		System.out.println("After remove sublist, myList = "+myList);
	}
}
