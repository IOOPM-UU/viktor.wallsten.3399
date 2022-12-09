package org.ioopm.calculator.Test;

import org.junit.Test;
import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;

public class DivisionTest {
    Constant c1 = new Constant(5);
    Constant c2 = new Constant(2);
    Division Divi = new Division(c1,c2);
    Constant c3 = new Constant(5);
    Constant c4 = new Constant(2);
    Constant c5 = new Constant(2.5);
    Division Divi2 = new Division(c3,c4);
    final EvaluationVisitor evaluator = new EvaluationVisitor();
    Environment env = new Environment();
    
    @Test (expected = RuntimeException.class)
    public void getValueTest(){
        Divi.getValue();
    }

    @Test
    public void isConstantTest(){
        assertFalse(Divi.isConstant());
    }

    @Test
    public void getNameTest(){
        assertEquals("/", Divi.getName());
    }

    @Test
    public void isCommandTest(){
        assertFalse(Divi.isCommand());
    }

    @Test
    public void getPriorityTest(){
        assertTrue(100 == Divi.getPriority());
    }

    @Test
    public void toStringTest(){
        assertEquals("5.0 / 2.0", Divi.toString());
    }

    @Test
    public void equalsTest(){
        assertTrue(Divi.equals(Divi2));
    }

    @Test
    public void evaluateTest(){
        assertEquals(c5, evaluator.evaluate(Divi, env));
    }
}