import java.util.Scanner;

public class Die {
  private int numberOfSides;
  private int value;

  public Die() {
      this.numberOfSides = 6;
  }

  public Die(int numberOfSides) {
      this.numberOfSides = numberOfSides;
  }

  public int roll() {
    this.value = (int) (Math.random() * numberOfSides) + 1;
    return this.get();
  }

  public boolean equals(Die otherDie)
  {
    if(otherDie.value == this.value)
    {
      System.out.println("true");
      return true;
    }
    System.out.println("false");
    return false;
  }

  public String toString() {
    return "Die(" + value + ")";
  }

  public int get() {
      return value;
  }

  public static void main(String [] args) {
    try (Scanner sc = new Scanner(System.in)) {
      System.out.print("Number of sides: ");
      int sides = sc.nextInt();
      if (sides <= 0) {
        throw new IllegalArgumentException("Illegal number of sides for die");
      }
        Die d = new Die(sides);
        System.out.println(d);
        System.out.println("Alea iacta est: " + d.roll());
        Die q = new Die(sides);
        q.roll();
        d.equals(q);
      }
  }
}