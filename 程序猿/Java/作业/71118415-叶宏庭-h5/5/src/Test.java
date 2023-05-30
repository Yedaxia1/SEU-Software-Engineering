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
		
		//������������󴴽�һ��ArrayList������ֵ���������͵�Collection����
		List<String> myList=a.arrayList(7);
		ArrayList<String> myArrayList=new ArrayList<String>(myList);
		LinkedList<String> myLinkedList=new LinkedList<String>(myList);
		HashSet<String> myHashSet=new HashSet<String>(myList);
		TreeSet<String> myTreeSet=new TreeSet<String>(myList);
		
		//ʹ�õ���������ÿһ�����͵�Collection
		disPlay(myList.iterator());
		disPlay(myArrayList.iterator());
		disPlay(myLinkedList.iterator());
		disPlay(myHashSet.iterator());
		disPlay(myTreeSet.iterator());
		
	}
	public static void disPlay(Iterator<String> it)
	{
		while(it.hasNext())
		{
			String temp=it.next();
			System.out.print(temp+" ");
		}
		System.out.print("\n");
	}
}
