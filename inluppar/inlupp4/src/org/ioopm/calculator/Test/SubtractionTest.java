package org.ioopm.calculator.Test;

import org.junit.Test;
import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;

public class SubtractionTest {
    Constant c1 = new Constant(5);
    Constant c2 = new Constant(2);
    Subtraction Subbi = new Subtraction(c1,c2);
    Constant c3 = new Constant(5);
    Constant c4 = new Constant(2);
    Constant c5 = new Constant(3);
    Subtraction Subbi2 = new Subtraction(c3,c4);
    final EvaluationVisitor evaluator = new EvaluationVisitor();
    Environment env = new Environment();
    
    @Test (expected = RuntimeException.class)
    public void getValueTest(){
        Subbi.getValue();
    }

    @Test
    public void isConstantTest(){
        assertFalse(Subbi.isConstant());
    }

    @Test
    public void getNameTest(){
        assertEquals("-", Subbi.getName());
    }

    @Test
    public void isCommandTest(){
        assertFalse(Subbi.isCommand());
    }

    @Test
    public void getPriorityTest(){
        assertTrue(50 == Subbi.getPriority());
    }

    @Test
    public void toStringTest(){
        assertEquals("5.0 - 2.0", Subbi.toString());
    }

    @Test
    public void equalsTest(){
        assertTrue(Subbi.equals(Subbi2));
    }

    @Test
    public void evaluateTest(){
        assertEquals(c5, evaluator.evaluate(Subbi, env));
    }
}