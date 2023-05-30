import java.util.*;
import static net.mindview.util.Print.*;

class MyException extends Exception{
	private String mas;
	public void displayMas() {print(mas);}
	public MyException(String s) {mas=s;}
}

public class Test {
	public static void main(String[] args)
	{
		try {
			throw new MyException("It's MyException!!");
		}catch(MyException e) {
			e.displayMas();
		}
	}
}
