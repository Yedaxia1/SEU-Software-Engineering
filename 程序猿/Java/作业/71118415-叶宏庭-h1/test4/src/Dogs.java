
class Dog{
	String name;
	String says;
	void setMessages(String a,String b)
	{
		name=a;
		says=b;
	}
	void displayMessages()
	{
		System.out.println(name+" "+says);
	}
}

public class Dogs {
	public static void main(String[] args)
	{
		Dog dog1=new Dog();
		Dog dog2=new Dog();
		
		dog1.setMessages("spot", "Ruff!");
		dog2.setMessages("scruffy", "Wurf!");
		
		dog1.displayMessages();
		dog2.displayMessages();
		
		Dog dog3=new Dog();
		
		dog3.setMessages("spot", "Ruff!");
		
		dog3.displayMessages();
		
		System.out.println(dog3==dog1? true:false);
		
		System.out.println(dog3.equals(dog1)? true:false);
			
		
	}

}
