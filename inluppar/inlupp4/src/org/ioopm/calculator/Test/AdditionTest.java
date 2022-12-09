package org.ioopm.calculator.Test;

import org.junit.Test;
import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;

public class AdditionTest {
    Constant c1 = new Constant(5);
    Constant c2 = new Constant(2);
    Addition addi = new Addition(c1,c2);
    Constant c3 = new Constant(5);
    Constant c4 = new Constant(2);
    Constant c5 = new Constant(7);
    Addition addi2 = new Addition(c3,c4);
    final EvaluationVisitor evaluator = new EvaluationVisitor();
    Environment env = new Environment();
    
    @Test (expected = RuntimeException.class)
    public void getValueTest(){
        addi.getValue();
    }

    @Test
    public void isConstantTest(){
        assertFalse(addi.isConstant());
    }

    @Test
    public void getNameTest(){
        assertEquals("+", addi.getName());
    }

    @Test
    public void isCommandTest(){
        assertFalse(addi.isCommand());
    }

    @Test
    public void getPriorityTest(){
        assertTrue(50 == addi.getPriority());
    }

    @Test
    public void toStringTest(){
        assertEquals("5.0 + 2.0", addi.toString());
    }

    @Test
    public void equalsTest(){
        assertTrue(addi.equals(addi2));
    }

    @Test
    public void evaluateTest(){
        assertEquals(c5, evaluator.evaluate(addi, env));
    }
}