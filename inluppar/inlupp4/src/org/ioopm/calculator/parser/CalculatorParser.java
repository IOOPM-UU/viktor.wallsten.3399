package org.ioopm.calculator.parser;

import org.ioopm.calculator.ast.*;

import java.io.StreamTokenizer;
import java.io.StringReader;
import java.sql.SQLSyntaxErrorException;
import java.io.IOException;

import java.util.*;

/**
 * Represents the parsing of strings into valid expressions defined in the AST.
 */
public class CalculatorParser {
    private StreamTokenizer st;
    private Environment vars;
    private static char MULTIPLY = '*';
    private static char ADDITION = '+';
    private static char SUBTRACTION = '-';
    private static char DIVISION = '/';
    private static String NEG = "Neg";
    private static char NEGATION = '-';
    private static String SIN = "Sin";
    private static String COS = "Cos";
    private static String LOG = "Log";
    private static String EXP = "Exp";
    private static String IF = "if";
    private static char ASSIGNMENT = '=';
    private static String GREATERTHANEQUALS = ">=";
    private static String LESSTHANEQUALS = "<=";
    private static char GREATERTHAN = '>';
    private static char LESSTHAN = '<';
    private static String EQ = "==";
    private static String FUNCTION = "function";
    public Boolean funcMode = false;
    public HashMap<String, FunctionDeclaration> functions = new HashMap<>(); 

    // unallowerdVars is used to check if variabel name that we
    // want to assign new meaning to is a valid name eg 3 = Quit
    // or 10 + x = L is not allowed
    private final ArrayList < String > unallowedVars = new ArrayList < String > (Arrays.asList("Quit",
        "Vars",
        "Sin",
        "Cos",
        "Exp",
        "Log",
        "Clear",
        "if",
        "else",
        "function"));

    /**
     * Used to parse the inputted string by the Calculator program
     * @param inputString the string used to parse
     * @param vars the Environment in which the variables exist
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     */
    public SymbolicExpression parse(String inputString, Environment vars) throws IOException {
        this.st = new StreamTokenizer(new StringReader(inputString)); // reads from inputString via stringreader.
        this.vars = vars;
        this.st.ordinaryChar('-');
        this.st.ordinaryChar('/');
        this.st.eolIsSignificant(true);
        SymbolicExpression result = statement(); // calls to statement
        return result; // the final result
    }

    /**
     * Checks wether the token read is a command or an assignment
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a valid expression
     */
    private SymbolicExpression statement() throws IOException {
        SymbolicExpression result;
        this.st.nextToken(); //kollar pÃ¥ nÃ¤sta token som ligger pÃ¥ strÃ¶mmen
        if (this.st.ttype == this.st.TT_EOF) {
            throw new SyntaxErrorException("Error: Expected an expression");
        }

        if (this.st.ttype == this.st.TT_WORD) { // vilken typ det senaste tecken vi lÃ¤ste in hade.
            if (this.st.sval.equals("Quit") || this.st.sval.equals("Vars") || this.st.sval.equals("Clear")) { // sval = string Variable
                result = command();
            } else {
                result = assignment(); // gÃ¥r vidare med uttrycket.
            }
        } else {
            result = assignment(); // om inte == word, gÃ¥ till assignment Ã¤ndÃ¥ (kan vara tt_number)
        }

        if (this.st.nextToken() != this.st.TT_EOF) { // token should be an end of stream token if we are done
            if (this.st.ttype == this.st.TT_WORD) {
                throw new SyntaxErrorException("Error: Unexpected '" + this.st.sval + "'");
            } else {
                throw new SyntaxErrorException("Error: Unexpected '" + String.valueOf((char) this.st.ttype) + "'");
            }
        }
        return result;
    }


    /**
     * Checks what kind of command that should be returned
     * @return an instance of Quit, Clear or Vars depending on the token parsed
     * @throws IOException by nextToken() if it reads invalid input
     */
    private SymbolicExpression command() throws IOException {
        if (this.st.sval.equals("Quit")) {
            return Quit.instance();
        } else if (this.st.sval.equals("Clear")) {
            return Clear.instance();
        } else {
            return Vars.instance();
        }
    }


