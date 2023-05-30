import java.util.*;
public class SimpleCollection {
	public static void main(String[] args)
	{
		Set<Integer> c = new HashSet<Integer>();
		for(int i=0;i<10;i++)
			c.add(i);
		System.out.println("Set c = "+c);
	}
}
