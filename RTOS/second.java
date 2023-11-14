class Stack {
    private int index;
    private int stack[];

    // default Constructor
    Stack() {

    }

    Stack(int size) {
        this.stack = new int[size];
    }

    //display all the data from the stack
    public void display() {
        for (int index = 0; index < this.index; index++) {
            System.out.println("i : " + index + ", data : "+ this.stack[index]);
        }
    }

    //push the data into stack
    public Boolean push(int data) {
        if (this.stack.length == index) {
            return false;
        }
        this.stack[this.index] = data;
        this.index++;
        return true;
    }

    //pop the data from the stack
    public int pop() {
        if (this.index > 0) {
            this.index--;
            return this.stack[this.index];
        }
        return -1;
    }
}