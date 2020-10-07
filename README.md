# Fault Detection Using LSTM Deep Learning Classification
This demo shows the full deep learning workflow for an example of signal data. We show how to prepare, model, and deploy a deep learning LSTM based classification algorithm to identify the condition or output of a mechanical air compressor.

![](Images/bearingsignal.png)
![](Images/confusionmat.png)

We show examples on how to perform the following parts of the Deep Learning workflow:

- Part1 - Data Preparation
- Part2 - Modeling
- Part3 - Deployment

![](Images/deeplearningworkflow.png)


This demo is implemented as a MATLAB project and will require you to open the project to run it. The project will manage all paths and shortcuts you need. There is also a significant data copy required the first time you run the project.

## Part 1 - Data Preparation ([View on Browser](./markdown_view/Part01_DataPreparation.md))

This example shows how to extract the set of acoustic features that will be used as inputs to the LSTM Deep Learning network.

To run:
1. Open MATLAB project Aircompressorclassification.prj
2. Open and run Part01_DataPreparation.mlx

## Part 2 - Modeling ([View on Browser](./markdown_view/Part02_Modeling.md))

This example shows how to train LSTM network to classify multiple modes of operation that include healthy and unhealthy signals.

To run:
1. Open MATLAB project Aircompressorclassification.prj
2. Open and run Part02_Modeling.mlx

## Part 3 - Deployment ([View on Browser](./markdown_view/Part03_Deployment.md))

This example shows how to generate optimized c++ code ready for deployment. 

To run:
1. Open MATLAB project Aircompressorclassification.prj
2. Open and run Part03_Deployment.mlx

Requires

- [MATLAB R2020b](https://www.mathworks.com/products/matlab.html)
- [Deep Learning Toolbox](https://www.mathworks.com/products/deep-learning.html)
- [Signal Processing Toolbox](https://www.mathworks.com/products/signal.html)
- [Audio Toolbox](https://www.mathworks.com/products/audio.html)
- [Parallel Computing Toolbox](https://www.mathworks.com/products/parallel-computing.html)
- [MATLAB Coder](https://www.mathworks.com/products/matlab-coder.html)
- [GPU Coder](https://www.mathworks.com/products/gpu-coder.html)

**[Download a free MATLAB trial for Deep Learning](https://www.mathworks.com/products/deep-learning.html)**

[![View Fault Detection Using Deep Learning Classification on File Exchange](https://www.mathworks.com/matlabcentral/images/matlab-file-exchange.svg)](https://www.mathworks.com/matlabcentral/fileexchange/74611-fault-detection-using-deep-learning-classification)

There is also a significant data download required the first time you run the project, which is licensed by Nishchal K. Verma, R. K. Sevakula, S. Dixit and A. Salour and subject to the license terms found in AirCompressorDataset.rights.

Copyright 2020 The MathWorks, Inc.