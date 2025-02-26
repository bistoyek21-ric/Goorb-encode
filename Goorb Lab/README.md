# Goorb Lab
# Created by: 21
## Part of [Goorb-encode](https://github.com/bistoyek-official/Goorb-encode) research project
## Author: Kasra Fouladi

Here is **Goorb Lab** source code, an open source simple cryptography lab\
built with the aim of making it easier to examine the security of various\
encryptions and the effectiveness of various attacks. This attack simulator\
can help people to test their encryption algorithms or their attack algorithms\
much easier.

**Disclaimer:** This project developed by **bistoyek R.I.C.** is intended solely for educational\
and research purposes. It should not be used for any malicious or illegal activities. Goorb Lab\
and its author are not responsible for any misuse of the information provided or any consequences\
resulting from its application

***
## Logic

### Oracle and Queries
Imagine there is no clue about cryptography but it is guaranteed that the key(s)\
of it won’t change in all of the attack time (clearly now it’s an easier problem),\
attacker has limited amount of supply and there is an oracle that could answer these\
queries:
- For $a$ such $a \in A$ what is $F(a)$. (costs $x$)
- For $b$ that $b \in B$ return $a$ random $a \in A$ which $F(a) = b$. (costs $y$)

### Processing and Queries
Attackers job is can splited into two main parts, strategy in sending queries and\
strategy in processing the data achieved from queries.

### Final test
After doing all queries and running out of supply, attacker have to decrypt 10000 randomly chosen\
cipher-blocks and it's accuracy is equal to $\frac{true guesses}/10000$, after each attack results\
will store in a csv file in a (k + 1)x4 grid while k is number of attemps, and in ${i+1}^{th}$ row\
$i^{th}$ attacks parameters stored in this format: supply, x, y, accuracy\
(first row value is equal to [supply, x, y, accuracy] to make it easier to work with the data)

***
## License
This project is licensed under the MIT License.\
The paper of the main project is published under following DOI and License:
- DOI: 10.13140/RG.2.2.35836.45444
- License: CC BY-SA 4.0
***
**All material and intellectual rights of this environment belong to [@kasrafouladi](https://github.com/kasrafouladi) and [@bistoyek-official](https://github.com/bistoyek-official), and any plagiarism is prosecuted.**
***
#### In case of any question here are emails you can send email to them:
- k04sr405@gmail.com
- 21bistoyek21bistoyek@gmail.com
