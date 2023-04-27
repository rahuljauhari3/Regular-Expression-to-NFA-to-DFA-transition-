# Regular-Expression-to-NFA-to-DFA-transition-
This file takes regular expression and string as input and convert RE into equivalent NFA and NFA into equivalent DFA. Then substring is taken and compared to DFA whether it is accepted by that DFA or not.

**Example:**
1. RE ```((a)|(((a)|((b)(a)))*))```  \\ a | (a | ba)*

   string: ```abbbbabababb```

   output: ```$a@b@b@b$bababa@b@b#```

   

   

2. RE ```(((((b)*)(a))*)((a)*))```  \\ (b*a)*a*

   string:``` baabaaaabbaab```

   output: ```$baabaaaabbaa@b#```    

   

3. RE ```((((b)|((a)(b)))*)|((((b)|((a)(b)))*)(a)))```  \\ (b | ab)* | (b |ab)*a

   string: ```abbaabbaaabba```

   output: ```$abba$abba$a$abba#```

   

4.  ```((((((b)*)(a))((b)*))(a))((b)*))```        \\b*ab*ab*

    string: ```baaabbaabab```

    output: ```$baa$abba$abab#```





5.``` (((((a)|(b))*)(((b)(a))(b)))(((a)|(b))*))```         \\(a|b)*bab(a|b)*

   string: ```bbaabaabaa```

   output: ```@b@b@a@a@b@a@a@b@a@a#```





6.``` (((((a)|(b))*)((b)(a)))|((a)|(b)))```         \\((a|b)*ba)|(a|b)

    string: ```baababaab```

    output: ```$baababa$a$b#```
