import java.util.*;

public class Test {
	public static void main(String[] args)
	{
		//������List
		LinkedList<Integer> m=new LinkedList<Integer>();
		//����ListIteratorָ��m���м�λ��
		ListIterator<Integer> it=m.listIterator(m.size()/2);
		//����ʮ��Ԫ��
		for(int i=0;i<10;i++)
		{
			it.add(i);//����Ԫ��
			it=m.listIterator(m.size()/2);//it����ָ��m���м�λ��
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
