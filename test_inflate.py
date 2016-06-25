# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_inflate.py                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbyttner <jbyttner@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/25 12:14:20 by jbyttner          #+#    #+#              #
#    Updated: 2016/06/25 19:44:12 by jbyttner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from subprocess import run
from random import sample, randrange

def call2(code, *params):
	run([code] + list(params), shell = True)

call2("ls", "-l", '/');

s = bytes(sample(range(32,127), randrange(80)))

with open("test/tmp.txt", "wb") as f:
	f.write(s);
	#print(s);



print(call2("test/a.out test/tmp.txt"))

print(call2("./a.out tmp.compressed"));

with open("TESTOUT", "rb") as f:
	a = f.read()
	print("Status is ", bool(a == s));
	print(a)
	print(s);
#print (s);
