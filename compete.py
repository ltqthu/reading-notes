import random
import matplotlib.pyplot as plt


def complete(a, b):
    count = 0
    while True:
        rnd = random.randint(0, 1)
        if rnd == 0:
            a -= 1
            b += 1
        else:
            a += 1
            b -= 1
        count += 1
        if a == 0:
            return 1, count
        if b == 0:
            return 0, count

def complete_statistic(a, b, n):
    a_win = []
    b_win = []
    for i in range(n):
        winner, count = complete(a, b)
        if winner == 1:
            b_win.append(count)
        else:
            a_win.append(count)
    return a_win, b_win



if __name__ == "__main__":
    a = 10
    b = 100
    a_win, b_win = complete_statistic(a, b, 100)
    plt.figure()
    plt.hist(a_win, 20)
    plt.xlabel("times")
    plt.show()
    plt.figure()
    plt.hist(b_win, 20)
    plt.xlabel("times")
    plt.show()
