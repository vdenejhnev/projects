package project2_5;

import java.util.concurrent.TimeUnit;

public class Car {
	String name;
	String color;
	double engine_value; 
	
	public Car(String name, String color, double engine_value) {
		this.name = name;
		this.color = color;
		this.engine_value = engine_value;
	}
	
	public void getCar2() {
		System.out.println("--------------------------");
		System.out.println("Name: " + this.name);
		System.out.println("Color: " + this.color);
		System.out.println("Engine value: " + this.engine_value);
	}
	
	public void rideCar(int speed) {
		int way = 0;
		for (;;) {
			way = way + speed;
			try {
	            TimeUnit.MILLISECONDS.sleep(1000);
	        }
	        catch (InterruptedException ex) {
	            Thread.currentThread().interrupt();
	        }
			System.out.println(this.name + ": " + way + " m");
		}
	}
	
	public static void main(String[] args) {
		Car BMW_M5 = new Car("BMW M5", "black", 18.9);
		Car BMW_M4_Competiotion = new Car("BMW_M4_Competiotion", "red", 50.9);
		Car Toyota_Camry = new Car("Toyota Camry", "white", 20.4);
		BMW_M5.getCar2();
		BMW_M4_Competiotion.getCar2();
		Toyota_Camry.getCar2();
		BMW_M5.rideCar(100);
	}
}


//Car('BMW', 'grey', 15.6);