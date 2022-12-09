package org.ioopm.calculator.Test;

import org.junit.Test;
import org.ioopm.calculator.ast.*;
import org.ioopm.calculator.parser.*;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;

public class AssignmentTest {
    Constant c1 = new Constant(5);
    Constant c2 = new Constant(2);
    Constant c3 = new Constant(5);
    Constant c4 = new Constant(2);
    Constant c5 = new Constant(7);
    Variable v1 = new Variable("x");
    Assignment Ass = new Assignment(c3,v1);
    Assignment Ass2 = new Assignment(c3,v1);
    final EvaluationVisitor evaluator = new EvaluationVisitor();
    Environment env = new Environment();
    
    @Test (expected = RuntimeException.class)
    public void getValueTest(){
        Ass.getValue();
    }

    @Test
    public void isConstantTest(){
        assertFalse(Ass.isConstant());
    }

    @Test
    public void getNameTest(){
        assertEquals("x = 5.0", Ass.getName());
    }

    @Test
    public void isCommandTest(){
        assertFalse(Ass.isCommand());
    }

    @Test
    public void getPriorityTest(){
        assertTrue(10 == Ass.getPriority());
    }

    @Test
    public void toStringTest(){
        assertEquals("x = 5.0", Ass.toString());
    }

    @Test
    public void equalsTest(){
        assertEquals(Ass2, Ass);
    }

    @Test
    public void evaluateTest(){
        assertEquals(c3, evaluator.evaluate(Ass, env));
    }
}