    /**
     * Checks wether the token read is an assignment between 2 expression and 
     * descend into the right hand side of '='
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a valid expression,
     *         the variable on rhs of '=' is a number or invalid variable
     */
    private SymbolicExpression assignment() throws IOException {
        SymbolicExpression result = expression();
        this.st.nextToken();
        while (this.st.ttype == ASSIGNMENT) {
            this.st.nextToken();
            if (this.st.ttype == this.st.TT_NUMBER) {
                throw new SyntaxErrorException("Error: Numbers cannot be used as a variable name");
            } else if (this.st.ttype != this.st.TT_WORD && this.st.ttype != '=') {
                throw new SyntaxErrorException("Error: Not a valid assignment of a variable"); //this handles faulty inputs after the equal sign eg. 1 = (x etc
            } else if (this.st.ttype == '=') {
                this.st.nextToken();
                result = new Eq(result, term());
            }else {
                if (this.st.sval.equals("ans")) {
                    throw new SyntaxErrorException("Error: ans cannot be redefined");
                }
                SymbolicExpression key = identifier();
                result = new Assignment(result, key);
            }
            this.st.nextToken();
        }
        this.st.pushBack();
        return result;
    }

    /**
     * Check if valid identifier for variable and return that if so
     * @return a SymbolicExpression that is either a named constant or a new variable
     * @throws IOException by nextToken() if it reads invalid input
     * @throws IllegalExpressionException if you try to redefine a string that isn't allowed
     */
    private SymbolicExpression identifier() throws IOException {
        SymbolicExpression result;

        if (this.unallowedVars.contains(this.st.sval)) {
            throw new IllegalExpressionException("Error: cannot redefine " + this.st.sval);
        }

        if (Constants.namedConstants.containsKey(this.st.sval)) {
            result = new NamedConstant(st.sval, Constants.namedConstants.get(st.sval));
        } else {
            result = new Variable(this.st.sval);
        }
        return result;
    }


    /**
     * Checks wether the token read is an addition or subtraction
     * and then continue on with the right hand side of operator
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     */
    private SymbolicExpression expression() throws IOException {
        SymbolicExpression result = term();
        this.st.nextToken(); // || this.st.ttype == ASSIGNMENT
        while (this.st.ttype == ADDITION || this.st.ttype == SUBTRACTION || this.st.ttype == GREATERTHAN || this.st.ttype == LESSTHAN) {
            int operation = st.ttype;
            this.st.nextToken();
            if (operation == ADDITION) {
                result = new Addition(result, term());
            } else  if (operation == SUBTRACTION){
                result = new Subtraction(result, term());
            } else if(operation == GREATERTHAN){
                operation = this.st.ttype;
                this.st.pushBack();
                this.st.nextToken();
                if(this.st.ttype == ASSIGNMENT){
                    this.st.nextToken();
                    result = new GreaterthanEquals(result, term());
                }
                else{
                    result = new Greaterthan(result, term());
                }
            } else if(operation == LESSTHAN){
                operation = this.st.ttype;
                this.st.pushBack();
                this.st.nextToken();
                if(this.st.ttype == ASSIGNMENT){
                    this.st.nextToken();
                    result = new Lessthanequals(result, term());
                }
                else{
                    result = new Lessthan(result, term());
                }
            }else{
                result = new Eq(result, term());
            }
            this.st.nextToken();
        }
        this.st.pushBack();
        return result;
    }

    /**
     * Checks wether the token read is an Multiplication or
     * Division and then continue on with the right hand side of
     * operator
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     */
    private SymbolicExpression term() throws IOException {
        SymbolicExpression result = primary();
        this.st.nextToken();
        while (this.st.ttype == MULTIPLY || this.st.ttype == DIVISION) {
            int operation = st.ttype;
            this.st.nextToken();

            if (operation == MULTIPLY) {
                result = new Multiplication(result, primary());
            } else {
                result = new Division(result, primary());
            }
            this.st.nextToken();
        }
        this.st.pushBack();
        return result;
    }

    /**
     * Checks wether the token read is a parantheses and then
     * continue on with the expression inside of it or if the
     * operation is an unary operation and then continue on with
     * the right hand side of that operator else if it's a
     * number/identifier
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a valid expression,
     *         missing right parantheses
     */
    private SymbolicExpression primary() throws IOException {
        SymbolicExpression result;
        if (this.st.ttype == '(') {
            this.st.nextToken();
            result = assignment();
            /// This captures unbalanced parentheses!
            if (this.st.nextToken() != ')') {
                throw new SyntaxErrorException("expected ')'");
            }
        }
        else if(this.st.ttype == '{'){
            this.st.nextToken();
            result = assignment();
            result = new Scope(result);
            if(this.st.nextToken() != '}'){
                throw new SyntaxErrorException("expected '}'");
            }
        } else if (this.st.ttype == NEGATION) {
            result = unary();
        } else if(functions.containsKey(this.st.sval)){
            result = functionCall();
        
        }
        else if (this.st.ttype == this.st.TT_WORD) {
            if (st.sval.equals(SIN) ||
                st.sval.equals(COS) ||
                st.sval.equals(EXP) ||
                st.sval.equals(NEG) ||
                st.sval.equals(IF) ||
                st.sval.equals(LOG)) {
                result = unary();
            } else if (st.sval.equals(FUNCTION)){
                result = functionMode();
            } 
            else{
                result = identifier();
            }
        } else {
            this.st.pushBack();
            result = number();
        }
        return result;
    }

