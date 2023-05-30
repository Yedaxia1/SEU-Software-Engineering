import java.util.*;
import static net.mindview.util.Print.*;

public class Test {
	public static void main(String[] args)
	{
		//创建HashSet<String>
		Set<String> mySet=new HashSet<String>();
		
		//在HashSet中插入五个元素
		mySet.add("Key1");
		mySet.add("Key2");
		mySet.add("Key3");
		mySet.add("Key4");
		mySet.add("Key5");
		
		//创建LinkedHashSet<String>
		LinkedHashSet<String> linkedSet=new LinkedHashSet<String>();
		
		//在LinkedHashSet中插入五个元素
		linkedSet.add("Key1");
		linkedSet.add("Key2");
		linkedSet.add("Key3");
		linkedSet.add("Key4");
		linkedSet.add("Key5");
		
		//输出HashSet
		print("mySet(HashSet) = "+mySet);
		
		//输出LinkedHashSet，对比结果
		print("linkedSet(LinkedHashSet) = "+linkedSet);
	}
}
