package project2;

public class project2_1 {
	public static void main(String[] args) {
        int a = 5;
        int b = 4;
        int c = 6;
        
        for (int i = 1; i <= 10; i++) {
        	System.out.println(i);
        	//System.out.println(sum_2(1.05 * i, 5.4 * i, 8.72 * i));
        }
    }
	/*
	public static void sum_1(double n, double m, double k) {
		System.out.println(n + m + k);
	}
	
	public static double sum_2(double n, double m, double k) {
		n = n + k + m;
		k = n + m;
		m = n * m - k;
		k = k * k / m + n;
		return k;
	}*/
}
