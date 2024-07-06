# DpdlTrainLLM

![Dpdl](https://www.dpdl.io/images/dpdl-io.png)

				www.dpdl.io

    
##  DpdlTrainLLM - a compact lightweight method for training and reproducing the GPT-2 model mini series

**Dpdl source code**:
[app/dpdltrainllmapp/](https://github.com/Dpdl-io/Dpdl-sample-Apps/tree/main/app/dpdltrainllmapp)

The app consists of the following Dpdl source:
[dpdlTrainLLM.h](https://github.com/Dpdl-io/Dpdl-sample-Apps/tree/main/app/dpdltrainllmapp/dpdlTrainLLM.h)

### Description


Performs LLM training in 40 steps to generate a GTP-2 model (124 Mb) from a data source that consists of 'tinystories' and 'tinyshakespeare' which are avaialbe as already tokenized datasets. 

The training is performed using the powerful and lightweight C library 'llm.c' (https://github.com/karpathy/llm.c).

More information about the steps implemented are described on this 'llm.c' [Discussion](https://github.com/karpathy/llm.c/discussions/481)

