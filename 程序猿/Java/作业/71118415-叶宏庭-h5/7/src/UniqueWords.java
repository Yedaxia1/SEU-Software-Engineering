import java.util.*;
import net.mindview.util.*;

public class UniqueWords {
	public static void main(String[] args)
	{
		//����Ԫ����ĸ����
		Set<String> vowels=new TreeSet<String>();
		Collections.addAll(vowels, "a e i o u".split(" "));
		//����words����
		Set<String> words=new TreeSet<String>(String.CASE_INSENSITIVE_ORDER);
		//���ļ�����words�����У���������ָ�
		words.addAll(new TextFile("src\\pack1\\yht11.java","\\W+"));
		//�����������ϣ����ڱ�ʾÿ��word����Ԫ���Ĵ���
		ArrayList<Integer> numbers=new ArrayList<Integer>();
		//����words����
		for(String i:words)
		{
			//��ÿһ��word���ַ��ָ�Ϊһ��ArrayList
			ArrayList<String> temp=new ArrayList<String>();
			Collections.addAll(temp, i.split(""));
			//����counter�����ڱ�ʾ����
			Integer counter=new Integer(0);
			//�������ɵ�ArrayList������һ��word��ÿһ���ַ����в���
			for(String j:temp)
			{
				//�����ַ���Сд��ʽ������vowels�У������ַ�ΪԪ����ĸ������++
				if(vowels.contains(j.toLowerCase()))
					counter++;
			}
			//������һ��word��������������������
			numbers.add(counter);
		}
		//����number���ϼ��ɻ�ȡԪ����ĸ���ֵ��ܴ���
		Integer sum=new Integer(0);
		for(Integer i:numbers)
			sum+=i;
		//���words���ϣ�numbers���ϣ�����
		Print.print("The words is: "+words);
		Print.print("The number of vowels for each one:"+numbers);
		Print.print("The total number of vowels is:"+sum);
	}
}
