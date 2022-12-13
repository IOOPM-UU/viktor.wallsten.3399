import java.util.LinkedList;

public class Queue {
    private LinkedList<Customer> queue;

    public Queue(){
        this.queue = new LinkedList<Customer>();
    }

    public int length() {
        return this.queue.size();
    }

    public void enqueue(Customer c){
        this.queue.addLast(c);
    }

    public void dequeue(){
        if (this.queue.size() == 0) {
            throw new EmptyQueueException();
        }
        else{
            this.queue.removeFirst();
        }
    }

    public Customer first(){
        return this.queue.getFirst();
    }

    public static void main(String args[]) {
        Queue q = new Queue();
        Customer c = new Customer(0, 3);
        Customer a = new Customer(1, 6);
        Customer b = new Customer(2, 9);
        Customer d = new Customer(3, 5);
        q.enqueue(c);
        q.enqueue(a);
        q.enqueue(b);
        q.enqueue(d);
        System.out.println("qeueu legnth: " + q.length());
        System.out.println("frist customer: " + q.first());
        q.dequeue();
        System.out.println("qeueu legnth: " + q.length());
        System.out.println("frist customer: " + q.first());
    }
}
