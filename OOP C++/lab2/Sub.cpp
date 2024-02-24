#include "Sub.h"
#include "FactoryInitializer.h"

void Sub::Execute(Operands& operands, Tokens& tokens, std::string& output, Reader& reader) {
    int operand1 = operands.GetAndPop();
    int operand2 = operands.GetAndPop();

    operands.Push(operand2 - operand1);

}

namespace {
    FactoryInitializer<Sub> Registration("-");
}