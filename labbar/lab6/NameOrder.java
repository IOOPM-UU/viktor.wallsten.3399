import java.util.Scanner;

public class NameOrder {

public static void main(String[] args) {
    Scanner sc1 = new Scanner(System.in);
    Scanner sc2 = new Scanner(System.in);
    String s1 = sc1.nextLine();
    String s2 = sc2.nextLine();

    if (s1.compareToIgnoreCase(s2) > 0) {
        System.out.println(s2 + " " + s1);
    }
    else{
        System.out.println(s1 + " " + s2);
    }
    }
}
