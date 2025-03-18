#!/bin/bash
###
 # @Author: wangyt32023@shanghaitech.edu.cn
 # @Date: 2025-03-16
 # @LastEditors: wangyt32023@shanghaitech.edu.cn
 # @LastEditTime: 2025-03-16
 # @FilePath: \lab5\lab6_starter\test.sh
 # @Description: 
 # Copyright (c) 2025 by CAS4ET lab, ShanghaiTech University, All Rights Reserved. 
### 

# Just run this file and you can test your circ files!
# Make sure your files are in the directory above this one though!

cp ex3.circ ex4.circ ex5.circ ./testing/circ_files

cd testing
rm -rf student_output
mkdir student_output
python3 test.py
cd ..
