import java.util.*;
import static net.mindview.util.Print.*;

public class Test {
	public static void main(String[] args)
	{
		//����HashMap<String,String>
		Map<String,String> myMap=new HashMap<String,String>();
		
		//��HashMap�в��������ֵ��
		myMap.put("Key1", "Value1");
		myMap.put("Key2", "Value2");
		myMap.put("Key3", "Value3");
		myMap.put("Key4", "Value4");
		myMap.put("Key5", "Value5");
		
		//���HashMap���۲�ɢ����������
		print(myMap);
		
		//����LinkedHashMap<String,String>
		LinkedHashMap<String,String> linkedMap=new LinkedHashMap<String,String>();
		
		//������myMap�г�ȡ��ֵ�ԣ����뵽linkedMap��
		for(int i=1;i<=5;i++)
		{
			linkedMap.put("Key"+i, myMap.get("Key"+i));
		}
		
		//��ӡ�������������linkedMap
		print(linkedMap);
	}
}
