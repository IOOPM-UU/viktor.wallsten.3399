import java.util.Scanner;

public class MyDieTest {
  private int numberOfSides;
  private int value;

  public MyDieTest() {
      this.numberOfSides = 6;
  }

  public MyDieTest(int numberOfSides) {
      this.numberOfSides = numberOfSides;
  }

  public int roll() {
    this.value = (int) (Math.random() * numberOfSides) + 1;
    return this.get();
  }

  public int get() {
      return value;
  }

  public int roll10()
  {
    int total = 0;
    int aux = 0;
    while (aux != 10) {
        value = this.roll();
        total += value;
        aux += 1;
    }
    return total;
  }

  public static void main(String [] args) {
      try (Scanner sc = new Scanner(System.in)) {
        System.out.print("Number of sides: ");
        int sides = sc.nextInt();
        MyDieTest d = new MyDieTest(sides);
        System.out.println("Alea iacta est: " + d.roll());
        System.out.println("total: " + d.roll10());
      }
  }
}