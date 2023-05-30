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
		
		//利用生成类对象创建一个ArrayList，并赋值给List对象
		List<String> myList=a.arrayList(7);
		//输出原始List
		System.out.println("Initial list = "+myList);
		//取List的一个sublist
		List<String> sub=myList.subList(1, 4);
		//输出sublist
		System.out.println("SubList = "+sub);
		//在List中移除sublist
		myList.removeAll(sub);
		//输出移除后的List
		System.out.println("After remove sublist, myList = "+myList);
	}
}
