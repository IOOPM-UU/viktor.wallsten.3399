package org.ioopm.calculator.Test;

import org.junit.Test;
import org.ioopm.calculator.ast.*;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;

public class ExpTest {
    final EvaluationVisitor evaluator = new EvaluationVisitor();
    Environment env = new Environment();
    Constant con = new Constant(5);
    Exp exp = new Exp(con);

    @Test (expected = RuntimeException.class)
    public void getValueTest(){
        assertTrue(5 == exp.getValue());
    }

    @Test
    public void isConstantTest(){
        assertFalse(exp.isConstant());
    }

    @Test
    public void getNameTest(){
        assertEquals("^", exp.getName());
    }

    @Test
    public void isCommandTest(){
        assertFalse(exp.isCommand());
    }

    @Test
    public void getPriorityTest(){
        assertTrue(150 == exp.getPriority());
    }

    @Test
    public void toStringTest(){
        assertEquals("^ 5.0", exp.toString());
    }

    @Test
    public void equalsTest(){
        Exp exp2 = new Exp(con);
        assertTrue(exp2.equals(exp));
    }

    @Test
    public void evaluateTest(){
        assertEquals(new Constant(Math.exp(5)), evaluator.evaluate(exp, env));
    }


}