import java.nio.*;
import java.util.*;

public class Test implements Readable {
	private static Random rand =new Random(47);
	private static final char[] mychar="ABCDEFGHIJ".toCharArray();
	private int count;
	public Test(int count){this.count=count;}
	public int read(CharBuffer cb)
	{
		if(count--==0)
			return -1;
		for(int i=0;i<mychar.length;i++)
			cb.append(mychar[rand.nextInt(mychar.length)]);
		cb.append(" ");
		return cb.length();
	}
	public static void main(String[] args)
	{
		Scanner s=new Scanner(new Test(10));
		while(s.hasNext())
			System.out.println(s.next());
	}
}
