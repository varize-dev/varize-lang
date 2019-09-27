# Introduction
Varize is a compilication-based programming language. The source file extension for it is ``.var`` and the bytecode extension is ``.val``
This file is a brief document of ``.val`` file format in ``Varize 1``.
# 0 Magic number (4 bytes)
Like ``.class`` file in Java, which use the bytes ``0xcafebabe`` as the fixed 4 bytes at the beginning of a ``.class`` file, we use the bytes of ``varl``, which is ``0x7661726c`` as our 'magic number'. 
# 1 Version (8 bytes)
We use a 8-byte ascii string as our version. This string will fill these 8 bytes
## 1.0 Version format
The first 4 bytes is the year of the release. The 5th byte is ``'w'``, which stand for ``week``. The 6th and 7th byte will be the week in that year. And the last byte will be a small letter, ranging from ``a`` to ``z``, representing the number of existing releases in that week. 
For example, if a release is the 2nd release in the 50th week of 2019, the version for it will be ``2019w50b``. 
# 2 ``.decl`` segment
## 2.0 ``.decl`` length (2 bytes) ($L)
These bytes will become an ``unsigned short`` in our code, representing the number of global variables in that ``.val`` file. 
## 2.1 ``.decl`` types ($L bytes)
I will call these bytes from ``d[0]`` to ``d[$L - 1]`` in this markdown file. Every single byte in this part will correspond an implementation info in the following ``.impl`` segment. There are currently 2 available options for ``d[i]``.
* ``'i'`` for assigning a primitive integer to this global variable when this ``.val`` file is loaded by the ``module loader`` in ``VVM``. The byte is ``0x69``.
* ``'f'`` for assigning a primitive function to this global variable when this ``.val`` file is loaded by the ``module loader`` in ``VVM``. The byte is ``0x66``.

# 3 ``.impl`` segment
This is the most expansive part in the entire ``.val`` file, for the implementations of functions will be stored here. 
## 3.0 ``.impl`` infos
I will call these infos from ``i[0]`` to ``i[k]`` in which ``k >= $L - 1``, so if a ``j`` satisfy the requirement ``j < $L``, ``i[j]`` will correspond ``d[j]``. 
### 3.0.0 When ``d[j]`` equals ``0x69`` (4 bytes)
The info ``i[j]`` will consume 4 bytesof file space storing that integer.
### 3.0.1 When ``d[j]`` equals ``0x66``
#### 3.0.1.0 Local variable count (2 bytes)
This ``unsigned short`` will decide how many bytes we will allocate when that function's stack frame is allocated.
#### 3.0.1.1 Parameter count (2 bytes)
This ``unsigned short`` will decide how many parameters we will read when that function's called.
#### 3.0.1.2 Instruction count (4 bytes) ($C[j])
This ``unsigned int`` will decide how many bytes the VM will read next as the function's instruction part when allocating the function object. 
#### 3.0.1.3 Instruction list
These will be a list of instructions with a size of ``$C[j]``, where instructions made of opcodes (1 byte) and optional oprands (4 bytes) comes side by side without a single bit of separation. 
# 4 Here we go
This is the full format of a ``Varize 1`` bytecode file. New opcodes and oprands will be added later on so I said ``Varize 1``. For example, ``d[m] = 'c'`` might come when classes and interfaces join the party in ``Varize 2``, and ``synchronize_obj`` and ``release_lock`` instruction will be given birth in the planning ``Multi-thread Update``, which might come in ``Varize 4``. The ``static`` block for module initialization will be on his/her way here with the ``.stat`` segment in ``Varize 3``. Nothing stays eternal and unchanging in this universe, including the potential base of future programming! 
Thanks for reading. 