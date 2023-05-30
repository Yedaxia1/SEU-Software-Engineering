package aliasing;

class myfloat{
	float a;
}

public class aliasing {
	public static void main(String[] args)
	{
		myfloat f1=new myfloat();
		myfloat f2=new myfloat();
		
		f1.a=3.7f;
		f2.a=3.8f;
		
		System.out.println(f1.a);
		System.out.println(f2.a);
		
		f1=f2;
		
		f1.a=4.0f;
		
		System.out.println(f1.a);
		System.out.println(f2.a);
	}
}
