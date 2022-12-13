public class Register {
    boolean open;
    Queue queue;

    public Register(){
        this.open = false;
        this.queue = new Queue();
    }

    public void open(){
        this.open = true;
    }

    public void closed(){
        this.open = false;
    }

    public boolean isOpend(){
        if (this.open == true) {
            return true;
        }
        return false;
    }

    public void step(){
        if (this.isOpend() && this.hasCustomers()) {
            this.queue.first().serve();
        }
    }

    public boolean hasCustomers(){
        if(this.queue.length() == 0){
            return false;
        }
        return true;
    }

    public boolean currentCustomerIsDone(){
        if (this.queue.first().isDone()) {
            return true;
        }
        return false;
    }

    public void addToQueue(Customer c){
        this.queue.enqueue(c);
    }

    public Customer removeCurrentCustomer(){
        Customer c = this.queue.first();
        this.queue.dequeue();
        return c;
    }

    public int getQueueLength(){
        return this.queue.length();
    }

}
