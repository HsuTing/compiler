#Compiler homework

##HW1

**Use**

> ./a.out (file name)

```
	input file: file name

	output file: "token.txt".
```

**Compile**

```
	gcc lexer.cpp
```

**Environment**

```
	ubuntu 14.04.2 LTS
```
**Language**

```
	c++
```

**File**

> lexer.cpp:

```
	input a file, analyze this file, cut the string, classify those substring,
	and make a token list.
```

##HW2:

**Use**

> ./set

```
	input file: "grammar.txt"

	output file: "set.txt"
```

> ./lltable

```
	inpput file: "set.txt"

	output file: "lltable.txt"
```

**Compile**

```
	make -f Makefile
```

**Environment**

```
	ubuntu 14.04.2 LTS
```
**Language**

```
	c++
```

**File**

> Data.h, Data.cpp:

```
	use to store data.
```

> set.cpp:

```
	use to make set.txt.
	function first to make first list
	function follow to make follow list
```

> lltable.cpp:

```
	use to make lltable.txt
	only one function.
```