    /**
     * Checks what type of Unary operation the token read is and
     * then continues with the expression that the operator holds
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     */
    private SymbolicExpression unary() throws IOException {
        SymbolicExpression result;
        int operationNeg = st.ttype;
        String operation = st.sval;
        this.st.nextToken();
        if (operationNeg == NEGATION || operation.equals(NEG)) {
            result = new Negation(primary());
        } else if (operation.equals(SIN)) {
            result = new Sin(primary());
        } else if (operation.equals(COS)) {
            result = new Cos(primary());
        } else if (operation.equals(LOG)) {
            result = new Log(primary());
        } else if(operation.equals(EXP)) {
            result = new Exp(primary());
        }
        else{
            //this.st.nextToken();
            SymbolicExpression arg = assignment();
            this.st.nextToken();
            SymbolicExpression s1 = primary();
            this.st.nextToken();
            if(!this.st.sval.equals("else")){
                throw new SyntaxErrorException("Must be else");
            }
            this.st.nextToken();
            SymbolicExpression s2 = primary();
            result = new Conditonal(arg,s1,s2);
        }
        return result;
    }

    /**
     * Checks if the token read is a number - should always be a number in this method
     * @return a SymbolicExpression to be evaluated
     * @throws IOException by nextToken() if it reads invalid input
     * @throws SyntaxErrorException if the token parsed cannot be turned into a valid expression,
     *         expected a number which is not present
     */
    private SymbolicExpression number() throws IOException {
        this.st.nextToken();
        if (this.st.ttype == this.st.TT_NUMBER) {
            return new Constant(this.st.nval);
        } else {
            throw new SyntaxErrorException("Error: Expected number");
        }
    }

    private SymbolicExpression functionMode() throws IOException{
        String name;
        ArrayList<Variable> parameters = new ArrayList<>();
        this.st.nextToken();
        if (this.st.ttype == this.st.TT_WORD){
            name = this.st.sval;
        }
            else{
            throw new SyntaxErrorException("Expected name");
        }
        this.st.nextToken();
        if (!(this.st.ttype == '(')){
            throw new SyntaxErrorException("Expected '('");
        }
        while (true) {
            this.st.nextToken();
            if (this.st.ttype == this.st.TT_WORD){
                Variable temp = new Variable(this.st.sval);
                if (parameters.contains(temp)){
                 throw new SyntaxErrorException("Parameter aldready used");
                }
                parameters.add(temp);
            }
            else if (this.st.ttype == ')'){
                break;
            }else if (!(this.st.ttype == ',')){
                throw new SyntaxErrorException("Wrong syntax1");
            }
        }
        this.funcMode = true;
        FunctionDeclaration tempfunc = new FunctionDeclaration(name, parameters, new Sequence()); 
        this.functions.put(name, tempfunc);
        // return new FunctionDeclaration(name, parameters, new Sequence());
        return tempfunc;
    }

    private SymbolicExpression functionCall() throws IOException{
        String name = this.st.sval;
        ArrayList<SymbolicExpression> argumnets = new ArrayList<>();
        this.st.nextToken();
        if (!(this.st.ttype == '(')){
            throw new SyntaxErrorException("Expected '('");
        }
        while (true) {
            this.st.nextToken();
            if (this.st.ttype == this.st.TT_NUMBER){
                SymbolicExpression temp = new Constant(this.st.nval);
                argumnets.add(temp);
            }
            else if (this.st.ttype == this.st.TT_WORD){
                SymbolicExpression temp = new Variable(this.st.sval);
                argumnets.add(temp);
            }
            else if (this.st.ttype == ')'){
                break;
            }else if (!(this.st.ttype == ',')){
                throw new SyntaxErrorException("Wrong syntax2");
            }
        }

        if (argumnets.size() != this.functions.get(name).parameters.size()){
            throw new SyntaxErrorException("Mismatch with number of argumnets");
        }

        return new Scope(new FunctionCall(name, argumnets, this.functions.get(name)));
    }

}