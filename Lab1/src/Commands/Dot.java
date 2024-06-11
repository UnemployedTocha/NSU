package Commands;

import Utility.Operands;

import java.util.StringTokenizer;

public class Dot implements Command{
    @Override
    public void Execute(StringTokenizer tokens, Operands operands) {
        int num = operands.GetAndPop();
        System.out.print(num + " ");
    }

    @Override
    public void Check(StringTokenizer tokens, Operands operands) {

    }

}
