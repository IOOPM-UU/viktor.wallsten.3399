import java.util.Scanner;

public class PairOfDice {
    private Die die1;
    private Die die2;

public PairOfDice() {
    this.die1 = new Die();
    this.die2 = new Die();
}

public void pairroll()
{
    this.die1.roll();
    this.die2.roll();
}

public int result()
{
    int total = 0;
    int int1 = this.die1.get();
    int int2 = this.die2.get();
    total = int1 + int2;
    System.out.println("die1: " + total);
    return total;
}
  
public void enskild()
{
    int val1 = this.die1.get();
    int val2 = this.die2.get();
    System.out.println("die1: "+ val1);
    System.out.println("die2: "+ val2);
}

public String toString() {
    return "Die(" + die1 + die2 + ")";
  }

public static void main(String [] args){
        try (Scanner sc = new Scanner(System.in)) {
            System.out.print("Number of sides: ");
            int sides = sc.nextInt();
            if (sides <= 0) {
            throw new IllegalArgumentException("Illegal number of sides for die");
            }
            PairOfDice d = new PairOfDice();
            System.out.println(d);
            d.pairroll();
            d.enskild();
            d.result();

        }
    }
}

