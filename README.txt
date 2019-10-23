Compilation and Execution:
==========================
Please refer to S1_Simulator_User_Guide.docx for compilation and execution steps.

Compiler version:
=================
This version of the S1SIM software was verifed on GCC version: 4.4.7


Execution of testcase:
======================
1. List of test scenario commands can be viewed by using the below command.

   testCntrlr -h

2. Non-UE related test cases (S1 SETUP, eNB Config etc) can be excuted in below format:

   testCntrlr <test_case_keyword>

   Example 1:
      testCntrlr S1SetupSucc

3. UE related test cases (Attach, Detach, TAU etc) can be excuted in below format:
   
   testCntrlr <test_case_keyword> <no_of_UEs>

   Example 1: to test end to end attach with 1 UE

      ./testCntrlr EndToEndAttach 1

   Example 2: to step by step attach with 5 UEs

      ./testCntrlr StepAttachWithImsi 5

4. A series of test commands can be executed together by writting the command
into a single file. The syntax for executing the test case file is below;

   testCntrlr –f <file_name>

   Example 1:

      ./testCntrlr –f testCaseList_1.txt

Note: Few sample test cases are placed in S1SIM/TestCntlrStub/bin folder, where
the final binary will get generated.

- testCaseList_2 - using which 1 UE attach, detach and service request,
                    tracking area update can be verified.


