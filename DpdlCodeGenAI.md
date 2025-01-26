# DpdlCodeGenAI

![Dpdl](https://www.dpdl.io/images/dpdl-io.png)

				www.dpdl.io



## DpdlCodeGenAI - generating and executing AI generative code (example: console SNAKE Game)

This Dpdl example makes use of the **Dpdl language plugin** '<em>DpdlAINerd</em>' to <ins>**automatically generate**</ins> and execute AI generated code  starting from a natural language description contained inside the Dpdl code.

The auto generated application in this case is a simple version of the popular SNAKE Game, written in C and running in the console.

```python
println("testing 'DpdlAINerd' Dpdl language plugin to automatically generate and execute code...")

>>ai
	>>c
	write a console program in C that implements the famous SNAKE game, with colorful graphics using ncurses colors
<<
int exit_code = dpdl_exit_code()

raise(exit_code, "Error in generating code from natural language description")

println("exit code: " + exit_code)

println("finished")
```

When the Dpdl code is executed, the code is <ins>automatically generated</ins>, <ins>compiled</ins> at runtime and <ins>executed</ins>.

The AI engine used by 'DpdlAINerd' was in this case the 'DeepSeek' model (also OpenAI can be eventually configured)

**Screenshot** (simple console SNAKE Game):

<img src="https://www.dpdl.io/images/platform/examples/dpdlcodegenai/dpdlcodegenai_game_snake.png" width="65%" height="65%">

[VIDEO of generated Game app in action](https://youtu.be/82SRI_L3vLc)




 
