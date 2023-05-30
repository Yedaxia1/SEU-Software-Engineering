import java.util.*;
import net.mindview.util.*;

public class UniqueWords {
	public static void main(String[] args)
	{
		//创建元音字母集合
		Set<String> vowels=new TreeSet<String>();
		Collections.addAll(vowels, "a e i o u".split(" "));
		//创建words集合
		Set<String> words=new TreeSet<String>(String.CASE_INSENSITIVE_ORDER);
		//将文件读入words集合中，采用正则分隔
		words.addAll(new TextFile("src\\pack1\\yht11.java","\\W+"));
		//创建数量集合，用于表示每个word出现元音的次数
		ArrayList<Integer> numbers=new ArrayList<Integer>();
		//遍历words集合
		for(String i:words)
		{
			//将每一个word按字符分隔为一个ArrayList
			ArrayList<String> temp=new ArrayList<String>();
			Collections.addAll(temp, i.split(""));
			//定义counter，用于表示数量
			Integer counter=new Integer(0);
			//遍历生成的ArrayList，即对一个word的每一个字符进行操作
			for(String j:temp)
			{
				//若该字符的小写形式包含在vowels中，即该字符为元音字母，计数++
				if(vowels.contains(j.toLowerCase()))
					counter++;
			}
			//遍历完一个word，将数量计入数量集合
			numbers.add(counter);
		}
		//遍历number集合即可获取元音字母出现的总次数
		Integer sum=new Integer(0);
		for(Integer i:numbers)
			sum+=i;
		//输出words集合，numbers集合，总数
		Print.print("The words is: "+words);
		Print.print("The number of vowels for each one:"+numbers);
		Print.print("The total number of vowels is:"+sum);
	}
}
