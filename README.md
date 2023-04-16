# Overview

This is the source codes repo for learning the compiler course from PKU: [北大编译实践在线文档](https://pku-minic.github.io/online-doc/#/).

# Progress

- Lv1. main 函数 finished
  - at 2023-04-16, 20:00:55, By Jingchang Shi
  - What I learned for now
    - Docker basic usages, how to change the default registry to a mainland server.
    - The framework of a compiler: frontend, IR, backend
    - Lexer and parser. Here, the lexer is flex and the parser is [bison](https://www.gnu.org/software/bison/manual/html_node/index.html).
    - A naive example to lex and parse a `.c` file written in the SysY language to AST which is then converted to Koopa IR. For now, the Koopa IR is presented in the string format.
    - The current codes pass the `autotest -koopa` tests

