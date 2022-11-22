package org.ioopm.calculator.parser;


import org.ioopm.calculator.ast.*;


public class test {

    public static void testPrinting(String expected, SymbolicExpression e) {
        if (expected.equals("" + e)) {
            System.out.println("Passed printing: " + e);
        } else {
            System.out.println("Error: expected '" + expected + "' but got '" + e + "'");
        }
    }

    public static void testEvaluating(SymbolicExpression expected, SymbolicExpression e) {
        Environment vars = new Environment();
        SymbolicExpression r = e.eval(vars);
        if (r.equals(expected)) {
            System.out.println("Passed: " + r);
        } else {
            System.out.println("Error: expected '" + expected + "' but got '" + r + "'");
        }
    }

    public static void main(String[] args) {
        Constant c1 = new Constant(5);
        Constant c2 = new Constant(2);
        Variable v = new Variable("x");
        Addition a = new Addition(c1, v);
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
        

        testPrinting("(5.0 + x) * (5.0 + x)", m);
        testPrinting("sin 1.0", s);
        testPrinting("(5.0 + x) / (5.0 + x) * (5.0 + x)", d);
        testEvaluating(facit, test);
        testEvaluating(zero, s);
        testEvaluating(a, a);
        testEvaluating(i, b);
        testEvaluating(e, f);
        testEvaluating(s, c);
        testEvaluating(thirteen, add);
        testEvaluating(a, ass1);
        testEvaluating(new Constant(5.141592653589793), n);
        testEvaluating(p, l);
        testEvaluating(p, div);
        testEvaluating(x, y);
        testEvaluating(y, x);
        System.out.println("x = " + x.hashCode() + "\ny = " + y.hashCode());
    }
}
