import java.util.*;

public class Test {
	public static void main(String[] args)
	{
		//创建空List
		LinkedList<Integer> m=new LinkedList<Integer>();
		//创建ListIterator指向m的中间位置
		ListIterator<Integer> it=m.listIterator(m.size()/2);
		//插入十个元素
		for(int i=0;i<10;i++)
		{
			it.add(i);//插入元素
			it=m.listIterator(m.size()/2);//it重新指向m的中间位置
		}
		it=m.listIterator();
		disPlay(it);
	}
	public static void disPlay(Iterator<Integer> it)
	{
		while(it.hasNext())
		{
			System.out.print(it.next()+" ");
		}
		System.out.print("\n");
	}
}
