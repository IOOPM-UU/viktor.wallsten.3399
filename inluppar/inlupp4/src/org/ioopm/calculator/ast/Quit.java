package org.ioopm.calculator.ast;

public class Quit extends Command{
    private static final Quit theInstance = new Quit();
    private Quit() {}

    public static Quit instance() {
        return theInstance;
    }

    @Override
    public SymbolicExpression accept(Visitor v) {
    return v.visit(this);
    }
}
