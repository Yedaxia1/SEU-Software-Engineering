import java.util.*;

class Gerbil{
	private int gerbilNumber;
	private static int TotalNumber;
	public Gerbil()
	{
		gerbilNumber = ++TotalNumber;
	}
	public void hop()
	{
		System.out.println("Gerbil"+gerbilNumber+
				" is hopping!"+" It's number is "+gerbilNumber);
	}
}


public class Test {
	public static void main(String[] args)
	{
		ArrayList<Gerbil> gerbils= new ArrayList<Gerbil>();
		gerbils.add(new Gerbil());
		gerbils.add(new Gerbil());
		gerbils.add(new Gerbil());
		gerbils.add(new Gerbil());
		gerbils.add(new Gerbil());
		for(int i=0;i<gerbils.size();i++)
			gerbils.get(i).hop();
	}
}
