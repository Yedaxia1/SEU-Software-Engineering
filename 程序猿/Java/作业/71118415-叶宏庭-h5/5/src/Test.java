import java.util.*;

class Generator{
	private static int sub;
	private static String[]movies={"Cat","Dog","Tiger","Lion","Monkey","Sneak","Pig"};
	public String next()
	{
		return movies[(sub++)%movies.length];//取余操作，实现字符列表的循环
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
		//生成类对象
		Generator a=new Generator();
		
		//利用生成类对象创建一个ArrayList，并赋值给各种类型的Collection对象
		List<String> myList=a.arrayList(7);
		ArrayList<String> myArrayList=new ArrayList<String>(myList);
		LinkedList<String> myLinkedList=new LinkedList<String>(myList);
		HashSet<String> myHashSet=new HashSet<String>(myList);
		TreeSet<String> myTreeSet=new TreeSet<String>(myList);
		
		//使用迭代器遍历每一种类型的Collection
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
