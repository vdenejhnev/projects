package project2_3;

public class main {
	public static void main(String[] args) {
		System.out.println(build_blocks(5));
		System.out.println(build_blocks(6));
		build_blocks(10);
		build_blocks(12);
		build_blocks(20);
	}
	
	public static int build_blocks(int N) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N + 2; j++) {
				System.out.print("# ");
			}
			System.out.println("");
		}
		System.out.println("");
		
		return(N*N);
	}
	
}
