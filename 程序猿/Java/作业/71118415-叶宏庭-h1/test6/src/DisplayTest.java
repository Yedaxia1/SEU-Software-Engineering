
public class DisplayTest {
	public static void main(String[] args)
	{
		//ʮ�����ơ��˽��Ʊ�ʾlongֵ
		long n1=0xffff;
		long n2=0372;
		
		//���Ϊ������
		System.out.println("n1 to binaryString"+" "+Long.toBinaryString(n1));
		System.out.println("n2 to binaryString"+" "+Long.toBinaryString(n2));
		
		//float��doubleָ�������������Сֵ
		float f1=Float.MAX_VALUE;
		float f2=Float.MIN_VALUE;
		
		double d1=Double.MAX_VALUE;
		double d2=Double.MIN_VALUE;
		
		System.out.println("Float max value is"+" "+f1);
		System.out.println("Float min value is"+" "+f2);
		
		System.out.println("Double max value is"+" "+d1);
		System.out.println("Double min value is"+" "+d2);
	}
}
