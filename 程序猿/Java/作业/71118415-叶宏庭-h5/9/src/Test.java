import java.util.*;
import static net.mindview.util.Print.*;

public class Test {
	public static void main(String[] args)
	{
		//����HashSet<String>
		Set<String> mySet=new HashSet<String>();
		
		//��HashSet�в������Ԫ��
		mySet.add("Key1");
		mySet.add("Key2");
		mySet.add("Key3");
		mySet.add("Key4");
		mySet.add("Key5");
		
		//����LinkedHashSet<String>
		LinkedHashSet<String> linkedSet=new LinkedHashSet<String>();
		
		//��LinkedHashSet�в������Ԫ��
		linkedSet.add("Key1");
		linkedSet.add("Key2");
		linkedSet.add("Key3");
		linkedSet.add("Key4");
		linkedSet.add("Key5");
		
		//���HashSet
		print("mySet(HashSet) = "+mySet);
		
		//���LinkedHashSet���ԱȽ��
		print("linkedSet(LinkedHashSet) = "+linkedSet);
	}
}
