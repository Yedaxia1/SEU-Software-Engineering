
interface I1 {
	void I1_Print1();
	void I1_Print2();
}

interface I2 {
	void I2_Print1();
	void I2_Print2();
}

interface I3 {
	void I3_Print1();
	void I3_Print2();
}

interface I4 extends I1,I2,I3 {
	void I4_Print1();
}

class A{
	void A_Print(){};
}

class B extends A implements I4{
	public void I1_Print1(){System.out.println("I1_Print1 in class B.");}
	public void I1_Print2(){System.out.println("I1_Print2 in class B.");}
	public void I2_Print1(){System.out.println("I2_Print1 in class B.");}
	public void I2_Print2(){System.out.println("I2_Print2 in class B.");}
	public void I3_Print1(){System.out.println("I3_Print1 in class B.");}
	public void I3_Print2(){System.out.println("I3_Print2 in class B.");}
	public void I4_Print1(){System.out.println("I4_Print1 in class B.");}
	public void A_Print(){System.out.println("A_Print1 in class B.");}
	
	void GetByI1(I1 i){i.I1_Print1();i.I1_Print2();}
	void GetByI2(I2 i){i.I2_Print1();i.I2_Print2();}
	void GetByI3(I3 i){i.I3_Print1();i.I3_Print2();}
	void GetByI4(I4 i){i.I4_Print1();}
	void GetByA(A a){a.A_Print();}
}

public class Test {
	public static void main(String[] args)
	{
		B b1=new B();
		B b2=new B();
		
		b1.GetByA(b2);
		b1.GetByI1(b2);
		b1.GetByI2(b2);
		b1.GetByI3(b2);
		b1.GetByI4(b2);
	}
}
