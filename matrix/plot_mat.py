import matplotlib.pyplot as plt

x = []
op=[]
meth=[]

with open(r"D:\github\prog_cpp\complex\toto.txt") as f:
    for line in f:
        sp = line.split()
        x.append(float(sp[0]))
        op.append(float(sp[1]))
        meth.append(float(sp[2]))

plt.plot(x, op, label="op")
plt.plot(x, meth, label="method")
plt.legend()
plt.show()
