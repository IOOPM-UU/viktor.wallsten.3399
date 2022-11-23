package org.ioopm.calculator;

import org.junit.Test;
import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;

public class additionTest {
    Constant c1 = new Constant(5);
    Constant c2 = new Constant(2);
    Variable v = new Variable("x");
    Addition a = new Addition(c1, v);
    Addition addi = new Addition(c1,c2);
    Sin s = new Sin(new Constant(0));
    Constant zero = new Constant(0);
    Cos c = new Cos(new Constant(0.5));
    Multiplication m = new Multiplication(a, a);
    Division d = new Division(a, m);
    SymbolicExpression i = new Constant(42);
    SymbolicExpression b = new Constant(42);
    SymbolicExpression e = new Variable ("x");
    SymbolicExpression f = new Variable ("x");
    Addition q = new Addition(v, c2);
    Addition w = new Addition(v, c1);
    Addition r = new Addition(new Constant(2), new Constant(3));
    Subtraction t = new Subtraction(r, new Constant(1));
    Addition u = new Addition(w, t);
    Addition g = new Addition(new Constant(3), new Constant(11));
    Constant facit = new Constant (19);
    Addition test = new Addition (r, g);
    Assignment ass = new Assignment(new Constant(8), (new Variable("x")));
    Addition add = new Addition(ass, new Constant(5));
    Constant thirteen = new Constant(13);
    Addition ad = new Addition(new Variable("x"), new Constant(2));
    Assignment ass1 = new Assignment(ad ,new Variable("x"));
    Variable x = new Variable("z");
    Variable y = new Variable("z");
    Constant p = new Constant(Math.PI);
    Constant pi = new Constant(Constants.namedConstants.get("pi"));
    Assignment l = new Assignment(new Constant(5), new Variable("pi"));
    Addition n = new Addition(new Constant(2), pi);
    Division div = new Division(new Constant(1.2), new Constant(0));
    


    @Test (expected = RuntimeException.class)
    public void getValueTest(){
        try{
            addi.getValue();
        }
        catch(RuntimeException e){
            assertTrue(true);
        }
        assertFalse(true);
    }

    @Test
    public void isConstantTest(){
        assertFalse(addi.isConstant());
    }

    @Test
    public void getNameTest(){

    }

    @Test
    public void priorityTest(){
        assertTrue(50.0 == addi.getPriority());
    }

    @Test
    public void testTrue(){
        assertTrue(true);
    }
    
    @Test
    public void testFalse(){
        assertFalse(false);
    }

}