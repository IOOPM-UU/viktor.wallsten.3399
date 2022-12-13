public class Simulation {
    public int time;
    public int intensity;
    public int maxGroceries;
    public int thresholdForNewRegister;
    private Store store;

    public Simulation(int t, int i, int m, int th){
        this.time = t;
        this.intensity = i;
        this.maxGroceries = m;
        this.thresholdForNewRegister = th;
    }

    public void step(){
        this.time++;
        int g = (int) (Math.random() * maxGroceries);
        int i = (int) (Math.random() * 100);
        if(i < intensity){
            Customer c = new Customer(this.time, g);
            this.store.newCustomer(c);
        }
        if (this.store.getAverageQueueLength() > thresholdForNewRegister) {
            this.store.openNewRegister();
        }
        store.step();
    }
}
