import java.util.*;
import static net.mindview.util.Print.*;

public class Test {
	public static void main(String[] args)
	{
		//创建HashMap<String,String>
		Map<String,String> myMap=new HashMap<String,String>();
		
		//在HashMap中插入五个键值对
		myMap.put("Key1", "Value1");
		myMap.put("Key2", "Value2");
		myMap.put("Key3", "Value3");
		myMap.put("Key4", "Value4");
		myMap.put("Key5", "Value5");
		
		//输出HashMap，观察散列码排序结果
		print(myMap);
		
		//创建LinkedHashMap<String,String>
		LinkedHashMap<String,String> linkedMap=new LinkedHashMap<String,String>();
		
		//按键从myMap中抽取键值对，插入到linkedMap中
		for(int i=1;i<=5;i++)
		{
			linkedMap.put("Key"+i, myMap.get("Key"+i));
		}
		
		//打印按键进行排序的linkedMap
		print(linkedMap);
	}
}
