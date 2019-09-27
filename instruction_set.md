# Here is a full list for all supported instruction in the current version:
## 0x00 nop (0 byte oprand) literally do nothing
## 0x01 pop (0 byte oprand) remove the top of the current op-stack
## 0x02 loadl (2 byte oprand - short ``num``) access local variable number ``num`` and push it to the top of the op-stack
## 0x03 storel (2 byte oprand - short ``num``) remove the top of the op-stack and change the local variable ``num`` into it
## 0x04 loadg (2 byte oprand - short ``num``) access global variable number ``num`` and push it to the top of the op-stack
## 0x05 storeg (2 byte oprand - short ``num``) remove the top of the op-stack and change the global variable ``num`` into it
## 0x06 local_function (2 byte oprand - short ``num``) access the function stored in the item ``num`` in the ``.impl`` segment
## 0x07 add (0 byte oprand) pop the top 2 items of the op-stack, add'em together and push the result back
## 0x08 sub (0 byte oprand) pop the top item ``i``, and pop the following top item ``j``, and push ``j - i`` back
## 0x09 mul (0 byte oprand) pop the top 2 items of the op-stack, multiply'em together and push the result back
## 0x0a div (0 byte oprand) pop the top item ``i``, and pop the following top item ``j``, and push ``j / i`` back (notice that the result is an integer, like C convention ``3 / 2 = 1`` rather than ``3 / 2 = 1.49999999999`` in Python)
## 0x0b and (0 byte oprand) pop the top 2 items of the op-stack, bitwise-and'em together and push the result back
## 0x0c or (0 byte oprand) pop the top 2 items of the op-stack, bitwise-or'em together and push the result back
## 0x0d xor (0 byte oprand) pop the top 2 items of the op-stack, bitwise-exclusive-or'em together and push the result back
## 0x0e not (0 byte oprand) pop the top item of the op-stack, bitwise-not it and push the result back
## 0x0f mod (0 byte oprand) pop the top item ``i``, and pop the following top item ``j``, and push ``j mod i`` back
## 0x10 call (0 byte oprand) pop the function object fron the top from the op-stack, read the amount of parameters for it and pop the parameters out of the stack(the first to pop = the last parameter)
## 0x11 push (4 byte oprand - int ``i``) push ``i`` into the stack
## 0x12 jump (4 byte oprand - int ``off``) jump back to the instruction at the offset ``off`` if the stack top is a non-0 integer, do nothing otherwise(consume the stack top)
## 0x13 cmpl pop the top item ``i``, and pop the following top item ``j``, and push ``1`` back if ``j < i``, ``0`` otherwise
## 0x14 cmpg pop the top item ``i``, and pop the following top item ``j``, and push ``1`` back if ``j > i``, ``0`` otherwise
## 0x15 cmple pop the top item ``i``, and pop the following top item ``j``, and push ``1`` back if ``j <= i``, ``0`` otherwise
## 0x16 cmpge pop the top item ``i``, and pop the following top item ``j``, and push ``1`` back if ``j >= i``, ``0`` otherwise
## 0x17 cmpeq pop the top item ``i``, and pop the following top item ``j``, and push ``1`` back if ``j == i``, ``0`` otherwise
## 0x18 cmpneq pop the top item ``i``, and pop the following top item ``j``, and push ``1`` back if ``j != i``, ``0`` otherwise