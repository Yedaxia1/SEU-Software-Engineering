
class Cycle{
	void ride()
	{
		System.out.println("Cycle is ridden!!");
	}
}

class Unicycle extends Cycle{
	void ride()
	{
		System.out.println("Unicycle is ridden!!");
	}
}

class Bicycle extends Cycle{
	void ride()
	{
		System.out.println("Bicycle is ridden!!");
	}
}

class Tricycle extends Cycle{
	void ride()
	{
		System.out.println("Tricycle is ridden!!");
	}
}

public class Test {
	public static void main(String []args)
	{
		Cycle []a= {new Unicycle(),new Bicycle(),new Tricycle()};
		for(Cycle i:a)
		{
			i.ride();
		}
		
	}

}
