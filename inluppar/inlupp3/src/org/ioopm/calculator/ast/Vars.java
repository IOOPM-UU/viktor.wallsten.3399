package org.ioopm.calculator.ast;

 
public class Vars extends Command {
    private static final Vars theInstance = new Vars();
    private Vars() {}


    public static Vars instance() {
        return theInstance;
    }

    public SymbolicExpression eval(Environment vars){
        vars.values();
        return null;
    }
}
