import java.util.*;

public class RandomTest {
	public static void main(String[] args)
	{
		Random r= new Random();
		
		int count1=0;
		int count2=0;
		
		for(int i=0;i<500;i++)
		{
			int a=Math.abs(r.nextInt()%2);
			if(a==0)
			{
				System.out.println("正面");
				count1++;
			}
			else
			{
				System.out.println("反面");
				count2++;
			}
		}
		System.out.println(count1);
		System.out.println(count2);
		
	}
}
