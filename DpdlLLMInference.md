# DpdlLLMInference

![Dpdl](https://www.dpdl.io/images/dpdl-io.png)

				www.dpdl.io



## DpdlLLMInference - Dpdl sample console app that performs inference on Llama-2 LLM models via embedded C code


Dpdl sample console application that allows to input a prompt about a story to be written, it will than generate by inference
on a LLM model a simple story based on the content provided in the input prompt.

Also different models can be interfered with this code, provided they are Llama-2 LLM models with fp32 sampling.
The Dpdl code makes use of embedded C code 'llama2.c' to perform the actual inference (https://github.com/karpathy/llama2.c)
The model used in this example is 'TinyStories': https://huggingface.co/datasets/roneneldan/TinyStories

**Dpdl source code:**
[app/dpdlLLMInference/dpdlLLMInfer.h]((https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/app/dpdlLLMInference/dpdlLLMInfer.h)
