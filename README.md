# Banking Management System (Turbo C++)

This is a C++ Project I had made using MS-DOS/Turbo C++ during my final year of High School. Turbo C++ is fairly dated, but it was still a lot of fun trying to make it look usable and interesting. Along with that, it actually makes use of quite a bit of binary and text file handling.

 The main code is in the BANK.cpp file. The reason everything is in .cpp file is because it was just easier to stick with one file when working with a 16-bit MS-DOS IDE. The .dat and .txt files store all the data for the project.

-----

This program is meant to simulate a Banking System for both the Customer and Bank Employees. The program works on a .dat binary file which stores the information about the customers, and a combination of a .dat and .txt file which stores transaction records.
 
Through the Server module, one can:
 - Create new records
 - Display all records, or display following a certain criteria.
 - Delete record
 - Update records
 - View All Transactions that have taken place in the bank.
 
Through the Customer module, one can:
 - View Details of the Customer
 - Withdraw or Deposit Money, and earn points for the same.
 - Redeem the Points for voucher codes.
 - View Transactions done by customer
 
Account Security: Each Customer has an Account No. as well as a PIN, through which they must login. The pin is randomly assigned at the point of Account Creation.

Reward Point System: The customer earns points by doing transactions (withdrawal/deposits). These points can be redeemed for Voucher Codes, which are randomly generated.

Transaction Ledger: Along with the .dat file, the program also stores all transactions in a .txt file which can be used and edited by the bank as needed.

---



