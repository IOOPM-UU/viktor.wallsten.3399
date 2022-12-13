public class Customer {
    int bornTime;
    int groceries;

    public Customer(int a, int b ){
        this.bornTime = a;
        this.groceries = b;
    }

    public void serve() {
        int old = this.groceries;
        this.groceries = old - 1;
    }

    public boolean isDone(){
        if (this.groceries == 0) {
            return true;
        }
        return false;
    }

    public String toString() {
        return "Customer(" + bornTime + ")";
      }

public static void main(String args[]) {
    Customer c = new Customer(0, 3);
    c.serve();
    c.serve();
    c.serve();
    if(c.isDone()) {
        System.out.println("The customer is done, just as expected!");
    } else {
        System.out.println("The customer is not done, but should be...");
            }
    }
}
