package org.ioopm.calculator.Test;

import org.junit.Test;
import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;

public class MultiplicationTest {
    Constant c1 = new Constant(5);
    Constant c2 = new Constant(2);
    Multiplication Multi = new Multiplication(c1,c2);
    Constant c3 = new Constant(5);
    Constant c4 = new Constant(2);
    Constant c5 = new Constant(10);
    Multiplication Multi2 = new Multiplication(c3,c4);
    final EvaluationVisitor evaluator = new EvaluationVisitor();
    Environment env = new Environment();
    
    @Test (expected = RuntimeException.class)
    public void getValueTest(){
        Multi.getValue();
    }

    @Test
    public void isConstantTest(){
        assertFalse(Multi.isConstant());
    }

    @Test
    public void getNameTest(){
        assertEquals("*", Multi.getName());
    }

    @Test
    public void isCommandTest(){
        assertFalse(Multi.isCommand());
    }

    @Test
    public void getPriorityTest(){
        assertTrue(100 == Multi.getPriority());
    }

    @Test
    public void toStringTest(){
        assertEquals("5.0 * 2.0", Multi.toString());
    }

    @Test
    public void equalsTest(){
        assertTrue(Multi.equals(Multi2));
    }

    @Test
    public void evaluateTest(){
        assertEquals(c5, evaluator.evaluate(Multi, env));
    }
}