
class Instrument{
	void play(String a) {System.out.println("Instrument.play() "+a);}
	String what() {return "Instrument";}
	void adjust() {System.out.println("Adjusting Instrument.");}
}

class Wind extends Instrument{
	void play(String a) {System.out.println("Wind.play() "+a);}
	String what() {return "Wind";}
	void adjust() {System.out.println("Adjusting Wind.");}
}

class Percussion extends Instrument{
	void play(String a) {System.out.println("Percussion.play() "+a);}
	String what() {return "Percussion";}
	void adjust() {System.out.println("Adjusting Percussion.");}
}

class Stringed extends Instrument{
	void play(String a) {System.out.println("Stringed.play() "+a);}
	String what() {return "Stringed";}
	void adjust() {System.out.println("Adjusting Stringed.");}
}

class Brass extends Wind{
	void play(String a) {System.out.println("Brass.play() "+a);}
	void adjust() {System.out.println("Adjusting Brass.");}
}

class Woodwind extends Wind{
	void play(String a) {System.out.println("Woodwind.play() "+a);}
	void adjust() {System.out.println("Adjusting Woodwind.");}
}

class MyInstrument1 extends Instrument{
	void play(String a) {System.out.println("MyInstrument1.play() "+a);}
	String what() {return "MyInstrument1";}
	void adjust() {System.out.println("Adjusting MyInstrument1.");}
}

class MyInstrument2 extends Woodwind{
	void play(String a) {System.out.println("MyInstrument2.play() "+a);}
	String what() {return "MyInstrument2";}
	void adjust() {System.out.println("Adjusting MyInstrument2.");}
}

public class Music3 {
	public static void tune(Instrument i)
	{
		i.play("MIDDLE_C");
	}
	public static void tuneAll(Instrument[]e)
	{
		for(Instrument i:e)
			tune(i);
	}
	public static void main(String []args)
	{
		Instrument[] orchestra= {
				new Wind(),
				new Percussion(),
				new Stringed(),
				new Brass(),
				new Woodwind(),
				new MyInstrument1(),
				new MyInstrument2()
		};
		tuneAll(orchestra);
	}
}
