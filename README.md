#compiler homework

##hw1:

**1. use:**

- ./a.out (file name)

```
	input file: file name

	output file: "token.txt".
```

**2. compile:**

```
	gcc lexer.cpp
```

**3. environment:**

```
	ubuntu 14.04.2 LTS
```
**4. language:**

```
	c++
```

**5. file:**

- lexer.cpp:

```
	input a file, analyze this file, cut the string, classify those substring,

	and make a token list.
```

##hw2:

**1. use:**

- ./set

```
	input file: "grammar.txt"

	output file: "set.txt"
```

- ./lltable

```
	inpput file: "set.txt"

	output file: "lltable.txt"
```

**2. compile:**

```
	make -f Makefile
```

**3. environment:**

```
	ubuntu 14.04.2 LTS
```
**4. language:**

```
	c++
```

**5. file:**

- Data.h, Data.cpp:

```
	use to store data.
```

- set.cpp:

```
	use to make set.txt.

	function first to make first list

	function follow to make follow list
```

- lltable.cpp:

```
	use to make lltable.txt

	only one function.
```
