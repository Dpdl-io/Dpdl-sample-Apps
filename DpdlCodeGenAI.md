# DpdlCodeGenAI

![Dpdl](https://www.dpdl.io/images/dpdl-io.png)

				www.dpdl.io



## DpdlCodeGenAI - generating and executing AI generative code (example: a simple console SNAKE Game)

This Dpdl example makes use of the **Dpdl language plugin** '[DpdlAINerd (DAN)](https://github.com/Dpdl-io/DpdlEngine/blob/main/doc/DpdlAINerd.md)' to <ins>**automatically generate**</ins> and execute AI generated code  starting from a natural language description contained inside the Dpdl code.

The auto generated application in this case is a simple version of the popular <ins>**SNAKE Game**</ins>, written in C and running in the console.

When the Dpdl code is executed, the C code is <ins>automatically generated</ins>, <ins>compiled</ins> in memory at runtime and <ins>executed</ins> right away.

Dpdl provides also the possibility to rewrite the code to a newly generated file so that it can be executed subsequently (see '@gen' parameter when executing the code) 

**Dpdl code:**

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

The AI engine used by 'DpdlAINerd' was in this case the '[DeepSeek](https://www.deepseek.com)' model, but also OpenAI is supported and can be eventually configured.

**'DpdlAINerd' config:**

```
[DpdlAINerd]
DAN_ENGINE=deepseek
DAN_API_KEY=your_api_key_here
DAN_AI_MODEL=deepseek-chat
```

**Screenshot** (simple console SNAKE Game):

<img src="https://www.dpdl.io/images/platform/examples/dpdlcodegenai/dpdlcodegenai_game_snake.png" width="65%" height="65%">

The snake direction can be controlled via the arrow keys and grows in size each time the 'F' (food) is eaten







 
