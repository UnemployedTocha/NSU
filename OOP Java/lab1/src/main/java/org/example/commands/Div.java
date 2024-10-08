package org.example.commands;

import org.example.utility.Operands;

import java.util.StringTokenizer;

public class Div implements Command{
    @Override
    public void Execute(StringTokenizer tokens, Operands operands) {
        int num1 = operands.GetAndPop();
        int num2 = operands.GetAndPop();
        operands.Push(num2 / num1);
    }

    @Override
    public void Check(StringTokenizer tokens, Operands operands) {

    }

}
