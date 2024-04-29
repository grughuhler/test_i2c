test_i2c: test_i2c.c
	gcc -o test_i2c test_i2c.c -li2c

clean:
	rm -f test_i2c
