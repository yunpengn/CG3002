# CG3002 AY1819 Sem1 *Dance Dance Team 09* :dancer:

This is the main repository for CG3002 project at the [National University of Singapore](http://www.nus.edu.sg) (AY2018/2019 Semester 1). CG3002 is the capstone module for the [Computer Engineering](http://ceg.nus.edu.sg) programme.

## Project Description

This project detects labelled dance moves performed by user. \
\
Accomplished with the use of:
1. Arduino: Obtain values from sensor and output to Raspberry Pi
2. Raspberry Pi: Load sensor values to Machine Learning model, send prediction to server
3. Machine Learning: Process raw data from sensor and output prediction

For more instructions on the software component, please see [here](software/README.md).

## How to use this project

- Make sure you have installed the relevant dependencies for each component of this system;
- First, put all data under `software/data/raw`;
	- You can download the dataset as a zip file from [here](https://drive.google.com/open?id=1osUyvorB94xz8Rma6hx3GpQum_hr1IFo). Unzip and put it under `software/data/raw`.
- Then, run `software/extract_raw.py` to extract features into `software/data/extract`;
	- Alternatively, you can download the extracted data as a zip file from [here](https://drive.google.com/open?id=1fIpLsw4CV4nv4n2KedFKPrSUbFYGdreF). Unzip and put it under `software/data/extract`.
- After that, run `software/train.py` to train the model (which will be stored under the `software/model` folder);
	- Alternatively, you can download the pre-trained model from [here](https://drive.google.com/open?id=1EzMIIPOIJJuPz4Yjbe7iztnOoPRHoR6M). Put it under `software/model`.
- During demo, do the following:
	- Run `ArduinoRpiCommunications` to start sending data from Arduino to the Raspberry Pi;
	- Run the following two programs at the same time:
		- `python software/main.py`
		- `python comms/server-client/final_eval_server.py [IP address] 3002 09`

## Team Members

| Name | Sub-team |
| :---: | :---: |
| Leow Zheng Yu | Hardware |
| Xiang Hailin | Hardware |
| Gauri Joshi | Software |
| Niu Yunpeng | Software |
| Chua Kun Hong | Communications |
| Ang Zhi Yuan | Communications |
