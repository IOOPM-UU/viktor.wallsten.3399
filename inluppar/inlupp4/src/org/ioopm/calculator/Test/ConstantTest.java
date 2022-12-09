package org.ioopm.calculator.Test;

import org.junit.Test;
import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;

public class ConstantTest {
    Constant c1 = new Constant(5);
    Constant c2 = new Constant(2);
    Addition addi = new Addition(c1,c2);
    Constant c3 = new Constant(5);
    Constant c4 = new Constant(2);
    Constant c5 = new Constant(7);
    Addition addi2 = new Addition(c3,c4);
    final EvaluationVisitor evaluator = new EvaluationVisitor();
    Environment env = new Environment();
    
    @Test
    public void getValueTest(){
        assertTrue(5 == c1.getValue());
    }

    @Test
    public void isConstantTest(){
        assertTrue(c1.isConstant());
    }

    @Test (expected = RuntimeException.class)
    public void getNameTest(){
        assertEquals("5.0", c1.getName());
    }

    @Test
    public void isCommandTest(){
        assertFalse(c1.isCommand());
    }

    @Test
    public void getPriorityTest(){
        assertTrue(200 == c1.getPriority());
    }

    @Test
    public void toStringTest(){
        assertEquals("5.0", c1.toString());
    }

    @Test
    public void equalsTest(){
        assertTrue(c1.equals(c3));
    }

    @Test
    public void evaluateTest(){
        assertEquals(c1, evaluator.evaluate(c1, env));
    }
}