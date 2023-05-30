import java.util.*;

class Generator{
	private static int sub;
	private static String[]movies={"Snow White","Star Wars","Cater Cauch"};
	public String next()
	{
		return movies[(sub++)%movies.length];//取余操作，实现字符列表的循环
	}
}
public class Test {
	public static void main(String[] args)
	{
		//创建生成类对象
		Generator a=new Generator();
		
		//创建容器
		String str[]={a.next(),a.next(),a.next(),a.next(),a.next()};
		ArrayList<String> myArrayList=new ArrayList<String>();
		LinkedList<String> myLinkedList=new LinkedList<String>();
		HashSet<String> myHashSet=new HashSet<String>();
		LinkedHashSet<String> myLinkedHashSet=new LinkedHashSet<String>();
		TreeSet<String> myTreeSet=new TreeSet<String>();
		
		//循环五次，每次取next，add到每一个容器中
		for(int i=0;i<5;i++)
		{
			String temp=a.next();
			
			myArrayList.add(temp);
			myLinkedList.add(temp);
			myHashSet.add(temp);
			myLinkedHashSet.add(temp);
			myTreeSet.add(temp);
		}
		
		//输出数组
		System.out.print("str[] = ");
		for(String i:str)
			System.out.print(i+",");
		
		//输出每个容器
		System.out.println("\nmyArrayList = "+myArrayList);
		System.out.println("myLinkedList = "+myLinkedList);
		System.out.println("myHashSet = "+myHashSet);
		System.out.println("myLinkedHashSet = "+myLinkedHashSet);
		System.out.println("myTreeSet = "+myTreeSet);
	}
}
