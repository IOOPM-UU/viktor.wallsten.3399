import java.util.LinkedList;

public class Store {
    Register registers[];

    public int getAverageQueueLength(){
        int registerOpen = 0;
        int total = 0;

        for(int i = 0; i < this.registers.length; i++){
            if (this.registers[i].isOpend()) {
                total += this.registers[i].getQueueLength();
                registerOpen++;
            }
        }
        return (total / registerOpen);
    }

    public void newCustomer(Customer c){
        int shortestq = 0;
        for(int i = 0; i < this.registers.length; i++){
            if(this.registers[i].getQueueLength() < registers[shortestq].getQueueLength() && this.registers[i].isOpend()){
                shortestq = i;
            }
        }
        if (this.registers[shortestq].isOpend()) {
            this.registers[shortestq].addToQueue(c);
        }
    }

    public void step(){
        for(int i = 0; i < this.registers.length; i++){
            if (registers[i].isOpend()) {
                this.registers[i].step();
            }
        }
    }

    public void openNewRegister(){
        for(int i = 0; i < this.registers.length; i++){
            if (!this.registers[i].isOpend()) {
                this.registers[i].open();
                break;
            }
        }
    }

    public String toStiString(){
        String str = "";
        for(int i = 0; i < this.registers.length; i++){
            if (registers[i] != null) {
                if (registers[i].queue.first() == null) {
                    str += "X []" + "\n";
                }
                else{
                    int qlength = registers[i].getQueueLength();
                    for(int j = 0; j < qlength; j++){
                        str += "@";
                    }
                    str += "\n";
                }
            }
        }
        return str;
    }

    public LinkedList<Customer>  getDoneCustomers(){
        LinkedList<Customer> done = new LinkedList<Customer>();
        for(int i = 0; i < this.registers.length; i++){
            if(this.registers[i].currentCustomerIsDone()){
                done.add(this.registers[i].removeCurrentCustomer());
            }
        }
        return done;
    }
}
