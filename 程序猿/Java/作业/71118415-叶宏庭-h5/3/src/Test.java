import java.util.*;

class Generator{
	private static int sub;
	private static String[]movies={"Snow White","Star Wars","Cater Cauch"};
	public String next()
	{
		return movies[(sub++)%movies.length];//ȡ�������ʵ���ַ��б��ѭ��
	}
}
public class Test {
	public static void main(String[] args)
	{
		//�������������
		Generator a=new Generator();
		
		//��������
		String str[]={a.next(),a.next(),a.next(),a.next(),a.next()};
		ArrayList<String> myArrayList=new ArrayList<String>();
		LinkedList<String> myLinkedList=new LinkedList<String>();
		HashSet<String> myHashSet=new HashSet<String>();
		LinkedHashSet<String> myLinkedHashSet=new LinkedHashSet<String>();
		TreeSet<String> myTreeSet=new TreeSet<String>();
		
		//ѭ����Σ�ÿ��ȡnext��add��ÿһ��������
		for(int i=0;i<5;i++)
		{
			String temp=a.next();
			
			myArrayList.add(temp);
			myLinkedList.add(temp);
			myHashSet.add(temp);
			myLinkedHashSet.add(temp);
			myTreeSet.add(temp);
		}
		
		//�������
		System.out.print("str[] = ");
		for(String i:str)
			System.out.print(i+",");
		
		//���ÿ������
		System.out.println("\nmyArrayList = "+myArrayList);
		System.out.println("myLinkedList = "+myLinkedList);
		System.out.println("myHashSet = "+myHashSet);
		System.out.println("myLinkedHashSet = "+myLinkedHashSet);
		System.out.println("myTreeSet = "+myTreeSet);
	}
}
