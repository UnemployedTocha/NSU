package Commands;

import Utility.Operands;

import java.util.StringTokenizer;

public interface Command {
    void Execute(StringTokenizer tokens, Operands operands);
    void Check(StringTokenizer tokens, Operands operands);
}
